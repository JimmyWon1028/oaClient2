# oaClient2 工作紀錄

日期使用 Asia/Taipei；同日按工作批次追加，不以新決策覆寫歷史事實。

## 2026-10-12：需求討論與來源閱讀

- 使用者要求閱讀既有 oaClient，討論跨平台第 2 代，先不寫程式碼。
- 已讀 Windows 舊專案的交接、開發歷程與主要來源，另核對 Reptool 的相關相依；初步結果見 PROJECT-PLAN.md。
- 使用者選定 Windows＋macOS、預留 Linux；既有 OA 網頁盡量不改，優先注音與啟動速度。
- Windows 報表內部暫不考慮，但明確要求保留呼叫 Windows Reptool。
- 使用者要求圖示的瀏覽器內建列印預覽，並指出 Electron 的預覽需自己以 PDF 功能實作。
- 已查證 Electron 44.7.0 原始碼，撤回先前第一候選排序；改以 C++／CEF Chrome runtime／CEF Views／CMake 為方向。Mac 修補與正式版本條件尚待固定及驗證。
- 工具方向採 VS Code 與平台編譯工具；Windows 可只安裝 Build Tools，不必完整 IDE。

## 2026-10-12：兩小時簡易版提出後停止

- 候選簡易版目標：載入網站、內建列印預覽、注音正常、啟動前或關閉清除快取。
- 開始前只做了本機唯讀工具查詢，使用者隨即要求「先別開始」「還沒討論完成」。
- 未安裝工具、下載 CEF、建立原型或開始計時；兩小時目前不是已啟動的交付承諾。

## 2026-10-12：專案初始化

- 授權：寫 agents、git init、工作目標寫成 Markdown。
- 完成：AGENTS.md、PROJECT-PLAN.md、.gitignore；本地 Git main 分支初始化。
- 驗證：文件可嚴格 UTF-8 解碼，無 Tab／替代字元；Git 顯示尚無提交，無遠端，忽略規則已核對。
- 沒有程式來源、程式骨架、工具安裝、CEF 套件或編譯／功能實測。

## 2026-10-12：Windows 優先、共用資料夾與 Mac 交接

使用者本輪指示：

- 「先完成windows版本」「把工作計畫 紀錄 進度 寫清楚」。
- Mac 版本在 Mac 系統沿用相同專案完成。
- 考慮不同系統使用相同專案資料夾。
- Mac 系統的 Codex 要能清楚讀到做到哪裡。

實際變更：

- 更新 AGENTS.md 與 PROJECT-PLAN.md，固定 Windows → macOS 的順序與同一份來源的接續原則。
- 新增 PROGRESS.md：穩定工作 ID、實際產物／證據、驗證與下一步，不捏造百分比。
- 新增 HANDOFF.md：第一入口、現有檔案、無程式／無建置的事實、Git 狀態與 Mac 接手要求。
- 新增本紀錄與 README.md 文件索引。
- 新增 .gitattributes：共用文字檔 LF 與常見二進位檔規則。
- 定義原始碼／文件共用，CEF SDK／建置／執行資料放在各系統本機非同步目錄；明列 .gitignore 不阻止 Dropbox 同步。
- 加入不同根路徑、大小寫、快取安全邊界與兩台 .git 同步操作的注意事項。

本輪驗證：文件讀回、嚴格 UTF-8、連結與 Git 文字規則核對；未執行 C++ 編譯、網站、列印預覽、注音、快取、Reptool 或 Mac 測試。

目前仍未開始程式實作；沒有安裝／下載依賴、Git 提交、遠端或其他系統上的修改。

## 2026-10-12：確認時間範圍與 Mac 架構

- 使用者確認兩小時不包含工具安裝、CEF 下載與測試；這些工作另行安排、計時與記錄，功能驗收要求保留。
- 使用者確認 Mac 只支援 Apple Silicon，固定 arm64，不規劃 Intel／x86_64 或 Universal 版本。
- 已同步更新 AGENTS.md、PROJECT-PLAN.md、PROGRESS.md、HANDOFF.md 與 README.md，移除時間包含項目及 Mac CPU 架構的待確認狀態。
- 尚待確認最低系統版本、Windows 架構、URL、注音輸入法、快取範圍與時機、舊設定相容、Reptool 納入時點及實作起算時點。
- 本輪只更新文件；沒有開始程式實作、計時、工具安裝、CEF 下載、建置或功能測試。
- 文件驗證：嚴格 UTF-8、LF、相對文件連結與最新決策一致性核對；未宣稱程式驗收通過。

## 2026-10-12：網站、清理範圍與可編輯 INI

- 使用者指定網站 oa.lysm.com.tw，並回答網站資料「都不保留」。
- 針對是否包含程式設定的澄清，使用者選定「網站資料全部清除，程式設定保留」。
- 使用者補充「就跟 oaclient 一樣保留在 .ini 中」「可以設定 .ini 的內容」。
- 最新策略：預設啟動前清除 oaClient2 全部網站資料，包括快取、Cookie、登入狀態與網站儲存；程式設定保存在可手動編輯的 Config.ini，不納入清理。
- 規劃可編輯首頁、視窗偏好與清理選項，具體 INI 欄位及相容映射於實作時列明。不得從 INI 自動還原被清除的網站登入憑證，亦不清理舊 oaClient／Reptool 或其他程式資料。
- 已更新 AGENTS.md、PROJECT-PLAN.md、PROGRESS.md、HANDOFF.md、README.md；網站與資料保留策略不再列為待確認。
- 本輪只更新文件，沒有建立執行用 Config.ini、程式碼或骨架，沒有工具安裝、套件下載、網站連線或功能測試。
- 文件驗證：UTF-8、LF、文件連結及範圍一致性；正式 URL 協定、INI 讀寫與啟動清理未實作／未測。

## 2026-10-12：授權開始 Windows 簡易版與環境準備

- 使用者明確授權「可以開始開發 Windows 簡易版」，工具及 CEF 準備完成後才開始計算兩小時，測試時間另計；需持續更新進度與 Mac 接續文件。
- 已核對本機既有 Build Tools 2022 17.14.40、MSVC 14.44.35207、Windows SDK 10.0.26100.0、CMake 3.31.6、Ninja 1.12.1。不因未加入 PATH 而重裝。
- 下載官方穩定版 CEF 154.0.34+g14c5a08+chromium-154.0.8037.98 Windows x64 標準套件；依官方索引校驗，再解壓至 LocalAppData/oaClient2/deps，不放進 Dropbox 共用專案。
- W01 進行中，實作計時尚未開始。套件校驗、環境可用與功能測試結果待後續追加。

## 2026-10-12：環境完成、0.1.0 簡易版與使用者驗證

- 官方 CEF 154.0.34 Windows x64 套件 SHA1 校驗一致，完成官方 cefsimple Release 建置；沿用既有 Build Tools，不安裝整套 Visual Studio。
- 環境完成／實作起算 11:25:29；0.1.0 首次實作與建置完成 11:35:44，約 10 分 15 秒。測試自約 11:36:33 起另計；之後需求討論、實作與測試交錯，未做逐秒完整計時。
- 新增 C++20／CEF Chrome／Views 主程式、UTF-8 INI、視窗偏好、Ctrl+P、F8、啟動前全清專用 profile、單例與清理目錄保護。
- 納入 clientReady、loginParam、apiUrl、prt 最小契約；保留既有 Reptool 呼叫，當次登入參數不持久保存。
- 26 項核心檢查／CTest 1/1 通過；正式 OA 首頁載入。使用者接手預覽／注音並回報「測試正常」，不擴大為所有細項驗收。
- 使用者要求可執行檔放在專案；批准完整交付版放 artifacts/windows。新增 package-windows.ps1，保留中間建置與 CEF SDK 在本機。

## 2026-10-12：0.1.1 下方工具列、同目錄 INI、最大化與 OA 圖示

- 使用者提供舊版工具列及 Console 截圖；明確左側開啟／關閉 Console，允許操作已開啟的舊 oaClient 比對。
- 讀取舊 PAS／DFM，核對首頁、伺服器網址、MAC/IP、瀏覽目錄、截圖、縮放及隱藏按鈕。舊版 Console 開關已實際操作，舊來源未修改。
- 使用者確認新版瀏覽主程式目錄；Config.ini 與 EXE 同目錄；只截 oaClient2 視窗，JPG 存同目錄 pict；每次啟動最大化；應用軟體圖示沿用舊 oaClient。
- 從舊 oaClient.res 的 MAINICON 取出原始圖示，與 oaClient_Icon2.ico 雜湊一致；匯出原工具列 Glyph，保留圖示與順序。
- 約 12:02 起比對與增補；12:17 左右第一輪 UI 發現 CEF DevTools 強制 Chrome style，第二個 Chrome BrowserView 會影響主視窗。移除該方案，改由 Views 外層＋原生 Chrome 網站／Console 子視窗，使用 CEF default/native DevTools 與 external parent。
- 約 12:23～12:27 進行宿主、Console 分頁與按鈕尺寸修正／建置；DevTools 新版設定鍵為 panel-selected-tab。這些修正計入實作，UI 驗證另計；沒有精確逐秒工時，不報虛構累計。
- 0.1.1 Release 建置成功，29 項核心檢查／CTest 1/1 通過。打包不覆蓋既有 Config.ini；若只有初版本機 INI，新位置缺少時複製保留。
- 使用者已授權關閉並重啟 oaClient2 測試。實際由 artifacts/windows 啟動、同目錄 INI、主視窗最大化、完整原圖示工具列及內嵌 Console 分頁已確認。其他按鈕實測見 PROGRESS.md 後續更新。
- 因主網站宿主變更，0.1.1 列印預覽／注音需使用者回歸；不把 0.1.0 的回報直接當作 0.1.1 驗收。
- 更新 README、操作文件、環境、進度、計畫、AGENTS 與 Mac 接續索引。Mac 尚未有來源實作、建置或測試；Git 尚無提交、遠端或標籤。

### 0.1.1 實測追加

- Console 開啟預設 Console panel，按鈕再次點擊關閉並還原內容高度。
- 伺服器對話框帶入正確 HomeUrl，確認相同網址後保存並載入。
- 放大／縮小／還原比例核對 INI 110%／100%，MAC 對話框顯示網路資訊。
- 12:35 成功擷取單一 oaClient2 視窗 JPG 到交付同目錄 pict，開圖核對範圍正確。
- 瀏覽目錄按鈕觸發後，檔案總管 UI 地址讀取遭工具授權逾時；該項未宣稱完整路徑實測通過。首頁獨立按鈕、伺服器取消與錯誤輸入路徑尚未逐項測試。
- 工具等待與文件讀取至約 13:05 才返回，這是核對／測試等待，不記為程式實作時間。最後狀態以 PROGRESS.md 為準。

- 13:07 核對後關閉本輪自建、綁定 127.0.0.1:8765 的測試頁 HTTP 伺服器；未關閉使用者的 oaClient／oaClient2。最後文件連結與 UTF-8 檢查通過。

## 2026-10-12：0.1.2 注音修正、cef子目錄、URL與縮放

- 約13:12開始處理使用者回報的Microsoft注音浮動組字窗。主網站恢復0.1.0的CEF Views Chrome BrowserView；Console獨立Chrome CefWindow由Windows原生嵌入下方，不把主網站改為原生子視窗。
- 使用者確認「已正常，沒有額外浮動組字窗」，記錄為0.1.2 Microsoft注音驗收；最新版列印預覽未重新驗收。
- 參考舊Bin布局，將CEF bootstrap／DLL／PAK／locales集中cef/，新增root launcher並保留Config.ini／pict定位。
- URL改為Win32單行預選網址、藍色提示與置中確定按鈕；X／ESC取消。最終展示尺寸580×200按DPI縮放，展示與ESC取消已測。
- 主框架OnLoadEnd重新套用ZoomPercent；13:28關閉含Console的程序並重啟，紀錄確認150%及HTTP200，之後恢復125%。
- 0.1.2 Release與29項核心檢查／CTest1/1通過。實作、建置、UI核對與使用者測試交錯，沒有精確逐秒工時，不虛構累計。

## 2026-10-12：0.1.3 圖檔內嵌主程式EXE

- 使用者要求8張視窗／工具列PNG編譯進EXE，不放在主程式目錄。修改launcher.rc／resources.h、ReadApplicationImage、CEF圖片讀取、CMake與打包腳本；assets原圖保留。
- 初次核心測試建置遇到非UNICODE目標的RT_RCDATA字串型別不符，改用MAKEINTRESOURCEW；資源逐位元核對又發現RC字串名稱格式差異，改為301～308數值資源ID。修正後Release／CTest1/1通過，8張RCDATA均與原PNG相同。
- 約13:44～13:50重啟驗證遇到Codex宿主的LocalAppData重導向：data與profile實體父路徑不同；清理保護拒絕。添加PROFILE_PATH_REJECTED診斷；嘗試旗標調整無效後撤回，未放寬清理保護。
- 13:44曾記錄Config.ini寫回error5，工具當下屬性顯示唯讀；沒有更改使用者設定內容或屬性。13:51～13:52改由檔案總管啟動，圖標與所有工具列圖示正常，INI縮放100%→110%→100%保存成功，已恢復當前使用者原比例。
- 交付root八張PNG已移除；舊debug.log保留。保存失敗曾留下Config.ini.tmp，後續正常保存後已不再存在，未另行匯入暫存設定。
- 更新AGENTS、README、計畫、進度、環境、操作、圖示來源及Mac交接；Mac未實作／未驗證，Git無提交／遠端／標籤。

## 2026-10-12：0.1.4 登入偏好、關閉登出、hcopen及Reptool

- 使用者要求跟舊版保存userid及其他參數；補充舊版關閉應登出，以及查看hcopen，並明確要求將Bin/prg全部複製及承接prg/Reptool.exe。
- 先讀舊AGENTS／HANDOFF／開發歷程，嚴格以現行CP950主PAS查cmd=ini、IniUserSet、DoLoadUserSet、FormCloseQuery、crmProtocolExecution與OpenReport；不以歷史備份當現況。只列舊UserSet鍵名，不記錄帳號值或複製個人INI。另唯讀核對公開OA my.func／pub.func／loader的設定及登入狀態契約，沒有執行正式登入。
- 新增通用UserSet保存、空值、$usr注入、load-userset序列化與func原腳本；在首個BrowserView前等待CEF偏好Cookie準備，解決網頁初始主題／語言／userid讀取時機。仍先清全網站profile，loginParam僅在記憶體。
- 關閉用500ms CEF任務查狀態／logout／最多20輪等待；避免阻塞UI及重複發送。公開頁面不一定提供全域getLoginState，保留$g.isLogin同義狀態來源。超時記錄，不宣稱伺服器登出成功。
- hcopen沿用原協定名稱長於open、suffix=open、不分大小寫的OS處理器規則，不自行解析／註冊。工具未查到Windows登錄，使用者答覆「這個我測試」；實際外部程式由使用者驗證。
- 從舊Bin/prg複製12份檔案（55,651,423bytes），來源、根prg及Windows交付prg逐一SHA256一致；prg加入Git忽略，Dropbox仍同步。預設prg/Reptool.exe，以launcher根解析相對路徑及工作目錄，維持兩個參數及登入附加／按鈕回復契約。
- 首輪編譯遇CEF閉包callback標頭型別問題，改用CefTask與std::function延遲回呼後成功。Release／CTest1/1、53項核心通過；Windows合成receiver實際接收中文／引號／尾端反斜線及INI兩參數，工作目錄正確。
- 約14:26～14:34本機CEF測試兩次啟動：初始Cookie在頁面腳本前就緒；INI保存、$usr與load-userset回呼通過；重啟讀回合成userid。兩次關閉均只發一次合成logout，等待600ms完成及state0後退出。事件檔保留artifacts/verification/events.jsonl，未操作真正登入表單。
- 舊0.1.3關閉時再次出現Config.ini寫回Windows error5，確認提示後正常退出；不宣稱正式交付INI權限問題已完全排除。0.1.4建置目錄的合成INI保存與重啟通過。
- 合成伺服器PID27040已確認命令列屬本輪後停止；建置測試INI恢復／移除、測試捷徑移除，保留事件結果。沒有改正式HomeUrl或匯入合成資料到交付INI。
- 工作計畫、進度、AGENTS、README、操作、環境、Mac交接及相容說明／prg清單已同步。Mac未實作／未測試，正式登入／登出及Reptool報表待使用者驗證。實作、建置與測試交錯，不虛構逐秒累計；Git仍未提交／遠端／標籤。

- 約14:39起最後由檔案總管啟動0.1.4交付版，正式OA首頁載入，交付INI新增def_lang偏好，確認新版cmd=ini已寫回實際設定。未操作帳密／驗證碼／登入；正式userid／公司別及登出、報表、hcopen仍留使用者實測。

## 2026-10-12：0.1.5 關閉Config.ini error5

- 使用者回報關閉時替換INI被拒。讀取屬性與ACL、核對原檔／tmp雜湊，內容相同且沒有readonly，不複製userid等個人值到紀錄。根因的外部持鎖／同步狀態尚未單獨證實，不再把工具屬性誤讀當唯一原因。
- 只改保存鏈：IniFile.Save先比較完整bytes；AtomicReplace更名CommitSettingsFile，既有檔用ReplaceFileW保留metadata，新檔仍MoveFileEx。可寫但禁止替換的錯誤使用OPEN_EXISTING寫回，寫入前保留原資料，不先truncate；完整寫入後調整EOF及flush，失敗嘗試還原，保留tmp。未解除readonly／修改ACL或靜默忽略真正拒寫。
- 新增九項測試，Release／CTest1/1、62項通過，含刪除共享限制下保存、原檔identity、短內容截尾、同內容不重寫與真正readonly失敗資料保留。
- 約15:20～15:24在真正Dropbox交付位置驗證100%→110%保存，一般視窗關閉寫回N；重啟110%生效，恢復100%及最大化關閉寫回Y，兩次正常退出，沒有error5或殘留tmp。測試沒有操作正式登入。
- 更新版本0.1.5、進度、工作計畫、操作與Mac接續保存契約。Windowsfallback原檔寫回非atomic替換，Mac不得直接照搬Win32實作。Git未提交；舊專案、個人登入參數與主程式設定位置均未另改。

### 0.1.5 使用者確認

2026-10-12，使用者在關閉保存修正交付後回覆「可以」。已同步進度與接續交接，僅確認此次error5修正可用；本輪未再修改程式、重新測試、提交Git或擴大其他功能驗收。

## 2026-10-12：0.1.6 picture與單EXE更新

- 使用者要求pict改picture、cef保持完整原始CEF元件且不混入應用檔。先編譯picture修改並搬移舊截圖，雜湊相同；後續使用者選擇不使用沙箱、只作ERP，以此取代先前接受root chrome_elf副本方案。
- 唯讀核對舊oaClient：Bin/cef/libcef.dll版本135.0.22；現行DPR加入cef DLL搜尋路徑並設定FrameworkDirPath／ResourcesDirPath／LocalesDirPath及NoSandbox=True。新版154官方bootstrap需要chrome_elf相鄰的限制僅適用該啟動方式，不是所有CEF宿主的通則。舊專案未修改。
- CMake改獨立EXE、不使用沙箱；官方library loader及版本／API檢查、子程序libcef-path、資源與locales路徑；8張圖和OA圖示直接編入EXE。移除launcher／bootstrap圖示建置工具，不修改CEF原始元件，不加入舊disable-web-security等旗標。
- 建置到新的本機windows-x64-standalone；Release／CTest1/1、62項核心通過。交付清理只針對指定舊應用二進位，保留個人INI、picture及prg／tpl。CEF234個檔案SHA256與原SDK相同，8張EXE圖片逐位元與assets相同。
- 約16:37實機首頁載入、截圖寫入picture且開圖確認正確、Console開啟／分頁及關閉；程序檢查確認子程序無沙箱且從cef載入DLL。普通工具CIM權限不足後改唯讀提升權限查詢，未輸出完整參數／個人設定。
- 進度、工作計畫、操作、AGENTS、Mac交接及環境同步更新。注音／列印等由使用者另測，未操作正式登入；Mac未實作、Git無提交／遠端／標籤。實作與測試交錯，沒有虛構精確工時。

- 0.1.6本輪實機正常關閉，無INI錯誤／tmp殘留；交付Config.ini與原設定SHA256一致。未登入，不能把此次關閉擴大為正式伺服器登出驗收。

- 0.1.6正常關閉後由檔案總管再次啟動，OA首頁與工具列正常；最新版目前已開啟供使用者測試。

## 2026-10-12：Mac 接續提示詞存檔

- 依使用者要求新增 docs/MAC-CODEX-PROMPT.md，採 UTF-8／LF，包含複製使用方式、文件閱讀順序、Apple Silicon 限定、最新產品要求、依賴隔離、驗證與工作紀錄規則。
- README、HANDOFF 加入入口，PROGRESS 的 D04 更新文件狀態。只新增／更新文件，沒有修改程式、建置產物或 Git 狀態；Mac 開發仍未開始。
- 已核對文字編碼及新增的相對文件連結；本輪沒有重新編譯或執行功能測試。

## 2026-10-12：Windows交付目錄改為oaClient2

- 使用者已自行將artifacts/windows改名為artifacts/oaClient2，方便之後直接壓縮資料夾；核對新目錄及EXE存在、舊目錄不存在。
- package-windows.ps1的目的地與清理範圍訊息、現行README／AGENTS／計畫／操作／環境／prg清單及Mac接續提示詞同步更新；PROGRESS／HANDOFF記錄最新要求。歷史測試路徑保留原記錄。
- 只更新打包設定及文件；核對PowerShell語法、UTF-8／LF與相對文件連結，未重新編譯或打包、未啟動或壓縮，個人INI與二進位未改。版本仍0.1.6，Git未提交。

## 2026-10-12：保留使用者精簡的prg

- 使用者自行刪除交付prg不需要的檔案，並明確要求不要再補回。核對目前只保留docto.exe、Reptool.exe、TSCLIB.dll、zint.dll。
- 移除package-windows.ps1對來源根prg的完整複製；交付prg由使用者維護，後續打包不補回、不覆蓋或清理。來源歷史副本未刪除；新交付目錄不自動帶入工具。
- 同步AGENTS、進度W18、計畫、交接、相容說明、操作、prg清單及Mac提示詞。核對PowerShell語法、UTF-8／LF與文件連結，未重新打包／編譯或啟動，未修改任何工具二進位或INI；版本仍0.1.6、Git未提交。

## 2026-10-12：共用部分不重寫，保留線上更新

- 使用者要求代碼不混亂、共用部分不要重寫，並補充線上更新保留但尚未實作。
- 核對src/common、src/app、平台介面及CMake；現行共用App仍含Windows子程序DLL路徑，Mac接手需最小平台抽取，不宣稱已完全分離。
- 新增docs/SHARED-CODE-RULES.md，更新AGENTS、README、Mac提示詞、計畫與交接；PROGRESS新增D07邊界規則及U01線上更新待辦。共用來源唯一、平台API分開，更新的來源／版本／安裝策略仍待設計。
- 本輪僅來源核對與文件更新，沒有重寫、移動或修改程式碼，沒有實作線上更新、重新編譯／打包／測試或修改使用者資料。已核對UTF-8／LF及文件連結，Git未提交。

## 2026-10-12：M01～M03 macOS arm64 首次移植與交付

- 使用者明確授權開始 Mac，並確認 Windows 停止操作／Dropbox 同步完成；讀取指定文件後核對 main、無提交／遠端／標籤及無衝突／lock。沒有改舊 oaClient／Reptool、Windows 交付或使用者 prg。
- 核對官方 154.0.34 stable macosarm64 standard，SHA1／SHA256 記錄於 ENVIRONMENT；固定 g14c5a08 的 #3410 修補已確認。SDK／build／profile 放 Mac 本機非同步目錄。Xcode -runFirstLaunch 修復官方範例 ibtool 初始化，cefsimple 完成。
- 19:28:26 開始實作，19:34:25 首輪 Release／CTest。後續修正／實機測試交錯，第一次桌面工具等待約 10 分鐘另計，未虛構累計工時。
- 新增 src/platform/macos 的 Cocoa CefAppProtocol 入口、官方 Framework loader／五種 Helper、CMake／plist／bundle、INI metadata 保存、清理保護、URL modal、網路資訊、TextEdit／Finder、SCK 截圖及 bundle 圖片讀取；新增 build／package／ICNS 腳本。
- app.cpp 僅抽取平台子程序、Console handle／座標、字型及新增生命週期診斷，原 common／UserSet／Cookie／登出／命令／工具列保留；新增 Windows cef_platform.cpp 保持既有 libcef-path、DIP／HWND 及字型。Mac 沒有另寫共用副本。
- Mac Console 使用獨立 Chrome Views CefWindow 的 Cocoa NSWindow 父子關係；將定位由內層 WebContents NSView 改成外層 Views handle，實測內容／焦點／1+1=2／F12／含 Console 關閉通過，主網站 Views 宿主未改。
- 修正 Cocoa delegate 安裝時機、結束 menu target、Mac no-startup-window；修正 CEF 自建根層 symlink 清理，unlink 不跟隨目標；修正重複 Framework 封裝 ln -sf 多餘連結及 ICNS 原 PNG 包裝。早期測試曾 SIGTERM 清理自建殘留程序，最終版本另行正常退出通過。
- 測試分離 Windows 原生案例，沿用共用案例；Mac Release／CTest1/1、61項通過，metadata／xattr、真正拒寫不改權限、symlink 安全邊界均核對。Windows 編譯／實機回歸未執行。
- 約20:03～20:06兩輪真實 CEF localhost 合成測試確認 UserSet／Cookie／$usr／func／125%保存，重啟全部網站儲存清理且 INI／picture 保留；logout 各送一次、600ms後完成、state0後退出，第二輪包含 Console。伺服器PID7559已停止。
- 正式 HTTPS OA HTTP200、最大化、原圖示工具列、URL預選／ESC、110%保存重啟→100%還原與JPG單窗口截圖已觀察；hcopen本機LaunchServices沒有處理器，未安裝／註冊替代。沒有操作正式帳密。
- 交付 artifacts/macos-arm64/oaClient2.app；build與交付逐檔一致，8張PNG與assets相同，ad-hoc codesign deep／strict及連結校驗通過，簽章非正式Developer ID／公證。SHA及事件／截圖證據見PROGRESS。
- 同步PROGRESS／HANDOFF／PROJECT-PLAN／README／環境／相容／共用規則，新增MACOS-USAGE。列印預覽／注音仍由使用者驗收，正式登入／登出、其他Mac、多螢幕、實體列印等未擴大驗收。Mac報表與U01線上更新未實作，需求保留。
- 沒有Git提交／推送／遠端／標籤。Windows交付prg與INI未修改或補回。

- Mac交付位置另行啟動核對：app旁INI獨立建立、正式首頁HTTP200／100%、網路資訊、Finder完整交付路徑與picture截圖已測。首次主框架41710ms如實記錄，沒有宣稱更快；保留正式首頁供使用者驗收。首次Mac提示詞增加歷史狀態註記，避免接手重做已完成移植。

## 2026-10-12：M03 注音浮窗測試範圍更正

- 使用者確認注音額外浮動組字窗為 Windows 專屬問題，Mac 不需測試該項，亦不列為待驗收。
- 同步協作規則、計畫、進度、交接、Mac 操作／接續提示詞與 README；Mac 一般注音輸入／焦點要求保留，不將範圍更正當成已驗收。
- 本輪只更新文件；未修改程式、重新建置、執行功能測試或操作 Git 提交／推送。

## 2026-10-12：M04 Mac 組態與拖曳安裝（進行中）

- 使用者確認 Mac 執行檔是完整 oaClient2.app，拖曳到 Applications 即可，首次啟動／設定後產生組態。Config.ini／picture／logs／browser-profile／instance.lock 全部集中 ~/Library/Application Support/oaClient2；Windows 配置不同且維持原路徑。
- Mac GetAppPaths／CEF log 路徑改至新位置；app.cpp 截圖只接 PictureDirectory 平台介面，Windows 返回既有 EXE/picture。INI／UserSet／Cookie／登出共用來源未改。package-macos.sh 只交付 .app，保留舊個人檔案，不新增安裝腳本。
- 新增 PLATFORM-PATHS 作為兩平台開發對照，連結至 AGENTS／HANDOFF／Windows 操作文件、計畫、共用規則、README 與 Mac 文件，避免 Windows 接手誤用 Mac 路徑。
- 新 Mac Release／CTest1/1、63項通過；保留設定／截圖／log 的 profile 清理案例通過，Windows 編譯／實機回歸未執行。/Applications 首次啟動、保存、重啟及截圖驗證後續追加。

## 2026-10-12：M04～M07 完成實作／Mac 驗證，W21／W22 留待 Windows

- 補上 M04 /Applications 安裝與首次組態、110% 保存、專用窗口 JPG、正常退出及重啟清 profile／保留 INI／picture／log 證據；Windows 路徑仍不同。
- 使用者指定 Mac 初始 URL 空白、確認設定後才保存，採本機歡迎頁與設定按鈕；Windows 也用相同啟動頁，另明確要求 Mac 專屬碼在 macOS 寫、Windows 專屬碼在 Windows 寫。共用 welcome.h 及 app.cpp 保持單一來源；Mac 啟用空白政策，Windows W21 待回 Windows 處理，未改 Windows 預設或交付 EXE。
- 使用者要求放大／縮小不要 Chromium 提示；用固定 CEF154 的 chrome_zoom_bubble 官方欄位，不改縮放階段或保存契約。依追加指示 Windows 相同功能先記錄 W22，到 Windows 再做；共用旗標預設 false，僅 Mac 入口設 true。
- 使用者回報額外 Chromium 新分頁；新增 Mac CEF relaunch 回呼，歡迎按鈕改 CEF UI 任務後開 modal，Cocoa 取消用正常 stopModalWithCode。保留 Views 主網站及 Console／登出契約。修正前已核對的自建程序曾無法正常結束並單獨停止；修正後測試網站與歡迎頁正常退出、重啟及 Finder 再開啟保持正確視窗，未直接測到 CEF singleton relaunch 分支。
- 最後 Release／CTest1/1、68項通過；歡迎頁空白 INI、設定／ESC、URL 保存／HTTP200／重啟，網站與歡迎頁縮放無彈窗、INI 比例重啟，以及正常退出均實測。最後 .app 更新至交付與 Applications、簽章 strict 通過；SHA／圖片結果與未驗收項目見 PROGRESS。
- 本輪 localhost URL 已清空、測試比例還原為測前 250%、測試 INI 保留備份；臨時伺服器停止、程式正常關閉，正式帳密／token 未操作。共用修改的 Windows 回歸待執行，Windows 個人 INI／交付／精簡 prg 未改，線上更新仍未實作，Git 未提交／推送／建立遠端或標籤。
- AGENTS／PLAN／PROGRESS／HANDOFF／README、平台路徑、Mac／Windows 操作及共用規則同步；Windows 接手必讀 W21／W22 與 PLATFORM-PATHS，避免誤用 Mac 配置。實作與建置／UI測試交錯，未編造精確累計時間。

## 2026-10-12：M08 刪除 Mac 交付舊設定與截圖

- 依使用者明確要求，刪除 artifacts/macos-arm64 的 Config.example.ini、Config.ini、picture／Snapshot20261012201957-546.jpg 及 Finder .DS_Store；核對後目前只剩 oaClient2.app。
- 刪除前確認目標與 picture 內容均為指定舊檔、沒有符號連結；刪除後主程式、Windows EXE／Config.ini 及 Mac 現用 Application Support INI／截圖雜湊不變。沒有清理現用瀏覽器資料、SDK／建置或其他交付目錄。
- 更新 M08 進度／計畫／交接與配置文件，標明先前保留規則已由此次指定清理取代；打包本來只交付 .app，不會補回舊檔。未改程式或打包腳本、未重新編譯／啟動／執行功能測試，未操作 Git 提交／推送。

## 2026-10-12：M09 Mac 完整重新編譯，不安裝

- 使用者要求重新編譯並指定不要安裝；核對 main／來源，未修改程式或 Windows 專屬實作。原本機 SDK／build／Mac 交付 app 已不存在，重新下載官方同版 arm64 CEF 並校驗大小／SHA1／SHA256，沒有升級 CEF。
- 在全新本機非同步建置目錄完成 Release；227份物件實際重編譯，CTest1/1、68項通過，建置／交付簽章 deep／strict 核對。Framework／五種 Helper／10份原生 arm64 Mach-O／圖示及265份 bundle 檔案／連結一致。
- 更新 artifacts/macos-arm64/oaClient2.app；SHA256：f7eccbcd7f6737fd7ffb861fb7a877948fcc8676bd151d390c036ae7ca894a24。未補回舊設定／圖片，Finder 重生 .DS_Store 已清除。編譯與核對紀錄存 artifacts/verification/macos-m09，未改 Applications、未啟動主程式，來源／Windows 交付／Mac 現用 INI／截圖雜湊不變。
- 更新 PROGRESS／HANDOFF／PROJECT-PLAN；本輪實機、列印與輸入測試未執行，不宣稱 Windows 回歸或 W21／W22 已完成。版本仍0.1.6，未提交／推送／建立遠端或標籤。

## 2026-10-12：D04 整理回 Windows 接續提示詞

- 依使用者要求整理可直接複製的提示詞，涵蓋 W21 共用歡迎頁與空白初始網址、W22 隱藏縮放彈窗、Windows／Mac 組態路徑及平台環境分工。
- 核對實際 Windows 入口尚未啟用 allow_empty_home_url／hide_zoom_bubble，共用頁面與介面已存在；Windows 設定／交付及使用者精簡 prg 契約保留，回歸仍待 Windows 執行。
- 更新 D04 進度／計畫／交接，本輪未修改程式或打包腳本，未編譯、安裝、啟動、執行測試或操作 Git 提交／推送。

## 2026-10-12：D04 Windows 接續提示詞存檔

- 依使用者要求將上一輪提示詞存為 docs/WINDOWS-CODEX-PROMPT.md，附日期、工作 ID 及複製使用方式，保留共用歡迎頁、縮放彈窗與兩平台組態配置要求。
- README／HANDOFF 加入入口，D04 進度與工作計畫同步。核對 UTF-8／LF 及相對連結；未修改程式、編譯／打包／安裝／測試或操作 Git 提交／推送。

## 2026-10-12：M10 隱藏背景登出，收到回應或三秒後退出

- 使用者確認原文指 logout，並要求收到登出回應提早退出，未收到最多3秒。新增共用 LogoutFlow 可選模式，Mac 入口啟用；Windows 原模式保留，新增待辦 W23，未修改 Windows 專屬碼或交付。
- app.cpp 在既有關閉入口立即送出一次並隱藏主窗／Console，用既有狀態回報及 CEF 延遲任務完成退出；新增晚建立 Console／Browser 及 Mac relaunch 隱藏保護。以正常 CEF browser close／shutdown 清理，INI／UserSet 格式不變。
- 加入有效 beforeunload 測試後曾看到離開網頁提示阻擋，該輪失敗；修正 CefJSDialogHandler 在背景關閉期間允許離開。最後 Release／CTest1/1、75項與兩輪實機通過：ACK951ms、無回應3029ms，包含原生選單、紅色關閉、Console、已啟用關閉攔截及正常程序退出。
- 合成頁 tests/pages/background-close.html 不保存登入／偏好；共用測試新增固定期限／回應／重複關閉案例，serve-contract.py 只增加可選頁面參數，原用法保留。證據存 artifacts/verification/macos-m10，正式 OA 登出仍待使用者確認。
- Mac 交付 .app 已更新並核對 build 一致／arm64／簽章；SHA256：27355abf79bf5a440fd2940d4e2d6ab1aa9213dc4b4e9447b451961c053ee75d。不安裝 Applications，現用 INI／picture 與 Windows 來源／交付雜湊一致，測試 URL 未持久保存，臨時伺服器及最後程序已停止。
- 更新協作規則、操作／相容、共用規則、進度／計畫／交接及 Windows 提示詞；Windows W23 待回 Windows 處理，W21／W22／U01 及其餘未測狀態保留。實作與測試後修正交錯，不編造工時；未操作 Git 提交／推送／遠端／標籤。


## 2026-10-13：M11／W24 瀏覽 Config.ini 所在目錄

- 依使用者最新定義，Mac／Windows 工具列共同開啟 Config.ini 的父目錄；共用 app.cpp 只改路徑與提示，無平台工具列副本、Windows 專屬碼或組態格式修改。
- 初次 CMake 因本機 CEF SDK 缺失失敗；重新下載並校驗相同固定 arm64配套後完成 Release／CTest1/1、75項、簽章與arm64核對。SDK版本不變；依追加要求保留本機 SDK、壓縮檔及建置目錄供後續使用。
- 真實 CEF 工具列按鈕已開啟 Finder 的 Application Support/oaClient2，Config.ini 與完整路徑可見。僅在記憶體覆寫空白測試URL，正常關閉3027ms／exit0；現用 INI／picture、Windows 專屬來源／交付與 Applications 既有主程式雜湊不變。
- 更新 Mac 交付 .app，未安裝，主執行檔SHA256：6c8994441d509d97c5597ec3a7f47938f8a54dac26ec2da058c4fe508da78f12，build／交付逐檔一致。驗證證據在 artifacts/verification/macos-m11；交付仍只保留 .app。
- 更新 AGENTS／PLAN／PROGRESS／HANDOFF、README、兩平台操作、平台路徑、共用規則、ENVIRONMENT與 Windows 提示詞。Windows 新增W24編譯／目錄實機回歸，W21～W23仍待 Windows，正式使用者驗收與U01未擴大完成，Git未提交／推送。


## 2026-10-13：M12／W25 網頁資訊與客戶端版本標題

- 核對舊oaClient現行CP950來源及OA標題流程，主視窗由共用app.cpp顯示網頁document.title與「[用戶端版本 0.1.6]」。依使用者澄清不寫死良穎，公司／軟體名稱從URL頁面取得；尚未取得資訊時使用oaClient2。未改舊來源、OA JS、INI格式、彈出視窗或Console流程。
- 增量Release／CTest1/1、75項、arm64及簽章通過。第一個測試啟動因既有App單例鎖被取消，不當成通過；原交付正常退出後，歡迎頁及OA公開首頁標題已實測，歡迎頁正常退出。使用者切換另一網站時名稱從良穎變炬塔，實際動態更新確認。
- 更新Mac交付，不安裝；SHA256：50844de4a8455e943f6e34d725c8f8eae9fa94a21e41696b1514179dc2cb9a7f。SDK／壓縮檔／build保留，Windows來源／交付、Applications既有主程式及picture未變。使用者在測試期間變更現用組態，保留其內容與目前開啟的本機build視窗，不回寫測前設定。
- 更新各工作紀錄與操作／相容／共用規則、Windows提示詞，新增W25待Windows編譯／實測。證據在artifacts/verification/macos-m12，未擴大列印／注音／登入登出驗收，U01尚未實作，Intel限制未改，Git未提交／推送。


## W25：Windows 相同標題需求確認（2026-10-13）

使用者明確要求 Windows 標題列與 Mac 相同：軟體名稱從 URL 頁面的 document.title 取得，顯示「網頁軟體名稱 [用戶端版本 0.1.6]」；尚未取得名稱時顯示「oaClient2 [用戶端版本 0.1.6]」。共用 M12 實作已備妥，Windows 編譯／實機測試及交付更新留到 Windows 環境。本輪只補記需求與交接，未修改程式或交付、未編譯／測試／安裝，不將 Mac 結果當成 Windows 驗證。


## D03：首次本機提交（2026-10-13）

使用者明確指示 commit，授權建立 main 的首次本機來源提交。提交共用及 Windows／macOS arm64來源、原圖資源、共用設定範例、腳本、測試與工作文件；不納入 artifacts、prg、個人Config.ini、CEF SDK／壓縮檔、建置、profile或快取。Git身分使用既有本機設定，實際SHA以git log取得，未建立遠端／標籤或推送。

本輪僅提交與同步Git交接狀態，沒有修改功能、重新編譯／安裝／操作App；既有Mac75項測試結果與Windows W21～W25待回歸狀態保留。歷史無提交記錄不全面改寫。


## 2026-10-13：M13／W26 工具列舊版間距與完整文字

- 依使用者圖片，唯讀核對舊DFM並在共用app.cpp採舊按鈕寬度，右側346→298 DIP，其他字型／圖示／高度／順序／功能不改。Windows專屬碼未動。
- 首輪實機發現CEF預設留白讓MAC與還原比例省略；依追加要求修正右側按鈕Insets左右各2 DIP。最終畫面完整字樣已核對，Release／CTest1/1、75項通過，仍待使用者最終間距驗收。
- Mac交付已更新、不安裝，SHA256：9bc544d13be3e6b0474d3921ced2a7f510728731b778f8f739ec7f2f2c812258，build一致／arm64／簽章通過；SDK／壓縮檔／build保留。Windows來源／交付、Applications主程式及picture未變；現用INI實機期間已有雜湊變更，保留現況，原視窗保存流程未改，不聲稱逐位元不變。
- 首輪App正常退出、最後測試視窗保留開啟；證據存artifacts/verification/macos-m13。更新工作文件與Windows提示詞，新增W26待回歸，未將Mac結果擴大成Windows完成；本輪未提交／推送、未安裝或操作Git遠端／標籤。


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


## 2026-10-13：W21～W26 Windows 接線與交付回歸

- Mac停止操作及Dropbox完成由使用者確認；main／遠端59a323a與固定v0.1.6來源核對，無lock／來源衝突。本輪沒有提交／推送／Tag或Release操作。
- Windows main.cpp五行啟用共用空白歡迎、隱藏縮放彈窗及BackgroundGrace，安全INI範例改空白；W24～W26沿用Mac已完成的app.cpp。common／app與Mac來源、產物未改。增加五項Windows啟動政策核心案例及合成頁動態title按鈕。
- MSVC Release／CTest1/1、74項通過，包含Windows保存拒寫／metadata與合成Reptool參數。W21空白UI／兩個入口／ESC／無效URL拒絕／保存重啟、W22網站110%重啟／無彈窗／還原、W23 ACK649及1117ms／無回應3007ms／logout一次／主窗與Console隱藏／beforeunload放行／全部程序退出已測。
- W24按鈕與實際Explorer Shell目錄一致；W25歡迎、OA及document.title動態名稱；W26原298 DIP／2 DIP留白、完整MAC／瀏覽目錄／截圖／還原比例及原圖示在Windows畫面核對。兩輪原legacy-contract真實CEF通過UserSet／Cookie前置回填／func／$usr與重啟全部網站儲存清理。
- Codex映射環境兩次PROFILE_PATH_REJECTED與Explorer UI授權逾時分開記錄，不放寬profile界線；經既有Explorer程序啟動後成功。未核對成功的Console輸入不列為通過，實作／測試／工具等待工時分開。
- 只更新交付EXE／安全範例，EXE SHA256 9b60d756ee39ca6dc3725e4e608f3d63ac18f1602b69c9bf43c53d32fc7daed2；CEF234份一致、不補回prg。Mac／報表工具／picture／tpl等275份不變，正式INI最後正常關閉更新Window後保留現况，不聲稱逐位元不變。測試INI還原、伺服器及App停止；SDK／壓縮檔／build保留。
- 同步計畫／進度／交接與操作／環境；證據在artifacts/verification/windows-w21-w26。列印／Microsoft注音、正式OA／Reptool／hcopen／工具列間距仍待使用者驗收；未測情境明列，U01未實作，R02後續依授權處理。


## 2026-10-13：W27 隱藏左下角JavaScript連結提示

- 依使用者圖片，核對CEF154的chrome_status_bubble正式欄位；共用CreateMainWindow新增STATE_DISABLED與英文日期註解，共兩行，不改OA選單／JavaScript。
- Windows MSVC增量Release／CTest1/1通過；真實CEF合成選單與子選單停留時無javascript:void(0)狀態提示，兩個JavaScript動作及事件均通過。
- 正常關閉原交付後僅換EXE，SHA256 e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c，版本0.1.6；合成頁退出／伺服器停止、原OA已重開供驗收。設定／CEF配置保持，prg／picture／tpl與Mac共275份雜湊不變，SDK／build保留。
- Mac專屬碼與產物未改，但共用設定須在Mac重編／實測才生效；沒有Git提交／推送／Tag／Release操作，不擴大列印／注音或正式OA驗收。證據在artifacts/verification/windows-w27，工作計畫／進度／交接同步。

## 2026-10-13：D03／R02 提交推送及Windows發布授權

使用者要求打包發布，隨後明確指定先commit、push；提交W21～W27來源與文件，W27已實測合成頁以相同內容保留tests/pages/status-hint.html供跨平台重現。提交前main／遠端同59a323a，沒有新lock或來源衝突；產物／個人INI／prg／SDK不納入Git，v0.1.6 Tag不移動，Mac資產保持。實際提交／推送／打包／發布結果後續追加。


## 2026-10-13：D03／R02 Windows提交推送、ZIP發布及下載核對

- W21～W27來源提交7958a60；Windows HTTPS首次因未登入失敗，使用者完成device授權後push成功，遠端SHA核對一致。origin/main更新失敗經fetch恢復，未force／移Tag。
- 製作及公開oaClient2-0.1.6-windows-x64.zip／.sha256至既有v0.1.6初版測試Release；189879293 bytes，ZIP SHA256 4d765e6d5748ce3d5768dd6ef5ed431d27dbcb13f07647f4aa71cc480ec0feb2，EXE e56d3d32仍為W27的0.1.6 x64。
- 新增scripts/create-windows-release.py，安全清單只納入EXE／安全範例／CEF234檔／現有prg4檔，不補回工具或修改交付。240檔CRC及SHA256一致，GitHub大小／digest與無登入公開下載ZIP／校驗檔逐位元一致。個人Config.ini、picture、logs、profile／cache、tpl、SDK／build皆不在ZIP或Git。
- 既有Mac兩資產ID／大小／digest、固定Tag來源0fe6f35與本機Mac／prg／picture／tpl共275份保護檔案不變；SDK／壓縮檔／build保留。Release說明明列Windows實際來源7958a60及待驗收項目，未重新編譯或擴大驗收。
- 更新進度／交接／計畫／Release與Windows操作、README現行歡迎頁／下載入口，發布結果及腳本另行提交推送；詳見artifacts/verification/releases-windows-v0.1.6/results.json。列印／注音／正式OA／Reptool／hcopen及間距、Mac W27目標平台回歸與未測競態保持，U01未實作。


## 2026-10-13：W28 停用Chromium儲存密碼提示

- 依使用者圖片，在共用App::OnContextInitialized設定credentials_enable_service=false／credentials_enable_autosignin=false；政策成功才建立網頁，失敗回報及結束message loop。未改OA／userid／UserSet／INI契約或網頁安全設定。
- Windows增量MSVC Release／CTest1/1、74項通過；同一合成表單舊版會提示，修正版原生POST結果頁與重啟AJAX送出皆無提示，兩次啟動政策紀錄通過。新增共用合成表單及localhost測試server，丟棄表單值、只記route／時間，未用正式帳密；server GET／303／204核對通過。
- 只更新本機交付EXE，SHA256 fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474，版本0.1.6 x64，與build一致；個人INI保持正常關閉保存、測試網址未寫入，Mac專屬來源／產物與prg／picture／tpl275份雜湊不變，SDK／壓縮檔／build保留。
- 合成App及server已停止，原OA已從修正版重開供使用者驗收；同步工作文件／操作／共用規則／Release狀態，證據artifacts/verification/windows-w28。Mac W27／W28未重編／實測；本輪未提交／推送／移Tag／重新發布，GitHub ZIP仍為W27，正式OA及其他使用者驗收與U01保持。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## 2026-10-13：R02／W28 同版重新打包與公開替換

- 依使用者「重新打包上傳，不要進版」，維持0.1.6；W28來源c5cd549已提交／推送，固定v0.1.6 Tag／Mac資產不變。僅重建本機origin/main追蹤快取恢復已推送SHA，不改分支歷史。
- 打包已測EXE fb57aac7，不重新編譯；ZIP 189879887 bytes，SHA256 92c371f3560daab3c23de117bb62d11b893be72530b045dbb5b20b8603e24099，240檔CRC／全部SHA256通過。排除個人INI／網站資料／picture／logs／tpl／SDK／build，不補回精簡prg。
- 新暫名兩資產上傳／digest確認後才替換指定同名Windows ZIP／.sha256，原公開URL無登入重新下載兩檔完全一致。Release說明已記錄W28來源及同版替換；Mac兩資產ID／大小／digest、Tag及275份本機保護檔案不變。
- 本機artifacts/releases同名ZIP／校驗檔亦更新，歷史W27檔保留前輪public-download；新證據artifacts/verification/releases-windows-w28/results.json。更新工作與發布文件，結果文件另行提交推送；SDK／壓縮檔／build與原OA視窗保留，未擴大驗收或實作U01。

## W29：Chrome衝突熱鍵交回網頁（2026-10-13）

使用者要求取消oaClient2內建Chrome的F1／F2／F3／F4／F9、Alt+W、Mod+F、Shift+F、Mod+E／S／N（Mod=Ctrl或Cmd，包含Ctrl+N），不是移除網頁自己的設定。共用common/keyboard.h精確匹配，app.cpp改為網頁優先接收一般加速鍵，OnPreKeyEvent不吞掉事件、OnKeyEvent在網頁處理後攔下指定Chrome預設動作；原F8／F12／Ctrl+P高優先功能及工具列保持。

Windows MSVC Release／CTest1/1、110 checks／0 failures（原74＋36項政策檢查）通過，包含Ctrl／Cmd正向及未列出的組合。共用合成頁tests/pages/keyboard-shortcuts.html已載入。使用者隨後要求「你編譯好，我測試」，因此未繼續逐項實機熱鍵矩陣，Chrome搜尋／儲存／新視窗及真實網頁按鍵接收均待使用者驗收，不宣稱UI熱鍵已通過；Cmd實機亦須在Mac回歸。

本機交付EXE已更新、與build一致，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6 x64。合成server／App已停止，原OA已重開供使用者測試；測試URL只在當次記憶體，未保存INI。使用者新增的f1.js清單保留、不執行／修改／納入Git，Mac專屬碼／產物及prg不改，SDK／build保留。此次未提交／推送／移Tag／重新發布，GitHub ZIP仍為W28；Mac W27～W29需回macOS重編／實測，U01未實作。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## 2026-10-13：W29／R02 熱鍵驗收與0.1.6同版更新

- 使用者回覆「可以了」並要求重新打包上傳、不進版；Windows W29記錄本次使用者驗收，來源6f2833b已提交／推送，不擴大代理UI矩陣／Mac Cmd或其他功能驗收。
- 沿用MSVC／CTest1/1、110項及使用者測試的EXE b5a5d19b，未重新編譯；同名Windows ZIP／.sha256先上傳校驗再替換，版本仍0.1.6、Tag／Mac兩資產不變。ZIP 189880195 bytes，SHA256 849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046。
- 安全清單240檔CRC／SHA256通過，公開原URL無登入重新下載兩檔與GitHub／本機一致；個人INI／網站資料／picture／logs／tpl／SDK／build不公開，prg仍現用4檔、不補回。
- 本機同名ZIP同步更新，W28歷史副本與證據保留，新證據artifacts/verification/releases-windows-w29/results.json。Mac／prg／picture／tpl275份不變，原OA／SDK／build保留；f1.js已不存在、不還原。更新文件並提交發布結果，Mac W27～W29與其他待驗收及U01保持。

## W30：Windows Ctrl+W 交回網頁與關閉回呼保護（2026-10-13）

依使用者選定行為，Windows只取消Chrome的Ctrl+W關閉分頁，OA網頁仍收到按鍵。沿用W29網頁先處理／Chrome後備攔截；Windows入口啟用disable_chrome_ctrl_w，Mac預設false且Cmd+W不變。共用關閉回呼增加失效browser／main frame保護，避免Chrome先銷毀主瀏覽器後再執行logout而解參照空frame；兩次Windows事件皆0xc0000005／RVA0x1053e，來源定位及詳細證據見[進度](PROGRESS.md)。

MSVC Release／CTest1/1、115項通過；合成頁有／無preventDefault各3次真正Ctrl+W均交給網頁且不關閉；正常Alt+F4、ACK1434ms／含Console1525ms、無ACK3019ms、logout一次／主窗與Console隱藏／beforeunload／全部程序退出通過。正式OA內部分頁與實體高速連按／長按待使用者驗收，Mac共用關閉保護須在macOS重新編譯回歸。

本機EXE版本仍0.1.6，SHA256 504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09，與build一致；Mac／CEF／prg等507份保護雜湊不變，保留已同步Mac M14～M18及D04差異、個人INI與SDK／build。測試App／server已停止，證據artifacts/verification/windows-w30；本輪未提交／推送／移Tag／發布，公開Windows仍W29、Mac仍M13，U01未實作。

## W30／R02：使用者驗收與同版發布授權（2026-10-13）

使用者對本機Ctrl+W修正回覆「可以了」，W30按此回報記錄Windows使用者驗收通過；不擴大為Mac、列印／注音或其他功能驗收。另明確授權commit、push、重新打包上傳、不進版：先提交／推送本次Windows修正與紀錄，再打包已建置／115項及使用者測過的同一EXE，替換既有v0.1.6同名Windows ZIP／.sha256。Tag、Mac兩資產及個人資料保持；先上傳校驗兩個暫名資產才替換，舊ZIP保留本機歷史證據。

Mac M14～M18及D04是接手時已有的未提交差異，保留於工作目錄，本次Windows提交只納入W30及發布紀錄。Mac新共用關閉保護仍須在macOS編譯回歸；U01未實作。前段待驗收／未發布是本次回報及授權前狀態，實際結果另行追加。
