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
