<?php

namespace {
  //2026.11.17 by codex, load framework libraries read-only while isolating all app configuration and generated files.
  $vendor = getenv('OA_HELPER_TEST_VENDOR');
  if (!$vendor || !is_file($vendor.'/autoload.php')) throw new \RuntimeException('Provide OA_HELPER_TEST_VENDOR.');
  require $vendor.'/autoload.php';
  //2026.11.17 by codex, test the real API source when supplied and keep snapshot verification available.
  $snapshot = rtrim(getenv('OA_HELPER_TEST_APP') ?: dirname(__DIR__).'/docs/desktop-helper/server/api/app', '/\\').'/';
  require $snapshot.'Util/DesktopHelper.php';
  require $snapshot.'Http/Controllers/DesktopHelperController.php';
  require $snapshot.'Http/Event/Bsi020010Event.php';
}

namespace Tests {
  abstract class TestCase extends \Illuminate\Foundation\Testing\TestCase
  {
    public function createApplication()
    {
      $root = getenv('OA_HELPER_TEST_ROOT');
      if (!$root || !is_dir($root.'/bootstrap/cache')) throw new \RuntimeException('Provide an isolated OA_HELPER_TEST_ROOT.');
      $app = \Illuminate\Foundation\Application::configure(basePath: $root)
        ->withExceptions()
        ->withRouting(using: function () {
          \Illuminate\Support\Facades\Route::get('desktop-helper/changes', [\App\Http\Controllers\DesktopHelperController::class, 'changes']);
        })->create();
      $app->afterBootstrapping(\Illuminate\Foundation\Bootstrap\LoadConfiguration::class, function ($app) {
        $app['config']->set([
          'app.env' => 'testing', 'app.debug' => false,
          'app.key' => str_repeat('s', 32), 'app.cipher' => 'AES-256-CBC',
          'app.timezone' => 'Asia/Taipei', 'app.url' => 'http://localhost',
          'cache.default' => 'array', 'cache.stores.array' => ['driver' => 'array'],
          'session.driver' => 'array', 'session.lifetime' => 120, 'session.cookie' => 'synthetic_session',
          'logging.default' => 'null', 'logging.channels.null' => ['driver' => 'monolog', 'handler' => \Monolog\Handler\NullHandler::class],
          'database.default' => 'companion_test',
        ]);
      });
      $app->make(\Illuminate\Contracts\Console\Kernel::class)->bootstrap();
      return $app;
    }
  }
}
