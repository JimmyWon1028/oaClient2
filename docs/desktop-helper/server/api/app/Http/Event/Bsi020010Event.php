<?php
//2026.11.13 by codex, load supplier quotes linked to the current customer quotation.
namespace App\Http\Event;

use App\Util\MyFunc As myfunc;
use App\Util\DesktopHelper;

class Bsi020010Event
{
  private $ut;

  public function __construct()
  {
    $this->ut = myfunc::myUt();
  }

  public function afterScroll($masrow)
  {
    $res = ['vendorQuotes' => []];
    if (empty($masrow['quano'])) return $res;

    $res['vendorQuotes'] = myfunc::select([
      'sql' => "
        Select
          Q.quano, Q.orditem,
          Q.mprdno, Q.brandno, B.brandna As brandna_ref,
          Q.crncy, Q.saleprc, Q.saleqty,
          Q.dcno, Q.leadtime, Q.rem
        From qua Q
          Left Join brand B
            On B.brandno=Q.brandno
        Where Q.trn='PQ'
          And Q.ordno=?
        Order By Q.orditem, Q.quadt Desc, Q.quano Desc
      ",
      'param' => [$masrow['quano']],
      'dbconn' => $this->ut['dbconn'],
    ]);

    return $res;
  }

  //2026.11.17 by codex, notify customer quotation saves while preserving the existing supplier quote lookup.
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
      DesktopHelper::record($this->ut['dbconna'], $action, $row);
    } catch (\Throwable $e) {
      logger()->warning('Desktop helper notification could not be queued.');
    }
    return ['affected' => 0, 'error' => false];
  }
}
