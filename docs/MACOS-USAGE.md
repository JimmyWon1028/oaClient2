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

## M14～M17 最新本機交付（2026-10-13）

本機artifacts/macos-arm64/oaClient2.app已套用W27～W29，版本仍0.1.6；移到連結不顯示Chrome左下角提示，登入不詢問保存密碼。指定F1／F2／F3／F4／F9、Option+W、Shift+F、Cmd或Ctrl+F／E／S／N先交網頁，停止指定Chrome fallback，原工具列與F8／F12／列印行為保留。不是停用OA自己快捷鍵；實體功能鍵／Fn與一般注音仍由使用者驗收。

另修正Mac Cocoa delegate的弱參照生命週期，正常重新開啟啟用既有主窗，背景登出期間不顯示新分頁。Release／111項、原生／AJAX表單、兩種快捷鍵頁、UserSet／網站清理與最終ACK1418ms／期限3019ms／reopen關閉回歸通過，詳細範圍與失敗見[PROGRESS](../PROGRESS.md)。正式OA與列印／注音並未因此驗收。

本輪未安裝或更新公開MacZIP，請測本機新.app；Releases仍是M13，沒有本輪功能。完整bundle265檔案／連結與build一致、10份arm64 Mach-O／ad-hoc deep strict核對。SDK／壓縮檔／build保留，Windows資料位置及交付不改。設定測試的CFFIXED_USER_HOME只屬/private/tmp合成環境；正常啟動仍用目前使用者Application Support，不是新增設定欄位或產品路徑配置。

## 2026-10-30：M20～M23 Mac 補齊 W32～W35

Mac 本機 arm64 0.1.6 已沿用共用外部協定／下載政策，Mac 入口補上共用亮色回呼與 Aqua，平台錯誤改為繁體中文及必要數字代碼；不修改系統外觀或 OA 主題。共用來源／Windows 專屬碼未再改，原有 UserSet／INI／附件與平台路徑保持。

Release／CTest 1/1、136項、10份arm64及簽章通過；GET／POST／Blob／popup／右鍵下載、取消／兩目錄／中文及空白名稱／內容／重啟，以及 Ctrl+P 完整預覽另存 PDF 已實測。系統亮暗切換、暗色環境、正式 OA／一般注音／外部程式及所有原生錯誤分支未驗收；一次複合退出殘留列 M24 待定位，兩輪交付最小退出正常，不宣稱全部關閉情境通過。只更新本機 .app，未安裝／提交／推送／發布，SDK／下載包／build保留；公開Mac仍M13、U01未實作。詳見 [本輪結果](../PROGRESS.md)。

## 2026-10-30：M24 Mac Cmd+Q 背景殘留修正完成

M24 已重現並修正：Console 有焦點時 Cmd+Q 未進入原生結束入口，之後關閉全部 Browser／Views 仍可能留下 CEF 主迴圈。Mac sendEvent 現在先讓既有原生選單處理精確的 Command+Q，呼叫原 terminate → 共用登出／隱藏／三秒流程；沒有改寫登出或強制結束程序。

最終 arm64 Release／CTest 1/1、136 checks／0 failures、10 份 arm64 與 deep strict 簽章通過；Console 焦點 Cmd+Q、已啟用 beforeunload、附件取消組合的 ACK619ms／無ACK3032ms及實際交付3043ms期限後皆正常 SHUTDOWN_COMPLETE，主程序／Helper 全部退出。 產品只改Mac main.mm，共用來源／Windows及附件實作保持；暫時診斷已撤回。新簽章測試的鑰匙圈等待另行辨識，僅隔離localhost測試帶官方 --use-mock-keychain，正式產品未加入這個參數。只更新本機0.1.6 .app，未安裝／提交／推送／發布，SDK／下載包／build保留；正式OA／真實鑰匙圈、系統亮暗切換及其他原未驗收範圍保持。詳見 [M24結果](../PROGRESS.md)。

## 2026-11-03：M25 Mac 0.1.7

客戶端Shift+F攔截已取消，本機artifacts/macos-arm64/oaClient2.app已重編為0.1.7，沿用共用W36的INI保存／自動修復。Release／CTest1/1、151項、10份arm64及deep strict簽章通過，純文字頁trusted Shift+F可輸入F；正式OA CPN與其他既有未驗收項目留使用者測試。固定CEF154.0.34 SDK／下載包／build已恢復並保留；只更新本機交付，未安裝／提交／推送／發布，Windows共用變更待目標平台回歸。詳見[進度](../PROGRESS.md)。

## 2026-11-11：M26 Mac 0.1.8

Mac本機交付已同步Windows0.1.8與W38「列印背景圖形預設開啟」，直接編譯唯一共用來源，Mac產品僅同步入口版本。Release／CTest1/1、151項、10份arm64及簽章通過；直接／Blob／清除profile重啟後原生預覽背景均保留。正式OA／MRT與印表機待使用者驗收；SDK／壓縮檔／build保留，未安裝／提交／推送／發布。詳見[進度](../PROGRESS.md)。
