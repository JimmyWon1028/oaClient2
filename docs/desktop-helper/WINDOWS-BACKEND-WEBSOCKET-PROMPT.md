# Windows 後端通知 WebSocket 接續提示詞

## W43：通知目標更正（2026-11-17，優先於早期範圍）

使用者明確更正為 **BSI020010 客戶詢報價**。主表 `qua`、單號 `quano`、單據日期 `quadt`；只通知後端今天的成功新增／修改，點擊亦開啟 BSI020010。更正取代原 BSI020020／ordno／orddt 範圍，不同時監看訂單。真正本機 API、快照及 Windows 0.1.9 已更新，正式主機未由代理部署；此次三份 PHP 都需上傳，重新登入後再測新儲存，先前修改不補發。檔案與限制見 [API-UPLOAD.md](API-UPLOAD.md)。

W41 接續結果（2026-11-17）：真正 API 本機來源及快照已更新，隔離測試完成；未部署正式站。最新差異／上傳檔案／驗證限制見 [API-UPLOAD.md](API-UPLOAD.md) 與 [BACKEND-MANIFEST.json](BACKEND-MANIFEST.json)。下列「尚未加入廣播」保留為本提示詞建立時的歷史線索。

你現在位於 Windows 的 oaClient2 專案。請完成內建 pet 所需的通知後端串接，保持現有 API 契約，以最小修改補齊 WebSocket 喚醒，不整套重寫後端。

本任務是後端來源修改、測試與準備更新檔；不代表授權自動上傳或部署正式站。不要覆蓋目前 Windows 端正在開發的 oaClient2 程式。

## 先確認現況

1. 讀 oaClient2 的 AGENTS.md、HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md，以及 docs/desktop-helper/README.md、API-UPLOAD.md。
2. 在 Windows 定位真正的 Megatower API 專案，讀取該專案 AGENTS.md，核對目前來源與未提交變更。不要硬編碼使用者、磁碟或 Dropbox 絕對路徑。
3. oaClient2 的 `docs/desktop-helper/server/` 是後端接續快照；先和實際 Megatower API 來源比較。要明確區分「實際 API 已修改」「快照已更新」及「正式站已部署」，不能只改快照便宣稱已部署。
4. 保留兩端既有變更，確認 Dropbox 已同步；與進行中的 Windows 整合工作協調，避免同時覆寫相同檔案。

截至本提示詞整理時，已讀到的來源差異：

- oaClient2 的 `src/app/desktop_helper_script.h` 接收目前網站 `$g.chatHub` 的 `notification`，`act=desktop-helper` 時送出原生 wake 訊息。
- `src/platform/windows/desktop_helper.cpp` 收到 wake 後仍呼叫 `desktop-helper/changes` 取得授權後的通知內容，並保留定時查詢作補漏。
- `desktop-helper/connect` 仍用於取得通知專用 Token 與初始游標。
- 因此 WebSocket 負責「有異動，立即讀取」；原本三個 PHP 檔與兩條路由仍有用途。
- oaClient2 快照中的 `api/app/Util/DesktopHelper.php` 已加入 `MyFunc::broadcast('desktop-helper', 'ALL')`，但本機真正 Megatower 專案的同名檔案尚未加入該廣播。
- 兩份 `DesktopHelperController.php`、`Bsi020020Event.php` 在當時逐位元相同。以上是接續線索，開始時仍需核對 Windows 最新來源。

## 已確認需求

- pet 是 oaClient2 內建功能，不另安裝或啟動獨立 Windows pet。
- 只有目前站台登入成功後顯示；未登入不顯示，登出即停止並隱藏，主程式關閉一起結束。
- 站台與 API 直接沿用 oaClient2 目前載入站台及該站最新 API 資訊，不增加 pet 網址設定，也不寫死 oa.megatowerinc.com 或開發網址。
- 只通知 BSI020010 的 ERP 表單新增／修改成功事件，而且單據日期 `quadt` 必須是後端今天。
- 過去或未來日期的單據，即使今天修改也不通知；外部匯入及直接 SQL 不在本輪範圍。
- 日期依 ERP 後端 app.timezone 判斷，沿用目前台北時間及既有日期／游標協定。

## 修改範圍

以實際 API 專案為主，核對以下檔案：

1. `api/app/Util/DesktopHelper.php`
   - 沿用目前按資料庫及日期隔離的通知 feed、事件序號、保存上限與 Cache 鎖。
   - 今天單據的新增／修改事件成功寫入後，透過既有 `MyFunc::broadcast` 發出 `desktop-helper` 喚醒訊息。
   - 網路廣播在 Cache 鎖釋放後才執行，避免持鎖等待外部服務。
   - 喚醒只表示有資料變更，不廣播單號、客戶、Token、帳密或其他業務內容。保留由 API 依權限查詢內容的流程。
   - 核對目前 OACS 已有的 ALL 通知行為及訊息格式，沿用現有服務，不新建另一套 WebSocket 伺服器。

2. `api/app/Http/Event/Bsi020010Event.php`
   - 保留新增／修改成功事件掛接及今天日期的篩選。
   - 廣播失敗不能使已成功的單據儲存回報失敗，也不能刪除已寫入的通知 feed。
   - 核對實際站台的 BSI020010 event 設定；如果已有自訂事件，合併通知掛接並保留原業務規則，不能直接覆蓋。

3. `api/app/Http/Controllers/DesktopHelperController.php`
   - 保留 connect 的既有登入／權限核對、通知專用 Token 及首次連線游標基準。
   - 保留 changes 對原登入 Session、帳號、資料庫、表單／資料列權限與目前單據日期的核對。
   - 保留跨日、gap 與游標處理；不要因改用 WebSocket 而放寬權限或繞過原 Session。
   - 沒有必要便不修改此檔。

4. `api/routes/web.php`
   - 核對以下既有兩條通知路由，不重複註冊、不拿開發端完整檔案覆蓋正式站：
     - `POST desktop-helper/connect`：沿用登入 middleware。
     - `GET desktop-helper/changes`：保留通知 Token 驗證及目前不啟動匿名 Session 的處理。
   - 尚未部署的新站仍需加入這兩條路由；已存在則核對內容，不為重複部署改動其他路由。

通知契約請讀實際 Controller 與 `docs/desktop-helper/API-UPLOAD.md`。原獨立 pet 的 C#、EXE、安裝包及 OA loopback 腳本已取消，不恢復它們。

## 失敗及補漏

- WebSocket 只用於喚醒，保留目前約 10 秒的定時補漏，不新增另一套輪詢機制。
- OACS 暫時不可用、斷線或廣播失敗時，單據仍正常儲存，通知 feed 保留供後續查詢。
- 同一事件經 WebSocket 與定時查詢交錯，不重複提醒。
- 多資料庫／站台的喚醒不能使客戶端拿錯 API 或權限；廣播不攜帶業務資料，實際內容仍由當前授權 API 決定。
- 訊息、測試輸出與日誌不顯示密碼、Token、連線資訊或個人資料；保留現有不含敏感細節的錯誤處理。

## 驗證

- 使用 PHP 8.2 相容環境，對修改檔執行 php -l。
- 沿用並更新隔離的 DesktopHelperTest；測試需攔截／模擬外部廣播，不向真實 OACS 全體使用者發送測試訊息，也不修改正式單據。
- 驗證今天新增／修改會記錄並觸發喚醒，過去／未來日期不觸發；取得內容仍必須有有效授權。
- 驗證廣播失敗不影響儲存及 feed，登入／資料庫／權限隔離、跨日、游標及缺口處理保持。
- 在明確允許的測試環境驗證完整流程：表單儲存成功 → OACS 喚醒 → oaClient2 立即讀 changes → pet 揮手及通知。另驗證 OACS 斷線時可由定時查詢補到，且不重複通知。
- 編譯、隔離測試、Windows 實際通知及正式站部署分別記錄，未執行的明確列為待驗證。

## 完成與交付

- 更新實際 API 來源後，同步必要的 oaClient2 後端快照／API 上傳清單及資源雜湊，避免兩份繼續不一致；保留進行中的 Windows 產品修改。
- 列出實際有差異的 PHP 檔、路由新增區塊、是否需操作 OACS，以及測試結果。
- 尚未部署的站台，交付應包含所需三個 PHP 檔及路由合併說明；若檔案與主機現況相同，只列必要差異。
- 不上傳測試、個人設定、.env、舊 OA loopback 腳本或已取消的獨立 pet。
- 本任務不自行 commit、push、發布或部署正式站。上傳前先核對真正主機的事件與路由現況。

回覆繁體中文；代碼兩格空白縮排，註釋英文，格式 `//yyyy.mm.dd by codex, reason in english`。不要增加無關功能、相依套件或重構。
