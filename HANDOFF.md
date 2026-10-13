# oaClient2 接續交接

最新Windows W30已由使用者驗收、提交／推送並同版更新公開ZIP；版本0.1.6、Tag與Mac資產保持，詳見末段。Mac新共用關閉保護仍須在macOS編譯回歸。

更新：2026-10-13。這是 Windows／Mac 上 Codex 的接手入口；以下歷史狀態以最新交接段為準。

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
