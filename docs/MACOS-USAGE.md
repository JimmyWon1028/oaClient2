# macOS arm64 操作與驗證

2026-10-12，版本 0.1.6。僅 Apple Silicon arm64；使用與 Windows 相同的 common／app 原始碼。

## 開啟與資料位置

將編譯交付的 `artifacts/macos-arm64/oaClient2.app` 拖曳至 Applications，再開啟 `/Applications/oaClient2.app`。完整 .app 包含主程式、Chromium Embedded Framework、五種 Helper、OA ICNS 及八張共用 PNG；拖曳完整 .app 即可，不需額外安裝腳本或外部組態／CEF／圖片。首次啟動會建立本機資料目錄與 Config.ini。兩平台差異見[PLATFORM-PATHS](PLATFORM-PATHS.md)。

| 資料 | 位置 | 規則 |
| --- | --- | --- |
| 程式設定 | ~/Library/Application Support/oaClient2/Config.ini | UTF-8，可手動修改；下次啟動讀取；不寫入 bundle。 |
| 截圖 | ~/Library/Application Support/oaClient2/picture/Snapshot*.jpg | 保留；只擷取 oaClient2 主視窗及開啟的 Console。 |
| 網站資料 | ~/Library/Application Support/oaClient2/browser-profile | ClearCache=Y 時，取得單例 flock 後、CEF 初始化前全清。 |
| log | ~/Library/Application Support/oaClient2/logs/application.log／cef.log | 與 profile 分開；application.log 不記錄登入參數。 |
| SDK／中間建置 | Library/Caches/oaClient2/deps／build/macos-arm64 | 本機非同步目錄，不放入 Dropbox。 |

首次建立獨立的 Mac Config.ini，不匯入 Windows 的個人設定。欄位、UserSet、縮放及 INI 編碼沿用 [Windows 設定說明](WINDOWS-USAGE.md)與[相容契約](LEGACY-COMPATIBILITY.md)。M05 起新安裝的 HomeUrl 預設空白，每次啟動最大化並顯示內嵌本機歡迎頁；按「設定伺服器網址」或下方網址按鈕，確認有效 HTTP／HTTPS 網址後才保存。取消仍停留歡迎頁；已有網址則直接載入，不覆蓋個人設定。ClearCache=N 會依既有設定契約保留網站資料，預設仍是 Y。

INI／picture／logs／profile／instance.lock 統一在 Application Support/oaClient2；清理只限其中 browser-profile，不清理資料根目錄或 bundle。Mac CommitSettingsFile 保留 metadata／xattr，flush 暫存後 rename；真正拒寫不修改 mode／ACL，保留原檔與 tmp。Mac 尚無 Windows 的原檔 fallback，不能將改名失敗說成已成功保存。

## 工具列與系統差異

沿用原圖示與順序：Console、首頁、網址、MAC、瀏覽目錄、截圖、還原比例、縮小、放大。F12 開關下方固定 220 DIP Console；F8 用 TextEdit 開啟實際 INI。macOS 功能鍵設定可能需要 Fn。

- Console 保留獨立 Chrome CefWindow，透過 Cocoa NSWindow 父子關係定位在主網站下方，並使用外層 Views Window handle；沒有改成另一個同窗 BrowserView 或原生主網站宿主。
- Mac 放大／縮小不顯示 Chromium 縮放彈窗，仍使用原生縮放階段、保存 ZoomPercent 並於重啟還原。Windows 相同需求僅記錄為 W22，待 Windows 環境實作。
- URL 對話框為單行全選、藍色提示及置中確定；X／ESC 取消，不修改 INI。確認後由共用流程檢查 HTTP／HTTPS，再保存與載入。
- 「瀏覽目錄」開啟實際 Config.ini 所在資料夾，即 ~/Library/Application Support/oaClient2；F8 開啟其中的 Config.ini 檔案。截圖用 ScreenCaptureKit，只合成主視窗與明確標記的 Console；本輪 macOS 26.7.1 可直接截取本程式視窗。其他系統若要求權限，依系統提示處理。
- 截圖 API 需要 macOS 14 以上；CEF 的技術部署 target 是 12.0，但本輪沒有驗收 12／13／14 等其他系統，不將 target 當成完整最低版本支援承諾。
- M10 起結束選單／關閉按鈕送出 logout 一次後立即隱藏主窗與 Console，背景收到 loginState=0 即退出，否則最多3秒後完成關閉。頁面 beforeunload 不阻擋背景退出，重複關閉不重送。合成已驗證，正式 OA 登出仍待驗收；三秒到期不代表伺服器已登出。
- Windows Reptool 不在 Mac bundle；cmd=prt 明確提示 Mac 報表尚未實作，保留網頁按鈕回復契約。
- hcopen／其他名稱長於 open 且不分大小寫以 open 結尾的協定，交給 OS 已登錄處理器。本機 LaunchServices 查詢沒有 hcopen 處理器，沒有自行安裝或註冊；真實外部開啟未測。

不使用沙箱，未加入 disable-web-security、忽略憑證或額外放寬網站安全旗標。Mac no-startup-window 只抑制 Chromium 自建起始窗口，網站仍由共用 Views 流程建立。

## 本輪驗證與待驗收

M01～M03 為 Release／CTest 1/1、61 項；M05 起為 68 項通過。已觀察正式 OA HTTP 200、最大化、工具列／圖示、Console 焦點／1+1=2／F12、網址預選／ESC、縮放保存／重啟還原、只含本窗口 JPG、正常退出。兩輪真實 CEF localhost 測試確認 INI／Cookie／$usr／回呼、網站資料逐項清除與延遲合成登出；詳細證據見 [PROGRESS](../PROGRESS.md)。

**列印預覽與注音留給使用者測試。** Ctrl+P／macOS Cmd+P 或網頁 window.print 應使用 Chrome runtime 完整內建預覽；固定 CEF 提交含 #3410 PDF 儲存修補，但尚未由使用者確認預覽、PDF 儲存與實體列印。沒有自製 PDF 預覽替代。

使用者於 2026-10-12 確認：額外注音浮動組字窗是 Windows 專屬問題，Mac 不需測試或列為待驗收。上述 Mac 注音測試只指一般輸入與焦點，不包含 Windows 浮窗問題，也不代表一般輸入已通過驗收。

正式 OA 登入／登出、hcopen 外部程式、其他 Mac 系統、多螢幕／視窗移動／最小化、Console 完整焦點回歸與穩定啟動速度基準尚未驗收。Windows 共用來源回歸待執行。

本輪採本機 ad-hoc 簽章，bundle 的 codesign --verify --deep --strict 已通過；沒有 Developer ID／公證／安裝包。CEF 日誌的 validation category 警告仍列為診斷，不能宣稱已完成正式發行簽署。U01 線上更新尚未實作，需求仍保留。

## 建置與更新

依 [ENVIRONMENT](ENVIRONMENT.md)設定本機 CEF_ROOT，執行 `bash scripts/build-macos.sh` 與 `bash scripts/package-macos.sh`。打包只更新 artifacts/macos-arm64/oaClient2.app；M08 已依使用者授權刪除交付旁舊 INI／picture，目前只剩 .app，後續打包不補回。Application Support 現用資料仍保留。Windows artifacts/oaClient2／prg 不變。

更新前正常關閉 oaClient2，再替換 Applications 的完整 .app，保留 Application Support 的 INI／picture／logs；不要手動只換 .app 內的主執行檔而破壞 bundle 簽章。本輪沒有建立自動更新機制。

## M04 新配置驗證

M01～M03 的 app 旁 INI／picture 與 Caches profile 是早期實測配置，M04 使用者最新要求已取代。最新實作與 `/Applications` 首次啟動／設定保存／重啟清理證據記於 [PROGRESS](../PROGRESS.md) M04，Windows 配置維持原契約。

## M10 最新背景關閉結果

Release／CTest1/1、75項通過；最後真實 CEF 合成回應951ms提早退出，無回應3029ms、Console 隱藏、beforeunload 允許及程序正常退出已驗證。交付已更新但未安裝 Applications；Windows 同需求 W23 待在 Windows 環境啟用／實測。詳細見 PROGRESS M10。


## M12 標題列（2026-10-13）

主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

Mac 實機已確認歡迎頁標題，以及 OA 網站「良穎資訊系統」與使用者切換網站後「炬塔資訊系統」兩個不同名稱，均帶實際0.1.6版號。Release／75項通過，交付已更新但未安裝；詳見 PROGRESS M12。


## M13／W26：舊版工具列間距與完整字樣（2026-10-13）

依使用者舊版圖片及現行DFM，右側首頁／網址／MAC／瀏覽目錄／截圖／還原比例／縮小／放大寬度採23／23／40／67／38／61／23／23 DIP，合計298 DIP（原346）。高度仍28 DIP、左Console仍30 DIP；保留原字型、圖示、工具順序及命令。右側按鈕左右內部留白各2 DIP，完整顯示MAC、瀏覽目錄、截圖及還原比例，不以省略號／隱藏文字／縮小字型達成間距。

使用同一份app.cpp，不新增平台工具列副本。Mac已編譯及實機核對完整文字；Windows專屬碼與交付未改，W26留待Windows編譯／實機回歸。Mac只更新交付、不安裝；SDK／壓縮檔／build保留。
