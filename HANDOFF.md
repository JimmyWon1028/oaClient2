# oaClient2 接續交接

最新公開發布 R03（2026-11-12）：[v0.1.8測試版](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)已提供Windows x64／Mac arm64 ZIP及SHA256，公開下載校驗通過。Tag固定a3de8b3，v0.1.6保持，詳見末段及[Release文件](docs/RELEASES.md)。

最新 Mac M26（2026-11-11）：已沿用Windows W38列印背景預設並更新本機arm64 0.1.8 App。Release／151項／簽章及直接、Blob、重啟原生預覽實測通過，正式OA／印表機待驗收，未安裝／發布。詳見末段。

最新 Mac M25（2026-11-03）：已取消客戶端 Shift+F 攔截並更新本機 arm64 0.1.7 App。Release／CTest1/1、151項、簽章及純文字頁大寫F實測通過；正式CPN留使用者驗收，未安裝／發布。詳見末段。

最新 Mac M24（2026-10-30）：背景殘留已修正並更新交付。Console 焦點 Cmd+Q 先走既有原生結束選單；ACK619ms／無ACK及附件取消複合回歸皆完整退出。最終 Release／136項與簽章通過，未安裝／發布。詳見末段及 [進度](PROGRESS.md)。

最新 Mac M20～M23（2026-10-30）：W32～W35 已沿用／補齊並更新本機 arm64 交付，Release／CTest1/1、136項及簽章通過；正式 OA、系統亮暗切換等仍待驗收，複合退出曾殘留一次（M24），詳見末段及 [進度](PROGRESS.md)。未安裝或發布。


最新文件 D04（2026-10-30）：已將 Windows W32～W35 修改彙整於 AGENTS／README，新增 [Mac 接續提示詞](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)。本輪只更新文件，Mac 尚未實作／建置；W35 的 Windows 實測限制保持，詳見末段。


最新 W35（2026-10-29）：Windows 匯出／下載啟用每次詢問儲存位置，沿用 Chromium 原生另存新檔。Release／CTest1/1、143項及 GET 匯出對話框跳出實測通過，選路徑後存檔／取消等因UI工具限制未完成實測；本機0.1.6 EXE已更新，未提交／發布。Mac需目標平台重編回歸，詳見本文末段。


最新 W34（2026-10-28）：Windows 與共用來源的自訂錯誤提示已改為繁體中文；Release／CTest1/1、143項及重複啟動對話框實測通過，本機0.1.6 EXE已更新。Mac專屬訊息待macOS處理，未提交／發布；詳見本文末段。


最新 W33（2026-10-20）：依使用者要求，Windows上方標題列／下方工具列固定亮色、不跟隨系統主題。入口啟用共用fixed_light_window_appearance，初始化強制原生／Chrome亮色，主題回呼重套工具列淺灰底與深色字。Release／CTest1/1、143項通過，歡迎頁視窗亮色及文字圖示正常、測試版已退出；Windows系統亮暗切換實測未執行（設定視窗工具啟動失敗），未改系統設定。本機0.1.6 EXE已更新，SHA256 `3890581dc08216046c3c7dab87b0bef945ce7b22fda3e0886608eb17821b3d53`。Mac旗標預設false、平台碼／產物未改，共用介面須macOS重編回歸；未提交／推送／發布，詳見[進度](PROGRESS.md)W33。

最新 W32（2026-10-20）：外部協定改為 `[其他字樣]open[可選其他字樣]`，不分大小寫；`hcopen:///`、`hcopenprint:///`、`wjopen:///` 均放行。只沿用 CEF `allow_os_execution` 交給系統，不查登錄或外部程式、不解析 URI 內容。Windows Release／CTest1/1、143項通過，本機0.1.6 EXE已更新；SHA256 `3a03b124a48864af570f6ba070b332fb25c95b9a1d84d076394ca11c2df1e6f3`。外部啟動由使用者測試，Mac須在macOS重編回歸；未提交／推送／發布。詳見[進度](PROGRESS.md)末段。

最新 W31：Windows 附件已修正並更新本機0.1.6 EXE；MSVC／CTest1/1、123項及原生實測通過，正式 BSI010010 待使用者驗收。沒有提交／推送／Release更新；詳見末段。

Windows 附件選檔接續：已建立[Windows 附件選檔修正提示詞](docs/WINDOWS-FILE-DIALOG-2026-10-16-PROMPT.md)（W31 待 Windows 實作／驗證；本輪僅文件）。

2026-10-16：M19 Mac 附件選檔修正已建置、更新本機交付，使用者回覆「我剛剛測試 oaclient2 附件 正確」。預設 Custom Files 合併網頁允許格式，另提供 All Files；版本仍0.1.6，未提交／推送／發布。詳見末段。

最新Windows W30已由使用者驗收、提交／推送並同版更新公開ZIP；版本0.1.6、Tag與Mac資產保持，詳見末段。Mac新共用關閉保護仍須在macOS編譯回歸。

更新：2026-10-13。這是 Windows／Mac 上 Codex 的接手入口；以下歷史狀態以最新交接段為準。

**最新 Mac 交付：M14～M17 已完成本輪 arm64 建置與合成實機回歸。** W27～W29已沿用同一份 common／app 套用到 `artifacts/macos-arm64/oaClient2.app`，版本仍0.1.6；Release／CTest1/1、111項通過。另最小修正Mac Cocoa delegate生命週期與背景reopen，最終ACK1418ms／期限3019ms、關閉中Finder再開啟兩次及全部程序退出通過。詳見本文末段與[進度](PROGRESS.md)。尚未安裝、提交／推送或更新公開MacZIP，公開下載仍為M13；後段Mac待重編為本輪前歷史。

下一輪 Mac 接續可直接複製 [2026-10-13 Windows 共用功能提示詞](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)，主要為 W27～W29，Mac 已有的 M01～M13只回歸、不重做。切換前仍須停止 Windows 編輯／建置／Git並等Dropbox同步；本輪提示詞及交接更新尚未提交／推送，不以遠端 reset 覆蓋這些文件。

目前最新Windows本機與GitHub交付皆為W29快捷鍵修正，EXE SHA256為b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6；MSVC／CTest1/1、110項通過，使用者已回覆「可以了」。來源6f2833b已推送，同名ZIP／校驗檔已替換且公開下載核對，ZIP SHA256為849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046；Tag／Mac資產未變，Mac W27～W29仍待目標平台回歸，詳見本文末段及[RELEASES](docs/RELEASES.md)。

2026-10-13最新結果：依使用者先commit、push再發布的順序，W21～W27來源7958a60已推送，Windows x64 ZIP與.sha256已加入既有[v0.1.6 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)，公開下載校驗通過；Tag與Mac資產未變。發布文件與可重現打包腳本另行提交，最新main以Git核對。完整R02結果見本文末段及[Release文件](docs/RELEASES.md)。

## 2026-10-13 Windows W21～W26 最新交接

- 使用者已確認Mac停止操作、兩台Dropbox同步完成；本輪Windows從main／遠端59a323a接手，無lock／來源衝突。
- Windows入口已啟用空白HomeUrl歡迎頁、隱藏縮放彈窗與背景登出；W24～W26直接沿用共用app.cpp，沒有修改或複製src/common／src/app、Mac專屬碼或Mac產物。
- MSVC Release／CTest1/1、74項通過；空白歡迎頁、兩個網址入口、ESC／無效URL、HTTP保存重啟、110%重啟、ACK649／1117ms、無回應3007ms、Console隱藏／beforeunload／全部程序退出、兩輪UserSet與完整網站儲存清理、設定目錄／動態標題／完整工具列字樣已在Windows實測。詳細結果、未測項目及工具環境失敗見[進度](PROGRESS.md)最新W21～W26段。
- 交付入口仍是artifacts/oaClient2/oaClient2.exe，SHA256：9b60d756ee39ca6dc3725e4e608f3d63ac18f1602b69c9bf43c53d32fc7daed2；僅更新EXE與設定範例，CEF234份一致、使用者精簡prg／picture／tpl與Mac交付不變。正式INI最後正常關閉更新Window欄位後保留現況，不回寫測前內容。Windows位置不改，SDK／壓縮檔／build保留。
- 正式交付已啟動OA並正常關閉；localhost伺服器及全部oaClient2程序已停止。測試INI已還原；列印預覽／Microsoft注音、正式OA登出／Reptool及最終工具列間距待使用者驗收，U01未實作。
- 本輪未提交／推送／發布；已有Mac Release不需再發。v0.1.6仍指向0fe6f35，不移Tag。後續Git與Windows R02發布依使用者授權；切回Mac前仍需停止操作並確認同步。

## 目前完成到哪裡

Windows x64 簡易版0.1.6已實作及建置，交付入口為 `artifacts/oaClient2/oaClient2.exe`；0.1.6依使用者要求改為不使用沙箱的獨立EXE，CEF執行元件全部在相鄰 `cef/`，沒有應用DLL或CEF目錄內的應用EXE。0.1.1 的Microsoft注音浮窗已於0.1.2修正，使用者確認「已正常，沒有額外浮動組字窗」。0.1.3將8張視窗／工具列PNG內嵌EXE並移除外部交付副本，主網站宿主保持相同。0.1.0列印預覽曾通過使用者測試，最新版尚未再次驗收。其他實測與限制見 [PROGRESS.md](PROGRESS.md)。

**macOS arm64 0.1.6 已實作、建置與初輪實機測試。** 交付入口為 `artifacts/macos-arm64/oaClient2.app`，M04 起 `.app` 安裝在 `/Applications`，`Config.ini`／`picture`／logs／profile／lock 在 `~/Library/Application Support/oaClient2/`；正式首頁、Console、設定、截圖及兩輪合成儲存／登出已測，列印預覽與注音待使用者驗收。CMake 現有 WIN32／APPLE 分支，Mac 僅 native arm64；Windows 共用來源回歸待執行。詳見 [Mac 操作](docs/MACOS-USAGE.md)、[驗證](PROGRESS.md)及[環境](docs/ENVIRONMENT.md)。

Git：main，已有ddf1bf9／655a6a1本機提交；使用者已授權建立公開repository https://github.com/JimmyWon1028/oaClient2、提交最新文件並推送，origin已建立。亦已授權Mac ZIP Releases與v0.1.6 Tag，Windows後續於Windows環境編譯測試再補齊。實際SHA與發布結果依Git／GitHub核對，後續操作仍依使用者授權。Windows CEF SDK／建置產物在本機 LocalAppData，不在 Git；交付資料夾是使用者核准的 Dropbox 同步例外。歷史段落的「無提交」是首次提交前狀態。

2026-10-12 使用者補充：注音額外浮動組字窗是 Windows 專屬問題，Mac 不需測試該項，也不列為待驗收。本文 Mac 的「注音驗證」只指一般輸入與焦點，不包含 Windows 浮窗問題；未因此宣稱 Mac 一般注音已驗收。

M04 最新組態以[平台路徑對照](docs/PLATFORM-PATHS.md)為準：Windows INI／picture 仍在 EXE 旁，Mac 才使用 Application Support。共用 INI 格式／UserSet 流程不變。後面 M01～M03 的 app 旁路徑是早期實測歷史。

## 接手順序與來源

1. 核對 Dropbox 已同步完成、Git 分支與 status、衝突副本；不要兩台同時修改來源或 .git。
2. 讀 AGENTS.md → 本文件 → PROGRESS.md → PROJECT-PLAN.md → CHANGELOG.md。
3. 讀 [操作／INI](docs/WINDOWS-USAGE.md)、[版本／建置](docs/ENVIRONMENT.md)。

使用者在 Mac 新對話可直接複製 [Mac 接續提示詞](docs/MAC-CODEX-PROMPT.md)。此檔已包含 0.1.6、不使用沙箱、picture 與跨平台隔離要求；建立提示詞不代表 Mac 已開始實作。

| 檔案 | 現有內容 |
| --- | --- |
| src/common/ini.* | UTF-8 INI、設定、只更新視窗欄位、命令解析、JS 字串跳脫；可共用。 |
| src/app/app.* | 主網站Views Chrome BrowserView、工具列、獨立ConsoleWindow嵌入、圖示資源讀取、縮放載入套用、命令處理。 |
| src/platform/platform.h | 平台邊界：路徑、清理、INI 原子替換、開啟資料夾、截圖、網路資訊、Console父視窗／尺寸、URL對話框、內嵌圖片讀取、報表呼叫。 |
| src/platform/windows/main.cpp | 獨立EXE的wWinMain；CefScopedLibraryLoader載入cef/libcef.dll，CefExecuteProcess、單例鎖、初始化前清理、CEF生命週期；明確no_sandbox=1。 |
| src/platform/windows/platform.cpp | 所有Win32、Shell、GDI+、網路API、AttachConsoleWindow、PromptServerUrl、ReadApplicationImage及清理保護。 |
| src/platform/windows/application_images.rc／oaClient2.exe.manifest | 主程式內嵌OA圖標、8張PNG RCDATA及Windows相容／DPI manifest。 |
| src/platform/windows/app.rc／resources.h | Win32 URL對話框及資源ID；PNG ID301～308。 |
| assets/ | 舊 oaClient MAINICON 與工具列圖示；來源說明見 README。 |
| scripts/ | Windows 建置及完整交付拷貝。 |
| tests/core_tests.cpp | 共用核心來源；Windows API 案例已移至 windows_tests.cpp，Mac 平台案例在 macos_tests.cpp；Mac 61 項通過，Windows 回歸待執行。 |
| tests/pages/acceptance.html | 列印／輸入／網站資料測試素材；不是已驗收的逐項結果。 |

## CEF 與 Console 的關鍵限制

Windows 使用 CEF 154.0.34+g14c5a08+chromium-154.0.8037.98 standard、C++20、MSVC v143。完整工具與雜湊見 ENVIRONMENT.md。

本輪實測確認：CEF 154 的 DevTools 強制 Chrome style；一個 Views Chrome Window 不能放兩個 Chrome BrowserView。直接把 DevTools BrowserView 放在主 Window 會改變主視窗，所以已撤回該實作。

現行主網站為CEF Views Chrome BrowserView，恢復0.1.0經使用者驗證正常的宿主；0.1.1將主網站改為原生Chrome子視窗後，Microsoft注音出現額外浮動組字窗，該方案已撤回。不能為Console再次改回該主網站宿主。

Console透過OnBeforeDevToolsPopup指定非default window，OnPopupBrowserViewCreated為DevTools建立獨立、無框Chrome CefWindow。Windows AttachConsoleWindow調整該獨立Console視窗的style與SetParent，嵌在主視窗下方220 DIP區域；僅Console使用原生重設父視窗，主網站不做。ResizeChild將DIP換成像素，ConsoleClient維護開關／關閉生命週期。

Mac需為Console設計及驗證Cocoa父視圖、座標、焦點與關閉生命週期；不能複製Win32 HWND／SetParent操作，不能把被撤回的Alloy DevTools當成可用方案，也不能自行改為PDF列印預覽替代需求。若Mac無法相同嵌入，先完成查證與具體替代介面再與使用者討論。

## 封裝、圖片與設定契約

- Windows根目錄oaClient2.exe包含應用功能，直接執行wWinMain；不使用bootstrap或應用DLL。USE_SANDBOX=OFF、CefSettings.no_sandbox=1由使用者明確選定（只跑ERP），不要自行改回沙箱。CEF官方runtime檔案全部在cef/且不混入應用檔；根目錄不需要chrome_elf.dll。Config.ini及picture由GetAppPaths定位至EXE同目錄。
- Windows8張圖片以RCDATA編入application_images.rc；ReadApplicationImage用LoadLibraryExW資料資源旗標讀root EXE，FindResourceW採resources.h的301～308，不重新執行EXE。主網站和工具列由記憶體AddPNG，無外部PNG依賴。assets仍是共用來源。
- Mac必須實作同一ReadApplicationImage平台介面，用原圖封裝到app bundle的Resources或其他內嵌資源；不能讀Windows EXE或要求圖檔放在主程式外部目錄。Windows RC／manifest不進Mac編譯。
- URL為Windows原生DialogBoxParam對話框，單行預選HomeUrl、藍色提示、置中確定，X／ESC取消；Mac須實作相同PromptServerUrl行為。
- UserSet.ZoomPercent百分比立即保存；OnAfterCreated與主框架OnLoadEnd套用。0.1.2實測150%保存、重啟還原成功；0.1.3一般啟動100%→110%→100%保存成功，最終保留100%。
- Codex封裝宿主啟動可能繼承套件重導向，使data與profile實體父路徑不一致；現行校驗正確拒絕並記PROFILE_PATH_REJECTED，不放寬清理界線。0.1.3改由Windows檔案總管啟動已確認網站與內嵌圖片正常。不要用不一致的工具環境路徑判斷用戶實際資料。

## Mac 第一批工作

- M01：確認 Apple Silicon、Xcode／Command Line Tools、CMake／Ninja；下載 arm64 CEF，核對版本與雜湊，固定本機依賴目錄。
- M02：新增 src/platform/macos 主入口與平台函式，支援 ObjC++、CEF framework loader、主 app／Helper app bundle、資源與沙箱要求；更新 CMake 的 APPLE 分支。
- 專用 profile／log 放在 Mac 使用者本機目錄，不能清理 Windows 資料、INI、picture 或報表檔案。
- 使用者最新要求 Config.ini 放在主程式同目錄。Mac 的 .app bundle 與相鄰外部 Config.ini 定位需明確設計；不要直接把 Windows 交付資料夾的個人 INI 或 Windows ReptoolPath 當成 Mac 設定，也不要把可修改 INI 寫入已簽署 bundle。
- 共用assets的OA圖示，產生macOS bundle圖示，並實作ReadApplicationImage與8張圖片的bundle資源封裝。工具列順序與首頁／Console 開關契約保持。
- Windows Reptool.exe 不可在 Mac 原生執行；Mac 報表方案仍待討論，平台函式應提供清楚未支援結果。
- M03：實測正式網站、內建列印預覽（含 PDF 儲存及 CEF #3410 配套）、注音、重新開啟網站資料清理、INI 保留、啟動時間、Console／工具列、關閉及多螢幕 DPI。
- Mac 修改共用來源後，標示 Windows 回歸尚未執行；回 Windows 再建置並驗證，勿假稱兩平台通過。

所有依賴、CMakeCache、.app／framework 建置輸出放在 Mac 本機非同步目錄，例如 ~/Library/Caches/oaClient2/build/macos-arm64。Mac 交付使用獨立 artifacts/macos-arm64；不另建分岔專案。

## 尚未完成

尚未承接的舊命令、正式UserSet登入回填／關閉登出、實際 Reptool 驗收、完整網站儲存逐項清理回歸、啟動速度與舊版同條件基準、各輸入法／DPI／印表機、Console 分隔線拖曳、正式程式碼簽署與安裝包均未完成。不要把簡易版、成功編譯或使用者整體回報擴大為全部驗收。

## 0.1.4 Mac接手增補

- 先讀docs/LEGACY-COMPATIBILITY.md。ini.*已提供SectionValues／SaveUserSetting／UserSettingsScript／SerializedUserSettings／EncodeCookieValue及相對程式路徑，保持鍵名大小寫、空值和資料字串跳脫。
- App在建立BrowserView前等待CEF Cookie manager，將UserSet偏好設成新的當次Cookie；初始化完成才載入網站，讓主題／語言／userid讀取時機正確。OnLoadStart／OnLoadEnd及clientReady回填$usr與原win_client契約。不能改成還原整個舊網站profile／Cookie。
- common/logout.h狀態流程可共用；WindowDelegate.CanClose透過BrowserClient.PrepareWindowClose及CEF500ms任務等待登入狀態與logout，最多20輪，不阻塞主執行緒；頁面若沒有全域getLoginState則讀$g.isLogin。loginParam只在記憶體。
- BrowserClient.GetRequestHandler／GetResourceRequestHandler與LegacyProtocolHandler沿用舊…open規則，作業系統須已有處理器。Mac必須實測LaunchServices與相應外部程式，不複製Windows協定登錄或exe。使用者表示Windows hcopen由其測試。
- 根prg是使用者要求複製的12份Windows外部工具，Git忽略、Dropbox同步，SHA256見docs/PRG-INVENTORY.md。Windows交付prg現已由使用者精簡維護，打包不再同步來源；默認prg/Reptool.exe，相對路徑從主程式根解析，工作目錄同根，INI參數維持。Mac報表方案仍待討論。
- 新測試tests/report_receiver.cpp為Windows合成程序，驗證兩參數、UTF-8與工作目錄，不能加入Mac編譯。tests/pages/legacy-contract.html＋tests/serve-contract.py可用於目標平台CEF設定／重啟／合成登出測試；當前只有Windows結果，53項核心與本機CEF已通過。

## 0.1.5 設定保存接續

- IniFile.Save先比對將輸出的UTF-8／LF內容；內容完全相同則成功返回，不建立暫存或再替換。比對讀取handle在提交前關閉，避免自身讀取鎖影響rename。
- 平台介面AtomicReplace已更名CommitSettingsFile。Windows既有檔優先ReplaceFileW保留ACL／streams；新檔MoveFileExW。若僅是access-denied／sharing／lock／unable-remove且既有檔仍可讀寫，使用OPEN_EXISTING，不預先truncate；持有handle排除其他writer，讀取原資料、寫入完整新資料、調整EOF、flush。寫入錯誤嘗試回復原內容，保留暫存供恢復；真正唯讀不解除屬性、真正權限拒絕不冒充成功。
- 無法rename時的原檔寫回不是atomic replacement；不要在Mac照搬Win32權限／同步策略。Mac需實作同名CommitSettingsFile，常規情況使用平台的安全替換，保留INI和文件約定。
- 核心62項新增不允許delete的reader鎖、原檔identity、短內容截尾、未改變內容及readonly真正失敗等檢查。舊0.1.4的53項是歷史結果，0.1.5不宣稱Mac已驗證。

- 0.1.5關閉Config.ini error5修正交付後，使用者回覆「可以」；該修正已獲確認。保留此保存流程，不將回覆擴大為其他功能或Mac已測試。

## 0.1.6 Mac接續與部署

依使用者最新明確選擇，不使用沙箱、只用來跑ERP；Windows採單EXE並將原始CEF runtime隔離cef/。先前root chrome_elf副本方案未實作，不自行改回launcher／DLL布局。主入口使用官方CefScopedLibraryLoader，OnBeforeChildProcessLaunch傳libcef-path；這是Windows專屬，Mac須以Framework／Helper設計獨立接續並驗證，沒有Mac編譯或實測結果。截圖使用picture；INI／圖片／prg／使用者其他資料均不能在打包或清理時覆蓋刪除。

當前本機建置目錄為windows-x64-standalone，舊windows-x64-toolbar只作歷史產物，不再交付。最新版交付EXE雜湊、62項與實機驗證見PROGRESS.md。CEF版本及外部相依不變時，一般功能只替換根EXE；CEF版本升級須完整更新cef。

- 0.1.6本輪實機正常關閉，無INI錯誤／tmp殘留；交付Config.ini與原設定SHA256一致。未登入，不能把此次關閉擴大為正式伺服器登出驗收。

- 0.1.6正常關閉後由檔案總管再次啟動，OA首頁與工具列正常；最新版目前已開啟供使用者測試。

## Windows交付目錄最新要求

2026-10-12使用者已將artifacts/windows改名為artifacts/oaClient2，以便直接壓縮完整資料夾。新的Windows入口為artifacts/oaClient2/oaClient2.exe，打包腳本已同步；不要重新建立舊windows目錄。Mac交付仍為artifacts/macos-arm64。應用依EXE相對位置定位CEF、INI與picture，這次不需修改程式或重新編譯；未宣稱新路徑啟動已重新實測。

## 交付prg由使用者維護

2026-10-12使用者已刪除Windows交付prg不需要的檔案，並明確指示「不要再補回來」。核對artifacts/oaClient2/prg只保留docto.exe、Reptool.exe、TSCLIB.dll、zint.dll。package-windows.ps1已移除整份來源prg複製，後續打包不補回、不覆蓋或清理交付prg。根prg保留歷史副本，不能用來自動恢復；新交付目錄的工具由使用者另行準備。

## 共用來源不重寫與線上更新

2026-10-12使用者明確要求代碼不混亂、共用部分不要重寫。接手必讀[共用程式碼規則](docs/SHARED-CODE-RULES.md)，直接沿用src/common及src/app，不複製成Mac專用版本。現行App::OnBeforeChildProcessLaunch仍含Windows DLL配置，僅透過必要平台介面抽取處理；保留共用流程、回呼時機、設定與回傳契約，不做全面重構。此次只核對來源與落地規則，未移動或修改任何程式碼。

U01線上更新必須保留，但尚未實作。共用更新流程後續設計保持一份，平台處理程式替換及重啟；來源、版本及安裝策略尚待設計。Mac提示詞已加入此需求，本輪不實作更新模組。

## M01～M03 最新接續（2026-10-12 Mac）

- 現有 Mac 平台入口／platform.mm／cef_platform.cpp／Helper／Info.plist 在 src/platform/macos；CMake 直接編譯原 app.cpp／ini.cpp，沒有另造共用副本。Windows DLL 子程序、Console handle／座標及字型移至 src/platform/cef_platform.h 的最小平台介面。
- Mac Console 是 Cocoa NSWindow child window，保留 CEF 自己的 view／window ownership；定位用外層 Views CefWindow，不能改用內層 WebContents NSView.window。主網站 Views 宿主不改。截圖只合成主窗口與明確標記的 Console，不含其他 Chrome 輔助窗口。
- CEF 仍是與 Windows 相同的 154.0.34+g14c5a08 stable，arm64 standard 已校驗；固定提交的 mac_print_preview_modal 修補包含 #3410。Framework／五種 Helper／八張 PNG／ICNS 封裝在 app，Mac 不讀 Windows EXE／DLL／prg。
- SDK／build／profile 在 Mac 本機 Library/Caches/oaClient2，各位置見 ENVIRONMENT；用 bash scripts/build-macos.sh／package-macos.sh 重現。交付只同步 artifacts/macos-arm64，Windows 交付未改。
- 一般保存用同一份 ini.cpp；Mac CommitSettingsFile 保留原 metadata／xattr、fsync 暫存後 rename。唯讀／ACL 拒寫明確失敗，不解除保護。Mac 未實作 Windows 的原檔寫回 fallback，rename 失敗保留 tmp；不是假稱所有同步鎖情境已通過。
- profile 全清需允許 Chromium 根層四種自身連結的 unlink，禁止追蹤它們，其他 symlink 仍拒絕。單例 flock 在清理前取得；不要對整個 Library/Caches 或 .app 旁目錄清理。
- 最終 Release／CTest1/1／61 項與兩輪真實 CEF 合成契約通過，含 Console 關閉、Cookie／Local Storage／IndexedDB／Service Worker／Cache Storage 清理、INI／picture 保留與延遲登出。正式 OA 登入及登出未驗收。
- Windows 回歸待執行：CMake 新平台分支、新 Windows cef_platform.cpp、app.cpp 必要介面呼叫、tests/core_tests.cpp／windows_tests.cpp 分離及更新測試素材。不要將 Mac 編譯當成 MSVC 成功。
- 列印與注音由使用者測試；hcopen 本機無 LaunchServices 處理器，實際 OS 外部開啟未執行。Mac Reptool 及 U01 更新仍未實作。正式 Developer ID／公證與其他 Mac 系統、多螢幕回歸未做。
- 早先段落是 Windows 交接時的歷史；Mac 現況以本節、PROGRESS M01～M03 及 MACOS-USAGE 為準。

- 最終交付版已從artifacts/macos-arm64實機啟動：正式OA HTTP200、100%、app旁INI／picture、Finder路徑及網路資訊均核對；目前保留首頁供使用者測試。首次主框架41710ms，啟動速度改善尚未證實，需另行量測與分離原因。

## M04：Mac 組態與拖曳安裝

- 使用者確認 Mac 只有完整 .app，拖曳到 Applications 即可；首次啟動以平台 API 建立 Application Support/oaClient2，再由原 LoadSettings 建立／讀取 Config.ini。
- Mac Config.ini／picture／logs／browser-profile／instance.lock 均在該根目錄；Windows 路徑保持不變，參見 PLATFORM-PATHS。舊 Mac 個人檔案保留，不自動匯入，不重新保存網站會話。
- 共用 app.cpp 截圖位置僅改呼叫 PictureDirectory；Windows 實作仍返回 EXE/picture，Mac 返回其 data/picture。共用 INI、Cookie／UserSet、登出與工具列流程未重寫。涉及共用與 Windows 介面，Windows 編譯／實機回歸待執行。
- 本輪實際建置與驗證狀態見 PROGRESS M04。SDK／中間建置仍在 Mac 本機 Caches，交付副本在 artifacts/macos-arm64，執行安裝在 /Applications。

## M05～M07／W21～W22 最新接續

- 使用者指定 Mac 專屬碼由 macOS 環境寫，Windows 專屬碼由 Windows 環境寫；共用來源仍唯一。最新規則後沒有再修改 Windows 專屬程式。M04 先前已加入的 Windows PictureDirectory 返回原 EXE/picture，仍待回歸，不擅自撤回。
- Mac HomeUrl 初始空白，歡迎頁直接內嵌共用 welcome.h；按鈕呼叫原 URL 對話框，ESC 不改 INI，確認後保存及載入；已有網址直接載入。Mac 入口 home_url.clear／allow_empty_home_url 啟用空白政策；Windows 仍保留原預設，W21 待 Windows 環境接線與實測。
- Mac hide_zoom_bubble=true；共用 AppContext 預設 false，CreateMainWindow 依旗標設定 CEF chrome_zoom_bubble。Windows 同需求 W22 只記錄，回 Windows 再做，不宣稱交付 EXE 已修正。
- M07 回報額外 Chromium 新分頁後，新增 Mac relaunch 回呼顯示既有主視窗；歡迎頁 Console 按鈕改延後開 modal，Cocoa 取消用正常 stopModalWithCode。保持 Views 主網站。正式結果與未測分支見 PROGRESS。
- Mac 單 .app 安裝 /Applications，資料在 Application Support；不匯入 Windows INI／prg、不保存登入 token。列印／一般注音留使用者，Windows 注音浮窗不列 Mac 測試，U01 線上更新仍未實作。

- M04～M07 最終 Release／CTest1/1、68項、簽章核對及 Mac 實機結果已追加 PROGRESS；交付及 /Applications 已更新。HomeUrl 空白，測前 250% 偏好已還原，程式正常關閉、localhost 伺服器停止；沒有保存測試 URL。W21／W22 尚未在 Windows 實作。

## M08：Mac 交付舊檔已清理

2026-10-12 使用者明確授權刪除不需要的檔案。artifacts/macos-arm64 目前只剩 oaClient2.app；舊 Config.example.ini、Config.ini、picture／Snapshot20261012201957-546.jpg 及 .DS_Store 已刪。Application Support 的現用設定與截圖、Windows 交付均未動，核對雜湊一致。前述舊 Mac app 旁資料保留為此次授權前的歷史紀錄；打包腳本已只交付 .app，不會自動補回舊檔。本輪未改程式、未建置或執行功能測試。

## M09：最新 Mac 重新編譯交付

2026-10-12 已按使用者要求完整重新編譯，官方固定 CEF 配套重新下載且雜湊一致；Release／CTest1/1、68項與簽章驗證通過，最新交付為 artifacts/macos-arm64/oaClient2.app（主程式 SHA256：f7eccbcd7f6737fd7ffb861fb7a877948fcc8676bd151d390c036ae7ca894a24）。使用者明確要求不要安裝，因此沒有替換 Applications、沒有啟動主程式，現用設定／截圖與 Windows 交付保持不變。本輪沒有程式碼修改，實機／列印／輸入測試未執行；重編譯證據見 PROGRESS M09 與 artifacts/verification/macos-m09。

## D04：回 Windows 接續提示詞要點（2026-10-12）

已依使用者要求整理可直接貼到 Windows 的提示詞：W21 沿用共用 welcome.h／app.cpp，Windows 入口啟用空白 HomeUrl 政策，設定確認後才保存、取消不改、既有網址直接載入；W22 在 Windows 啟用 hide_zoom_bubble，保留原縮放／INI／重啟契約。Windows 專屬碼只在 Windows 環境修改。

交接必讀 PLATFORM-PATHS：Windows EXE 旁 INI／picture、LocalAppData data/log/profile；Mac Applications app、Application Support 組態／圖片／logs／profile。SDK／build 各自在本機非同步目錄；交付分別 artifacts/oaClient2 與 artifacts/macos-arm64。Windows 個人 INI、Reptool 契約及使用者精簡 prg 保留、不補回；共用移植修改須回 Windows 編譯／實測。此次只整理提示詞與文件，未改程式、未建置／安裝／測試；M09 的 Mac 重編譯結果不代替 Windows 驗證。

D04 Windows 提示詞已存為 [docs/WINDOWS-CODEX-PROMPT.md](docs/WINDOWS-CODEX-PROMPT.md)，可直接複製回 Windows 接續 W21／W22；本輪只存檔與更新文件入口，未修改程式或交付產物。

## M10／W23：最新關閉流程

Mac 已改為 logout 一次→立即隱藏主窗與 Console→收到 loginState=0 提早退出，否則最多3秒後完成關閉；不再等最多10秒。原命令／狀態格式不變，共用 LogoutFlow 的新模式由 Mac background_logout_close 啟用；Windows 預設 false，W23 需在 Windows 環境接續，其他 Windows 現況與 W21／W22 不擴大完成。

Final Release／CTest1/1、75項及合成實機951ms／3029ms、有效 beforeunload、Console 隱藏與程序正常退出已確認；正式 OA 登出仍待驗收。交付 .app 已更新，SHA256：27355abf79bf5a440fd2940d4e2d6ab1aa9213dc4b4e9447b451961c053ee75d；未安裝 Applications，現用 INI／截圖及 Windows 來源／交付雜湊不變，最後測試程序／伺服器已停止。前面的10秒及等待確認流程是舊版歷史或 Windows 現行，不再用於 Mac。Windows 提示詞已加 W23。


## M11／W24 最新目錄定義（2026-10-13）

兩平台「瀏覽目錄」均指實際 Config.ini 所在目錄。共用 app.cpp 已用 paths.config.parent_path()，提示也已更新。Mac 是 ~/Library/Application Support/oaClient2，Windows 目前是 EXE 同目錄；不要再以 AppPaths.application 作為按鈕目標。Windows 專屬碼與交付未改，W24 須回 Windows 編譯／實機核對，提示詞已加入。

Mac Release／CTest1/1、75項及 Finder 實際目錄已測，測試程序正常退出；已更新 artifacts/macos-arm64/oaClient2.app，SHA256：6c8994441d509d97c5597ec3a7f47938f8a54dac26ec2da058c4fe508da78f12。未安裝 Applications，現用 INI／picture與 Windows 來源／交付雜湊不變。證據在 artifacts/verification/macos-m11。

本機 SDK 曾缺失，已重下載同版且雜湊一致。使用者明確要求編譯完成保留 CEF SDK；目前 SDK、下載壓縮檔及 build 留在 Library/Caches/oaClient2，後續不要自動清除，不將它們移入 Dropbox。列印／一般注音、正式 OA 登出與 Windows 回歸尚未因此完成，U01需求保留。


## M12／W25 最新標題列（2026-10-13）

主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

只改共用 app.cpp 的主視窗初始標題／OnTitleChange，原彈出視窗與 Console 行為保留；無 OA JS 或 Windows 專屬碼修改。Mac Release／CTest1/1、75項、歡迎頁及公開OA標題已測。使用者在測試期間切換另一個網站，標題由良穎更新炬塔，也再次確認名稱沒有寫死；個人 INI 在使用者操作期間有變更，保留現值，不回寫測前內容。

已更新 artifacts/macos-arm64/oaClient2.app，SHA256：50844de4a8455e943f6e34d725c8f8eae9fa94a21e41696b1514179dc2cb9a7f，build／交付一致、arm64／codesign deep strict通過；未安裝。SDK／壓縮檔／build保留。原交付 App 已正常關閉、第一個被單例阻擋的啟動取消後重新測試；歡迎頁測試程序exit0，最新本機 build 視窗依使用者操作保留開啟。Windows W25尚未編譯／實測，W21～W24與U01狀態不變，證據見 artifacts/verification/macos-m12。


## W25：Windows 相同標題需求確認（2026-10-13）

使用者明確要求 Windows 標題列與 Mac 相同：軟體名稱從 URL 頁面的 document.title 取得，顯示「網頁軟體名稱 [用戶端版本 0.1.6]」；尚未取得名稱時顯示「oaClient2 [用戶端版本 0.1.6]」。共用 M12 實作已備妥，Windows 編譯／實機測試及交付更新留到 Windows 環境。本輪只補記需求與交接，未修改程式或交付、未編譯／測試／安裝，不將 Mac 結果當成 Windows 驗證。


## D03：首次本機提交（2026-10-13）

使用者明確指示 commit，授權建立 main 的首次本機來源提交。提交共用及 Windows／macOS arm64來源、原圖資源、共用設定範例、腳本、測試與工作文件；不納入 artifacts、prg、個人Config.ini、CEF SDK／壓縮檔、建置、profile或快取。Git身分使用既有本機設定，實際SHA以git log取得，未建立遠端／標籤或推送。

本輪僅提交與同步Git交接狀態，沒有修改功能、重新編譯／安裝／操作App；既有Mac75項測試結果與Windows W21～W25待回歸狀態保留。歷史無提交記錄不全面改寫。


## M13／W26 最新工具列間距（2026-10-13）

依使用者舊版圖片及現行DFM，右側首頁／網址／MAC／瀏覽目錄／截圖／還原比例／縮小／放大寬度採23／23／40／67／38／61／23／23 DIP，合計298 DIP（原346）。高度仍28 DIP、左Console仍30 DIP；保留原字型、圖示、工具順序及命令。右側按鈕左右內部留白各2 DIP，完整顯示MAC、瀏覽目錄、截圖及還原比例，不以省略號／隱藏文字／縮小字型達成間距。

只改共用app.cpp的GetPreferredSize／按鈕固定尺寸與Insets。第一版只縮窄寬度時，CEF預設內部留白造成MAC／還原比例省略，該UI輪失敗；依使用者「不要隱藏按鈕字樣」追加要求改Insets後，最終Mac截圖確認所有文字完整及舊版間距，Release／CTest1/1、75項通過。

交付已更新、未安裝；SHA256：9bc544d13be3e6b0474d3921ced2a7f510728731b778f8f739ec7f2f2c812258，build／交付及arm64／codesign核對通過。Windows來源／交付、Applications既有主程式與picture雜湊不變。現用Config.ini在實機期間雜湊有變更，既有關閉視窗設定保存流程未改，保留現值，沒有回寫測前內容，不宣稱INI逐位元不變。第一輪測試正常exit0；最新build視窗保留開啟供使用者驗收。證據在artifacts/verification/macos-m13。

Git基準為首次提交ddf1bf9；使用者已授權建立M13工具列修正的本機提交，實際SHA以git log核對。未推送／建立遠端或標籤；Windows W26及W21～W25待回歸，U01保留且未實作。


## M13：工具列修正本機提交（2026-10-13）

使用者明確授權提交本次舊版間距與完整按鈕字樣修正；包含app.cpp及相關規則、計畫、進度、交接與Windows W26待回歸文件。基準為ddf1bf9，實際新SHA以git log核對；不包含交付App、個人組態、SDK或建置產物，未推送／建立遠端或標籤。先前「未提交」為此次授權前狀態。

本輪只核對差異並建立提交，未修改功能、重新編譯／安裝／操作App；沿用M13的Release／75項及完整文字實機結果，Windows回歸仍待執行。


## W26：Windows 工具列要求確認（2026-10-13）

使用者明確要求Windows版工具列間距同舊版，MAC、瀏覽目錄、截圖及還原比例等按鈕字樣完整顯示，不使用省略號／隱藏文字。沿用已提交的M13共用來源（655a6a1），不複製工具列；Windows編譯、實機測試及交付更新留到Windows環境，Mac結果不能代替Windows驗證。

本輪只補記需求與交接，未改程式或交付、未編譯／測試／安裝／提交／推送；Windows專屬碼、個人設定及精簡prg保持。


## D03／R01／R02：公開GitHub與ZIP下載（2026-10-13）

使用者已核准建立公開repository https://github.com/JimmyWon1028/oaClient2、提交最新Windows確認文件並推送；origin已建立。另要求編譯檔從oaClient2的Releases下載，以ZIP發布且不得包含Config.ini或其他快取。先提供Mac arm64，Windows在Windows環境完成編譯與實機測試後再補齊（R02），本輪不發布舊Windows產物。

Mac ZIP本機已核對：只有完整.app，無INI／profile／cache／picture／logs／Finder metadata；解壓逐檔及連結一致、10份arm64 Mach-O、codesign deep strict通過。ZIP大小144461135 bytes，SHA256 8f1cdbdf81990f78eebbf9e79be9e7c8001f4fff240a0b4c07d40f3a929a6493；程式內容與M13一致，沒有重新實作或重新編譯。公開發布／下載校驗結果後續追加，Windows回歸及U01尚未因此完成。本機SDK／壓縮檔／build保留，沒有安裝。

發布說明及可重現流程見[Release文件](docs/RELEASES.md)。歷史無遠端／未推送紀錄保留為本次授權前狀態。


## D03／R01 公開推送與下載核對結果（2026-10-13）

公開repository為[JimmyWon1028/oaClient2](https://github.com/JimmyWon1028/oaClient2)，main已推送到0fe6f35並與遠端一致，包含本機兩筆功能提交與最新Windows需求確認文件。GitHub[v0.1.6初版測試Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)已發布，Tag固定來源0fe6f357173fb7802cca8504c2ea007dd5e7834d，不因後續文件提交移動。

僅提供Mac arm64 ZIP與同名.sha256；GitHub大小／digest與本機相同，不帶登入憑證的公開重新下載兩檔逐位元一致，ZIP CRC通過。ZIP大小144461135 bytes，SHA256 8f1cdbdf81990f78eebbf9e79be9e7c8001f4fff240a0b4c07d40f3a929a6493；解壓bundle逐檔／連結一致、10份arm64 Mach-O／簽章核對，無Config.ini、cache、profile、picture、logs或Finder metadata。未把SDK、建置或個人資料推入Git，未安裝或清除本機SDK。

此輪只是發布與下載驗證，沒有重新編譯或擴大功能驗收。Windows R02等在Windows環境完成W21～W26後再補齊，U01仍未實作。發布證據存artifacts/verification/releases-v0.1.6；本段結果文件另行提交推送，最新main SHA以Git log／ls-remote核對。


## W27 最新Windows交付（2026-10-13）

使用者要求移到選單時不顯示左下角javascript:void(0)。共用app.cpp停用CEF chrome_status_bubble，未修改OA；Windows增量Release／CTest1/1與真實CEF合成選單／子選單動作測試通過。交付EXE SHA256：e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c，取代前輪9b60d756版本，版本仍0.1.6。

原OA網址已重開供使用者測實際選單；合成伺服器已停。Mac產物與prg／picture／tpl不變，Mac需回macOS編譯／實測才能套用這次唯一共用設定。SDK／build保留、Git尚未提交／推送／發布，v0.1.6 Tag不動；詳細結果見[PROGRESS](PROGRESS.md) W27。


## D03／R02 最新交接：Windows ZIP已公開（2026-10-13）

W21～W27來源7958a60fc75a35d4387a028ab8ccfb73e98200c0已透過Windows Git Credential Manager的HTTPS登入推送；遠端確認一致。既有[v0.1.6 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)新增Windows x64 ZIP／.sha256，189879293 bytes，SHA256 4d765e6d5748ce3d5768dd6ef5ed431d27dbcb13f07647f4aa71cc480ec0feb2。EXE e56d3d32版本0.1.6與W27相同，Tag仍0fe6f35，Release明列Windows後續來源，不移Tag、不改Mac資產。

240檔CRC／全部SHA256、GitHub大小／digest、無登入公開重新下載兩檔一致。只包含EXE、安全範例、CEF234份和現有精簡prg4份，沒有個人INI／picture／logs／網站資料／tpl／SDK／build；不從根prg補回。scripts/create-windows-release.py提供可重現打包，已有輸出會拒絕覆寫。發布文件／腳本另行提交推送，最新main以Git核對；詳見[RELEASES](docs/RELEASES.md)及本機artifacts/verification/releases-windows-v0.1.6。

本機保護的Mac專屬來源／產物及prg／picture／tpl共275檔雜湊不變，SDK／壓縮檔／build保留，原OA視窗保留。列印／注音、正式OA登入登出／Reptool／hcopen及間距待使用者驗收；Mac W27共用設定未重編／實測、其他DPI與窗口競態未獨立驗證，U01未實作。切回Mac前仍須停止Windows編輯／建置／Git並確認Dropbox同步，不以Git push推定Dropbox完成。


## W28 最新交接：本機已停用儲存密碼提示（2026-10-13）

共用app.cpp在OnContextInitialized以CEF RequestContext偏好停用密碼保存與自動登入，先設定成功才建立網頁，不改OA／INI／userid／UserSet契約。Windows MSVC Release／CTest1/1、74項通過；同一合成表單舊版提示可重現，修正版原生送出及重啟AJAX無提示且正常完成，啟動紀錄確認政策套用。正式OA登入由使用者驗收，原網址已重開，合成server已停止。

本機EXE版本0.1.6，SHA256 fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474，與build一致。個人設定保留原關閉Window保存，localhost網址未寫INI；Mac／prg／picture／tpl共275份不變，SDK／壓縮檔／build保留。現有GitHub Windows ZIP仍為W27，沒有W28修正；main基準80402ed，本輪未提交／推送／移Tag／重新發布，後續依使用者授權處理。

Mac須在macOS重編／實測W27與W28共用變更，不在Windows修改Mac產物。合成素材tests/pages/password-save.html，測試server用python tests/serve-password-save.py指定事件檔（例如artifacts/verification/windows-w28/events.jsonl），僅127.0.0.1:8765，丟棄表單值；啟動App加--url=http://127.0.0.1:8765/只覆寫當次記憶體。Windows證據見artifacts/verification/windows-w28，未驗收項目及U01保持。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## R02／W28 最新交接：同版Windows ZIP已替換（2026-10-13）

使用者明確要求重新打包上傳但不進版。W28來源c5cd54939caf34d14bd7395fb4f7073b6a134e3c已透過HTTPS推送；App／CMake仍0.1.6，v0.1.6 annotated Tag物件67e29679及來源0fe6f35不變。原Release同名Windows ZIP與.sha256已替換，Mac兩資產ID／大小／digest完全不變。

最新ZIP 189879887 bytes，SHA256 92c371f3560daab3c23de117bb62d11b893be72530b045dbb5b20b8603e24099；EXE仍為W28的fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474。240檔CRC／全部SHA256、本機與GitHub大小／digest及無登入原URL重新下載ZIP／校驗檔一致，不含個人INI／網站資料／picture／logs／tpl／SDK／build，prg只有現用4份。不需重啟使用者現用OA；本輪只提交及打包／發布，沿用W28實測。

artifacts/releases/oaClient2-0.1.6-windows-x64.zip及.sha256現在是最新同版檔；本輪新打包副本在artifacts/releases/windows-w28。歷史W27兩檔保留artifacts/verification/releases-windows-v0.1.6/public-download，SHA256 4d765e6d，不能再當成最新公開下載。新證據artifacts/verification/releases-windows-w28/results.json／package.json／release-public.json。來源及產物可追溯，發布紀錄另行提交，最新main以Git核對。

275份Mac專屬來源／產物與prg／picture／tpl雜湊不變，SDK／壓縮檔／build保留。正式OA登入、列印／注音及其他驗收未擴大，Mac W27／W28待macOS重編／實測，U01未實作。切換平台仍須停止Windows操作並確認Dropbox同步，不能以push完成推定同步完成。

## W29：Chrome衝突熱鍵交回網頁（2026-10-13）

使用者要求取消oaClient2內建Chrome的F1／F2／F3／F4／F9、Alt+W、Mod+F、Shift+F、Mod+E／S／N（Mod=Ctrl或Cmd，包含Ctrl+N），不是移除網頁自己的設定。共用common/keyboard.h精確匹配，app.cpp改為網頁優先接收一般加速鍵，OnPreKeyEvent不吞掉事件、OnKeyEvent在網頁處理後攔下指定Chrome預設動作；原F8／F12／Ctrl+P高優先功能及工具列保持。

Windows MSVC Release／CTest1/1、110 checks／0 failures（原74＋36項政策檢查）通過，包含Ctrl／Cmd正向及未列出的組合。共用合成頁tests/pages/keyboard-shortcuts.html已載入。使用者隨後要求「你編譯好，我測試」，因此未繼續逐項實機熱鍵矩陣，Chrome搜尋／儲存／新視窗及真實網頁按鍵接收均待使用者驗收，不宣稱UI熱鍵已通過；Cmd實機亦須在Mac回歸。

本機交付EXE已更新、與build一致，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6 x64。合成server／App已停止，原OA已重開供使用者測試；測試URL只在當次記憶體，未保存INI。使用者新增的f1.js清單保留、不執行／修改／納入Git，Mac專屬碼／產物及prg不改，SDK／build保留。此次未提交／推送／移Tag／重新發布，GitHub ZIP仍為W28；Mac W27～W29需回macOS重編／實測，U01未實作。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## W29／R02 最新交接：熱鍵驗收後已同版發布（2026-10-13）

使用者對W29回覆「可以了」，Windows熱鍵依此記錄驗收通過；代理原未執行逐項UI矩陣仍保留，不擴大為其他功能／Mac Cmd驗收。依「不要進版」維持0.1.6，來源6f2833b7f7789509abb8f4b60d9b3ea0e0daa01f已推送，原Release同名Windows ZIP／.sha256已替換；Tag來源0fe6f35與Mac兩資產ID／大小／digest保持。

最新ZIP 189880195 bytes，SHA256 849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046；EXE b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，與使用者測試及MSVC／110項版本相同。本機及原公開URL無登入下載ZIP／校驗檔、GitHub大小／digest、240檔CRC及SHA256全部一致；不含個人INI／網站資料／picture／logs／tpl／SDK／build，現有prg4份不補回。

artifacts/releases同名兩檔已更新，新增打包副本artifacts/releases/windows-w29；歷史W28副本及驗證證據保留。新證據artifacts/verification/releases-windows-w29/results.json／package.json／release-public.json，公開Windows資產ID635910442／635911490、Release仍411036061。275份Mac平台／產物與prg／picture／tpl雜湊不變，原OA保持開啟，不重新建置或打斷使用者操作。

本輪接手時f1.js已不在工作目錄，沒有補回或納入Git；無追蹤來源衝突。SDK／build保留，Mac W27～W29仍需macOS重編／實測，其他使用者驗收與U01保持；發布紀錄另行提交推送，最新main以Git核對。跨平台切換前仍須停止Windows操作並確認Dropbox同步。

## D04：Mac接續Windows今日功能提示詞（2026-10-13）

依使用者要求將Mac接續提示寫成.md，新增[MAC-WINDOWS-2026-10-13-PROMPT.md](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)。基準main／已推送cb68ba2、Windows實際W29來源6f2833b；核心範圍W27連結狀態提示、W28密碼保存政策及W29 Chrome衝突熱鍵（包含Mac Cmd）。Mac已完成M01～M13，不重做平台移植，W21～W26只作既有共用功能回歸；版本維持0.1.6、共用來源唯一、平台路徑／SDK隔離／交付與未驗收範圍明列。

原MAC-CODEX-PROMPT.md新增最新提示入口並保留首次移植歷史，README／交接入口同步。提示詞包含Windows停止操作／Dropbox同步、Git差異核對、Mac固定CEF／Release／核心測試／簽章／實機、保留SDK及個人設定、先更新交付不自動安裝／發布，以及不把Windows熱鍵驗收當成Mac Cmd已通過。

本輪只建立／更新文件，沒有修改程式、建置／操作App、更新SDK或產物、提交／推送／移Tag／發布。文件UTF-8／LF與相對連結核對；Mac W27～W29仍待目標平台編譯／實測，其他未驗收及U01未實作保持。切換Mac前仍須停止Windows編輯／建置／Git，等待兩台Dropbox同步；未提交文件須辨識保留。

## M14～M17 最新 Mac 接續交付（2026-10-13）

接手main／origin皆cb68ba20a7c1862cd58f851c3a3c1940cf555a05，使用者確認Windows停止且Dropbox同步完成；D04未提交提示詞／文件保留，沒有reset或cherry-pick。共用app／common完全未改，沿用W27～W29完成Mac Release／CTest1/1、111項及兩種15組trusted鍵盤矩陣、原生／AJAX密碼表單、選單與HTTP連結、歡迎／網址／縮放／popup／標題／兩輪偏好及網站清理回歸。

M17唯一產品差異在Mac main.mm：以objc_precise_lifetime保留weak Cocoa delegate，既有reopen回呼只顯示共用主窗、關閉期間不顯示。最終Finder正常reopen與背景reopen=1兩次、timeout3019ms／ACK1418ms、Console／beforeunload／全部退出通過。早期新分頁／未退出失敗與停止殘留程序另列於[PROGRESS](PROGRESS.md)，不以SIGTERM當作正常退出。沒有增加Apple Event替換或Mac快捷鍵副本。

交付artifacts/macos-arm64/oaClient2.app已更新，版本0.1.6；主執行檔SHA256 879b1e1747f0a59f75afa7cfc0790f257aa3acfe62b72edbd8239226e99c4a7e。265檔案／連結與build一致、10份arm64 Mach-O／deep strict簽章通過。Windows交付／ZIP／prg等272項保護雜湊不變，SDK／壓縮檔／build保留；本輪app及8765 server全部已停止。先供使用者測試，未安裝Applications或提交／推送／發布／移Tag，Mac公開ZIP仍為M13，不含本輪修正。

偏好／保存／重啟測試使用已核對的/private/tmp隔離home，沒有覆蓋個人設定；正常Window保存現況保留。正式列印／一般注音／實體Fn與OA功能留使用者驗收，其他未測項目見進度，U01未實作。下一步是使用本機交付.app驗收，再依實際授權提交／推送及處理Mac ZIP；不沿用已執行的Windows發布授權自動替換Mac資產。

## M18：Mac 交付時間顯示（2026-10-13）

使用者要求與系統相同時間並記錄問題。Finder原05:06是.app外層目錄時間，內部最新主執行檔實為13:26:11，兩者皆UTC+8；rsync -a保留外層舊時間。package-macos.sh現於交付簽章核對後touch -m外層.app，後續顯示系統打包時間；現有交付更新為13:43:20，265份內容不變／簽章通過。未重新編譯或安裝／發布，M14～M17功能與待驗收狀態保持。此mtime不能取代來源雜湊、實際編譯或功能驗證。

## W30：Windows Ctrl+W 交回網頁與關閉回呼保護（2026-10-13）

依使用者選定行為，Windows只取消Chrome的Ctrl+W關閉分頁，OA網頁仍收到按鍵。沿用W29網頁先處理／Chrome後備攔截；Windows入口啟用disable_chrome_ctrl_w，Mac預設false且Cmd+W不變。共用關閉回呼增加失效browser／main frame保護，避免Chrome先銷毀主瀏覽器後再執行logout而解參照空frame；兩次Windows事件皆0xc0000005／RVA0x1053e，來源定位及詳細證據見[進度](PROGRESS.md)。

MSVC Release／CTest1/1、115項通過；合成頁有／無preventDefault各3次真正Ctrl+W均交給網頁且不關閉；正常Alt+F4、ACK1434ms／含Console1525ms、無ACK3019ms、logout一次／主窗與Console隱藏／beforeunload／全部程序退出通過。正式OA內部分頁與實體高速連按／長按待使用者驗收，Mac共用關閉保護須在macOS重新編譯回歸。

本機EXE版本仍0.1.6，SHA256 504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09，與build一致；Mac／CEF／prg等507份保護雜湊不變，保留已同步Mac M14～M18及D04差異、個人INI與SDK／build。測試App／server已停止，證據artifacts/verification/windows-w30；本輪未提交／推送／移Tag／發布，公開Windows仍W29、Mac仍M13，U01未實作。

## W30／R02：使用者驗收與同版發布授權（2026-10-13）

使用者對本機Ctrl+W修正回覆「可以了」，W30按此回報記錄Windows使用者驗收通過；不擴大為Mac、列印／注音或其他功能驗收。另明確授權commit、push、重新打包上傳、不進版：先提交／推送本次Windows修正與紀錄，再打包已建置／115項及使用者測過的同一EXE，替換既有v0.1.6同名Windows ZIP／.sha256。Tag、Mac兩資產及個人資料保持；先上傳校驗兩個暫名資產才替換，舊ZIP保留本機歷史證據。

Mac M14～M18及D04是接手時已有的未提交差異，保留於工作目錄，本次Windows提交只納入W30及發布紀錄。Mac新共用關閉保護仍須在macOS編譯回歸；U01未實作。前段待驗收／未發布是本次回報及授權前狀態，實際結果另行追加。

## W30／R02：0.1.6 同版更新完成（2026-10-13）

Windows Ctrl+W修正已由使用者回覆「可以了」驗收，來源a56ec05688462400e23137ba87bd63c875444221已提交／推送；沿用MSVC／CTest1/1、115項及使用者測過的同一EXE，沒有重新編譯或進版。EXE SHA256 504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09。本次共用關閉保護仍待macOS編譯回歸，不擴大其他功能驗收。

既有[v0.1.6 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)的[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)與[校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)已替換為W30。ZIP 189880372 bytes，SHA256 **2ca590f6cd878a4a66612d8a4d25d99c46a432c23af26fb53177d64583252d33**；Windows資產ID636632177／636633864。先上傳兩個暫名資產／校驗digest才替換原名，公開原URL無登入重新下載兩檔與本機及GitHub一致，240檔CRC／全部SHA256通過。

ZIP仍只含EXE、安全範例、CEF234及現用prg4；不含個人INI／picture／logs／profile／cache／tpl／SDK／build，不補回工具。本機artifacts/releases同名兩檔已同步，W29歷史副本保留。Mac兩資產ID／大小／digest及固定Tag67e29679→0fe6f35不變，507份Mac平台／產物與CEF／prg等保護檔案雜湊一致。Mac M14～M18及D04既有未提交差異保留於工作目錄，未混入Windows提交；SDK／下載包／build保留。U01未實作。

證據artifacts/verification/releases-windows-w30/results.json／package.json／release-public.json及public-download；發布結果文件另行提交推送，最新main以Git核對。前段W30待驗收／未發布及W29公開雜湊為本次驗收／發布前歷史。

## 2026-10-16：M19 Mac 附件選檔篩選修正與驗收

- BSI010010 圖檔→加入原生視窗預設 JPEG image；Show Options 才能看到逐項格式，單獨 PDF 篩選仍不可選，同檔案改所有檔案則可選。使用者提供 Chrome 只有 Custom Files／All Files 的參考圖並授權修正。
- src/app/app.h 接線 GetDialogHandler，platform/cef_platform.h 提供平台介面；Mac file_dialog.mm 使用 Cocoa NSOpenPanel，將 CEF 提供的副檔名合併成預設 Custom Files，明確 All Files 允許其他格式。MIME 未展開時交還 CEF，等已展開的回呼，不硬編碼 OA 副檔名。Mac CMake 加入來源與 UniformTypeIdentifiers；Windows 平台實作／EXE未改，預設仍回傳 nullptr，Windows 編譯／回歸未執行。
- 固定官方 SDK 原本已不在本機；重新取得相同154.0.34 arm64套件，SHA256仍2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe。SDK／壓縮檔／新build皆保留。Release／CTest1/1、116 checks／0 failures、10份arm64 Mach-O及deep strict簽章通過。
- 隔離Cocoa home的真實CEF合成頁測過五格式同選及回傳、MIME PDF／XLSX、未允許TXT／XLS不可選、PNG單選、All Files選TXT仍單選、再次開啟預設、ESC保留先前選檔；無限制／目錄原CEF視窗開啟與取消正常。素材只驗證副檔名與callback，不代表文件解碼或正式上傳測試。儲存對話框、pending選檔時父窗關閉未獨立實測。
- 使用者最後回覆「我剛剛測試 oaclient2 附件 正確」，記錄為本次附件修正驗收通過，不擴大其他功能。交付artifacts/macos-arm64/oaClient2.app已更新，265檔案／連結／mode與build一致；主執行檔SHA256 9388faa75d04e2aaf8df5e4105b0fcd6632ac4b901aec8f55f6b0ee82190b3e2。未安裝、commit／push／Tag或公開ZIP更新。
- 原舊版登出ACK後全部瀏覽器關閉但程序未完成退出，核對後以SIGTERM結束；本輪沒有修改退出邏輯。隔離新版期限3005ms並有SHUTDOWN_COMPLETE。UI工具在測試退出後重新啟動build版並讀正常設定，使用者在修正版測附件；目前視窗保留，內容與已更新交付一致。個人INI只保留正常操作現況，未回寫測試快照／合成設定；Windows保護雜湊保持。server已停止。證據artifacts/verification/macos-m19/results.json及logs，UI圖像在本對話工具結果，無另存PNG。

## 2026-10-16：D04／W31 Windows 附件選檔修正提示詞

使用者回報 Windows 有相同附件選檔問題，要求將 Windows 修正提示詞存成 .md；已建立[Windows 附件選檔修正提示詞](docs/WINDOWS-FILE-DIALOG-2026-10-16-PROMPT.md)。Windows 待辦 W31：先在目標平台重現，沿用現有 GetDialogHandler／PlatformFileDialogHandler 接線，預設 Custom Files 合併網頁允許格式，另提供 All Files；MIME／單選／多選／取消與 Unicode 等需 Windows 實測。Mac M19 已驗收不代表 Windows 已完成；Windows factory 目前仍 inline nullptr，待 Windows 接續實作。

本輪只新增提示詞並同步工作紀錄，沒有修改任何程式、建置／操作 App 或更新平台產物；版本0.1.6，未提交／推送／發布。切換前由 Mac 停止操作並確認 Dropbox 同步，Windows 保留現有未提交 Mac 工作。

## 2026-10-16：W31 Windows 附件選檔格式修正與本機交付

狀態：已在 Windows 重現、修正、MSVC x64 Release／原生實機測試及更新本機 EXE；版本維持0.1.6，正式 OA BSI010010 圖檔→加入待使用者驗收。未提交、推送、移 Tag、打包 ZIP 或更新 GitHub Release；公開 Windows 仍 W30、Mac 仍 M13。

接手由使用者確認 Mac 停止編輯／建置／Git、兩台 Dropbox 同步完成。實際 main HEAD 為8d104ba7af6c75b91527a14a6d2b6ed64d03dc2b，無 Git lock／來源衝突副本；M14～M19、D04 既有未提交差異保留，未 reset／checkout。接手差異在 artifacts/verification/windows-w31/baseline.patch／baseline-status.txt；Mac 專屬來源、打包腳本與 .app 雜湊均不變。

Windows 根因：同一跨平台 tests/pages/file-dialog.html 的 accept=.jpg,.png,.pdf,.xls,.xlsx 完整傳入 CEF，原生預設卻列 JPEG／PNG／PDF／兩種 Excel／自訂檔／所有檔案七項，預選 JPEG。觀測版確認五項 accept_extensions 完整，MIME image/*、application/pdf、XLSX 亦由固定 CEF 正確展開；沒有把 Mac 原因當 Windows 證據，也沒有修改正式附件或 OA JavaScript。

平台實作 src/platform/windows/file_dialog.cpp 使用 IFileOpenDialog，動態合併 CEF 副檔名為第一項 Custom Files、第二項 All Files；不寫死 OA 清單。file_dialog_filter.h 對未展開、未知、空項或 wildcard 拒絕自訂處理並交回 CEF；Save／選目錄／無 accept 沿用原流程。Unicode、原單多選、檔案／路徑存在與 owner 保持。COM／Show 在獨立 STA，CEF UI 延遲任務完成 callback；取消不回傳空成功。瀏覽器關閉先非同步取消對應視窗，UI loop 結束後於 CefShutdown 前收束 worker。

沿用 M19 app.h 的唯一 GetDialogHandler 接線，沒有另造 BrowserClient／工具列。W31 新差異為 Windows CMake source、cef_platform.h Windows factory／取消介面、app.cpp OnBeforeClose 的兩行平台通知、Windows main.cpp shutdown hook、兩份 Windows 選檔來源、Windows 核心測試及共用測試頁附加關閉情境。Mac factory／實作保持，取消 hook 在非 Windows 為 no-op；必要共用 header／app.cpp 仍待 macOS 編譯回歸，不在 Windows 宣稱 Mac 產物更新。

MSVC Release／CTest1/1、**123 checks／0 failures**（Windows 原115＋8項篩選契約）通過；不是 Mac116項或 UI 驗證替代品。第一次原生編譯缺少 cef_callback.h 的 include 順序而失敗，已修正並保留 build-first-failed.log。最終 UI：五格式同選／FileList、TXT預設隱藏、MIME JPG／PNG／PDF／XLSX 同選且 XLS／TXT 被篩掉、PNG單選、明確 All Files 選TXT仍單選、中文及空白路徑、ESC／Cancel 保留原選檔、重開預設均通過。無限制原對話框回傳TXT，原目錄流程回傳6個拋棄式檔名；原 Chromium PDF Save 視窗成功產生111832 bytes測試檔。這些只驗證篩選、原生回呼與 change／檔名，不代表文件內容解碼或正式上傳。

第一輪 UI 曾發現 popup 已關閉而 picker 留下，記為失敗；補上 OnBeforeClose 通知與原生非同步 WM_CLOSE 後重測通過。最終 popup 關閉只完成一次 Cancel、無殘留；主瀏覽器在選檔 pending 時關閉亦 Cancel、SHUTDOWN_COMPLETE、全部程序退出。最終 build 另重測五檔；交付 EXE 再實測 MIME PDF／XLSX、Cancel／重開及一般 Alt+F4 約3秒退出。未知 MIME fallback 的原生 UI、其他 Windows／DPI／網路路徑未執行。

本機 EXE **91ffcaceab028182599fb4fd5e0d40ad4cc887869967ffc84fbfb715e5289ee9**，PE machine=0x8664，build／交付一致。package-windows.ps1 新增可選 -ExecutableOnly，本輪使用此模式只換 EXE；不寫 CEF、範例或任何個人交付檔。最終515項保護雜湊全部與接手一致。正式 Config.ini 在中途正常關閉保存後曾有差異，交付版最後正常關閉後與原雜湊相同；全程保留實際現況、不回寫過期快照，未將 localhost／合成偏好保存至正式 INI。Windows INI／picture 仍在 EXE旁，prg／tpl／下載、Mac／公開 ZIP 不動；SDK／下載包／build 均保留。

工具環境失敗：Codex 宿主 LocalAppData 重導向曾觸發既有 PROFILE_PATH_REJECTED；未放寬程式保護。停止 App 後，只針對明確核對的 oaClient2 專用 mapped browser-profile 清理再測；Python alias 不可執行，改用 bundled Python，localhost server 於正常桌面可存取的執行環境啟動，綁127.0.0.1。測試 URL 僅 --url 當次記憶體，不注入 UserSet；server 與測試 App 最後皆停止，不自動重開正式 OA。再次啟動仍依既有設定清除網站登入狀態。

證據 artifacts/verification/windows-w31/results.json、build.log／core-tests.log、observed-cef.log、ui-first-*／ui-final-*／delivery-*、protected-before.json／protected-result.json 及 save-regression.pdf；UI 截圖在本次 Computer Use 回傳，沒有另外保存 PNG。約15:57～16:07查證／觀測、16:07～16:11初版實作及建置、16:12～16:19實測，約16:19～16:20生命週期修正／建置，16:20後最終回歸與交付；工具等待與測試另計，不虛構精確累計工時。

下一步：由使用者以本機交付測正式 BSI010010 附件；Mac 在 macOS 回歸必要共用介面，不能沿用本輪 Windows 結果。其他列印／注音／正式 OA／Reptool 待驗收、U01未實作保持。

## W34：使用者可見錯誤訊息改為繁體中文（2026-10-28）

- 依使用者圖片及「顯示的錯誤訊息都使用繁體中文」，Windows 入口、平台函式與唯一共用 INI／app 的自訂錯誤提示改為繁體中文。重複啟動顯示「oaClient2 已在執行，請先關閉原視窗後再重新開啟。」；涵蓋設定檔讀寫／編碼、網站資料清理保護、主控台、開啟目錄、截圖及 Reptool 啟動。檔名、設定鍵、產品名與錯誤代碼保留供辨識。
- 使用者可見訊息不再附加可能是英文的 std::error_code::message() 或 CEF 偏好錯誤；檔案系統／Windows 錯誤以中文說明加數字代碼呈現，密碼政策失敗的原始 CEF 診斷寫入 application.log，既有停止啟動政策保持。不改 OA 網頁內容、INI 格式／偏好、命令、清理或登出流程。
- Windows MSVC x64 Release／CTest 1/1、143 checks／0 failures 通過。Computer Use 實際啟動交付版，再次啟動確認中文重複執行對話框、確定按鈕及文字無亂碼；兩個重複提示皆關閉，測試主視窗 Alt+F4 正常退出，有 SHUTDOWN_COMPLETE。未逐一強制觸發所有磁碟／權限／截圖／報表錯誤；列印、注音與其他既有待驗收範圍不擴大。
- 單例測試最初以沙箱 PowerShell 持有 mutex，與正常桌面命名物件隔離，沒有觸發預期分支；已釋放，改以正常桌面真正啟動第二個交付 EXE 驗證。Computer Use 一次無截圖幾何的點擊失敗，重新擷取視窗後正常關閉；未把上述工具結果當作產品失敗。
- package-windows.ps1 -ExecutableOnly 只更新 artifacts/oaClient2/oaClient2.exe，版本仍 0.1.6。build／交付 SHA256 同為 ac03403cefdb9ae0e5415141e887b07b0a582552afa2513566c31c008670562c；528 份受保護檔案雜湊一致，含交付 Config.ini／CEF／prg／picture 及 Mac 平台來源／產物。正式 INI 保留正常關閉後現況，沒有寫入合成設定或回復快照。
- 共用改動僅 src/common/ini.cpp 與 src/app/app.cpp，Windows 專屬改動為 main.cpp／platform.cpp；Mac 專屬碼及 .app 未改。Mac 平台既有英文錯誤與系統 localizedDescription 仍待 macOS 環境改為繁體中文，並沿用共用來源重編／實測；不能宣稱 Mac 全部訊息已完成。本輪未提交、推送、移 Tag、打包 ZIP 或更新 Release，SDK／下載包／build 保留，U01 未實作。
- 證據：artifacts/verification/windows-w34/build.log、core-tests.log、source-audit.json、protected-before.json／protected-result.json 及 results.json；對話框圖像在本輪 Computer Use 回傳，未另存 PNG。約 10:26～10:28 實作／建置，10:29～10:34 工具與實機驗證，其後文件／核對另計，不捏造逐秒累計。

## W35：匯出／下載每次詢問儲存位置（2026-10-29）

- 使用者要求匯出檔案或另存時一律跳出「另存新檔」，由使用者指定路徑，取代直接存到預設路徑。共用 src/app/app.cpp 在建立任何瀏覽器前設定全域 RequestContext 的 download.prompt_for_download=true；沿用 Chromium 的原生儲存對話框、建議檔名與取消處理，未改 OA 網頁、上傳選檔、下載目錄或 INI 欄位，未增加平台流程副本。
- 固定 CEF154 SDK 的 tests/ceftests/download_unittest.cc 已使用同名偏好驗證 Chrome 預設下載；本輪實際啟動政策成功並記錄 DOWNLOAD_PROMPT_REQUIRED。若偏好套用失敗，寫原始診斷至程式紀錄、顯示繁體中文錯誤並停止啟動，避免靜默直接儲存。
- Windows MSVC x64 Release、CTest 1/1、143 checks／0 failures 通過。使用剛更新的交付 EXE 與 localhost 合成 GET attachment，實際點擊後跳出繁體中文「另存新檔」，保留中文建議檔名 W35伺服器匯出.csv；對話框停留時，C:/Users/Lenovo/Downloads 中該測試檔未出現。
- 驗證限制：Computer Use 對已出現的原生對話框無法 set_value，重新擷取後的輸入亦回報 failed to activate captured window。因此未完成選路徑後實際儲存、取消、POST／Blob／新視窗匯出、右鍵另存連結、PDF／列印儲存或重啟 UI 回歸；不把測試素材或編譯成功當作這些情境已通過。正式 OA 匯出由使用者接續驗收。
- 因工具無法操作對話框，最後只核對並結束本輪記錄 PID／EXE 路徑的測試程序及其子程序，再停止本輪 localhost 伺服器，確認無 oaClient2 殘留；這不是正常退出實測。測試網址只由 --url 傳入當次記憶體，未寫入正式 INI，沒有登入或上傳至外部網站。
- package-windows.ps1 -ExecutableOnly 只更新 artifacts/oaClient2/oaClient2.exe，版本仍 0.1.6；build／交付 SHA256：57d1a8d2426525f0ce567efe04809709898bb80e5ade6a4e2794e06970fb2290。528 份保護檔案雜湊不變，含交付 Config.ini、CEF、prg、picture 與 Mac 平台來源／產物；SDK／下載包／build 保留，未提交／推送／移 Tag／打包 ZIP／發布。
- Mac 專屬碼及 .app 未改；共用下載政策須回 macOS 重編及實機確認才會套用 Mac 交付，W34 的 Mac 專屬錯誤翻譯與其他原待驗收項目、U01 未實作狀態保持。
- 證據：artifacts/verification/windows-w35/build.log、core-tests.log、app-before.cpp、startup.log、protected-before.json／protected-result.json、results.json 與僅本機合成下載素材 serve-downloads.py／requests.jsonl。UI 畫面在 Computer Use 回傳，未另存 PNG；約 17:19～17:20 實作／建置，17:20～17:24 實測與工具排除，其後文件核對另計，不捏造累計工時。

## D04：Windows 修改紀錄與 Mac 接續提示詞（2026-10-30）

使用者要求把 Windows 修改記錄於 AGENTS／README，並另存可在 Mac 執行相同修改的 .md 提示詞。已新增 [MAC-WINDOWS-2026-10-30-PROMPT.md](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)，彙整 W32 外部協定、W33 固定亮色、W34 繁體中文錯誤與 W35 每次詢問儲存路徑；Mac 直接沿用共用來源，在 macOS 入口啟用亮色政策及翻譯平台錯誤，再於目標平台建置／實測。這是待 Mac 執行的工作範圍，不代表本輪已完成 Mac 修改。

AGENTS.md 與 README.md 已加入近期功能／Windows實際驗證／Mac待辦，README另核對更新本機 Mac M19 與公開 ZIP Windows W30／Mac M13 的差異；舊 Mac 提示入口加註最新連結、保留歷史。W31／M19 附件不重做，W27～W29已完成範圍不回退，Windows Ctrl+W政策不移植成Mac Cmd+W。提示詞明列W35只驗證GET對話框跳出、實際存檔／取消等未測完，以及共用唯一來源、兩平台路徑、同步、SDK保留、0.1.6與交付／發布邊界。

本輪接手 main／HEAD 8d104ba7af6c75b91527a14a6d2b6ed64d03dc2b，保留既有未提交Windows／Mac來源與文件，未發現Git lock或衝突副本。僅更新文件，沒有修改程式、建置／操作App、變更SDK或平台交付、提交／推送／移Tag／安裝／發布。檢查UTF-8／LF、相對連結、git diff --check及程式／腳本／測試／主要交付檔雜湊；Mac實作、編譯與實機驗證未執行，既有其他未驗收及U01未實作狀態保持。文件核對證據在artifacts/verification/docs-mac-2026-10-30。

下一步：Windows 停止編輯、建置與 Git，待兩台 Dropbox 同步完成，再於 Mac 開啟同一專案使用新提示詞；本輪不宣稱同步已完成。

## 2026-10-30：M20～M23 Mac 補齊 W32～W35

Mac arm64 0.1.6 已補齊 W32～W35 並更新本機交付：外部協定直接沿用共用判斷、Chrome／Cocoa 固定亮色、Mac 自訂錯誤繁體中文化，以及每次下載原生另存新檔。Release／CTest 1/1、136 checks／0 failures、10 份 arm64 Mach-O 與 deep strict 簽章通過；下載及合成回歸範圍、一次未解的複合退出殘留見 [PROGRESS](PROGRESS.md) 末段。版本仍 0.1.6，未安裝、提交、推送或發布。

產品僅修改 Mac main.mm／platform.mm；共用來源直接沿用，未複製或修改 Windows 專屬實作。下載 GET／POST／Blob／popup／右鍵、中文／空白檔名、兩目錄、取消／重啟及 Ctrl+P 完整預覽另存 PDF 已實測。設定／清理、110%重啟、附件格式選單及動態標題回歸通過；系統亮暗切換／暗色環境、正式 OA／外部協定／一般注音及所有原生錯誤分支未驗收。

M24：一次附件／beforeunload／Console 等複合操作後，全部 Browser 關閉但主程序殘留，已擷取堆疊並結束本輪殘留程序；原因待定位。實際交付的單獨無 ACK 3012ms、開關 Console 後 3011ms 均完整退出，不能用兩次通過抹除複合失敗。主執行檔 SHA256：6797e8a69846e43d0e0b5e11a27292fefbd3fe0c0c342129696af6aa313c01f0；265項與build一致，301份受保護檔不變。只更新交付 .app，SDK／下載包／build保留；未安裝／Git操作／發布，U01未實作。詳細證據與限制見 [PROGRESS](PROGRESS.md) M20～M24。

## 2026-10-30：M24 Mac Cmd+Q 背景殘留修正完成

M24 已重現並修正：Console 有焦點時 Cmd+Q 未進入原生結束入口，之後關閉全部 Browser／Views 仍可能留下 CEF 主迴圈。Mac sendEvent 現在先讓既有原生選單處理精確的 Command+Q，呼叫原 terminate → 共用登出／隱藏／三秒流程；沒有改寫登出或強制結束程序。

最終 arm64 Release／CTest 1/1、136 checks／0 failures、10 份 arm64 與 deep strict 簽章通過；Console 焦點 Cmd+Q、已啟用 beforeunload、附件取消組合的 ACK619ms／無ACK3032ms及實際交付3043ms期限後皆正常 SHUTDOWN_COMPLETE，主程序／Helper 全部退出。 僅更新本機 artifacts/macos-arm64/oaClient2.app，版本維持0.1.6；主執行檔SHA256 b8715817e17036d7b05e830db48433232e6293c286a4390a9769f00a48ccd862，265項與build一致，299份受保護檔案不變。所有暫時診斷／附件參照嘗試已撤回，共用app／介面及Windows碼不變。SDK／下載包／build保留，未安裝、提交、推送、改Tag或發布。

新簽章測試版曾等待系統鑰匙圈授權，後續只在隔離localhost測試使用官方 --use-mock-keychain 啟動參數，沒有寫入產品或個人設定；正式鑰匙圈與OA仍待使用者驗收。M24原待定位狀態由本段取代，歷史失敗保留；完整對照、限制與證據見 [PROGRESS](PROGRESS.md) M24。

## 2026-10-30：W36 印表字型／Reptool 查證交接

使用者要求查清楚舊版選定印表字型如何設定FRX，並確認由Reptool.exe完成。已確認兩代宿主均有通用 UserSet.report_font 保存及報表呼叫；舊Reptool在frx／fr3分支把Arial Unicode MS替換成指定名稱、寫tmp-範本後載入。

已以現行oaClient2保存函式＋Delphi21.0 TMemIniFile隔離重現缺口：oaClient2移除／不寫UTF-8 BOM，本機ACP950的舊讀法將中文報表字型讀錯；有BOM控制正確。原先有BOM也會在下次保存被移除，不能只手動修INI。建議修正唯一INI輸出契約，保留Reptool／prg與既有保存保護；本輪僅查證，尚未套用產品修正／更新交付。

交付INI當下尚無report_font，正式網頁選字型命令是否送達及真正FRX預覽／列印未實測，不宣稱編碼是本次回報唯一原因。現行Reptool亦未讀ParamStr(2)，而從EXE旁／上一層找INI，非標準設定路徑需另確認。來源行號、實測、證據與待辦見 [W36相容性查證](docs/LEGACY-COMPATIBILITY.md)及[進度](PROGRESS.md)末段。未修改產品／舊專案／個人設定，未產品建置、提交／推送／發布；Mac與其他待驗收範圍保持。

## 2026-10-30：W36 修正／0.1.7 最新Windows交接

使用者已授權修正、舊INI自動修復、確認report_font保存並進版。Windows本機EXE現為0.1.7，UTF-8 BOM保存；LoadSettings在啟動時以唯一保存流程修復既有無BOM設定，保留鍵值／註解、同內容不重寫，拒寫回報、不解readonly／ACL。Reptool來源／EXE／呼叫不改。

MSVC Release／CTest1/1、160項通過；獨立合成CEF選單選標楷體／新細明體，report_font落盤／load-userset成功，正常關閉重啟後Cookie／$usr／選單皆還原，新版UI產生的INI經舊Delphi讀取正確。正式OA選單／真正FRX預覽列印待使用者測試，不能以合成結果代替驗收。

交付artifacts/oaClient2/oaClient2.exe已更新且與build相同，SHA256 ebc31ebb1e8a56085b11c696b6149bf0e1300f420c4a4173197ede1f54899cc4；528份個人INI／CEF／prg／Mac來源及.app等保護檔案不變。正式INI由使用者下次啟動0.1.7自動修復，不回寫測試資料；測試App／server已正常結束。未提交／推送／Tag／發布，SDK／下載包／build保留。

Mac仍交付0.1.6／M24；唯一共用INI及版本修改待macOS重編／回歸，Mac入口版本紀錄留該平台同步，不在Windows改Mac專屬碼。詳細見[進度](PROGRESS.md)末段與[相容性查證及修正](docs/LEGACY-COMPATIBILITY.md)，前段未修正狀態是授權前歷史。

## 2026-11-03：M25 CPN 大寫 F 輸入查證（尚未修正）

使用者回報 Mac 0.1.6 BSI020020 訂單明細 CPN 無法輸入大寫 F，並表示已註解網頁 my.hotkey.js 的 Shift+F。再次於目前開啟的正式 CPN 欄位測試，Shift+F 未插入文字、Shift+G 正常；已刪除測試 G，保留使用者原有 fff，沒有儲存／取消訂單、導頁或重啟 App。這次測的是半形 F；全形 Ｆ 未獨立測試。

客戶端 src/common/keyboard.h 仍明確將 Shift+F 判為 IsWebsiteShortcut，src/app/app.cpp 的 OnPreKeyEvent 標記為快捷鍵，OnKeyEvent 回傳 true，會攔下正常文字輸入。前輪相同 0.1.6 二進位的純 HTML 隔離頁亦重現 F 只有 keydown／keyup、沒有 beforeinput／input，大寫 S 則正常，無須 OA 熱鍵程式即可重現。證據保留於 artifacts/verification/macos-m25。現行執行路徑為 artifacts/macos-arm64/oaClient2.app，主執行檔 SHA256 仍為 b8715817e17036d7b05e830db48433232e6293c286a4390a9769f00a48ccd862。

本輪僅查證與記錄，未修改產品／my.hotkey.js、重編、安裝或發布；App 保持開啟。後續需修正客戶端 Shift+F 攔截並於 Mac 重編／實測；目前共用來源已含 W36／0.1.7，不能把重編結果誤稱為原 0.1.6。其他未驗收項目保持。

## 2026-11-03：M25 取消客戶端 Shift+F 攔截

依使用者明確要求，移除 src/common/keyboard.h 中 Shift+F 的唯一攔截條件；既有 OnPreKeyEvent／OnKeyEvent 因此不再將它當成快捷鍵處理。其他按鍵政策不變，未修改網頁 my.hotkey.js 或 Windows 專屬來源。既有 core_tests.cpp 的 Shift+F 預期改為一般文字輸入，保留原有未提交的 W36 檢查。

以 xcrun clang++ 直接編譯現有共用＋Mac 平台核心測試，151 checks／0 failures，包含 Shift+F 不攔截及其餘快捷鍵、INI／Mac 保存保護；證據 artifacts/verification/macos-m25/shift-f-fix/core-tests.log。初次直接使用 PATH clang++ 未帶正確 SDK 而失敗，改用 xcrun 後成功。未執行完整 CEF App 建置／UI 修正版驗收：原 Library/Caches/oaClient2/deps 與 build/macos-arm64 目前不存在，Downloads／private tmp 亦未找到對應 CEF SDK。未下載／升級依賴。

本次完成來源修改，現有 0.1.6 App 未更新或重啟，使用者目前開啟的 App 仍是修正前版本。後續完整重編需恢復原固定 CEF SDK；目前共用來源版本為 W36／0.1.7，須按實際來源版本記錄交付，Windows 同一共用修改的編譯／實機回歸待 Windows 環境執行。未安裝、提交、推送或發布。

## 2026-11-03：M25 Mac 0.1.7 編譯與交付完成

依使用者「移除後進版0.1.7編譯」授權，Mac main.mm 啟動版本同步0.1.7；CMake／共用標題與網頁client_version已為W36的0.1.7，直接沿用，不回退共用INI BOM／啟動修復。Shift+F已從唯一keyboard.h政策移除，其他快捷鍵保持，未修改OA網頁或Windows專屬碼。

原本機CEF SDK／build缺失，重新下載同一固定CEF154.0.34 macosarm64官方套件；307056359 bytes、SHA256 2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe與既有紀錄一致。使用Xcode工具鏈／SDK完成Release、CTest1/1、151 checks／0 failures、deep strict簽章與10份Mach-O全arm64核對；SDK／原壓縮檔／build均保留於原Library/Caches/oaClient2路徑。

使用者已處理訂單並關閉舊App後，package-macos.sh更新artifacts/macos-arm64/oaClient2.app，265份檔案／連結／mode與build一致；bundle版本與實機標題均0.1.7，主執行檔SHA256 3b1494c142fb22ec82820feca63f5fd35b8ac671098bab18f0763dcacc0d77e4。294份受保護Windows來源／交付／prg／發布及個人Mac INI／picture雜湊不變。

實際交付App以隔離Cocoa home及僅測試用--use-mock-keychain載入localhost純文字頁；trusted Shift+F的keydown／keypress／beforeinput(data=F)／input(value=F)／keyup完整出現，畫面顯示F。此參數未加入產品／個人設定；正式OA CPN、正式鑰匙圈及其他原待驗收項目仍留使用者驗收，不以合成頁代替。測試Cmd+Q正常走既有登出，ACK30ms、SHUTDOWN_COMPLETE與主程序退出，localhost server已停止；退出後AX查詢timeout不代表程序殘留。

證據：artifacts/verification/macos-m25/build-0.1.7內build.log、ctest.log、package.log／package-results.json、events.jsonl／shift-f-results.json、runtime-application.log及protected-before.json。未安裝Applications、提交／推送、改Tag或發布；Windows須在Windows環境重編／回歸此共用Shift+F修改。前段未重編／App仍0.1.6為此次編譯授權前狀態。

## 2026-11-03：W37 Windows 0.1.7 Shift+F最新交付

已依使用者要求沿用M25的共用Shift+F移除來源，重新編譯Windows並只更新artifacts/oaClient2/oaClient2.exe，版本維持0.1.7。MSVC Release／CTest1/1、160項通過，包含Shift+F不攔截；本輪未再修改產品來源或網頁，保留W36 INI編碼／自動修復與其他熱鍵政策。

build／交付SHA256：76d28963b6a585039a7992860f9e21f21d05e759f669c29d85cd763b117b6a32。567份來源／測試／腳本、個人INI／CEF／Reptool／prg及Mac產物保護檔案不變，SDK／build保留；未提交／推送／改Tag／發布。本輪未操作App，Windows Shift+F實際輸入及正式OA留使用者測試，不能以Mac結果宣稱Windows UI驗收。詳見[進度](PROGRESS.md)W37與artifacts/verification/windows-w37-shift-f，前段Windows待重編已由本段取代。
## W38：列印預覽保留報表背景（2026-11-11）

使用者回報IMG列印預覽與MRT預覽的標題色彩不同，並已開啟Windows App供檢查。已在現行0.1.7同一份Packing List重現：MRT與報表輸出Blob頁為黑底白字，輸出頁的Chromium完整列印預覽因「背景圖形」未勾選而變成白底淡字；手動勾選後立即恢復黑底白字。原附件Invoice與Packing List內容不同，只以同報表對照確認色彩原因，不修改報表標題／欄位或OA資料；未實際列印或傳送到印表機。

共用src/app/app.cpp於任何瀏覽器建立前讀取printing.print_preview_sticky_settings，保留既有字典與appState其他欄位，只設定version=2及isCssBackgroundEnabled=true。每次啟動重新套用預設，配合原網站profile清理；原生預覽內仍可手動切換。政策失敗記錄原始CEF診斷、繁體中文回報並停止啟動。不改INI欄位、網站／MRT、Reptool或列印引擎，不注入網站CSS。

Windows MSVC x64 Release／CTest1/1、160 checks／0 failures通過，版本維持0.1.7。build EXE SHA256：e5559db624def5e206de68c99a46ff0eca659f2c6fc9db5d67a6a364d3fc22ef。新增tests/pages/print-background.html供直接／Blob原生預覽回歸；修正版首次啟動、重啟及交付EXE更新尚待執行，已詢問使用者目前是否有未儲存工作，未關閉正式主窗。正式報表勾選背景的觀察是原版手動對照，不當成修正版已驗收。本輪建立的報表彈窗已關閉、原MRT頁保持開啟。

建置內的正常權限CTest已完整通過；另一次受限工具環境直接重跑核心EXE停在外部協定檢查之後，已取消該重跑，不把它當成通過或覆蓋CTest結果。證據在artifacts/verification/windows-w38-print-background（build.log、ctest.log、app-before.cpp、baseline-status.txt與protected-before.json）；UI畫面由Computer Use回傳，未另存。保留接手時既有未提交差異；未提交／推送／進版／發布。Mac專屬碼與.app未改，共用政策須在macOS重編實測；SDK／下載包／build保留。
## W38：使用者授權後完成更新與Windows實測（2026-11-11）

使用者已回覆「可以關閉並重開」。已正常關閉原App，僅以package-windows.ps1 -ExecutableOnly替換交付EXE；build與artifacts/oaClient2/oaClient2.exe的SHA256皆為e5559db624def5e206de68c99a46ff0eca659f2c6fc9db5d67a6a364d3fc22ef，版本維持0.1.7，CEF／prg不重打包。

使用實際交付EXE與localhost合成頁，首次原生列印預覽、Blob彈窗列印、正常退出後清除profile再重啟的首次預覽，均自動保留黑底白字、淺藍色底及條紋背景圖片；無需手動勾選。紀錄每次有PRINT_BACKGROUNDS_ENABLED，首次偏好appState亦核對version=2及isCssBackgroundEnabled=true。兩輪測試正常SHUTDOWN_COMPLETE，合成server已停止；未點列印或實際輸出檔案。正式OA／MRT最終報表與印表機仍由使用者驗收，不把合成頁當成正式報表已驗收。

受限環境本機server無法供桌面程式連線，改以正常權限loopback server；最後工具直接啟動正式OA繼承套件重導向，既有PROFILE_PATH_REJECTED正確拒絕，未放寬資料清理。已關閉提示並改從使用者原開啟的檔案總管啟動。上述工具環境問題與列印色彩修正分別記錄。

266份保護檔案最終與接手快照一致，含INI、CEF、prg、picture與Mac平台來源；測試過程正常關閉曾更新Window欄位，最後保留目前狀態，沒有回寫測前快照或保存合成URL。Mac.app未修改，Mac共用政策仍須目標平台重編／實測。證據新增runtime-first.log／runtime-restart.log／runtime-final.log、first-print-state.json、protected-result.json與results.json；未提交／推送／進版／發布，SDK／下載包／build保留。前段待重啟／未交付狀態由本段更新。

最後已從既有檔案總管成功啟動修正版，正式OA首頁載入完成、顯示0.1.7及未登入，保留開啟供使用者測試；未操作登入。最終開啟以Computer Use畫面核對，runtime-formal.log僅保留先前工具直接啟動的路徑拒絕紀錄，不將其當成此次檔案總管成功啟動的紀錄。

## W39：Windows進版0.1.8（2026-11-11）

依使用者「進版」要求，將CMakeLists.txt版本、共用app.cpp主視窗標題及兩處網頁client_version、Windows main.cpp啟動版本同步為0.1.8。僅調整版本字串，保留W38列印背景預設、INI／UserSet及其他現行行為；Mac專屬來源／0.1.7.app未修改，共用版本與W38政策須回macOS重編回歸。

Windows MSVC x64 Release／CTest1/1、160 checks／0 failures通過；package-windows.ps1 -ExecutableOnly僅替換artifacts/oaClient2/oaClient2.exe，build／交付SHA256一致：123f0884fa82b405cbb7fdbceebb6a8f3bedcf4df333ae86e542589b7a46d2f1。沿用本次已授權正常關閉／重啟；第一次拷貝時舊App仍在既有背景退出階段而檔案鎖定，等待退出後更新成功，沒有強制結束程序。

527份受保護檔案與本輪接手一致，含正式INI、CEF、prg／picture、Mac平台來源與完整.app。沒有重跑完整W38預覽矩陣或正式報表／印表機，前輪0.1.7合成結果與其他待驗收範圍分開記錄。證據artifacts/verification/windows-w39-version-0.1.8：建置／CTest、版本修改前來源副本與保護清單。保留全部既有未提交修改；SDK／壓縮檔／build保留，未提交／推送／建立Tag／打包ZIP／發布。

已從檔案總管重新開啟交付EXE，Computer Use確認正式OA視窗標題為「炬塔資訊系統 [用戶端版本 0.1.8]」，保留開啟供使用者操作；未執行登入。工具第一次因未擷取幾何而點擊失敗，重新擷取後已正常開啟。

## 2026-11-11：M26 Mac 沿用 Windows W38／W39，交付 0.1.8

使用者要求Mac與Windows相同修改及進版，並確認原「0.1.18」為0.1.8、Windows已停止編輯／建置／Git且Dropbox同步完成。接手main／HEAD 8d104ba，無Git lock或conflicted copy，保留全部既有未提交差異。本輪產品只將Mac main.mm啟動版本0.1.7同步0.1.8；CMake／共用標題與client_version、W38列印背景政策直接使用原共用來源，沒有複製、重寫或修改Windows專屬碼。Shift+F取消攔截與INI／UserSet保存保持現行契約。

既有固定CEF154.0.34 arm64 SDK／壓縮檔／build均存在，直接增量編譯，未下載／升級或清除。Mac Release／CTest1/1、151 checks／0 failures、deep strict簽章及10份Mach-O全部arm64通過。package-macos.sh已更新artifacts/macos-arm64/oaClient2.app；bundle與實機主窗版本0.1.8，265份檔案／連結／mode與build一致，主執行檔SHA256 0265eb58d47598d6fffb7d8c05631a23df104369cc8fc6176e9cbb4ad1ca8f38。323份保護檔案雜湊不變，含共用來源／CMake／測試／腳本、Windows來源及交付／prg／發布、個人Mac INI／picture。

實際交付App以隔離Cocoa home及僅測試用--use-mock-keychain，載入tests/pages/print-background.html的localhost頁。直接Ctrl+P、Blob彈窗右鍵列印及正常退出清除profile後再啟動的首次原生預覽，均自動保留黑底白字、淺藍底與條紋背景，未手動勾選背景。首輪Preferences的appState核對version=2及isCssBackgroundEnabled=true；兩輪START／SITE_DATA_CLEARED／PRINT_BACKGROUNDS_ENABLED均確認。Blob視窗Ctrl+P／Cmd+P未開預覽，改用原生右鍵列印完成，未修改或宣稱修正該視窗快捷鍵。沒有實際列印／存PDF，正式OA／MRT與印表機留使用者驗收。

兩輪Cmd+Q正常登出ACK15ms／28ms、SHUTDOWN_COMPLETE，測試App及localhost server已停止。測試專用參數／網址未寫入產品或個人設定；正式鑰匙圈／注音及其他既有未驗收項目不擴大完成。證據在artifacts/verification/macos-m26-0.1.8：build.log、ctest.log、package.log、first-print-state.json、application.log、protected-before.json、results.json及runtime紀錄，UI畫面由Computer Use回傳。只更新本機交付，未安裝Applications、提交／推送、改Tag、打包公開ZIP或發布；Windows本機0.1.8保持。前段Mac仍0.1.7／W38待重編由本段更新。

## 2026-11-12：G01 提交與推送授權

使用者明確要求「commit, push」。本批納入截至Windows W39／Mac M26的0.1.8既有未提交來源、跨平台附件選檔、外部協定、亮色外觀、繁體中文錯誤、下載詢問、INI UTF-8 BOM／自動修復、Shift+F修正、列印背景預設，以及測試素材／建置腳本／交接文件。遠端沿用origin的既有GitHub repository及main，不建立新遠端、Tag或Release；App／EXE／SDK／建置產物、個人INI／picture／profile及本機驗證紀錄按既有忽略規則排除。

提交前確認遠端main與本機基準8d104ba一致，37份待提交文字檔無二進位／解碼替代字元或掃描到的私密金鑰／token，git diff --check通過，Mac交付雜湊仍與M26驗證結果一致。本輪未改產品、重編或重跑實機功能；既有Windows160項、Mac151項與各自驗收限制以各工作紀錄為準，不宣稱正式OA／MRT／印表機全部驗收。此批依授權提交後推送origin/main，最終提交與遠端一致性以Git核對結果為準；未發布新版下載檔。

## 2026-11-12：R03 公開發布 v0.1.8（Windows／Mac）

使用者明確要求publish release，沿用既有測試版形式，新增[oaClient2 v0.1.8 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)，提供Windows x64／Mac Apple Silicon arm64 ZIP及各自.sha256，共4個資產。來源與v0.1.8 Tag固定a3de8b3f8cfd046912bfef19ae7dbf0865df3f6e；前輪G01已實際commit／push並核對遠端一致。本輪直接打包既有各平台已建置的0.1.8交付檔，不重編、不擴大正式OA／MRT／印表機等驗收，也不安裝App。

Windows ZIP 189895114 bytes，SHA256 335c30631616fa0cac24d7da878d08643ee02c4b705f841a7a1e321198ce8199；240檔為EXE、安全範例、CEF234及現用精簡prg4，不補回其他工具。Mac ZIP 144472509 bytes，SHA256 2f5b406cc3acf542c994c5fcb817facec480a73da911ab44874f9594da41f2b8；只有完整.app，解壓265份檔案／連結／mode與交付一致、10份arm64 Mach-O及deep strict簽章通過。兩平台排除個人INI／網站登入與儲存／picture／logs／快取／tpl／SDK／build，Mac未做Developer ID簽署或公證。沿用Windows160項及Mac151項與原生預覽實測，詳細限制保留各工作紀錄及Release說明。

四個公開資產的GitHub大小／digest與本機一致；未帶登入憑證從公開URL重新下載ZIP／校驗檔，全部逐位元相同，兩ZIP CRC及Windows240檔SHA256通過。既有v0.1.6 Release／4資產ID、大小、digest及固定Tag67e29679→0fe6f35保持不變，522份交付／個人設定保護檔雜湊不變。草稿Tag API查詢曾回傳404，該步完整遠端雜湊核對實際在公開後補做通過，不能把它寫成發布前已完成。

本次Release ID 442477933，資產ID／下載URL／校驗及保護結果見artifacts/verification/releases-v0.1.8/results.json；本機ZIP保留artifacts/releases/v0.1.8，SDK／原壓縮檔／build保留。舊Release與Tag不移動，發布結果文件另行提交推送、v0.1.8仍指向實際App來源a3de8b3；U01程式內線上更新未實作。前段「未發布／公開仍0.1.6」為本次授權前歷史。
