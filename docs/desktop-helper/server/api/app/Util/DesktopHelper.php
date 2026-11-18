<?php

namespace App\Util;

use Illuminate\Support\Facades\Cache;

//2026.11.17 by codex, keep desktop notification cursors isolated by database and calendar date.
class DesktopHelper
{
  const MENU = 'BSI020010';
  const LIMIT = 500;

  public static function today()
  {
    return \Carbon\Carbon::now(config('app.timezone', 'Asia/Taipei'))->format('Ymd');
  }

  public static function documentDate($value)
  {
    if ($value instanceof \DateTimeInterface) return $value->format('Ymd');
    $value = preg_replace('/[-\/]/', '', trim((string)$value));
    $value = substr($value, 0, 8);
    if (!preg_match('/^\d{8}$/D', $value)) return '';
    return checkdate((int)substr($value, 4, 2), (int)substr($value, 6, 2), (int)substr($value, 0, 4)) ? $value : '';
  }

  public static function key($database, $date)
  {
    return 'desktop-helper:events:'.hash('sha256', $database.'|'.self::MENU.'|'.$date);
  }

  public static function record($database, $action, array $row)
  {
    $date = self::today();
    if (!in_array($action, ['add', 'mod'], true)
      || (isset($row['_menuid']) && strtoupper($row['_menuid']) !== self::MENU)
      || self::documentDate($row['quadt'] ?? '') !== $date
      || empty($row['quano'])) return;

    $key = self::key($database, $date);
    Cache::lock($key.':lock', 5)->block(2, function () use ($key, $action, $row) {
      $feed = Cache::get($key, ['sequence' => 0, 'events' => []]);
      $feed['sequence']++;
      $feed['events'][] = [
        'id' => $feed['sequence'],
        'action' => $action,
        'quano' => (string)$row['quano'],
      ];
      $feed['events'] = array_slice($feed['events'], -self::LIMIT);
      //2026.11.17 by codex, do not wake clients when the cache driver reports a failed feed write.
      if (!Cache::put($key, $feed, 172800)) throw new \RuntimeException('Desktop helper feed could not be saved.');
    });
    //2026.11.17 by codex, wake existing OACS clients without broadcasting order data or granting access.
    MyFunc::broadcast('desktop-helper', 'ALL');
  }

  public static function feed($database, $date)
  {
    return Cache::get(self::key($database, $date), ['sequence' => 0, 'events' => []]);
  }
}
