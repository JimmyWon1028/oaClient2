# 後端 API 上傳與介面說明

日期：2026-11-17。最新工作 ID：W43。使用者已更正通知目標為 **BSI020010 客戶詢報價**，取代先前 BSI020020 客戶訂單。真正 Megatower API 本機來源及快照已更新；代理未部署正式主機。使用者先前回報已上傳的是更正前版本，這次仍需更新下列三個 PHP。

## 本次需上傳的三個檔案

從本目錄 `server/` 複製到後端對應位置：

1. [DesktopHelperController.php](server/api/app/Http/Controllers/DesktopHelperController.php) → `api/app/Http/Controllers/DesktopHelperController.php`
2. [DesktopHelper.php](server/api/app/Util/DesktopHelper.php) → `api/app/Util/DesktopHelper.php`
3. [Bsi020010Event.php](server/api/app/Http/Event/Bsi020010Event.php) → `api/app/Http/Event/Bsi020010Event.php`

本次三份都有變更，不能只更新 Util。最新大小及 SHA256 見 [BACKEND-MANIFEST.json](BACKEND-MANIFEST.json)。`server/api/tests/Feature/DesktopHelperTest.php` 是隔離測試，不必上傳。

`Bsi020010Event.php` 已保留真正本機來源的建構式及 `afterScroll` 供應商報價查詢，只增加 `afterInsert`／`afterModify` 通知。主機若有其他客製事件，請合併掛接與通知方法，保留原規則。核對正式資料庫 `oa_menutable` 的 BSI020010 `event`：空白時 Table2Controller 使用預設 `Bsi020010Event`，非空白則需在實際指定類別合併。代理未查正式資料庫 event 設定。

原 `Bsi020020Event.php` 不需刪除或覆蓋；新版 Util 拒絕舊訂單欄位及非 BSI020010 的 `_menuid`，不再產生訂單通知。`qua` 包含其他用途，通知只由 BSI020010 成功表單儲存產生，不監聽整張資料表。

## 路由與 OACS

已存在的兩條路由保持；新站才在 `api/routes/web.php` 合併以下區塊，不用開發端完整檔案覆蓋主機：

```php
//2026.11.17 by codex, scope read-only companion notifications to the current ERP login.
Route::post('desktop-helper/connect', 'DesktopHelperController@connect')->middleware('auth');
Route::get('desktop-helper/changes', 'DesktopHelperController@changes')->withoutMiddleware([
  \Illuminate\Session\Middleware\StartSession::class,
  \Illuminate\View\Middleware\ShareErrorsFromSession::class,
]);
```

沿用主機 Session、Cache、路由快取及部署流程，無資料表／認證帳密變更。多主機 Session 與事件快取必須共用；原 Session 核對不支援只把 Session 存在瀏覽器 Cookie 的 driver。

沿用既有 `services.oacs.host`、`MyFunc::broadcast` 及 OACS `/internal/notify` 的 ALL → `notification`；配套一致時不用上傳／重啟 OACS，不放寬來源檢查。feed 寫入成功並釋放鎖後才發送 `desktop-helper` 喚醒，內容無單號、使用者資料或 Token。OACS 失敗不改單據儲存結果，事件供定時補查；Cache 寫入失敗不廣播。

## 介面與通知條件

- `POST <目前站台 API 根網址>/desktop-helper/connect`：沿用登入 Session，核對 **BSI020010** 選單權限及 `master_table=qua`，取得 `token`、`scope`、`date`、`cursor`、`expires_at`。
- Token 僅留當次記憶體，不進入 INI、URL、日誌或 console。綁定 Session／帳號／資料庫及 BSI020010；更正前訂單 Token 不接受，需重新取得存取權。
- `GET <同一 API 根網址>/desktop-helper/changes?date=<API 日期>&cursor=<游標>`：Authorization 使用通知 Bearer Token，再核對原 Session、帳號、資料庫、選單及資料列權限。
- 回傳 `date`、`cursor`、`gap`、`events`；事件包含 `id`、`action`（add／mod）、**`quano`**。
- 只通知 BSI020010 表單成功新增／修改，且 **單據日期 `quadt` 為後端今天**；主表 `qua`、單號 `quano`。過去／未來日期、外部匯入、直接 SQL 不在範圍，讀取時再核對目前日期與權限。
- 今天依 ERP `app.timezone` 的 `Ymd`（Asia/Taipei），不由 Windows UTC 判斷。快取按資料庫／表單／日期隔離，最多500筆、每頁100筆，保留 gap、跨日與去重。
- 首次 connect 以當下游標為基準，**先前編輯不補發**。登出、切換資料庫、過期或失去權限時拒絕存取。

oaClient2 沿用目前頁面 `$g.api_root` 取得權限，監聽既有 `$g.chatHub` 的 `notification`／`connect`，喚醒後由原生非同步工作立即讀 changes，保留10秒補查。無新增網址、獨立 EXE、loopback 橋接或外部 Chrome／Edge 接線。WebSocket 喚醒本身不授予單據存取權。

## 上傳後驗證

1. 更新三份 PHP，確認路由及 BSI020010 event 掛接，依主機既有流程處理快取。
2. 使用修正後 Windows oaClient2 **0.1.9**，重新登入並等待小熊出現。登入由使用者操作。
3. 登入完成後，再於 Mac 或其他 ERP 視窗編輯／確認今天的 **BSI020010 客戶詢報價**。Windows pet 應收到「修改詢報價」；新增則是「新增詢報價」。
4. 點通知在 oaClient2 開啟 BSI020010，以 `quano` 定位；表單編輯中保留內容並提示先儲存／取消。

正式流程尚未驗證；代理未異動正式單據、代填帳密或部署。若未收到，接續核對正式主機三檔、event、權限、OACS 及10秒補查，不能以本機測試推定主機已更新。

## 本機驗證與歷史

W43：PHP 8.2.33／PHPUnit 11.5.56，真正 API 與快照各23 tests／71 assertions及語法檢查通過。涵蓋舊訂單欄位／錯誤表單排除、qua 權限／舊表 Token 拒絕，以及原鎖／廣播失敗、權限、跨日、分頁、gap 與去重。使用記憶體 SQLite、array Cache／Session、Http fake，不載入正式 `.env`、不連正式資料庫、不發真實 OACS。

OACS 真實 dispatcher＋假 Socket／路由契約6項、客戶端腳本16項通過。Windows MSVC Release／CTest2/2（178核心＋16腳本）通過；原生合成頁已實測新增／修改詢報價、點擊 BSI020010 與編輯保護。證據：`artifacts/verification/windows-w43-bsi020010/`。正式 OA、完整切站／跨日矩陣、方向鍵、注音、列印、Reptool 本輪未重測，Mac未重編。

重跑：`tests/run-desktop-helper-php.ps1 -Php <PHP8.2> -ApiRoot <真正API目錄> -TestRoot <API外隔離目錄>`，加 `-Snapshot` 測快照；`node tests/desktop_helper_oacs_tests.cjs <真正API目錄>`；`node tests/desktop_helper_script_tests.cjs`。測試／bootstrap 不上傳。

歷史：D05原始12／27、W40的14／32、W41的21／66均是更正前 BSI020020 結果。W41補齊真正本機 API 廣播並保留當時 Controller／事件／路由；使用者隨後回報已上傳，代理未遠端核對。W43取代其通知表單及三檔上傳範圍。[RESOURCE-MANIFEST.json](RESOURCE-MANIFEST.json) 保留 D05 原始雜湊，不當作最新部署清單。
