# Windows oaClient2 內建 pet 整合提示詞

## W43：通知目標更正（2026-11-17，優先於早期範圍）

使用者明確更正為 **BSI020010 客戶詢報價**。主表 `qua`、單號 `quano`、單據日期 `quadt`；只通知後端今天的成功新增／修改，點擊亦開啟 BSI020010。更正取代原 BSI020020／ordno／orddt 範圍，不同時監看訂單。真正本機 API、快照及 Windows 0.1.9 已更新，正式主機未由代理部署；此次三份 PHP 都需上傳，重新登入後再測新儲存，先前修改不補發。檔案與限制見 [API-UPLOAD.md](API-UPLOAD.md)。

## W40 追加決策（2026-11-17，優先於下列原始提示）

使用者改用既有 Megatower OACS／Socket.IO 即時喚醒，保留原生 10 秒補查以防漏訊，不新增 pet 站台設定、獨立連線或其他瀏覽器功能。工具列 MAC 左側加入 icon only、透明背景小熊按鈕以切換顯示／隱藏；訊息泡泡右上角有 × 可收起，保留小熊，新事件再彈出。其他 App 指所有 oaClient2 以外的 App，不限定 Excel；不額外開啟 Excel、不考慮外部 Chrome。若需要登入 oaClient2 或上傳 API，明確通知使用者操作，不代填登入。實作及驗證狀態見 PROGRESS.md W40，API 上傳以同目錄 API-UPLOAD.md 最新版本為準。

你現在位於 Windows 的 oaClient2 專案。請依以下已確認需求開始整合，沿用現有 C++20／CEF 架構，完成 Windows 建置與實機驗證。

## 先閱讀與核對

1. 先讀專案 `AGENTS.md`，依序讀 `HANDOFF.md`、`PROGRESS.md`、`PROJECT-PLAN.md`、`CHANGELOG.md`，以及 `docs/SHARED-CODE-RULES.md`、`docs/PLATFORM-PATHS.md`。
2. 確認 Windows 環境、Git 分支及工作區，並核對 Dropbox 已同步；保留現有變更。不要自行 commit、push、進版、發布或部署正式站。
3. 閱讀 `docs/desktop-helper/README.md`、`docs/desktop-helper/API-UPLOAD.md`、`docs/desktop-helper/RESOURCE-MANIFEST.json`。先核對複製資源雜湊，之後再作必要修改。
4. 所需小熊素材及通知後端快照都已放在本 oaClient2 專案內，不依賴 Mac 絕對路徑或已刪除的獨立 pet 專案。
5. 先追蹤現有登入／登出、網站切換、CEF 命令、INI 與關閉流程，再說明本次最小修改範圍並開始實作。真正的需求／資料流疑問先確認，不擴充其他功能。

## 已確認的產品需求

- 本輪只做 Windows。小熊成為 oaClient2 內建功能；只需執行 oaClient2，不另裝或啟動獨立 pet EXE，不帶回舊 C# 程式、安裝腳本或 Windows 自動啟動登錄。
- **目前站台登入成功後才出現 pet。** 啟動 oaClient2、歡迎頁、未登入或登入失敗時不顯示；頁面載入完成／clientReady 不等於登入成功。登出時立即隱藏並停止通知。
- pet 本體視覺大小約 100 × 100 像素，類似 Codex pet；預設在桌面右下角，可拖曳。考慮 Windows 顯示縮放，避免變成大型視窗。
- 小熊使用已確認的 3D 圓潤金黃色小熊，待機眨眼，有通知時揮手及顯示泡泡。平常不搶鍵盤焦點；透明空白區不擋 Excel 操作。
- 切到 Excel／其他 App 或最小化 oaClient2 後，pet 仍可置頂顯示並接收通知。使用獨立的桌面小視窗，避免隨主視窗最小化而一起隱藏；主網站 CEF 宿主保持原架構。
- 關閉 oaClient2 時，pet、計時器與網路工作一起結束，沿用原本的關閉／登出順序，不改為常駐系統匣繼續運作。

## 站台設定只有一份

- **直接沿用 oaClient2 設定及目前載入的站台，不另設 pet 的網站網址或 API 網址輸入。**
- 沿用現有 `Config.ini` 的 HomeUrl、網站切換流程與目前站台回報的 apiUrl。沒有本輪新的全域預設站台；不要把原本其他客戶的 HomeUrl 改成 Megatower。
- 前一版獨立 pet 的預設 oa.megatowerinc.com、settings.json 與 API 主機推導邏輯均已作廢，不移植進 oaClient2。
- 切站時先停止舊通知工作、清除當次 Token／游標／通知紀錄並隱藏 pet。等待新站台登入成功，取得該站最新 API 資訊及通知存取權後才啟動；不能拿上一站保存在 INI 的 apiUrl 當作新站已確認的 API。
- 沒有通知 API 的站台保持正常使用，不連到其他預設主機補查，也不使網站登入失敗。

## 通知業務範圍與後端

- 監看 BSI020010 客戶詢報價，**只通知單據日期 quadt 為 ERP 後端今天日期的新增／修改**。不是依 crtdtm／upddtm 判斷單據日期。過去或未來日期的單據即使今天修改也不通知。
- 已確認只需 ERP 表單新增／修改成功事件，外部匯入、直接 SQL 或其他系統寫入不在本輪範圍。
- 沿用原通知 API，每 10 秒查詢一次；第一次取得存取權以當下游標為起點，不把今天已存在的單據當成新通知。
- API 依原登入 Session、資料庫與表單／資料列權限授權。保留事件游標、跨日換日、缺口提示與重複通知防護；本機不能用 UTC 日期代替 API 回傳的日期。
- 網頁背景計時器不負責持續輪詢，避免最小化或背景暫停後停收通知。背景工作不得阻塞 CEF UI 執行緒，停止／換站後不套用舊回應。
- 點擊通知後還原並使用 oaClient2 現有主視窗開啟對應單據，不另開系統預設瀏覽器。如果該表單正在編輯，保留未儲存內容，不強制切單、刷新或重新查詢。

## 串接及安全邊界

- 優先由 oaClient2 在可信主框架內注入專用登入觀察與通知接線，沿用既有登入 Session 取得通知 API 存取權；必要資料經 CEF 原生訊息通道交接。
- 不恢復舊版 127.0.0.1 HTTP 橋接，不監聽固定連接埠，也不要求瀏覽器額外允許本機網路。
- 通知 Token 僅留記憶體，不經 console.log、INI、一般命令列、URL 查詢參數、日誌或磁碟檔案。既有 Reptool loginParam 契約保持。
- 新訊息只接受目前可信站台的主框架；核對來源及目前登入／站台世代，避免 popup、iframe、舊網站訊息誤啟動本機功能。
- 既有 loginState 處理目前主要用在關閉登出；本次通知啟停須另接生命週期，保留原本關閉判斷、回應及時序。
- 網路存取只指向目前確認的 API；使用正常 HTTPS 憑證驗證，不關閉憑證驗證、不自動轉交 Token 到其他來源。

## 專案分層與修改邊界

- `src/app/app.cpp`／`app.h`：必要的登入、站台切換、CEF 接線、通知啟停及點擊回到單據。
- `src/common`：可共用的通知狀態／游標邏輯保持唯一來源；不複製現有 INI、UserSet、登入登出或工具列流程。
- `src/platform/windows`：Windows 透明置頂視窗、拖曳、DPI／多螢幕、動畫及原生生命週期，透過平台邊界接線。
- 更新 CMake 及既有資源封裝，把小熊素材編入 Windows 交付；遵循目前圖片內嵌 EXE 的規範，不把應用功能放進 cef/。
- `assets/desktop-helper/bear-sprites.png` 是本輪已確認的唯一角色圖；`preview-idle-wave.gif` 只供對照動作，不代表 Windows 原生顯示已驗證。
- Mac 本輪不啟用 pet、不改 Mac 專屬實作或 .app。共用介面變更須記錄 Mac 待回歸，避免新增未實作的連結相依。
- 目前 oaClient2 原始碼尚未加入任何 pet 實作；不要把資源複製、後端測試或舊 GIF 當作 oaClient2 已完成整合。
- `docs/desktop-helper/server/` 是後端快照／交付參考，不是已部署站台。後端目前不需因內建化改協定；若確有必要改動，先列明原因、檔案及影響範圍。不要只改快照便宣稱正式站已更新。

## 驗證與交付

1. 先跑與變更相稱的 Windows 建置及既有核心測試，確認原 CEF 主網站、注音、內建列印預覽、UserSet／INI、Reptool 及關閉流程相容；未執行的逐項列出。
2. Windows 實測：啟動未登入無 pet、登入成功才顯示、登入失敗無 pet、登出即隱藏、切站不混用 Token 或通知。
3. 實測約 100 像素、透明邊緣、拖曳、置頂、不搶焦點、顯示縮放、多螢幕，以及最小化後在 Excel 上方通知。
4. 使用已明確允許異動的測試環境單據：今天新增／修改會通知；昨天單據今天修改不通知；初始基準不重放、同一事件不重複、跨日／斷線恢復／權限撤回／通知缺口均按協定處理。不為測試直接更改未確認的正式單據。
5. 點通知回到 oaClient2 對應單據；表單有未儲存內容時保留。關閉後確認 pet、輪詢及所有本次工作都停止。
6. 更新本機 Windows 交付版時保留個人 Config.ini、CEF、prg、picture、範本與 Mac 產物；不清理 SDK、下載包或建置目錄。
7. 同步更新 HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md，列出檔案、實際建置／測試證據、未測項目及下一步。本次沒有 commit／push／發布／正式部署授權。

回覆使用繁體中文。程式碼兩格空白縮排、註釋英文，新增註釋格式為 `//yyyy.mm.dd by codex, reason in english`。保持最小修改，保留既有規則。
