<?php

namespace Tests\Feature;

use App\Http\Controllers\DesktopHelperController;
use App\Http\Event\Bsi020010Event;
use App\Util\DesktopHelper;
use Carbon\Carbon;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Schema;
use Symfony\Component\HttpKernel\Exception\HttpException;
use Tests\TestCase;

//2026.11.17 by codex, exercise notifications using only an isolated in-memory database and session handler.
class DesktopHelperTest extends TestCase
{
  protected function setUp(): void
  {
    parent::setUp();
    config([
      'database.default' => 'companion_test',
      'database.connections' => [
        'companion_test' => ['driver' => 'sqlite', 'database' => ':memory:', 'prefix' => ''],
        'system_pointer' => ['driver' => 'sqlite', 'database' => 'companion_test', 'sysdb' => true],
      ],
      'cache.default' => 'array',
      'session.driver' => 'array',
      'session.encrypt' => false,
      'app.timezone' => 'Asia/Taipei',
      'services.oacs.host' => 'http://oacs.invalid',
    ]);
    //2026.11.17 by codex, keep every broadcast test isolated from real OACS and network services.
    Http::preventStrayRequests();
    Http::fake(['http://oacs.invalid/internal/notify' => Http::response(['ok' => true], 200)]);
    DB::purge('companion_test');
    $schema = Schema::connection('companion_test');
    $schema->create('oa_menutable', function (Blueprint $table) {
      foreach (['menuid', 'caption', 'stop_yn', 'master_table', 'def_filter', 'user_filter', 'group_filter'] as $field) $table->string($field)->nullable();
    });
    $schema->create('oa_usermenus', function (Blueprint $table) { $table->string('userid'); $table->string('menuid'); });
    $schema->create('oa_groupmenus', function (Blueprint $table) { $table->string('groupid'); $table->string('menuid'); });
    $schema->create('oa_usergroups', function (Blueprint $table) { $table->string('userid'); $table->string('groupid'); });
    $schema->create('oa_agent', function (Blueprint $table) { $table->string('userid'); $table->string('agent'); });
    $schema->create('qua', function (Blueprint $table) { $table->string('quano'); $table->string('quadt'); $table->string('owner')->nullable(); });
    $this->db()->table('oa_menutable')->insert(['menuid' => DesktopHelper::MENU, 'caption' => 'Fixture', 'master_table' => 'qua']);
    $this->db()->table('oa_usermenus')->insert(['userid' => 'FIXTURE', 'menuid' => DesktopHelper::MENU]);
    app('session')->put('_userid', (object)['userid' => 'FIXTURE', 'agent' => []]);
    app('session')->put('dbconna', 'companion_test');
    app('session')->save();
    Cache::flush();
    Carbon::setTestNow(Carbon::create(2026, 11, 17, 10, 0, 0, 'Asia/Taipei'));
  }

  protected function tearDown(): void
  {
    Carbon::setTestNow();
    DB::purge('companion_test');
    parent::tearDown();
  }

  private function db() { return DB::connection('companion_test'); }

  private function connect()
  {
    $request = Request::create('/desktop-helper/connect', 'POST');
    $request->setLaravelSession(app('session')->driver());
    return (new DesktopHelperController())->connect($request)->getData(true);
  }

  private function changes($lease, $cursor = null, $date = null)
  {
    $request = Request::create('/desktop-helper/changes', 'GET', [
      'cursor' => $cursor ?? $lease['cursor'],
      'date' => $date ?? $lease['date'],
    ]);
    $request->headers->set('Authorization', 'Bearer '.$lease['token']);
    return (new DesktopHelperController())->changes($request)->getData(true);
  }

  private function record($order = 'TEST-001', $date = '20261117', $action = 'add', $database = 'companion_test')
  {
    $this->db()->table('qua')->insert(['quano' => $order, 'quadt' => $date, 'owner' => 'FIXTURE']);
    DesktopHelper::record($database, $action, ['quano' => $order, 'quadt' => $date]);
  }

  public function test_only_todays_additions_and_modifications_are_reported(): void
  {
    $lease = $this->connect();
    $this->record();
    $this->record('TEST-002', '20261117', 'mod');
    $this->record('TEST-OLD', '20261116', 'mod');
    $this->record('TEST-FUTURE', '20261118', 'add');
    $this->record('TEST-DELETE', '20261117', 'del');
    $result = $this->changes($lease);
    $this->assertSame(['TEST-001', 'TEST-002'], array_column($result['events'], 'quano'));
    $this->assertSame(['add', 'mod'], array_column($result['events'], 'action'));
    $this->assertSame([], $this->changes($lease, $result['cursor'])['events']);
  }

  public function test_login_uses_current_baseline_and_database_isolation(): void
  {
    $this->record('TEST-EXISTING');
    $lease = $this->connect();
    $this->record('TEST-OTHER', '20261117', 'add', 'other_fixture');
    $this->assertSame([], $this->changes($lease)['events']);
  }

  public function test_midnight_rolls_over_and_rechecks_the_current_document_date(): void
  {
    //2026.11.17 by codex, cross midnight within the actual lease lifetime instead of testing an expired token.
    Carbon::setTestNow(Carbon::create(2026, 11, 17, 23, 59, 30, 'Asia/Taipei'));
    app('session')->save();
    $lease = $this->connect();
    $this->record();
    Carbon::setTestNow(Carbon::create(2026, 11, 18, 0, 0, 1, 'Asia/Taipei'));
    $this->record('TEST-NEW-DAY', '20261118', 'mod');
    $result = $this->changes($lease);
    $this->assertSame('20261118', $result['date']);
    $this->assertSame(['TEST-NEW-DAY'], array_column($result['events'], 'quano'));
    $this->db()->table('qua')->where('quano', 'TEST-NEW-DAY')->update(['quadt' => '20261119']);
    $this->assertSame([], $this->changes($lease)['events']);
  }

  public function test_revoked_login_rejects_the_token(): void
  {
    $lease = $this->connect();
    app('session')->forget('_userid');
    app('session')->save();
    try { $this->changes($lease); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }

  public function test_switching_database_rejects_the_original_token(): void
  {
    $lease = $this->connect();
    app('session')->put('dbconna', 'other_fixture');
    app('session')->save();
    try { $this->changes($lease); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }

  public function test_revoked_menu_permission_is_checked_on_every_poll(): void
  {
    $lease = $this->connect();
    $this->db()->table('oa_usermenus')->delete();
    try { $this->changes($lease); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(403, $error->getStatusCode()); }
  }

  public function test_row_filter_does_not_expose_other_owners_orders(): void
  {
    $lease = $this->connect();
    $this->db()->table('oa_menutable')->update(['user_filter' => 'owner']);
    $this->record('TEST-VISIBLE');
    $this->record('TEST-HIDDEN');
    $this->db()->table('qua')->where('quano', 'TEST-HIDDEN')->update(['owner' => 'OTHER']);
    $result = $this->changes($lease);
    $this->assertSame(['TEST-VISIBLE'], array_column($result['events'], 'quano'));
    $this->assertSame(2, $result['cursor']);
  }

  public function test_lost_history_is_explicit_and_date_validation_is_strict(): void
  {
    $lease = $this->connect();
    Cache::put(DesktopHelper::key('companion_test', '20261117'), [
      'sequence' => 600,
      'events' => [['id' => 600, 'action' => 'mod', 'quano' => 'TEST-UNAVAILABLE']],
    ], 3600);
    $result = $this->changes($lease);
    $this->assertTrue($result['gap']);
    $this->assertSame(600, $result['cursor']);
    $this->assertSame('', DesktopHelper::documentDate('2026-02-30'));
    $this->assertSame('20261117', DesktopHelper::documentDate('2026/11/17'));
  }

  public function test_poll_route_requires_a_token_and_does_not_create_an_anonymous_session(): void
  {
    $response = $this->getJson('/desktop-helper/changes');
    $response->assertStatus(401);
    $this->assertSame([], $response->headers->getCookies());
  }

  public function test_poll_route_can_use_scoped_access_without_browser_cookies(): void
  {
    $lease = $this->connect();
    $this->record();
    $response = $this->getJson('/desktop-helper/changes?date='.$lease['date'].'&cursor='.$lease['cursor'], [
      'Authorization' => 'Bearer '.$lease['token'],
    ]);
    $response->assertStatus(200)->assertJsonPath('events.0.quano', 'TEST-001');
    $this->assertSame([], $response->headers->getCookies());
  }

  public function test_saved_order_hooks_publish_once_per_addition_and_modification(): void
  {
    $lease = $this->connect();
    $row = ['quano' => 'TEST-HOOK', 'quadt' => '20261117'];
    $this->db()->table('qua')->insert($row);
    $event = new Bsi020010Event();
    $this->assertFalse($event->afterInsert($row)['error']);
    $this->assertFalse($event->afterModify($row)['error']);
    $this->assertSame(['add', 'mod'], array_column($this->changes($lease)['events'], 'action'));
    Http::assertSentCount(2);
  }

  public function test_cache_failure_does_not_fail_the_business_save_hook(): void
  {
    Cache::shouldReceive('lock')->once()->andThrow(new \RuntimeException('Fixture failure'));
    Log::shouldReceive('warning')->once()->with('Desktop helper notification could not be queued.');
    $result = (new Bsi020010Event())->afterInsert(['quano' => 'TEST-CACHE', 'quadt' => '20261117']);
    $this->assertFalse($result['error']);
    Http::assertNothingSent();
  }

  public function test_oacs_wakes_without_disclosing_order_data_and_skips_other_dates(): void
  {
    $this->record();
    $this->record('TEST-MOD', '20261117', 'mod');
    $this->record('TEST-OLD', '20261116');
    $this->record('TEST-FUTURE', '20261118', 'mod');
    $this->record('TEST-DELETE', '20261117', 'del');
    Http::assertSentCount(2);
    Http::assertSent(function ($request) {
      return $request->data() === ['act' => 'desktop-helper', 'userid' => 'ALL', 'data' => null];
    });
  }

  public function test_oacs_failure_preserves_cursor_and_does_not_fail_the_save_hook(): void
  {
    $lease = $this->connect();
    Http::swap(new \Illuminate\Http\Client\Factory());
    Http::preventStrayRequests();
    Http::fake(['http://oacs.invalid/internal/notify' => Http::response(['ok' => false], 500)]);
    Log::shouldReceive('warning')->twice()->with('Desktop helper notification could not be queued.');
    $row = ['quano' => 'TEST-OACS', 'quadt' => '20261117'];
    $this->db()->table('qua')->insert($row);
    $event = new Bsi020010Event();
    $this->assertFalse($event->afterInsert($row)['error']);
    $this->assertFalse($event->afterModify($row)['error']);
    $result = $this->changes($lease);
    $this->assertSame(['add', 'mod'], array_column($result['events'], 'action'));
    $this->assertSame(2, $result['cursor']);
    $this->assertSame([], $this->changes($lease, $result['cursor'])['events']);
  }

  public function test_broadcast_runs_after_feed_commit_and_cache_lock_release(): void
  {
    //2026.11.17 by codex, acquire the same lock inside the fake transport to verify no network call holds it.
    Http::swap(new \Illuminate\Http\Client\Factory());
    Http::preventStrayRequests();
    Http::fake(['http://oacs.invalid/internal/notify' => function ($request) {
      $key = DesktopHelper::key('companion_test', '20261117');
      $lock = Cache::lock($key.':lock', 5);
      $acquired = $lock->get();
      try {
        $this->assertTrue($acquired);
        $this->assertSame(1, DesktopHelper::feed('companion_test', '20261117')['sequence']);
        $this->assertSame(['act' => 'desktop-helper', 'userid' => 'ALL', 'data' => null], $request->data());
      } finally {
        if ($acquired) $lock->release();
      }
      return Http::response(['ok' => true], 200);
    }]);
    $this->record();
    Http::assertSentCount(1);
  }

  public function test_failed_cache_write_does_not_broadcast_or_fail_the_save_hook(): void
  {
    $lock = Cache::lock(DesktopHelper::key('companion_test', '20261117').':lock', 5);
    Cache::shouldReceive('lock')->once()->andReturn($lock);
    Cache::shouldReceive('get')->once()->andReturn(['sequence' => 0, 'events' => []]);
    Cache::shouldReceive('put')->once()->andReturn(false);
    Log::shouldReceive('warning')->once()->with('Desktop helper notification could not be queued.');
    $result = (new Bsi020010Event())->afterModify(['quano' => 'TEST-WRITE-FAILURE', 'quadt' => '20261117']);
    $this->assertFalse($result['error']);
    Http::assertNothingSent();
  }

  public function test_oacs_disconnect_preserves_feed_for_polling_without_repeating_events(): void
  {
    $lease = $this->connect();
    Http::swap(new \Illuminate\Http\Client\Factory());
    Http::preventStrayRequests();
    Http::fake(['http://oacs.invalid/internal/notify' => function () {
      throw new \Illuminate\Http\Client\ConnectionException('Synthetic disconnect');
    }]);
    Log::shouldReceive('warning')->once()->with('Desktop helper notification could not be queued.');
    $row = ['quano' => 'TEST-DISCONNECT', 'quadt' => '20261117'];
    $this->db()->table('qua')->insert($row);
    $this->assertFalse((new Bsi020010Event())->afterModify($row)['error']);
    $result = $this->changes($lease);
    $this->assertSame(['TEST-DISCONNECT'], array_column($result['events'], 'quano'));
    $this->assertSame([], $this->changes($lease, $result['cursor'])['events']);
  }

  public function test_connect_requires_login_and_menu_permission(): void
  {
    $this->db()->table('oa_usermenus')->delete();
    try { $this->connect(); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(403, $error->getStatusCode()); }
    app('session')->forget('_userid');
    try { $this->connect(); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }

  public function test_switching_account_rejects_the_original_token(): void
  {
    $lease = $this->connect();
    app('session')->put('_userid', (object)['userid' => 'OTHER', 'agent' => []]);
    app('session')->save();
    try { $this->changes($lease); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }

  public function test_expired_and_unknown_tokens_cannot_read_notifications(): void
  {
    $lease = $this->connect();
    $unknown = $lease;
    $unknown['token'] = str_repeat('0', 64);
    try { $this->changes($unknown); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
    Carbon::setTestNow(Carbon::now()->addSeconds(config('session.lifetime') * 60 + 1));
    try { $this->changes($lease); $this->fail('Expected access rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }

  public function test_retention_limit_pagination_and_reset_cursor_remain_explicit(): void
  {
    $lease = $this->connect();
    $row = ['quano' => 'TEST-LIMIT', 'quadt' => '20261117'];
    $this->db()->table('qua')->insert($row);
    for ($i = 0; $i < DesktopHelper::LIMIT + 2; $i++) DesktopHelper::record('companion_test', 'mod', $row);
    $feed = DesktopHelper::feed('companion_test', '20261117');
    $this->assertCount(500, $feed['events']);
    $this->assertSame(502, $feed['sequence']);
    $this->assertSame(3, $feed['events'][0]['id']);
    $result = $this->changes($lease);
    $this->assertTrue($result['gap']);
    $this->assertCount(100, $result['events']);
    $this->assertSame(102, $result['cursor']);
    $next = $this->changes($lease, $result['cursor']);
    $this->assertFalse($next['gap']);
    $this->assertSame(103, $next['events'][0]['id']);
    $reset = $this->changes($lease, 999);
    $this->assertTrue($reset['gap']);
    $this->assertSame(102, $reset['cursor']);
  }

  //2026.11.17 by codex, scope both event production and existing leases to customer quotations only.
  public function test_customer_quotation_scope_replaces_customer_orders(): void
  {
    $this->assertSame('BSI020010', DesktopHelper::MENU);
    DesktopHelper::record('companion_test', 'mod', ['ordno' => 'OLD-ORDER', 'orddt' => '20261117']);
    DesktopHelper::record('companion_test', 'mod', [
      '_menuid' => 'BSI020020', 'quano' => 'WRONG-MENU', 'quadt' => '20261117',
    ]);
    $this->assertSame(0, DesktopHelper::feed('companion_test', '20261117')['sequence']);
    Http::assertNothingSent();
    $this->db()->table('oa_menutable')->update(['master_table' => 'ord']);
    try { $this->connect(); $this->fail('Expected quotation table rejection'); }
    catch (HttpException $error) { $this->assertSame(403, $error->getStatusCode()); }
  }

  public function test_pre_migration_order_lease_cannot_read_quotation_events(): void
  {
    $lease = $this->connect();
    $key = 'desktop-helper:token:'.hash('sha256', $lease['token']);
    $binding = Cache::get($key);
    $binding['menu'] = 'BSI020020';
    Cache::put($key, $binding, 3600);
    try { $this->changes($lease); $this->fail('Expected old menu lease rejection'); }
    catch (HttpException $error) { $this->assertSame(401, $error->getStatusCode()); }
  }
}
