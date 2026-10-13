# Windows／Mac 共用程式碼規則

2026-10-12依使用者要求：代碼不要混亂，共用部分不要重寫；線上更新保留，但尚未實作。

## 共用來源只有一份

- src/common/ini.*：沿用現有INI讀寫、命令解析、字串處理、UserSet與設定還原；不建立Mac專用副本。
- src/common/logout.h：沿用既有登出狀態流程；不另寫Mac版登出邏輯。
- src/app/app.*：沿用網站、CEF回呼、工具列順序、偏好Cookie、縮放與命令處理。平台差異由介面提供，不複製整份app.cpp到Mac。
- assets/：共用OA原圖；Windows資源與Mac bundle封裝各自處理。
- 共用功能測試沿用同一份案例；Windows API測試須拆至平台範圍，不在Mac複製或重寫整份核心測試。

## 平台實作分開

src/platform/platform.h提供共用介面；Win32實作放src/platform/windows，Cocoa／Objective-C++實作放src/platform/macos。CMake明確選擇各平台來源、編譯旗標、依賴與資源，不能把兩平台的入口或系統API一起編譯。

需要平台實作的項目包括程式／資料路徑、CEF載入與子程序配置、設定檔提交、快取目錄清理、Console原生嵌入、URL對話框、截圖、開啟目錄、網路資訊、圖片資源與外部程式呼叫。

如為沿用現有程式而需要抽取平台介面，僅移出系統相依部分並接回原流程；保持原呼叫順序、時機、設定格式及回傳契約。不得以跨平台為由重新設計共用業務邏輯，或在共用檔案到處加入平台判斷。

## 目前仍待拆出的相依

本輪核對Windows 0.1.6來源，Mac尚未開始，不能宣稱已完全跨平台：

- App::OnBeforeChildProcessLaunch目前直接組合cef/libcef.dll及libcef-path，是Windows配置。Mac接手應透過平台介面或平台CEF回呼提供配置，保留其餘共用App，不將Windows DLL路徑帶入Mac。
- INI目前保存Windows Reptool預設路徑。Mac報表未支援的結果及必要預設差異由平台邊界處理；INI解析／UserSet契約沿用，不刪除Windows設定能力。
- Console已呼叫AttachConsoleWindow／ResizeBrowserChild平台介面，Mac實作相應Cocoa行為；保留共用開關及生命週期。
- CMake目前只編譯Windows；新增APPLE分支時沿用共用來源清單，分別處理平台入口、CEF framework／Helper及測試相依。

## 線上更新：保留，尚未實作

線上更新列為後續功能，Windows／Mac均保留。共用的版本判斷、下載及更新流程後續設計為唯一來源；平台層處理EXE／app bundle替換、程序退出及重新啟動差異。這是規劃邊界，目前沒有更新模組或可用的自動更新功能。

更新來源、版本規則、CEF是否一併更新、檔案驗證與安裝／重啟流程尚待設計。更新時須沿用既有資料保留要求：不覆蓋個人Config.ini、picture或使用者維護的prg，不補回已刪除工具。

## 驗證與交接

修改共用來源後，記錄實際差異及Windows／Mac各自的編譯、測試結果。尚未回到另一平台測試時明列待回歸，不能宣稱兩平台均正常。切換電腦前停止編輯／建置與Git操作，等待Dropbox同步完成。

Windows交付使用artifacts/oaClient2，Mac交付使用artifacts/macos-arm64；中間建置與CEF SDK各自保存在本機非同步目錄。

使用者最新指定平台開發環境：Mac 專屬程式碼在 macOS 開發，Windows 專屬程式碼在 Windows 開發；目標平台的編譯與實機驗證分別執行。共用來源保持唯一，可為當前平台做必要修改並記錄另一平台待回歸；不得為分工再複製共用功能。

M05／W21 的歡迎頁保留單一 src/common/welcome.h 與 app.cpp 按鈕流程，直接編入應用程式，不需要外部 HTML 檔。Mac 入口啟用空白網址；Windows 入口及預設調整待回 Windows 完成，不在 Mac 修改 Windows 專屬來源。

## M02 移植後現況（2026-10-12）

以上「仍待拆出」段落保留首次盤點背景；本輪已最小抽取 DLL 子程序／Console handle／座標及字型到 cef_platform.h 與兩平台實作，CMake 已有 Windows／Mac 分支。common／app 未複製；Mac 入口只接共用 App。app.cpp 新增 browser 生命週期診斷，不更改 INI／命令／Cookie／登出順序。

Windows platform.cpp、main.cpp／報表及打包腳本未改，新增 Windows cef_platform.cpp 保持原行為；MSVC／Windows 實機回歸待執行。核心測試用同一 core_tests.cpp，Windows 原生案例移到 windows_tests.cpp，Mac 原生案例在 macos_tests.cpp。線上更新仍未實作。

## M04 路徑差異

兩平台 INI／UserSet 格式與實作不變；GetAppPaths 提供 Windows EXE 旁 INI、Mac Application Support INI。共用截圖呼叫 PictureDirectory，Windows 返回 EXE/picture，Mac 返回資料根/picture。不得為 Mac 配置另寫一份 common 或把 Application Support 硬編碼到共用 app；Windows 接手依[PLATFORM-PATHS](PLATFORM-PATHS.md)核對。

## M10／W23 共用關閉模式

common/logout.h／app.cpp 保持唯一關閉來源，新增可選 BackgroundGrace：logout一次、立即隱藏、回應提早完成或最多3秒，CEF任務及原狀態格式沿用。Mac 入口啟用 background_logout_close；Windows 預設 false、原輪詢流程保留，W23 留待 Windows 環境處理。CefWindow 隱藏與 CEF JSDialogHandler 共用介面不加入 Win32／Cocoa 直接相依；Mac relaunch 平台差異留 main.mm。Windows 專屬來源未改，但共用介面／測試新增後 Windows 編譯與實機回歸待執行。


## M11／W24：瀏覽 Config.ini 所在目錄（2026-10-13）

使用者已重新定義兩平台「瀏覽目錄」：開啟實際 Config.ini 的父目錄，取代主程式目錄。共用 app.cpp 直接使用 paths.config.parent_path()，工具列提示同步更新，不複製平台工具列、不更改 INI 配置。Mac 目標為 ~/Library/Application Support/oaClient2；Windows 目前 INI 與 EXE 同目錄，W24 留待 Windows 編譯／實機回歸與交付更新。Windows 專屬程式碼在 Windows 環境修改，本輪未動 Windows 專屬碼；Mac 只更新交付 .app，不安裝 Applications。


## M12／W25：網頁資訊與版本標題（2026-10-13）

主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

共用 app.cpp 保持唯一來源，Windows 專屬碼及交付不在 Mac 改；W25 留待 Windows 編譯／實機回歸。Mac 本輪重新編譯只更新交付，不安裝，保留 CEF SDK／壓縮檔／build。


## M13／W26：舊版工具列間距與完整字樣（2026-10-13）

依使用者舊版圖片及現行DFM，右側首頁／網址／MAC／瀏覽目錄／截圖／還原比例／縮小／放大寬度採23／23／40／67／38／61／23／23 DIP，合計298 DIP（原346）。高度仍28 DIP、左Console仍30 DIP；保留原字型、圖示、工具順序及命令。右側按鈕左右內部留白各2 DIP，完整顯示MAC、瀏覽目錄、截圖及還原比例，不以省略號／隱藏文字／縮小字型達成間距。

使用同一份app.cpp，不新增平台工具列副本。Mac已編譯及實機核對完整文字；Windows專屬碼與交付未改，W26留待Windows編譯／實機回歸。Mac只更新交付、不安裝；SDK／壓縮檔／build保留。


## 2026-10-13：Windows W21～W26 接續結果

Windows入口已啟用空白HomeUrl／allow_empty_home_url、hide_zoom_bubble及background_logout_close；W24設定父目錄、W25網站動態title與0.1.6版本、W26右側298 DIP／完整字樣直接編譯原共用app.cpp。共用來源沒有複製或重寫，Mac專屬碼與交付未改。

Windows MSVC Release／CTest1/1、74項與本輪歡迎頁、網址／縮放重啟、ACK／三秒期限／Console／beforeunload／全部退出、UserSet／網站儲存、目錄／動態標題／完整字樣實測已完成；詳見[最新Windows結果](../PROGRESS.md)。正式列印／Microsoft注音／OA登出／Reptool及間距待使用者驗收，未測情境以進度為準，U01未實作。

交付artifacts/oaClient2/oaClient2.exe與安全範例已更新；Windows INI／picture仍在EXE旁，CEF仍在cef/，prg不補回／覆蓋。正式INI最後正常關閉更新Window後保留現況；不宣稱逐位元不變。SDK／壓縮檔／build保留。本輪未提交／推送／發布，固定v0.1.6 Tag不動，後續Git／R02仍依使用者授權。前段Windows「尚未啟用／待回歸」是此次接續前狀態。


## W27：共用連結狀態泡泡設定

chrome_status_bubble=STATE_DISABLED僅設在共用app.cpp的CEF BrowserSettings，不另寫Windows／Mac選單或修改OA JS。Windows已編譯／合成實測並交付；Mac專屬碼／產物未動，回macOS重編／實測後才生效，不能將Windows結果當成Mac驗收。


## W28：共用密碼保存政策（2026-10-13）

共用App::OnContextInitialized在建立任何頁面前透過CEF RequestContext.SetPreference停用credentials_enable_service／credentials_enable_autosignin；不使用舊版失效switch、不複製平台登入邏輯或修改OA JS。Chromium偏好定義見[官方來源](https://chromium.googlesource.com/chromium/src/+/HEAD/components/password_manager/core/common/password_manager_pref_names.h)，本機固定CEF154已成功套用／實測。既有UserSet／userid與啟動專用profile清理保持；false停止詢問保存，不以此單一偏好宣稱所有既存密碼自動填入皆已禁用。Windows完成、Mac待macOS重編／實測，Mac產物未更新。

## W29：唯一共用快捷鍵政策

common/keyboard.h只定義使用者指定的Chrome衝突鍵；app.cpp透過SetPreferAccelerators(false)與OnPreKeyEvent／OnKeyEvent使網頁先收到真實事件，再停止指定Chrome fallback，不用ExecuteJavaScript重送假按鍵。原高優先F8／F12／Ctrl+P保持。CEF154 API及來源已核對，Windows編譯／110項通過，UI矩陣依使用者要求留其驗收；Mac平台碼／產物未改，Cmd實機回歸未執行。使用者提供的f1.js是清單資料，未修改／執行／納入Git。
