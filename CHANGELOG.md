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

## D04：Mac接續Windows今日功能提示詞（2026-10-13）

依使用者要求將Mac接續提示寫成.md，新增[MAC-WINDOWS-2026-10-13-PROMPT.md](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)。基準main／已推送cb68ba2、Windows實際W29來源6f2833b；核心範圍W27連結狀態提示、W28密碼保存政策及W29 Chrome衝突熱鍵（包含Mac Cmd）。Mac已完成M01～M13，不重做平台移植，W21～W26只作既有共用功能回歸；版本維持0.1.6、共用來源唯一、平台路徑／SDK隔離／交付與未驗收範圍明列。

原MAC-CODEX-PROMPT.md新增最新提示入口並保留首次移植歷史，README／交接入口同步。提示詞包含Windows停止操作／Dropbox同步、Git差異核對、Mac固定CEF／Release／核心測試／簽章／實機、保留SDK及個人設定、先更新交付不自動安裝／發布，以及不把Windows熱鍵驗收當成Mac Cmd已通過。

本輪只建立／更新文件，沒有修改程式、建置／操作App、更新SDK或產物、提交／推送／移Tag／發布。文件UTF-8／LF與相對連結核對；Mac W27～W29仍待目標平台編譯／實測，其他未驗收及U01未實作保持。切換Mac前仍須停止Windows編輯／建置／Git，等待兩台Dropbox同步；未提交文件須辨識保留。

## 2026-10-13：M14～M17 Mac 接續 W27～W29

- 使用者確認Windows停止操作與兩台Dropbox同步完成；main／遠端cb68ba2、固定Tag、未提交D04文件與來源無衝突核對。直接沿用app／common，沒有重寫、複製或更改Windows專屬來源／交付／ZIP／prg。
- M14選單／子選單／普通HTTP連結無狀態泡泡且動作正常；M15原生POST及重啟AJAX無密碼保存提示，啟動偏好政策成功；M16兩種頁面情境各15組true native鍵盤事件，編輯／F12 Console與既有設定、popup、動態標題、兩輪UserSet及網站資料清理回歸通過。注音來源Ctrl事件key使用注音符號，證據副本按code／keyCode驗證，未改系統設定或人工重送JS事件。
- 背景退出中reopen曾生成Chrome新分頁並殘留，記為失敗。M17最終只在Mac main.mm保留weak delegate的明確強生命週期，再於既有reopen回呼檢查背景狀態；移除暫試Apple Event替換。最終Finder background=1兩次、不顯示／不延期限、ACK1418ms／期限3019ms、logout一次／Console／beforeunload／exit0與Helper全部退出通過。
- 原固定CEF／本機SDK增量Release、CTest1/1／111項、完整bundle10份Mach-O arm64／deep strict簽章通過。package-macos.sh更新交付.app，265檔案／連結／mode與build一致；主執行檔SHA256 879b1e1747f0a59f75afa7cfc0790f257aa3acfe62b72edbd8239226e99c4a7e。272項Windows等保護雜湊保持，SDK／下載包／build不清除。
- 設定回歸使用已核對Cocoa實際路徑的/private/tmp隔離home，正式個人INI未寫入合成UserSet／測試URL；正常Window保存現況保留，不回寫快照。測試server與app已停止，證據artifacts/verification/macos-m14-m16，詳見PROGRESS。UI圖像在Computer Use回傳，未新增不存在的PNG證據。
- 同步交接／進度／計畫／操作／共用規則／環境／Release／README與AGENTS最新狀態，保留歷史。版本仍0.1.6、未安裝、提交／推送、移Tag或公開更新Mac ZIP；正式列印／一般注音／實體Fn與OA功能尚待使用者，其他未測範圍明列，U01未實作。

## 2026-10-13：M18 Finder 顯示時間與系統一致

- 使用者回報交付.app顯示上午05:06，要求使用系統時間並記錄。核對外層mtime05:06:07、內部主執行檔13:26:11，系統UTC+8；原因為增量建置不更新外層目錄、rsync -a保留該時間，並非時區或舊程式。
- package-macos.sh於簽章核對成功後touch -m交付.app外層；現有交付更新為系統2026-10-13 13:43:20（UTC+8）。265份內部檔案／連結內容一致、codesign deep strict／bash -n／git diff --check通過，證據artifacts/verification/macos-m18/results.json。
- 同步計畫／進度／交接與本紀錄；未重新編譯、安裝、提交／推送或發布，版本與M14～M17驗收範圍不變，Windows／SDK／build保持。

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

## 2026-10-16：M19 Mac 附件選檔修正與使用者驗收

- 依Chrome參考圖改為預設Custom Files合併網頁允許格式，另提供All Files；修正原CEF預設JPEG及逐項PDF篩選不可選問題。平台NSOpenPanel使用CEF副檔名／MIME展開，不寫死OA格式，單選／多選與取消callback保持。
- 新增Mac file_dialog.mm與測試頁，Mac CMake接線UniformTypeIdentifiers；共用app.h／cef_platform.h只加入handler介面。Windows專屬碼及交付未改，Windows編譯回歸未執行。
- 固定SDK重新取得、SHA256核對；Release／CTest1/1、116 checks／0 failures、10份arm64及簽章通過。實機五格式同選、MIME、單選、All Files、取消／重新開啟及原無限制／目錄流程通過；使用者回覆「我剛剛測試 oaclient2 附件 正確」，按本次附件修正記錄驗收。
- 只更新本機Mac .app，265項與build一致，主EXE SHA256 9388faa75d04e2aaf8df5e4105b0fcd6632ac4b901aec8f55f6b0ee82190b3e2；版本0.1.6，未安裝、commit／push／Tag／發布。SDK／下載包／build保留；server停止、使用者目前修正版視窗保留。隔離設定／舊版退出及未測範圍詳見PROGRESS、HANDOFF；證據artifacts/verification/macos-m19。

## 2026-10-16：D04／W31 Windows 附件修正提示詞

依使用者「windows 有相同的問題」要求，新增[Windows 附件選檔修正提示詞](docs/WINDOWS-FILE-DIALOG-2026-10-16-PROMPT.md)，整理 Chrome 兩項格式選單目標、Mac M19 既有接線／實測、Windows 原因核對與平台實作、MIME／Unicode／單多選／取消測試及本機 EXE 交付。同步交接／進度／計畫；本輪只寫文件，不修改程式或產物、不建置／操作 App、不提交／推送／發布，W31 保持待 Windows 實作驗證。

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

## 2026-10-20：W32 外部協定包含open及主程式編譯

依使用者最終要求，唯一共用IsLegacyOpenProtocol改為scheme內有前綴＋open＋可選後綴，不分大小寫，支援hcopen、hcopenprint、wjopen與其他同型名稱。CEF轉交系統流程保持，不新增Windows登錄／外部程式檢查、註冊或URI解析。Windows MSVC Release／CTest1/1、143項通過；只更新本機0.1.6 oaClient2.exe，SHA256 3a03b124a48864af570f6ba070b332fb25c95b9a1d84d076394ca11c2df1e6f3，build／交付一致，253項保護雜湊不變。外部開啟由使用者測試，Mac待macOS重編回歸；設定／CEF／prg／picture／Mac.app／公開ZIP保持，SDK與build保留，未提交／推送／發布。同步進度、計畫、交接與協定／Windows操作文件；證據artifacts/verification/windows-w32。

## 2026-10-20：W33 上下視窗區域固定亮色

依使用者「上下都不要跟著系統主題變色」，Windows入口啟用共用fixed_light_window_appearance，App在CEF初始化前force-light-mode、RequestContext固定Chrome LIGHT／預設色；HeightDelegate及按鈕主題回呼重套既有淺灰底／深色字。未複製平台工具列或改OA主題設定，Mac旗標預設false／專屬來源與產物不動，共用介面待macOS重編回歸。MSVC Release／CTest1/1、143項及空白設定視窗初驗通過；系統亮暗切換實測未執行，Windows設定工具啟動失敗、未改系統設定。只換本機0.1.6 EXE，SHA256 3890581dc08216046c3c7dab87b0bef945ce7b22fda3e0886608eb17821b3d53，build／交付一致，253項保護雜湊不變；測試版退出，個人INI／CEF／prg／picture／Mac.app／公開ZIP及SDK／build保留，未提交／推送／發布。同步交接、進度、計畫與規則／Windows操作；證據artifacts/verification/windows-w33。

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

## 2026-10-30：W36 印表字型／FRX／Reptool 來源與編碼查證

依使用者要求，只查證而未修改產品。對照舊oaClient64通用cmd=ini及OpenReport、oaReptool現行frx／fr3載入分支、oaClient2保存與LaunchReport，確認report_font透過INI交給Reptool，後者以字串替換Arial Unicode MS並載入tmp-範本，宿主不直接修改FRX。

確認oaClient2的UTF-8無BOM輸出／移除原BOM與舊TMemIniFile預設ACP不相容。隔離MSVC probe直接編譯現行保存函式及Windows平台，Delphi21.0 probe讀取結果證實：兩種初始BOM狀態經保存均無BOM，客戶端讀回正確但ACP950的舊讀法中文字型錯誤；UTF-8有BOM控制正確。第一次沙箱CMake路徑隔離失敗保留，正常本機暫存重跑建置成功。沒有產品建置／CTest、正式選單／FRX列印或Mac驗證。

另核對兩份Reptool.exe雜湊相同、交付INI目前缺report_font及無BOM，現行Reptool不讀第二參數而找EXE旁／上一層INI；不拷貝舊個人設定或推定正式現象僅有單一原因。更新相容性文件、計畫、進度與交接；證據artifacts/verification/windows-w36-report-font-audit。最小建議為修正oaClient2唯一INI輸出編碼，尚未套用。產品來源／交付／個人資料／舊專案未改，SDK及build保留，未提交／推送／發布。

## 2026-10-30：W36 修正INI相容性、自動修復並升版0.1.7

依使用者後續授權實作，取代前段僅查證／未修正狀態。共用IniFile.Save輸出UTF-8 BOM，LoadSettings啟動自動修復既有無BOM的UTF-8 Config.ini，保留原鍵值／註解及LF保存方式；已修復且內容相同不重寫，拒寫回報、不解除readonly或改ACL。CommitSettingsFile保護及原UserSet／Reptool呼叫保持，未修改Reptool來源或EXE。使用者要求進版，CMake／共用標題與client_version／Windows啟動紀錄同步0.1.7。

新增17項必要回歸，Windows Release／CTest1/1、160項全過；原保存鎖／metadata流程相關檢查保持。獨立合成UI實際select變更標楷體及新細明體，原cmd=ini保存report_font、load-userset回呼正確；落盤有BOM，正常重啟後首個腳本Cookie、$usr、選單與load-userset還原。舊Delphi21.0在ACP950正確讀取同一UI保存檔。正式OA／Reptool／印表機待使用者測試。工具前期CEF Junction及套件映射／select set_value問題另記，不改產品保護。

僅替換交付EXE，build／交付SHA256 ebc31ebb1e8a56085b11c696b6149bf0e1300f420c4a4173197ede1f54899cc4。528份保護檔案全不變，含正式INI、CEF／prg／Reptool、Mac碼及.app；正式INI下次啟動新版自動修復，不寫入合成字型或其他測試資料。測試App正常退出／server停止，SDK／下載包／build保留。Mac共用來源與版本變動待macOS重編回歸、平台版本紀錄在Mac同步；本輪Mac交付仍0.1.6，未提交／推送／建立Tag／發布，其他驗收及U01保持。證據artifacts/verification/windows-w36-ini-fix，詳細見PROGRESS／相容性文件。

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

## 2026-11-03：W37 Windows 0.1.7移除Shift+F攔截交付

依使用者要求，使用現有M25共用keyboard.h及core_tests.cpp重編Windows，不改產品來源、不進版。MSVC x64 Release／CTest1/1、160 checks／0 failures，Shift+F一般文字政策檢查通過；未執行Windows UI／正式OA驗收，留使用者測試。

僅以ExecutableOnly更新本機oaClient2.exe，SHA256 76d28963b6a585039a7992860f9e21f21d05e759f669c29d85cd763b117b6a32，與build一致。567份來源、測試、腳本、正式INI／CEF／Reptool／prg及Mac交付等檔案不變；未操作App、提交／推送／改Tag／發布，SDK／下載包／build保留。同步進度／交接／計畫及README，證據artifacts/verification/windows-w37-shift-f，原其他驗收及U01狀態保持。
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
