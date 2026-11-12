# oaClient2 工作目標與開發規劃

更新日期：2026-10-12（Asia/Taipei）。

## 目前狀態與授權

Windows 簡易版 0.1.6 已實作、建置與交付；環境於 11:25:29 完成後起算，工具／CEF 準備與測試不計入兩小時。使用者已驗證 0.1.0 預覽／注音正常；0.1.1 的 Microsoft 注音浮窗已在0.1.2修正，由使用者確認正常；最新列印預覽待回歸。Mac 僅 arm64，已完成首次移植／建置與初輪測試，列印／注音待使用者驗收。

接手入口：[HANDOFF.md](HANDOFF.md)。實際進度：[PROGRESS.md](PROGRESS.md)。操作與 INI：[WINDOWS-USAGE.md](docs/WINDOWS-USAGE.md)。歷史決策：[CHANGELOG.md](CHANGELOG.md)。以下保留需求與來源查證，功能狀態以 PROGRESS.md 為準。

## 專案目的

開發跨平台的 oaClient 第 2 代，在盡量不修改既有 OA 網頁的前提下，提供網站宿主、本機整合、正常注音輸入與瀏覽器內建列印預覽，並改善可量測的啟動體驗。

## 已確認的範圍

| 項目 | 決策 |
| --- | --- |
| 目標平台與順序 | 先 Windows，完成該階段驗證後，再於 Mac 開發 macOS；Linux 正式支援另行排期。 |
| Mac CPU 架構 | 僅 Apple Silicon（arm64）；Intel／x86_64 與 Universal 版本不在範圍內。 |
| 專案共用 | 不同系統沿用同一份專案資料夾與原始碼，平台建置和執行資料各自放在本機非同步目錄。 |
| OA 網頁 | 盡量沿用，客戶端承接原命令與回傳方式。 |
| 初版網站 | `https://oa.lysm.com.tw/`；INI 指定，正式網站已實機載入，HTTP 200。 |
| 網站資料清理 | 啟動前清除 oaClient2 專用瀏覽器資料；網站快取、Cookie、登入狀態與網站儲存都不保留。 |
| 程式設定 | 使用者明確要求跟舊 oaClient 一樣保存在 .ini，並可修改 INI 內容；保留程式設定，清理不能刪除它。 |
| 優先改善 | 注音輸入、啟動速度。 |
| 網頁列印 | 必須有瀏覽器內建的分頁預覽及列印設定介面。 |
| Windows 報表 | 保留呼叫既有 Reptool；報表內部與列印引擎暫不重寫。 |
| macOS 報表 | 行為與範圍尚待討論，不宣稱可執行 Windows Reptool。 |

2026-10-12 使用者確認注音額外浮動組字窗為 Windows 專屬問題，Mac 不需測試該項，亦不列為 Mac 待驗收。Mac「正常注音輸入」要求保留，僅驗證一般輸入與焦點；不把 Windows 的浮窗回歸項目套用到 Mac。

## 既有專案閱讀結果

- 主要來源：`C:/Users/Lenovo/Dropbox/delphi-project/oaClient64`。
- 既有宿主為 Delphi VCL 與 CEF；實際編譯目標不能僅由 oaClient64 名稱推定。
- `oaClient.dpr` 管理程序單例、CEF 啟動、快取與結束流程，含 `--enable-print-preview` 的條件設定。
- `fmMainOaClientu.pas` 管理視窗、網頁、IME、下載、設定注入及 Console 命令。
- `IUty.pas` 管理路徑、INI 與共用工具。主要來源有 CP950／Big5 編碼。
- OA 網頁透過 Console 訊息要求儲存設定、開啟報表、讀取磅秤、開啟資料夾等，客戶端再執行 JavaScript 回傳。
- 已讀到的命令包括 `ini`、`prt`、`scale`、`load-userset`、`opendir`、`clearcache`、`openurl`、`clientReady`、`loginParam`、`printLandscape`，另有 `loginState`／`apiUrl` 訊息及自訂協定處理；這是初步盤點，並非完整相容性驗證。
- 磅秤目前讀取外部文字檔，不是客戶端直接讀取串列埠。
- `OpenReport` 呼叫 `Reptool.exe`，傳入報表命令、附加登入參數與設定檔路徑。新版本需核對參數引號、路徑、編碼與呼叫行為。
- 既有報表工具包含 FastReport 與 Office COM 相依；跨平台宿主不代表這些報表能力自動跨平台。
- 舊版歷史曾有 IME／焦點／PDF 問題及大幅優化撤回；以目前來源與實測結果為準。

## 技術方向及查證紀錄

| 層次 | 目前方向 |
| --- | --- |
| 主程式 | C++20。 |
| 網頁宿主 | CEF Chrome runtime；必須區分 Chrome style 與 Alloy style 的介面及功能。 |
| 視窗介面 | 主網站 CEF Views Chrome BrowserView；Console 獨立 Chrome CefWindow，由 Windows 嵌入下方。 |
| 建置系統 | CMake。 |
| 網頁 | 沿用既有 HTML／JavaScript。 |
| 本機功能 | 共用服務與 Windows／macOS 平台整合分開。 |

截至 2026-10-12 的查證結果：

1. Electron 44.7.0 的 `ShowScriptedPrintPreview`／`RequestPrintPreview` 回報無效呼叫，不能直接提供使用者要求的 Chrome 式預覽。`print()`／`printToPDF()` 不等於內建完整預覽；因此撤回先前將 Electron 列為第一候選的建議。
2. CEF Chrome runtime 有 Chrome UI 與列印預覽整合，Windows 已固定 CEF 154.0.34，macOS 套件與實測尚待接續。
3. CEF macOS 問題 #3410 涉及預覽「儲存 PDF」時瀏覽器關聯失敗；問題已關閉並標示 M154，主分支有對應修補。仍須核對實際採用的已發行套件是否包含修補，不能將主分支狀態直接視為正式版本驗證通過。
4. WebView2 在 Windows 有內建瀏覽器預覽；Tauri 的 macOS 使用 WKWebView 原生列印流程，兩者不是同一套 Chrome 介面。
5. Qt WebEngine 官方範例使用 QPrintPreviewDialog 組合預覽，與直接沿用 Chrome 預覽不同。

查證來源：

- [Electron 44.7.0 列印原始碼](https://raw.githubusercontent.com/electron/electron/v44.7.0/shell/browser/printing/print_view_manager_electron.cc)
- [CEF 架構文件](https://github.com/chromiumembedded/cef/blob/master/docs/architecture.md)
- [CEF macOS 問題 #3410](https://github.com/chromiumembedded/cef/issues/3410)
- [CEF 修補設定](https://raw.githubusercontent.com/chromiumembedded/cef/master/patch/patch.cfg)
- [WebView2 列印文件](https://learn.microsoft.com/en-us/microsoft-edge/webview2/how-to/print)
- [Wry macOS 列印實作](https://raw.githubusercontent.com/tauri-apps/wry/dev/src/wkwebview/mod.rs)
- [Qt 列印預覽範例](https://doc.qt.io/qt-6.8/qtwebengine-webenginewidgets-printme-example.html)

## 開發工具規劃

- 共用編輯器：VS Code，搭配 C/C++、CMake Tools。
- Windows：獨立 Visual Studio Build Tools 即可，完整 Visual Studio IDE 為選配。先以 Build Tools 2022、MSVC v143 x64／x86、Windows SDK 與 CMake 為基準，最終版本以選定 CEF 套件要求為準。
- macOS：Apple Silicon Mac、Xcode 與 Command Line Tools，使用 arm64 工具鏈與 CEF 套件；版本需配合 CEF，實機用於編譯、注音及列印預覽驗證。
- 網頁除錯：CEF DevTools；版本管理：Git。
- 本機曾進行初步唯讀查詢：Git 可用，Python 命令指向 WindowsApps 別名；未由 PATH 查到 CMake／cl／Ninja。這不等於完整工具安裝盤點，也未確認 Python 可執行。
- Windows 已沿用既有工具，完成 CEF 下載校驗與編譯；詳細版本見 docs/ENVIRONMENT.md。

來源：[CEF 範例建置指南](https://github.com/chromiumembedded/cef-project/blob/master/README.md)、[Microsoft 獨立 Build Tools 說明](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170)、[VS Code CMake 說明](https://code.visualstudio.com/docs/cpp/cmake-quickstart)。

## 簡易版與本輪增補目標

| 目標 | 驗收方式／目前狀態 |
| --- | --- |
| 載入網站 | INI 指定 OA，HTTPS 200，實機載入；已實作。 |
| 瀏覽器列印預覽 | Ctrl+P／window.print 使用 Chrome 內建預覽；0.1.0 使用者回報正常，最新版本待回歸。 |
| 注音 | 0.1.2 Microsoft 注音由使用者確認正常，無額外浮動組字窗；其他情境待測。 |
| 清理網站資料 | 啟動前專用 profile 全清，INI／picture 保留；核心合成資料測試通過，真實儲存逐項回歸待做。 |
| 工具列／Console | 沿用原圖示與順序，下方開關 Console；主視窗保持最大化。 |
| INI／截圖位置 | Config.ini 與 EXE 同目錄，瀏覽該目錄；只截 oaClient2 視窗，JPG 存入 picture。 |
| 應用圖示 | 沿用 oaClient MAINICON，套用 EXE、視窗與工作列。 |
| Reptool | 最小呼叫契約已寫入，真實啟動與報表未驗收。 |

## INI 與網站資料的界線

- 程式設定檔名稱採 Config.ini，依最新要求放在主程式同目錄，不放在 CEF profile 或可清除快取目錄內；Mac bundle 對應位置待設計。共用專案保留不含個人資料的設定範例；實際 INI 不納入 Git、不與另一平台共用機器路徑。
- 使用者可手動修改內容；規劃支援首頁網址、視窗偏好及網站資料清理選項，下次啟動讀取並套用。實際欄位、UTF-8 與相容範圍已列明於 docs/WINDOWS-USAGE.md。
- 網站預設為 oa.lysm.com.tw；預設啟動前清除全部網站資料。已實作基本 INI 讀寫，不代表完整舊設定相容。
- 網站資料涵蓋快取、Cookie、登入狀態、Local Storage、IndexedDB、Service Worker 等專用瀏覽器儲存；啟動前清理，不保留上次網站工作階段。
- 網站登入憑證、Cookie 與網站儲存不能透過 INI 還原，避免「資料已刪除但又自動登入」。程式偏好與網站會話需分開辨識。
- Reptool 的程式路徑、設定路徑及當次登入參數依已確認契約規劃；不清除既有 Reptool／oaClient 的設定，也不把網站登入 token 當成需要永久保存的程式偏好。
- 驗收包含修改 INI 後網址／視窗設定生效、資料清理後 INI 不變、重新登入需求，以及錯誤或缺少設定時的可辨識結果。清理目錄須確認為本程式專用，避免誤刪共享專案或其他資料。

## 共用資料夾與跨平台建置

目前目錄規則如下；已建立 Mac 平台來源，尚未建立共用 CMakePresets.json：

| 資料 | 存放與使用規則 |
| --- | --- |
| 原始碼、CMakeLists.txt、共用 CMakePresets.json | 共用專案內；不依賴電腦上的固定路徑。 |
| 共用功能 | 規劃放在 src/common，處理設定、命令解析及共用生命週期。 |
| 平台功能 | 規劃放在 src/platform/windows、src/platform/macos；Windows Reptool 呼叫不進入 Mac 編譯。 |
| 文件及安全設定範例 | 共用專案內，全部使用相對文件連結與 UTF-8／LF。 |
| CEF SDK 與平台資源 | 各系統本機非同步目錄，以本機參數傳入建置；Mac 固定 arm64 套件，版本、架構、來源與雜湊在交接時記錄。 |
| 建置目錄 | 各系統本機非同步目錄，例如 Windows 的 LocalAppData/oaClient2/build/windows-x64、Mac 的 ~/Library/Caches/oaClient2/build/macos-arm64；最終路徑於環境設定時固定。 |
| 執行設定、profile 與快取 | profile／快取在各平台本機目錄；INI 在主程式同目錄，截圖在同目錄 picture，清理不得刪除。 |
| 執行檔與安裝包 | 編譯輸出仍在本機；使用者核准完整交付放 artifacts/oaClient2，Mac 用另一平台交付目錄。 |

`.gitignore` 不影響 Dropbox 同步。即使 Git 忽略 build、快取或套件，仍須將這些資料放在共用資料夾之外。CMake 建置必須使用明確的 source／build 目錄，不能依賴目前工作目錄或重用另一系統的 CMakeCache.txt。

Windows 與 macOS 使用不同根路徑是正常的；以專案根、標準平台路徑及建置參數定位檔案。檔名大小寫需一致；不依賴 Windows 捷徑、符號連結或同步檔案權限即可跨平台使用。

## 後續工作階段

1. **W01：Windows 環境與版本**：核對本機工具，固定 CEF 與工具鏈；套件、建置目錄放在共用資料夾外，保留後續 Mac 編譯所需的共用結構。
2. **W02～W05：Windows 四項功能**：網站載入、內建列印預覽、注音與快取清理；驗收細項見簡易版目標表及 PROGRESS.md。
3. **W06：Windows Reptool 相容**：保留既有呼叫契約，核對路徑、參數引號與編碼；最小呼叫已納入簡易版，實際驗收待做。
4. **W07：Windows 交付與交接**：可執行版本、建置說明、操作說明、已通過／未通過／未測的驗證紀錄、CEF 與工具版本，及 Mac 下一步。
5. **M01～M03：Mac 接續**：在同一份已同步專案中設定 Apple Silicon Mac 的本機工具與 arm64 依賴，完成 arm64 編譯，再於 Mac 驗證載入、內建預覽、注音與快取；必要的平台修正需回歸 Windows，不規劃 Intel 或 Universal 建置。
6. **後續完整相容與穩定化**：完整 Console 命令、設定還原、登入／登出、下載、自訂協定、不同電腦／印表機、焦點／DPI 與簽署等；Linux 另行排期。

討論中曾估算完整範圍試用版約 4～6 週、穩定版約 6～10 週；這是以單人開發、兩平台設備備妥及能持續取得測試回饋的條件式估計，並非目前已啟動的排程。簡易版已授權並於環境完成後起算；額外需求與測試分別記錄。

## 尚待決定／驗證

- 最低 Windows／macOS 版本；Windows 初版目前為 x64，Mac 固定 arm64。
- Microsoft 注音浮窗已驗收；其他輸入法／焦點／DPI 情境待測。
- 完整舊 OA 命令及設定還原範圍、Reptool 實際驗收。
- Mac CEF 原生子視窗／Console、內建預覽與 #3410 配套、Config.ini 與 app bundle 的對應路徑。
- 啟動速度基準、不同印表機與正式簽署。

## 初始化歷史（不代表現況）

以下為最初只有文件時的記錄；目前已有程式與 Windows 交付版。

## 本次初始化紀錄

- 建立 `AGENTS.md` 與本工作規劃文件。
- 建立 `.gitignore`，排除建置產物、CEF 套件、快取與個人執行設定。
- 已成功初始化本地 Git，分支名稱為 `main`，尚無提交與遠端。
- 未建立程式碼、程式骨架、遠端或提交，未安裝／下載依賴。

## 本輪計畫更新

- 確定 Windows 先完成，macOS 在 Mac 上使用相同專案接續，不另建分岔專案。
- 補上跨系統共用資料夾、依賴／建置／執行資料隔離與同步規則。
- 建立 PROGRESS.md、HANDOFF.md 與 CHANGELOG.md，讓 Mac 上的 Codex 可以從實際狀態接續。
- 新增 README.md 文件入口與 .gitattributes 文字換行規則。
- 本輪仍只更新文件與 Git 文字規則；沒有開始程式實作或安裝工具。

## 0.1.2／0.1.3 增補決策

- CEF 檔案集中 cef/；0.1.2／0.1.3歷史採root launcher與cef bootstrap。0.1.6依使用者新要求改為獨立EXE、不使用沙箱，CEF目錄只放官方runtime元件。
- URL 對話框依使用者圖，單行預選網址、藍色提示、置中確定、X／ESC 取消。
- UserSet.ZoomPercent 即時保存並於主框架載入後重新套用，避免導航重置縮放。
- 視窗與工具列8張圖檔編譯進主程式 EXE，不放在交付根目錄；assets 保留共用來源。Mac 透過平台資源讀取及 app bundle 實作相同行為。

## 0.1.4 已授權範圍與決策

本輪新增完整UserSet偏好保存、回填，含userid及公司別；承接cmd=ini、load-userset及原func腳本，保留鍵名大小寫、空值與序列化格式。從INI重建當次偏好Cookie，不保留舊網站會話。關閉依舊版查登入狀態／logout／最多約10秒等待，改用非阻塞CEF任務。hcopen沿用OS協定處理器，使用者自行測試。舊Bin/prg完整複製至專案及Windows交付，Reptool以相對路徑定位並保留兩個命令列參數、工作目錄及按鈕回復。

完整來源／偏好清單／流程差異見[相容說明](docs/LEGACY-COMPATIBILITY.md)，檔案SHA256見[prg清單](docs/PRG-INVENTORY.md)。Mac來源仍未實作；這些設定與CEF契約在相同專案接續，Windows外部exe不可在Mac直接使用。

## 0.1.5 關閉保存修正

使用者回報關閉時Cannot replace Config.ini／Windows error5。設定與暫存內容相同、沒有readonly屬性；避免重複替換相同內容，既有檔優先保留metadata替換，只有改名受阻但仍可寫時原檔保存，不修改使用者ACL／readonly。普通保存、真正拒寫及資料保留均分別測試，不把刪除權限和寫入權限混為一談。

## 0.1.6 截圖與部署

截圖資料夾由pict改picture。應用功能全部編入根目錄oaClient2.exe，CEF官方runtime保持cef/且不混入應用檔；CEF版本不變時一般修改只更新EXE。使用者先接受保留沙箱時根目錄chrome_elf副本方案，後續明確改選「不使用沙箱」「只用來跑ERP」，以後者為準，前者未實作。Mac沿用同一專案及picture／INI保留契約，平台啟動與部署需在Apple Silicon另行實作驗證，不能複製Windows實作。

## Windows交付目錄與壓縮

依2026-10-12使用者最新要求，Windows交付使用artifacts/oaClient2，方便直接壓縮整個oaClient2資料夾。內容保留oaClient2.exe、cef、prg、Config.ini、picture及使用者其他資料；不因改名重新建立舊windows目錄。Mac交付維持獨立artifacts/macos-arm64，本機依賴與中間建置仍不進同步目錄。

## 交付prg由使用者維護

2026-10-12使用者已刪除Windows交付prg不需要的檔案，並明確指示「不要再補回來」。核對artifacts/oaClient2/prg只保留docto.exe、Reptool.exe、TSCLIB.dll、zint.dll。package-windows.ps1已移除整份來源prg複製，後續打包不補回、不覆蓋或清理交付prg。根prg保留歷史副本，不能用來自動恢復；新交付目錄的工具由使用者另行準備。

## 共用來源與線上更新要求

依2026-10-12使用者明確指示，共用部分沿用唯一來源，不重寫、不複製成Windows／Mac兩份。平台差異經src/platform/platform.h與各平台實作處理；必要相依抽取做最小修改，保留既有流程，平台回歸分別記錄。詳細界線及現行待拆相依見[共用程式碼規則](docs/SHARED-CODE-RULES.md)。

U01線上更新保留於Windows／Mac後續工作範圍，尚未實作；來源、版本策略、CEF配套與安裝方式待設計。共用流程保持一份，平台替換／重啟分開；更新須保留INI、picture及使用者prg現況，不補回已刪除工具。

## M01～M03 Mac 移植決策與狀態（2026-10-12）

沿用原 common／app，不重寫業務流程。Mac 使用 Cocoa 入口、CEF Views 主網站、獨立 Chrome Console CefWindow 以 NSWindow 父子關係定位；INI／picture 在 .app 旁，SDK／中間建置／profile 在本機 Library/Caches。Mac 報表明確未支援，Windows 報表與使用者精簡 prg 原樣保留。

CEF 固定同版本 arm64 standard，正式發行提交 14c5a08 含 #3410 修補；內建列印預覽能力與注音仍由使用者驗收。Mac 無沙箱，但沒有關閉網站安全檢查。Windows 共用修改的編譯／實機回歸待執行。Mac ad-hoc 簽章供本機測試，正式 Developer ID／公證／安裝策略未設計完成。

M01／M02 已完成，M03 已通過適當自動／實機項目，保留使用者列印／注音、正式登入／登出與 hcopen 等驗收。CEF 預設部署門檻為 macOS 12；本輪只測 26.7.1，截圖用 macOS 14 起的 ScreenCaptureKit，低版本顯示未支援，不宣稱最低產品系統已驗收。詳細結果見 PROGRESS；U01 線上更新需求保留且尚未實作。

## M04：Windows／Mac 分開的檔案配置（2026-10-12）

使用者正式確認 Mac 執行資料全部集中 ~/Library/Application Support/oaClient2：Config.ini、picture、logs、browser-profile、instance.lock。Mac 編譯交付為單一 oaClient2.app，拖曳至 Applications 即可；首次啟動建立預設組態，後續設定保存到同一位置。CEF／Helper／圖片仍封裝在 .app，SDK／中間建置留本機開發目錄。

Windows 延續 EXE 旁 Config.ini／picture、LocalAppData 網站資料與 logs，與 Mac 配置不同。共用 INI 格式／讀寫及 UserSet 只有一份，平台 GetAppPaths／PictureDirectory 分開提供路徑。詳細對照為[PLATFORM-PATHS](docs/PLATFORM-PATHS.md)，Windows 接手必讀。這項最新決策取代先前 Mac INI／picture 放 app 旁的配置；舊資料保留，不自動匯入或覆蓋。

## M05／W21：共用歡迎頁與平台開發分工

使用者確認 Mac 安裝前預設 URL 空白，設定確認後才保存，首次顯示本機歡迎頁並提供設定網址按鈕；取消不變更 HomeUrl，既有設定直接載入。歡迎頁在 src/common/welcome.h 保持唯一內容，app.cpp 使用原平台 URL 對話框及保存流程。Windows 同樣需求已確認，但 Windows 入口空白預設與驗證留待 Windows 環境，W21 尚未完成。

Mac 專屬程式碼由 macOS 環境開發，Windows 專屬程式碼由 Windows 環境開發；共用來源保持唯一，修改須交接另一平台回歸。兩平台組態位置仍依 M04，不自行改成同一路徑。

## M06／W22：隱藏 Chromium 縮放彈窗

Mac 透過 CEF 154 的 chrome_zoom_bubble 停用提示，維持原放大／縮小階段、UserSet.ZoomPercent 保存及重啟還原。使用者明確指定 Windows 也要、先記錄、到 Windows 再做；W22 未實作。共用 AppContext.hide_zoom_bubble 預設 false，僅 Mac 入口目前設 true，不更改 Windows 交付。

## M07：Mac 正常視窗與再次開啟

使用者回報額外 Chromium 新分頁。Mac 實作 OnAlreadyRunningAppRelaunch：顯示／啟用既有 oaClient2，返回已處理避免預設 Chrome 視窗。網址歡迎頁按鈕離開 Console 回呼後才開 modal，Cocoa 取消採正常 stopModalWithCode。主網站仍是 CEF Views Chrome BrowserView，Console 與登出契約保留；修正與實際回歸分別記於 PROGRESS，不以 API 文件推定所有關閉情境通過。

## M08：Mac 交付目錄只保留 .app

2026-10-12 使用者確認舊交付旁的 INI 與截圖不需要，明確要求刪除。此輪限定清理 artifacts/macos-arm64 的 Config.example.ini、Config.ini、picture 與 Finder .DS_Store，保留 oaClient2.app；現用 Application Support 資料、Windows 交付及驗證素材不在此次清理範圍。打包仍只交付 .app，不新增全目錄自動刪除規則。

## M09：重新編譯與安裝分開

2026-10-12 使用者授權 Mac 重新編譯，追加明確指示編譯完成不要安裝。本輪只準備原固定 SDK、完整編譯／既有測試／簽章與配套核對，更新 artifacts/macos-arm64/oaClient2.app；不安裝到 Applications、不啟動主程式、不改個人組態。結果分列於 PROGRESS M09，未把編譯成功當成重新實機驗收。

## D04：Windows 接續開發提示詞

2026-10-12 依使用者要求整理 W21 相同歡迎頁、W22 隱藏縮放彈窗及兩平台組態配置差異，提示 Windows 專屬碼留到 Windows 環境改。保留共用來源唯一、既有個人網址／UserSet／登出／Reptool／prg 契約，指定 Windows 建置與實機回歸；Mac 結果不擴大為 Windows 完成。本輪僅更新交接文件，沒有新增產品實作。

D04 提示詞已存為 [Windows 接續提示詞](docs/WINDOWS-CODEX-PROMPT.md)，保留原提示內容及 W21／W22 邊界；Windows 專屬程式碼仍留待 Windows 環境處理。

## M10／W23：先隱藏、登出回應或最多三秒後退出

2026-10-12 使用者確認登出 logout 命令，新增關閉體驗：送出一次後立即隱藏主視窗及 Console；背景收到完成回應立即結束，沒有回應則最多等3秒後關閉全部本程式瀏覽器並退出。用 CEF 非阻塞任務與 steady_clock，重複關閉不重送、不延長期限。背景關閉時 beforeunload 自動允許，避免隱藏後仍等待對話框；不以三秒到期宣稱伺服器已登出。

共用 LogoutFlow／app 保持唯一，新模式由平台入口啟用。Mac 本輪完成，Windows W23 留待 Windows 環境實作與回歸，Windows 原輪詢模式暫留，不修改 Windows 專屬來源。Mac 更新交付、不安裝，正式 OA 登出留使用者驗收；INI／UserSet／資料位置與清理規則保持。


## M11／W24：瀏覽 Config.ini 所在目錄（2026-10-13）

使用者已重新定義兩平台「瀏覽目錄」：開啟實際 Config.ini 的父目錄，取代主程式目錄。共用 app.cpp 直接使用 paths.config.parent_path()，工具列提示同步更新，不複製平台工具列、不更改 INI 配置。Mac 目標為 ~/Library/Application Support/oaClient2；Windows 目前 INI 與 EXE 同目錄，W24 留待 Windows 編譯／實機回歸與交付更新。Windows 專屬程式碼在 Windows 環境修改，本輪未動 Windows 專屬碼；Mac 只更新交付 .app，不安裝 Applications。


## M12／W25：網頁資訊與版本標題（2026-10-13）

主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

共用 app.cpp 保持唯一來源，Windows 專屬碼及交付不在 Mac 改；W25 留待 Windows 編譯／實機回歸。Mac 本輪重新編譯只更新交付，不安裝，保留 CEF SDK／壓縮檔／build。


## W25：Windows 相同標題需求確認（2026-10-13）

使用者明確要求 Windows 標題列與 Mac 相同：軟體名稱從 URL 頁面的 document.title 取得，顯示「網頁軟體名稱 [用戶端版本 0.1.6]」；尚未取得名稱時顯示「oaClient2 [用戶端版本 0.1.6]」。共用 M12 實作已備妥，Windows 編譯／實機測試及交付更新留到 Windows 環境。本輪只補記需求與交接，未修改程式或交付、未編譯／測試／安裝，不將 Mac 結果當成 Windows 驗證。


## D03：首次本機提交（2026-10-13）

使用者明確指示 commit，授權建立 main 的首次本機來源提交。提交共用及 Windows／macOS arm64來源、原圖資源、共用設定範例、腳本、測試與工作文件；不納入 artifacts、prg、個人Config.ini、CEF SDK／壓縮檔、建置、profile或快取。Git身分使用既有本機設定，實際SHA以git log取得，未建立遠端／標籤或推送。

本輪僅提交與同步Git交接狀態，沒有修改功能、重新編譯／安裝／操作App；既有Mac75項測試結果與Windows W21～W25待回歸狀態保留。歷史無提交記錄不全面改寫。


## M13／W26：舊版工具列間距與完整字樣（2026-10-13）

依使用者舊版圖片及現行DFM，右側首頁／網址／MAC／瀏覽目錄／截圖／還原比例／縮小／放大寬度採23／23／40／67／38／61／23／23 DIP，合計298 DIP（原346）。高度仍28 DIP、左Console仍30 DIP；保留原字型、圖示、工具順序及命令。右側按鈕左右內部留白各2 DIP，完整顯示MAC、瀏覽目錄、截圖及還原比例，不以省略號／隱藏文字／縮小字型達成間距。

使用同一份app.cpp，不新增平台工具列副本。Mac已編譯及實機核對完整文字；Windows專屬碼與交付未改，W26留待Windows編譯／實機回歸。Mac只更新交付、不安裝；SDK／壓縮檔／build保留。


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


## 2026-10-13：W21～W26 Windows 已接續

使用者確認Mac停止操作及同步完成後，在Windows入口啟用與Mac相同的空白首頁政策、hide_zoom_bubble及background_logout_close。Settings預設物件仍保留既有相容fallback，兩平台入口都明確選擇空白政策；已有INI網址不覆蓋，歡迎data URL不保存。共用welcome／LogoutFlow／app保持原單一來源，W24設定父目錄、W25網站title＋實際0.1.6版本、W26右側298 DIP與完整字樣直接沿用，不重寫。

Windows MSVC Release、CTest1/1與74項，以及本輪UI／兩輪UserSet儲存回歸已通過，交付EXE更新；每項實測、環境失敗與未驗收項目見[進度](PROGRESS.md)最新W21～W26段。背景無回應三秒到期不代表伺服器登出成功。Windows INI／picture仍在EXE旁，個人設定、報表工具與Mac產物保留；SDK／壓縮檔／build不清除。

列印預覽／Microsoft注音、正式OA登入登出／Reptool、hcopen及工具列間距使用者驗收尚未完成；其他DPI、晚建立Console／一般popup特定競態尚未獨立實測，歡迎頁縮放及網址X取消已另行補測通過。U01保留且仍未實作。R02後續ZIP須不含個人INI／快取，Git提交／推送／公開發布仍依授權；不移動既有v0.1.6 Tag、不改Mac資產。


## W27：不顯示Chrome連結狀態提示

使用者要求滑鼠移到OA選單時，左下角不顯示javascript:void(0)。使用CEF正式chrome_status_bubble=STATE_DISABLED停用瀏覽器連結狀態提示；網站選單命令／JavaScript不改，共用app.cpp保持唯一來源。Windows本輪建置／合成選單與子選單實機通過、交付EXE更新，正式OA由使用者驗收。Mac不在Windows重編或改平台實作，需在macOS接續共用設定回歸；U01與其他未驗收範圍保持。

2026-10-13使用者新增授權：先commit／push本輪W21～W27，再接續Windows ZIP打包與公開發布。只納入安全來源／文件／共用測試；ZIP排除個人INI及網站資料，保留既有Mac資產與固定Tag，記錄Windows實際來源提交及下載雜湊。


## D03／R02：Windows發布已執行（2026-10-13）

依使用者先commit／push再打包發布的順序，W21～W27來源7958a60已透過HTTPS推送，Windows x64 ZIP與.sha256補齊既有v0.1.6初版測試Release。以安全清單排除個人INI／picture／logs／網站資料／tpl／SDK／build，只保留現有精簡prg4份；CRC／全部240檔SHA256及公開下載一致，Tag與Mac資產未變。實際來源／雜湊與重現流程見[RELEASES](docs/RELEASES.md)。發布文件及腳本另行提交，不改應用來源。

R02完成打包／公開發布／下載校驗，沒有新增安裝程式或U01線上更新。W21～W27的實作、Windows編譯／合成實機已分別記錄；列印／Microsoft注音、正式OA／Reptool／hcopen及最終間距仍待使用者驗收，其他DPI與窗口競態未獨立驗證。Mac需在macOS重編／實測W27才套用共用設定，不在Windows修改Mac產物。


## W28：登入後不再詢問儲存密碼（2026-10-13）

使用者要求關閉圖片中的Chromium儲存密碼彈窗。共用App在建立瀏覽器前停用RequestContext credentials_enable_service及credentials_enable_autosignin，沒有新增INI欄位、修改OA登入表單或停用網頁安全檢查；設定失敗回報並停止啟動。userid／公司別及其他UserSet偏好回填照舊，不把程式偏好當成密碼或登入token還原。

Windows已實作／MSVC／CTest1/1、74項／舊版正向重現與修正版原生、重啟AJAX實測，本機交付更新；正式OA登入待使用者驗收。共用來源只有一份，Mac平台與產物保持，Mac重編／實測未執行。GitHub ZIP仍為已發布W27，本輪未提交／推送／移Tag／重新發布；列印／注音等與U01未實作不擴大完成。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## R02／W28：0.1.6同版資產替換已完成（2026-10-13）

使用者要求重新打包上傳、不進版，已維持0.1.6／原Tag及Release，Windows同名ZIP與校驗檔替換為來源c5cd549的W28密碼提示修正；Mac資產不變。先上傳兩檔／校驗才替換，公開原URL重新下載兩檔一致，ZIP 189879887 bytes、SHA256 92c371f3，240檔CRC／全部SHA256通過。舊ZIP保留本機歷史證據，發布結果文件另行提交推送，詳細資訊見[RELEASES](docs/RELEASES.md)。

此次授權允許明確替換指定Windows同名資產，取代前段不靜默覆蓋的待授權狀態；不擴大為任意版本／Tag／Mac資產變動。W28正式OA登入仍待使用者驗收，Mac W27／W28待目標平台重編／實測，列印／注音等及U01未實作保持。

## W29：Chrome衝突熱鍵交回網頁（2026-10-13）

使用者要求取消oaClient2內建Chrome的F1／F2／F3／F4／F9、Alt+W、Mod+F、Shift+F、Mod+E／S／N（Mod=Ctrl或Cmd，包含Ctrl+N），不是移除網頁自己的設定。共用common/keyboard.h精確匹配，app.cpp改為網頁優先接收一般加速鍵，OnPreKeyEvent不吞掉事件、OnKeyEvent在網頁處理後攔下指定Chrome預設動作；原F8／F12／Ctrl+P高優先功能及工具列保持。

Windows MSVC Release／CTest1/1、110 checks／0 failures（原74＋36項政策檢查）通過，包含Ctrl／Cmd正向及未列出的組合。共用合成頁tests/pages/keyboard-shortcuts.html已載入。使用者隨後要求「你編譯好，我測試」，因此未繼續逐項實機熱鍵矩陣，Chrome搜尋／儲存／新視窗及真實網頁按鍵接收均待使用者驗收，不宣稱UI熱鍵已通過；Cmd實機亦須在Mac回歸。

本機交付EXE已更新、與build一致，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6 x64。合成server／App已停止，原OA已重開供使用者測試；測試URL只在當次記憶體，未保存INI。使用者新增的f1.js清單保留、不執行／修改／納入Git，Mac專屬碼／產物及prg不改，SDK／build保留。此次未提交／推送／移Tag／重新發布，GitHub ZIP仍為W28；Mac W27～W29需回macOS重編／實測，U01未實作。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## W29／R02：驗收後同版上傳完成（2026-10-13）

Windows W29快捷鍵由使用者回覆「可以了」完成此次驗收，依重新上傳／不要進版要求，來源6f2833b已推送，同名0.1.6 Windows ZIP與校驗檔已替換；Mac資產與Tag保持。ZIP 189880195 bytes、SHA256 849a2678，240檔CRC／全部SHA256及無登入原URL下載一致，舊W28副本保留。範圍只含Windows快捷鍵回報，不把代理未執行的UI矩陣或Mac Cmd／其他功能補成驗收通過；U01未實作。來源及最新校驗見[RELEASES](docs/RELEASES.md)，發布結果文件另行提交推送。

## D04：Mac接續Windows今日功能提示詞（2026-10-13）

依使用者要求將Mac接續提示寫成.md，新增[MAC-WINDOWS-2026-10-13-PROMPT.md](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)。基準main／已推送cb68ba2、Windows實際W29來源6f2833b；核心範圍W27連結狀態提示、W28密碼保存政策及W29 Chrome衝突熱鍵（包含Mac Cmd）。Mac已完成M01～M13，不重做平台移植，W21～W26只作既有共用功能回歸；版本維持0.1.6、共用來源唯一、平台路徑／SDK隔離／交付與未驗收範圍明列。

原MAC-CODEX-PROMPT.md新增最新提示入口並保留首次移植歷史，README／交接入口同步。提示詞包含Windows停止操作／Dropbox同步、Git差異核對、Mac固定CEF／Release／核心測試／簽章／實機、保留SDK及個人設定、先更新交付不自動安裝／發布，以及不把Windows熱鍵驗收當成Mac Cmd已通過。

本輪只建立／更新文件，沒有修改程式、建置／操作App、更新SDK或產物、提交／推送／移Tag／發布。文件UTF-8／LF與相對連結核對；Mac W27～W29仍待目標平台編譯／實測，其他未驗收及U01未實作保持。切換Mac前仍須停止Windows編輯／建置／Git，等待兩台Dropbox同步；未提交文件須辨識保留。

## M14～M17：Mac 沿用今天共用功能（2026-10-13）

已在macOS直接編譯唯一common／app套用W27～W29，不複製功能。M14對應連結狀態提示，M15對應密碼保存政策，M16對應指定Chrome熱鍵與既有共用回歸。M17是本輪實測發現的Mac專屬delegate生命週期修正：保持強參照，reopen沿用共用main_window並遵守背景關閉狀態；沒有更動Windows／INI／網站安全政策。工作ID先核對未占用，結果及失敗分別見[PROGRESS](PROGRESS.md)。

版本仍0.1.6，本機完整.app已更新、Release／111項與合成實機通過；正式列印／一般注音／實體Fn與OA驗收留使用者。此輪只授權交付測試，未安裝／commit／push／更新Mac公開ZIP或移Tag；Windows已公開W29保持，U01仍未實作。SDK／壓縮檔／build保留。

## M18：Mac 交付顯示系統打包時間（2026-10-13）

使用者要求Finder的交付.app時間與系統時間一致，並要求記錄此問題。Mac打包完成、簽章核對成功後，以系統目前時間更新交付oaClient2.app外層目錄的修改時間；內部檔案仍保留各自真實建置時間，不以全部改時間冒充重新編譯。這是交付metadata規則，版本、程式功能及Windows配置保持。

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

## 2026-10-16：M19 Mac 附件選檔格式

使用者要求修正BSI010010圖檔→加入只能預設選圖檔，並提供Chrome只有Custom Files／All Files的格式選單。確認採同一行為：Custom Files預設同時允許網頁宣告的全部格式；All Files作為明確手動解除格式篩選選項，保留原單選／多選契約。不修改OA JavaScript、INI或上傳契約。

Mac平台以CEF提供的副檔名及MIME展開資料建立原生NSOpenPanel，系統差異維持於src/platform/macos/file_dialog.mm；共用header只增加平台handler接線，Windows預設仍回傳nullptr。儲存／目錄／無限制使用原CEF流程。Mac建置、實機及交付核對完成，使用者回覆「我剛剛測試 oaclient2 附件 正確」；細項與未測範圍見PROGRESS的M19。Windows編譯／回歸未執行，不以Mac結果宣稱Windows通過。

版本維持0.1.6，只更新本機artifacts/macos-arm64/oaClient2.app；未安裝、提交／推送／Tag／發布。固定SDK重新取得並核對相同SHA256後保留，沒有升級CEF；既有個人設定、Windows交付及prg保持原邊界。U01及其他待驗收不擴大完成。

## 2026-10-16：W31 Windows 附件選檔格式修正待辦

使用者明確回報 Windows 有與 Mac 相同的選檔問題；目標為預設 Custom Files 同時允許網頁指定的全部格式、另提供 All Files，保留每次 accept／MIME、單選／多選與回呼契約。Windows 仍須先核對實際原因，不直接套用 Mac 原生對話框結論；沿用共用接線，系統實作留在 Windows 平台。

本輪依要求只將實作、建置、原生 UI 測試、資料保護及本機交付要求整理為[Windows 附件選檔修正提示詞](docs/WINDOWS-FILE-DIALOG-2026-10-16-PROMPT.md)（D04）。W31 尚未實作／建置／驗收，Mac 不修改 Windows 專屬碼；現有 Mac M19 驗收、版本0.1.6及未提交／未發布狀態保持。

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

## 2026-10-20：W32 外部協定放行規則

使用者最終確認 `[其他字樣]open[可選其他字樣]`，包含hcopen、hcopenprint、wjopen，不分大小寫；取代舊結尾open與中途尚未交付的hcopen限定規則。只沿用CEF交給系統，不新增Windows登錄／外部程式存在檢查、不自行註冊或解碼執行URI。共用唯一來源ini.cpp與核心測試已更新，Windows Release／CTest1/1、143項通過，本機0.1.6 EXE已交付，實際外部命令由使用者測試。Mac專屬碼／產物不動，需macOS重編及實測；未提交／推送／發布，詳見[進度](PROGRESS.md)W32。

## 2026-10-20：W33 系統主題不影響上下配色

使用者要求上方標題列及下方工具列不隨系統主題變色。Windows固定原生／Chrome亮色模式，主題回呼保留工具列#F0F0F0背景及#222222文字；工具列圖示／命令／尺寸不變。共用唯一AppContext旗標預設false，Windows啟用，Mac須macOS接續／回歸，不在Windows修改Mac專屬碼或交付。Windows Release／CTest1/1、143項與亮色視窗初驗通過，本機0.1.6 EXE已更新；實際Windows系統亮暗切換矩陣未執行，設定工具未開啟且未更動系統。未提交／推送／發布，詳見[進度](PROGRESS.md)W33。

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

## W36：印表字型至 FRX 的 Reptool 相容性（2026-10-30）

本輪使用者要求查證，並明確補充FRX字型由Reptool.exe完成。查明責任鏈為UserSet.report_font → Reptool讀INI → frx／fr3替換Arial Unicode MS；oaClient2的保存及啟動已有，確定存在UTF-8無BOM與舊TMemIniFile預設ACP的編碼缺口，已用真正保存函式與Delphi probe重現。

後續最小修正方向為唯一INI保存輸出使用舊工具可辨識的UTF-8 BOM，保持UserSet／登入參數／兩參數呼叫與既有CommitSettingsFile保護，不改舊專案、prg或重寫FRX引擎。此輪尚未實作；正式選單是否送出report_font、設定檔路徑、重啟回填與真正報表預覽／列印仍待驗證。Reptool目前由EXE旁／上一層找INI、不讀ParamStr(2)，任意ReptoolConfigIni不能假定相容。詳細證據及限制見 [相容性文件 W36](docs/LEGACY-COMPATIBILITY.md)；不將Windows Reptool能力當成Mac原生報表已完成。

## W36：修正／自動修復／0.1.7進版結果（2026-10-30）

使用者明確授權修正oaClient2、確認report_font、編譯供測試，追加既有Config.ini須自動修復並進版。採最小共用修正：INI固定UTF-8 BOM，啟動讀完既有檔即沿原Save／CommitSettingsFile修復，保持鍵值／註解與同內容不重寫；拒寫不解除屬性或改ACL。不是從舊版匯入設定，不修改Reptool／prg或重寫FRX。

Windows版本0.1.7，MSVC Release／160項及合成select→report_font→load-userset→重啟Cookie／$usr還原通過，舊Delphi讀取同一UI保存檔正確。本機EXE已交付，正式OA／FRX預覽及實際列印留使用者測試；Mac沿用唯一共用來源，須回macOS更新平台版本紀錄、重編及回歸，0.1.6.app本輪不變。未發布新ZIP或Tag，其他未驗收與U01保持，詳見[進度](PROGRESS.md)。

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

## W37：Windows沿用Shift+F移除來源重編（2026-11-03）

使用者明確要求Windows移除Shift+F攔截、重編供測試，版本維持0.1.7。沿用M25共用keyboard.h與原測試，不複製或重寫平台鍵盤邏輯；其他熱鍵及W36 INI流程保持。Windows MSVC Release／CTest1/1、160項通過，本機EXE已更新，Windows UI及正式OA由使用者測試；未再修改產品來源／Mac產物，未提交／推送／發布，詳見[進度](PROGRESS.md)W37。
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

## 2026-11-12：R03 改為正式 Release／Latest

使用者明確要求將v0.1.8改為正式Release，已取消GitHub prerelease標記並設為Latest，更新發行標題與說明首行為正式版。GitHub releases/latest端點確認tag=v0.1.8、draft=false、prerelease=false，Release ID仍442477933；四資產名稱／大小／SHA256 digest與變更前一致，未重編／重打包／重傳、未移動來源Tag或修改其他版本。各功能驗收限制保持，不因正式Release標記擴大驗收。證據artifacts/verification/releases-v0.1.8/before-stable.json、release-notes-stable.md、release-stable.json。前段測試版形式是本次更正前狀態，下載連結不變。
