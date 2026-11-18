<?php

namespace App\Http\Controllers;

use App\Util\DesktopHelper;
use App\Util\MyFunc As myfunc;
use Illuminate\Http\Request;
use Illuminate\Session\EncryptedStore;
use Illuminate\Session\Store;
use Illuminate\Support\Facades\Cache;

//2026.11.17 by codex, grant the local companion read-only notification access tied to the existing login session.
class DesktopHelperController extends Controller
{
  public function connect(Request $request)
  {
    $user = myfunc::getSession('_userid');
    abort_unless($user && !empty($user->userid), 401);
    $database = myfunc::dbconna();
    $this->authorizedMenu($database, $user);
    $token = bin2hex(random_bytes(32));
    $seconds = max(60, (int)config('session.lifetime', 120) * 60);
    $session = $request->session();
    Cache::put($this->tokenKey($token), [
      'session' => $session->getId(),
      'userid' => $user->userid,
      'database' => $database,
      'menu' => DesktopHelper::MENU,
    ], $seconds);
    $date = DesktopHelper::today();
    $feed = DesktopHelper::feed($database, $date);
    return $this->reply([
      'token' => $token,
      'scope' => hash('sha256', $session->getId().'|'.$database.'|'.$user->userid.'|'.DesktopHelper::MENU),
      'date' => $date,
      'cursor' => $feed['sequence'],
      'expires_at' => time() + $seconds,
    ]);
  }

  public function changes(Request $request)
  {
    $token = $request->bearerToken();
    abort_unless(is_string($token) && preg_match('/^[a-f0-9]{64}$/D', $token), 401);
    $binding = Cache::get($this->tokenKey($token));
    abort_unless(is_array($binding) && ($binding['menu'] ?? null) === DesktopHelper::MENU, 401);
    $original = $this->originalSession($binding['session']);
    $user = $original->get('_userid');
    $database = $original->get('dbconna') ?: env('DB_DATABASE');
    if (!$user || empty($user->userid) || $user->userid !== $binding['userid'] || $database !== $binding['database']) {
      Cache::forget($this->tokenKey($token));
      abort(401);
    }
    $menu = $this->authorizedMenu($database, $user);
    $date = DesktopHelper::today();
    $feed = DesktopHelper::feed($database, $date);
    $cursor = $request->query('date') === $date ? max(0, (int)$request->query('cursor', 0)) : 0;
    $reset = $cursor > $feed['sequence'];
    if ($reset) $cursor = 0;
    $first = $feed['events'][0]['id'] ?? ($feed['sequence'] + 1);
    $gap = $cursor < $first - 1;
    $events = array_slice(array_values(array_filter($feed['events'], function ($event) use ($cursor) {
      return $event['id'] > $cursor;
    })), 0, 100);
    $next = $events ? end($events)['id'] : $feed['sequence'];
    $visible = [];
    if ($events) {
      $query = myfunc::dbconn($database)->table('qua')
        ->where('quadt', $date)
        ->whereIn('quano', array_column($events, 'quano'));
      $this->applyFilters($query, $menu, $database, $user->userid);
      $visible = $query->pluck('quano')->map(function ($value) { return (string)$value; })->all();
    }
    return $this->reply([
      'date' => $date,
      'cursor' => $next,
      'gap' => $gap || $reset,
      'events' => array_values(array_filter($events, function ($event) use ($visible) {
        return in_array($event['quano'], $visible, true);
      })),
    ]);
  }

  private function tokenKey($token)
  {
    return 'desktop-helper:token:'.hash('sha256', $token);
  }

  private function originalSession($id)
  {
    $driver = app('session')->driver();
    $handler = clone $driver->getHandler();
    $serialization = config('session.serialization', 'php');
    if (config('session.encrypt')) {
      $store = new EncryptedStore('desktop-helper-probe', $handler, app('encrypter'), $id, $serialization);
    } else {
      $store = new Store('desktop-helper-probe', $handler, $id, $serialization);
    }
    //2026.11.17 by codex, read without saving or extending the original browser session.
    $store->start();
    return $store;
  }

  private function authorizedMenu($database, $user)
  {
    abort_unless(myfunc::validDbconna($database), 403);
    $conn = myfunc::dbconn($database);
    $menu = $conn->table('oa_menutable')->where('menuid', DesktopHelper::MENU)->first();
    abort_unless($menu && $menu->stop_yn !== 'Y' && $menu->caption !== '-' && $menu->master_table === 'qua', 403);
    $principals = array_merge([$user->userid], myfunc::getSysdbconn()->table('oa_agent')
      ->where('agent', $user->userid)->pluck('userid')->all());
    $allowed = $conn->table('oa_usermenus')->where('menuid', DesktopHelper::MENU)
      ->whereIn('userid', $principals)->exists();
    if (!$allowed) {
      $allowed = $conn->table('oa_groupmenus as G')
        ->join('oa_usergroups as U', 'G.groupid', '=', 'U.groupid')
        ->where('G.menuid', DesktopHelper::MENU)->whereIn('U.userid', $principals)
        ->whereNotExists(function ($query) {
          $query->selectRaw('1')->from('oa_usermenus as P')
            ->whereColumn('P.userid', 'U.userid')->whereColumn('P.menuid', 'G.menuid');
        })->exists();
    }
    abort_unless($allowed, 403);
    return $menu;
  }

  private function applyFilters($query, $menu, $database, $userid)
  {
    if ($menu->def_filter === 'crtuserid') $query->where('crtuserid', $userid);
    else if (!empty($menu->def_filter)) $query->whereRaw($menu->def_filter);
    $fields = array_filter(array_map('trim', explode(',', $menu->user_filter ?? '')));
    $groupField = trim($menu->group_filter ?? '');
    foreach (array_merge($fields, $groupField ? [$groupField] : []) as $field) {
      abort_unless(preg_match('/^[A-Za-z_][A-Za-z0-9_]*$/D', $field), 403);
    }
    if ($fields || $groupField) {
      $groups = $groupField ? myfunc::dbconn($database)->table('oa_usergroups')
        ->where('userid', $userid)->pluck('groupid')->all() : [];
      $query->where(function ($filter) use ($fields, $groupField, $groups, $userid) {
        $filter->whereRaw('1=0');
        foreach ($fields as $field) $filter->orWhere($field, $userid);
        foreach ($groups as $group) $filter->orWhereRaw('StrIn(?, '.$groupField.')', [$group]);
      });
    }
  }

  private function reply($body)
  {
    return response()->json($body)->header('Cache-Control', 'no-store');
  }
}
