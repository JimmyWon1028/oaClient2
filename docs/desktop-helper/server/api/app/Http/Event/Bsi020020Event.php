<?php

namespace App\Http\Event;

use App\Util\DesktopHelper;
use App\Util\MyFunc As myfunc;

//2026.11.17 by codex, publish today's saved order changes without affecting the business save result.
class Bsi020020Event
{
  public function afterInsert($row)
  {
    return $this->notify('add', $row);
  }

  public function afterModify($row)
  {
    return $this->notify('mod', $row);
  }

  private function notify($action, $row)
  {
    try {
      $ut = myfunc::myUt();
      DesktopHelper::record($ut['dbconna'], $action, $row);
    } catch (\Throwable $e) {
      //2026.11.17 by codex, omit exception details because they can contain business or connection data.
      logger()->warning('Desktop helper notification could not be queued.');
    }
    return ['affected' => 0, 'error' => false];
  }
}
