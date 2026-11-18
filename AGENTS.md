# oaClient2 專案協作規則

建立日期：2026-10-12（Asia/Taipei）。使用者最新明確指示優先於本文件。

## 開始工作前

- 接手先依序讀取 [HANDOFF.md](HANDOFF.md)、[PROGRESS.md](PROGRESS.md)、[PROJECT-PLAN.md](PROJECT-PLAN.md) 與 [CHANGELOG.md](CHANGELOG.md)，確認目前做到哪裡、實際驗證結果與下一步。
- 本專案是 oaClient 第 2 代；既有來源在目前 Windows 電腦為 `C:/Users/Lenovo/Dropbox/delphi-project/oaClient64`。這是來源定位資訊，不能硬編碼到新程式；Mac 上的路徑須重新定位。
- 查閱既有專案時，先讀該專案的 `AGENTS.md`、`HANDOFF.md` 與 `docs/DEVELOPMENT-HISTORY.md`，再核對目前來源。歷史備份或已撤回的修改不能直接當成現行需求。
- 既有 oaClient 與 oaReptool 是參考來源；本專案的授權不代表可以修改它們。

## 語言與格式

- 回覆、進度說明與專案文件使用繁體中文。
- 程式碼使用兩個空白縮排，不使用 Tab。
- 新專案文字檔預設使用 UTF-8；讀取舊專案須尊重各檔案原有編碼，主要 PAS／DPR 有 CP950／Big5 檔案。
- 不得以含替代字元的解碼結果覆寫來源，亦不得為統一格式而重排整份舊檔。

## 目前授權與工作邊界

- 使用者已確認開發順序為先完成 Windows，再於 Mac 上沿用同一專案接續開發 macOS。
- 使用者最新要求：Mac 專屬程式碼由 macOS 環境開發，Windows 專屬程式碼由 Windows 環境開發；平台編譯及實機驗證也各自在目標系統執行。共用來源仍只有一份，Mac 修改共用來源後須交接 Windows 回歸，不在 Mac 接續修改 Windows 專屬實作。
- 2026-10-12 使用者已明確授權開始 Windows 簡易版開發，先準備工具與 CEF；環境完成後再開始計算兩小時，測試時間另計。
- 先前「先別開始」的暫停指示已由最新開始開發指示取代；可在本次功能範圍內下載依賴、準備工具、實作、建置與測試，不必重複詢問。
- 使用者後續明確授權的範圍可直接執行，不必重複確認；授權未涵蓋的功能或行為變更先列明差異供討論。
- 環境可用後記錄兩小時實作的起算時間，測試另列時段；準備工具與 CEF 的時間不計入。若測試後修正程式，另記實作時間。
- 使用者已確認兩小時不包含工具安裝、CEF 下載與測試；這些工作另行記錄，不把未測功能宣稱驗收通過，也不因排除測試時間而省略驗證。

## 已確認的產品要求

- 先交付並驗證 Windows 版本；macOS 後續在 Mac 系統使用同一專案資料夾完成，僅支援 Apple Silicon（arm64），不提供 Intel／x86_64 或 Universal 版本；架構預留 Linux。
- 既有 OA 網頁盡量不改；承接現有命令、設定還原與 JavaScript 回傳契約。
- 優先驗證注音輸入與啟動速度，不宣稱更換框架就能保證改善。
- 列印預覽須使用瀏覽器內建的完整預覽介面，以使用者提供的 Chrome／Edge 式畫面為基準。
- PDF 檢視器、自製 PDF 預覽介面及只有作業系統列印對話框，均不能直接當成內建瀏覽器預覽需求已完成。若需替代方案，先由使用者選定。
- Windows 必須保留呼叫既有 `Reptool.exe` 的能力，包含報表參數、登入參數與設定檔路徑；報表內部與列印引擎暫不重寫。
- 初版網站為 `oa.lysm.com.tw`；網址放在可由使用者編輯的 `Config.ini`，正式使用的協定與連線狀態在實作驗證時記錄。
- 簡易版需可載入網站、開啟內建列印預覽、正常使用注音，並於啟動前清除全部網站資料。
- 使用者已確認網站快取、Cookie、登入狀態、Local Storage、IndexedDB、Service Worker 等網站資料都不保留；程式設定保留在 `.ini`。清理僅限 oaClient2 本機專用瀏覽器資料，不得刪除 Config.ini、報表範本、下載檔案、舊 oaClient 或其他瀏覽器資料。
- 保留舊式 INI 設定習慣，允許手動修改網址、視窗偏好及清理選項；程式必須在下次啟動讀取並套用。具體欄位與相容映射在實作前記錄，不自行全面匯入舊個人設定。
- 程式設定與網站登入資料分開；不得將已清除的 Cookie、登入 token 或網站儲存從 INI 自動還原。Reptool 當次登入參數需保持既有呼叫契約，不能因此持久保存網站登入狀態。

## 技術與驗證

- 目前 Windows 採 C++20、CEF 154.0.34 Chrome runtime、CEF Views 與 CMake；版本與工具鏈已固定於 docs/ENVIRONMENT.md。主網站使用 CEF Views Chrome BrowserView，保留 Microsoft 注音整合；Console 使用獨立 Chrome CefWindow，由 Windows AttachConsoleWindow 嵌在下方。不可將主網站改回 0.1.1 的原生子視窗宿主，亦不可將第二個 Chrome BrowserView 或 Alloy DevTools 放在同一 Views Window。
- 不以使用 Chromium 推定框架提供 Chrome 列印預覽；Electron 已確認不符合直接內建該介面的要求。
- 選定 CEF 版本前，確認 Windows／macOS 列印預覽支援、相關修補及元件配套，區分主分支與已發行版本。
- 使用者功能、設定值、事件時機與順序有相依關係；調整前先核對舊命令契約，不自行套用舊版已撤回的優化。
- 靜態檢查、成功編譯、實機功能驗證分別記錄。未執行的項目寫「未執行／待確認」。
- Windows 驗證不能代替 macOS 驗證；注音、列印預覽及啟動時間均需在目標平台實測。
- 2026-10-12 使用者明確確認：注音額外浮動組字窗是 Windows 專屬問題，macOS 不需測試或列為待驗收；Mac 一般注音輸入與焦點驗證保留，不將 Windows 浮窗問題套用到 Mac。

## Git 與紀錄

- Git 僅在本專案初始化；未授權時不建立遠端、不推送、不建立提交或標籤。
- 不追蹤帳密、Cookie、個人設定、瀏覽器使用者資料、快取、建置產物或下載的 CEF 二進位套件。
- 需求與決策寫入 `PROJECT-PLAN.md`；每次工作後同步更新 `PROGRESS.md`、`HANDOFF.md`，並追加 `CHANGELOG.md`。
- 每項工作保留穩定的工作 ID，記錄狀態、涉及檔案、建置結果、平台／輸入法／列印實測、阻礙與下一步。未做的項目明列未執行，不用推測的完成百分比。
- Mac 上的 Codex 接手須先確認本機同步狀態與 Git 分支；不可僅憑舊對話、執行檔時間戳或 Windows 測試推定 macOS 已完成。
- 發現 Dropbox 同步衝突或來源變動時先核對，避免覆蓋其他電腦的工作。

## 不同系統共用同一專案資料夾

- 使用者明確要求「代碼不要混亂」「共用的部分不要重寫」：共用功能保留唯一來源；Mac直接編譯沿用src/common及src/app，不複製出Mac專屬INI、命令、UserSet、登出或工具列版本。詳細邊界見[共用程式碼規則](docs/SHARED-CODE-RULES.md)。
- 系統API、CEF平台載入／子程序設定及資源封裝放在src/platform/windows或src/platform/macos，透過共用平台介面呼叫。必要介面抽取只做最小修改，保持原流程、時機、設定與回傳契約，記錄涉及共用檔案及另一平台回歸狀態；不得藉移植全面重構或重寫共用功能。
- 線上更新功能必須保留於Windows／Mac工作計畫，目前尚未實作；後續共用更新流程保持一份，平台只處理系統差異。更新來源、版本策略、CEF配套及安裝／重啟方式尚待設計，不宣稱已有自動更新能力。
- 共用原始碼、CMake 建置描述、可共用的 presets、文件、測試素材及不含機器資料的設定範例。Mac 接續此專案，不另建平行專案或複製一份分岔來源。
- 所有專案內部文件連結使用相對路徑；程式不得硬編碼磁碟代號、使用者名稱或 Dropbox 絕對路徑。
- Windows／macOS 的 SDK、建置與執行資料各自放在本機。Windows Config.ini／picture 在 EXE 同目錄；Mac 執行資料全部在 ~/Library/Application Support/oaClient2，.app 放 /Applications。兩平台配置不同，必讀[平台路徑對照](docs/PLATFORM-PATHS.md)，不能把 Mac 配置套用到 Windows；清理只限專用 browser-profile。
- `.gitignore` 只影響 Git，不會阻止 Dropbox 同步。不得把忽略清單當成兩平台建置資料隔離的方法。
- 使用 CMake 平台條件與獨立平台模組處理差異；共用邏輯不直接依賴 Win32、Windows SDK 或 Reptool。
- CEF 路徑由本機設定／環境參數提供；共用設定不保存本機絕對路徑。CMakeUserPresets.json 若使用，須保持本機專屬並依既有忽略規則管理。
- 檔名、include 與路徑大小寫完全一致，避免只有大小寫不同的檔案；新文字檔 UTF-8、LF，依 `.gitattributes` 保存。
- 不共用 CMakeCache.txt、.obj、.lib、.dll、.exe、.app、.framework 或平台安裝包；測試要確認執行的是該平台剛建置的版本。
- 上述建置隔離規則有一項使用者核准的交付例外：完整 Windows 可執行交付版放在專案 `artifacts/oaClient2/`，供直接開啟與 Dropbox 同步；此目錄不納入 Git。Mac 不得執行或將其 Windows DLL／EXE 當成 Mac 建置依賴，後續 Mac 交付使用獨立平台目錄。
- 同步交接時，原電腦先停止編輯、建置與 Git 操作，等待 Dropbox 同步完成，再由另一台核對。不得兩台同時操作同步中的 `.git`；有 lock、conflicted copy 或來源差異時先排除問題。

## 2026-10-12 新增已確認要求

- 下方沿用舊 oaClient 可見工具列；左側開啟／關閉嵌入式 Console。
- 主程式每次啟動最大化；Windows Config.ini 在 EXE 同目錄，Mac Config.ini 在 Application Support/oaClient2；皆可編輯且保留。
- 「瀏覽目錄」統一定義為開啟實際 Config.ini 所在目錄：Windows 目前為 EXE 同目錄，Mac 為 Application Support/oaClient2。不以主程式目錄作為目標；截圖只擷取 oaClient2 視窗。Windows 存 EXE 旁 picture；Mac 存 Application Support/oaClient2/picture。
- 應用程式與工具列圖示沿用舊 oaClient 原資源，不更改舊專案。
- 使用者已授權關閉並重啟 oaClient2 進行本輪測試；列印預覽與注音由使用者驗證，新宿主仍需回歸，不擴大舊版回報。

- 0.1.2 Microsoft 注音已由使用者確認「已正常，沒有額外浮動組字窗」。列印預覽尚未重新驗收，不擴大 0.1.0 的回報。
- 0.1.6依使用者最新要求不使用沙箱（只跑ERP）：Windows主程式oaClient2.exe包含全部應用功能，不再是launcher；CEF官方執行元件全部在cef/，不混入應用EXE／DLL，根目錄不放chrome_elf.dll。Config.ini及picture在主程式同目錄。CEF版本未變時，一般功能只更新EXE；首次交付或CEF升級仍需完整CEF配套。
- 輸入 URL 對話框依使用者圖片：單行預選網址、藍色提示、置中確定、X／ESC 取消。縮放保存 UserSet.ZoomPercent，主框架載入完成後套用。
- 0.1.3起視窗及工具列的8張PNG內嵌EXE；0.1.6改由application_images.rc直接編入主程式RCDATA；交付主程式目錄不放 PNG。原圖保留 assets 作為共用來源，Mac 須實作平台資源讀取，不讀 Windows EXE。

## 0.1.4 新增相容要求

- 使用者要求跟舊版相同保存userid及其他UserSet偏好；網站透過cmd=ini寫入Config.ini，load-userset回傳$tmp.userSet並執行原func回呼，頁面載入回填$usr。不得只實作userid或自行匯入舊個人設定。
- 啟動前仍清除全部舊網站資料；依最新要求，之後僅從INI的UserSet偏好重新建立當次偏好Cookie，以供userid、公司別、字型、語言及主題使用。這是程式設定回填，不還原網站登入Cookie／token／密碼。loginParam仍僅存當次記憶體。
- 關閉主視窗先查登入狀態；已登入才呼叫logout，依舊版最多等待約10秒，以CEF延遲任務維持UI可回應，收到登出狀態才退出，超時明確記錄。
- hcopen:///依舊來源crmProtocolExecution交給作業系統已登錄的處理器；保留不分大小寫、名稱長於open且以open結尾的協定規則。使用者明確表示hcopen由其自行測試；不自行新增登錄或替代解析URI。
- 舊Bin/prg曾完整複製至專案及Windows交付，來源及12份歷史檔案SHA256見docs/PRG-INVENTORY.md。使用者後續已自行精簡交付prg並明確要求「不要再補回來」；打包不再複製根prg，交付prg由使用者維護，不補回、不覆蓋或刪除其中檔案。prg不納入Git，Mac不得執行或當作Mac依賴。
- 預設prg/Reptool.exe；ReptoolPath空白亦採此預設，明確相對路徑從主程式根目錄解析。呼叫保留報表命令＋當次登入參數及第二個INI參數，工作目錄為主程式根目錄。

- 0.1.5關閉INI error5修正：內容相同不重寫；平台保存介面CommitSettingsFile優先保留原檔metadata替換，改名被拒但可寫時原檔寫回，真正拒寫保留資料及回報。不可為避錯而清除readonly或修改ACL；Mac按同名介面接續，原檔fallback不等於原子替換。

## M04：Mac 拖曳安裝與平台組態差異（2026-10-12）

使用者已確認：Mac 交付為完整 oaClient2.app，拖曳到 Applications 即完成程式放置；首次啟動／設定保存時產生組態，無額外安裝腳本。Mac Config.ini、picture、logs、browser-profile、instance.lock 統一放 ~/Library/Application Support/oaClient2，CEF／Helper／圖示仍在 bundle。Windows 維持 EXE 旁 INI／picture、LocalAppData 網站資料與紀錄；不得因 Mac 修改而改成相同路徑。

組態欄位與 INI／UserSet／登出流程保持唯一共用來源，僅平台 GetAppPaths／PictureDirectory 提供不同位置。接續 Windows 開發須先讀[平台路徑對照](docs/PLATFORM-PATHS.md)。舊 Mac app 旁 INI／picture 保留，新版不自動匯入；不能從 Windows 個人設定或網站登入資料回填。

## M05／W21：未設定網址的共用歡迎頁

Mac 新安裝時 HomeUrl 空白，啟動顯示本機歡迎頁與「設定伺服器網址」按鈕；確認有效網址後才保存 HomeUrl。取消仍停留歡迎頁，已有網址直接載入。歡迎頁內容及按鈕流程使用同一份共用來源。

使用者也要求 Windows 使用相同啟動頁，但 Windows 入口的空白預設、資源／功能接線與 MSVC／實機驗證留待 Windows 環境完成（W21）。Mac 端不得將需求或共用頁面來源當成 Windows 交付版已更新；既有 Windows 個人網址與 EXE 旁組態配置保留。

## M06／W22：隱藏縮放彈窗

使用者要求 Mac 與 Windows 放大／縮小時不顯示 Chromium 縮放彈窗，保留原縮放階段、UserSet.ZoomPercent 保存及重啟還原。Mac 本輪啟用；Windows 只記錄 W22，回 Windows 環境再實作、編譯及實測。共用 AppContext.hide_zoom_bubble 預設 false，Mac 入口設 true；Windows 入口及交付 EXE 尚未變更，不宣稱已完成 Windows 修正。

## M08：Mac 交付舊檔清理（2026-10-12）

使用者已明確授權刪除 artifacts/macos-arm64 中不再使用的 Config.example.ini、Config.ini、picture／舊 JPG 及 .DS_Store，目前只保留 oaClient2.app。先前對這些指定舊檔的保留決策已由本次清理取代；Application Support 現用設定／截圖及 Windows 資料仍保留。後續打包只交付 .app，不自行補回，也不擴大成全目錄清除規則。

## M10／W23：隱藏背景登出與三秒退出（2026-10-12）

使用者已確認原文「登入命令」指登出 logout，並追加：關閉時送出登出一次，立即隱藏主視窗與 Console；背景收到登出完成回應（既有 loginState=0 契約）就立即結束，未收到則最多等待3秒再關閉全部本程式瀏覽器並退出。3秒到期不等於伺服器登出成功，不再以舊最多10秒流程作為 Mac 現行要求。

沿用 common/logout.h 與 app.cpp 唯一來源；AppContext.background_logout_close 預設 false，Mac 入口啟用 true，Windows 現行流程保留，W23 留待 Windows 環境實作／編譯／實測。關閉期間不重新顯示窗口，延遲 Console 建立不得留下新窗口；beforeunload 在背景關閉期間自動允許，避免離開頁面提示阻擋退出。INI／UserSet／profile 清理與既有欄位不另改。

本輪僅更新 Mac 交付 .app，不安裝到 Applications。實機以 localhost 合成頁驗證，正式 OA 登出仍待使用者驗收，不能以合成回應宣稱伺服器已登出。


## M11／W24：瀏覽 Config.ini 所在目錄（2026-10-13）

使用者已重新定義兩平台「瀏覽目錄」：開啟實際 Config.ini 的父目錄，取代主程式目錄。共用 app.cpp 直接使用 paths.config.parent_path()，工具列提示同步更新，不複製平台工具列、不更改 INI 配置。Mac 目標為 ~/Library/Application Support/oaClient2；Windows 目前 INI 與 EXE 同目錄，W24 留待 Windows 編譯／實機回歸與交付更新。Windows 專屬程式碼在 Windows 環境修改，本輪未動 Windows 專屬碼；Mac 只更新交付 .app，不安裝 Applications。


## M01：本機 CEF SDK 保留（2026-10-13）

使用者明確要求：本機 CEF SDK 編譯完成不要清除。保留本機解壓 SDK、原下載壓縮檔及建置目錄供後續增量編譯使用，不將它們同步到 Dropbox 或納入 Git；後續不得因完成建置／交付而自動清理。交付 .app 與本機 SDK 是不同用途。


## M12／W25：網頁資訊與版本標題（2026-10-13）

主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

共用 app.cpp 保持唯一來源，Windows 專屬碼及交付不在 Mac 改；W25 留待 Windows 編譯／實機回歸。Mac 本輪重新編譯只更新交付，不安裝，保留 CEF SDK／壓縮檔／build。


## M13／W26：舊版工具列間距與完整字樣（2026-10-13）

依使用者舊版圖片及現行DFM，右側首頁／網址／MAC／瀏覽目錄／截圖／還原比例／縮小／放大寬度採23／23／40／67／38／61／23／23 DIP，合計298 DIP（原346）。高度仍28 DIP、左Console仍30 DIP；保留原字型、圖示、工具順序及命令。右側按鈕左右內部留白各2 DIP，完整顯示MAC、瀏覽目錄、截圖及還原比例，不以省略號／隱藏文字／縮小字型達成間距。

使用同一份app.cpp，不新增平台工具列副本。Mac已編譯及實機核對完整文字；Windows專屬碼與交付未改，W26留待Windows編譯／實機回歸。Mac只更新交付、不安裝；SDK／壓縮檔／build保留。


## D03／R01／R02：公開GitHub與ZIP下載（2026-10-13）

使用者已核准建立公開repository https://github.com/JimmyWon1028/oaClient2、提交最新Windows確認文件並推送；origin已建立。另要求編譯檔從oaClient2的Releases下載，以ZIP發布且不得包含Config.ini或其他快取。先提供Mac arm64，Windows在Windows環境完成編譯與實機測試後再補齊（R02），本輪不發布舊Windows產物。

Mac ZIP本機已核對：只有完整.app，無INI／profile／cache／picture／logs／Finder metadata；解壓逐檔及連結一致、10份arm64 Mach-O、codesign deep strict通過。ZIP大小144461135 bytes，SHA256 8f1cdbdf81990f78eebbf9e79be9e7c8001f4fff240a0b4c07d40f3a929a6493；程式內容與M13一致，沒有重新實作或重新編譯。公開發布／下載校驗結果後續追加，Windows回歸及U01尚未因此完成。本機SDK／壓縮檔／build保留，沒有安裝。

發布說明及可重現流程見[Release文件](docs/RELEASES.md)。歷史無遠端／未推送紀錄保留為本次授權前狀態。


## 2026-10-13：Windows W21～W26 接續結果

Windows入口已啟用空白HomeUrl／allow_empty_home_url、hide_zoom_bubble及background_logout_close；W24設定父目錄、W25網站動態title與0.1.6版本、W26右側298 DIP／完整字樣直接編譯原共用app.cpp。共用來源沒有複製或重寫，Mac專屬碼與交付未改。

Windows MSVC Release／CTest1/1、74項與本輪歡迎頁、網址／縮放重啟、ACK／三秒期限／Console／beforeunload／全部退出、UserSet／網站儲存、目錄／動態標題／完整字樣實測已完成；詳見[最新Windows結果](PROGRESS.md)。正式列印／Microsoft注音／OA登出／Reptool及間距待使用者驗收，未測情境以進度為準，U01未實作。

交付artifacts/oaClient2/oaClient2.exe與安全範例已更新；Windows INI／picture仍在EXE旁，CEF仍在cef/，prg不補回／覆蓋。正式INI最後正常關閉更新Window後保留現況；不宣稱逐位元不變。SDK／壓縮檔／build保留。本輪未提交／推送／發布，固定v0.1.6 Tag不動，後續Git／R02仍依使用者授權。前段Windows「尚未啟用／待回歸」是此次接續前狀態。


## W27：隱藏連結狀態提示（2026-10-13）

使用者要求滑鼠移到選單時不顯示左下角javascript:void(0)提示；共用app.cpp使用CEF chrome_status_bubble=STATE_DISABLED，不改OA選單JavaScript。Windows已編譯／合成實機驗證並更新交付；Mac專屬碼與產物未修改，Mac需在macOS重編／實測才會套用，不宣稱已更新Mac交付。設定／prg／picture保留，SDK／build不清除。


## D03／R02：Windows提交推送與公開發布完成（2026-10-13）

使用者已授權先commit／push再打包發布；W21～W27來源7958a60已透過HTTPS推送。既有v0.1.6 Release新增Windows x64 ZIP與.sha256，排除個人INI／網站資料／picture／logs／tpl，現有精簡prg只有原4份，不補回根prg。240檔CRC／SHA256及無登入公開下載兩檔一致；Tag與Mac資產不變。實際來源／大小／雜湊／可重現腳本見[Release文件](docs/RELEASES.md)，發布文件另行提交，最新main以Git核對。前段未提交／待R02是此次授權前歷史；Mac W27待目標平台重編／實測，其他未驗收及U01保持。


## W28：登入後不提示儲存密碼（2026-10-13）

使用者要求不要顯示Chromium「要儲存密碼嗎」彈窗；共用app.cpp在任何瀏覽器建立前設定RequestContext的credentials_enable_service=false與credentials_enable_autosignin=false，失敗時回報並停止啟動，不靜默沿用可保存密碼的政策。不修改OA登入表單、INI／userid／UserSet契約或安全檢查，Windows已建置／合成實機驗證並更新本機EXE，正式登入待使用者驗收。Mac專屬碼／產物未改，W27／W28留待macOS重編／實測；GitHub ZIP仍為W27，本輪沒有提交／推送／移Tag／重新發布。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## R02／W28：同版重新發布完成（2026-10-13）

依使用者明確「不要進版」要求，W28來源c5cd549已推送，Windows ZIP與.sha256已替換為同名新版，版本維持0.1.6；v0.1.6 Tag與Mac兩資產保持。新ZIP SHA256為92c371f3560daab3c23de117bb62d11b893be72530b045dbb5b20b8603e24099，公開下載兩檔及240檔CRC／SHA256通過；舊Windows ZIP保留於本機歷史發布證據，最新資訊見[RELEASES](docs/RELEASES.md)。正式OA等及Mac W27／W28回歸仍待驗收，U01未實作；發布結果文件另行提交推送，前段未發布狀態為此次授權前歷史。

## W29：Chrome衝突熱鍵交回網頁（2026-10-13）

使用者要求取消oaClient2內建Chrome的F1／F2／F3／F4／F9、Alt+W、Mod+F、Shift+F、Mod+E／S／N（Mod=Ctrl或Cmd，包含Ctrl+N），不是移除網頁自己的設定。共用common/keyboard.h精確匹配，app.cpp改為網頁優先接收一般加速鍵，OnPreKeyEvent不吞掉事件、OnKeyEvent在網頁處理後攔下指定Chrome預設動作；原F8／F12／Ctrl+P高優先功能及工具列保持。

Windows MSVC Release／CTest1/1、110 checks／0 failures（原74＋36項政策檢查）通過，包含Ctrl／Cmd正向及未列出的組合。共用合成頁tests/pages/keyboard-shortcuts.html已載入。使用者隨後要求「你編譯好，我測試」，因此未繼續逐項實機熱鍵矩陣，Chrome搜尋／儲存／新視窗及真實網頁按鍵接收均待使用者驗收，不宣稱UI熱鍵已通過；Cmd實機亦須在Mac回歸。

本機交付EXE已更新、與build一致，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6 x64。合成server／App已停止，原OA已重開供使用者測試；測試URL只在當次記憶體，未保存INI。使用者新增的f1.js清單保留、不執行／修改／納入Git，Mac專屬碼／產物及prg不改，SDK／build保留。此次未提交／推送／移Tag／重新發布，GitHub ZIP仍為W28；Mac W27～W29需回macOS重編／實測，U01未實作。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## W29／R02：驗收後0.1.6同版發布完成（2026-10-13）

使用者回覆「可以了」並要求同版重新上傳，Windows W29快捷鍵已記錄使用者驗收；來源6f2833b已推送，同名ZIP／.sha256已替換，版本維持0.1.6，Tag／Mac兩資產不變。新ZIP SHA256 849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046，公開下載兩檔及240檔CRC／SHA256通過；資料排除、精簡prg與SDK保留規則維持。詳細來源／驗收範圍與下載見[RELEASES](docs/RELEASES.md)，Mac W27～W29及其他待驗收、U01不擴大完成；發布結果文件另行提交。

## M14～M17：Mac 沿用 W27～W29 與重新開啟修正（2026-10-13）

Mac本機完整.app已沿用唯一common／app套用W27～W29，Release／CTest1/1、111項與合成實機回歸通過，版本仍0.1.6。M17唯一產品修改在Mac main.mm：明確保留weak Cocoa delegate的強生命週期，既有reopen只啟用共用主窗、背景關閉不顯示；最終Finder背景reopen兩次、ACK1418ms／期限3019ms與全部退出通過。Windows專屬碼／交付／ZIP／prg不改，共用源未複製或修改。

本輪僅更新artifacts/macos-arm64/oaClient2.app，未安裝、commit／push／移Tag或更新Mac公開ZIP；Releases仍為M13，前段Mac待回歸為此次接續前歷史。正式列印／一般注音／實體Fn與OA功能留使用者驗收，細項及早期失敗以[進度](PROGRESS.md)為準，U01仍未實作。本機SDK／下載包／build保留，個人設定不注入合成資料或回寫快照。

## W32：外部協定前綴＋open＋可選後綴（2026-10-20）

使用者最終指定 `[其他字樣]+open+[其他字樣]:///`，包含hcopen、hcopenprint、wjopen，不分大小寫；open前至少有字樣、後方可空，取代前述「只以open結尾」規則及中途未交付的hcopen限定方案。只沿用CEF allow_os_execution交給系統；依使用者要求不檢查Windows登錄／外部程式、不自行註冊或解析執行URI。唯一common/ini.cpp及共用核心測試已修改，Windows Release／CTest1/1、143項通過，本機0.1.6 EXE已更新；實際外部命令由使用者測試。Mac碼／產物未改，需在macOS重編回歸；未提交／推送／發布，其他未驗收及U01保持。詳見[進度](PROGRESS.md)W32。

## W33：上下區域不隨系統主題變色（2026-10-20）

使用者明確要求上方標題列與下方工具列不跟隨Windows系統主題；Windows入口啟用共用fixed_light_window_appearance，CEF原生／Chrome固定亮色，主題回呼重套工具列既有淺灰底及深色字。AppContext旗標預設false，Mac入口／產物未改，共用介面需macOS重編回歸，不以Windows交付宣稱Mac已套用。Windows Release／CTest1/1、143項及亮色視窗初驗通過，本機0.1.6 EXE已更新；Windows系統亮暗切換實測尚未執行，未變更系統設定。設定／CEF／prg／Mac交付與SDK保留，未提交／推送／發布；詳見[進度](PROGRESS.md)W33。

## W34：錯誤提示統一繁體中文（2026-10-28）

使用者要求所有顯示的錯誤訊息使用繁體中文。Windows 與唯一共用 INI／app 的自訂錯誤提示已翻譯，系統錯誤保留數字代碼，可能為英文的原始診斷只放紀錄；圖片中的重複啟動提示已實機確認。Release／CTest1/1、143項通過，本機0.1.6 EXE已更新，未提交／推送／發布。Mac專屬錯誤提示及系統localizedDescription須在macOS接續修改、編譯及實測，共用訊息沿用原來源，不另複製翻譯流程；Mac產物未改。完整範圍及證據見[進度](PROGRESS.md)W34。

## W35：匯出／下載必須詢問儲存位置（2026-10-29）

使用者要求匯出或另存一律跳出「另存新檔」指定路徑。共用 app.cpp 於建立瀏覽器前設定 download.prompt_for_download=true，沿用 Chromium 原生對話框與建議檔名；政策失敗用繁體中文回報並停止啟動，不退回直接儲存。Windows已編譯／143項及合成GET對話框跳出驗證、本機0.1.6 EXE已更新，選路徑後存檔／取消等因UI工具限制尚未實測。Mac須macOS重編回歸，專屬碼／產物未改；未提交／發布，詳見[進度](PROGRESS.md)W35。

## D04：Windows W32～W35 修改彙整與 Mac 接續提示（2026-10-30）

依使用者要求，Windows 已做的修改同步記錄於本文件與 [README](README.md)，並新增 [Mac 接續 Windows 修改提示詞](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)，可在 Mac 直接複製使用。本次只更新文件，尚未在 macOS 實作、編譯或更新交付。

- W32：外部協定採前綴＋open＋可選後綴，不分大小寫；Mac 沿用唯一共用判斷與 CEF 系統轉交，不新增處理器檢查或註冊。
- W33：標題列及工具列固定亮色；Mac 須在 macOS 入口啟用既有 fixed_light_window_appearance，必要 Cocoa 差異留平台層，實測亮暗環境，不能把 Windows 初驗當成完整切換驗收。
- W34：應用程式錯誤提示繁體中文化；共用訊息已有翻譯，Mac 接續翻譯平台英文與系統錯誤顯示路徑，保留數字代碼及原始診斷紀錄。
- W35：匯出／下載每次跳出原生「另存新檔」指定路徑；Mac 沿用共用 download.prompt_for_download=true，再測實際儲存、取消與各匯出來源。Windows 只驗證 GET 對話框跳出，其他未測項目不擴大完成。

W31 是 Windows 對應附件修正，Mac M19 已有相同需求且使用者確認，只作必要共用介面回歸；W30 共用關閉保護保留，Windows 專屬 Ctrl+W 不移植為 Mac Cmd+W。Mac 不重做 W27～W29 或首次移植，不複製共用流程。

本機最新 Windows 為 W35／0.1.6，EXE SHA256 57d1a8d2426525f0ce567efe04809709898bb80e5ade6a4e2794e06970fb2290；W32～W35 Release／143項已通過，Mac 仍須目標平台編譯實測。依現有發布紀錄，公開 ZIP 為 Windows W30／Mac M13，本機後續修改尚未發布。切換前停止 Windows 操作並確認 Dropbox 同步，保留未提交來源／SDK／build／個人資料；不自行提交、推送、移 Tag、安裝或發布。詳細限制與步驟以提示詞及 [進度](PROGRESS.md) 為準。

## 2026-10-30：M20～M23 Mac 補齊 W32～W35

Mac 本機 arm64 0.1.6 已沿用共用外部協定／下載政策，Mac 入口補上共用亮色回呼與 Aqua，平台錯誤改為繁體中文及必要數字代碼；不修改系統外觀或 OA 主題。共用來源／Windows 專屬碼未再改，原有 UserSet／INI／附件與平台路徑保持。

Release／CTest 1/1、136項、10份arm64及簽章通過；GET／POST／Blob／popup／右鍵下載、取消／兩目錄／中文及空白名稱／內容／重啟，以及 Ctrl+P 完整預覽另存 PDF 已實測。系統亮暗切換、暗色環境、正式 OA／一般注音／外部程式及所有原生錯誤分支未驗收；一次複合退出殘留列 M24 待定位，兩輪交付最小退出正常，不宣稱全部關閉情境通過。只更新本機 .app，未安裝／提交／推送／發布，SDK／下載包／build保留；公開Mac仍M13、U01未實作。詳見 [本輪結果](PROGRESS.md)。

## 2026-10-30：M24 Mac Cmd+Q 背景殘留修正完成

M24 已重現並修正：Console 有焦點時 Cmd+Q 未進入原生結束入口，之後關閉全部 Browser／Views 仍可能留下 CEF 主迴圈。Mac sendEvent 現在先讓既有原生選單處理精確的 Command+Q，呼叫原 terminate → 共用登出／隱藏／三秒流程；沒有改寫登出或強制結束程序。

最終 arm64 Release／CTest 1/1、136 checks／0 failures、10 份 arm64 與 deep strict 簽章通過；Console 焦點 Cmd+Q、已啟用 beforeunload、附件取消組合的 ACK619ms／無ACK3032ms及實際交付3043ms期限後皆正常 SHUTDOWN_COMPLETE，主程序／Helper 全部退出。 產品只改Mac main.mm，共用來源／Windows及附件實作保持；暫時診斷已撤回。新簽章測試的鑰匙圈等待另行辨識，僅隔離localhost測試帶官方 --use-mock-keychain，正式產品未加入這個參數。只更新本機0.1.6 .app，未安裝／提交／推送／發布，SDK／下載包／build保留；正式OA／真實鑰匙圈、系統亮暗切換及其他原未驗收範圍保持。詳見 [M24結果](PROGRESS.md)。

## W36：0.1.7 INI編碼、既有設定自動修復及印表字型（2026-10-30）

使用者明確授權修正oaClient2的INI編碼相容問題、確認選定印表字型後report_font保存、編譯供測試，追加已產生的Config.ini須自動修復並進版。Windows本機交付現為0.1.7；INI唯一保存採UTF-8 BOM，啟動LoadSettings先沿同一Save修復既有無BOM的UTF-8檔，原鍵值／註解保留、相同內容不重寫；真正拒寫明確回報，不解readonly、不改ACL，不匯入舊個人設定。

Reptool來源／EXE及呼叫契約不修改；report_font仍走通用UserSet。Windows Release／CTest1/1、160項與合成select保存／load-userset／重啟Cookie及$usr回填、舊Delphi讀取同一UI保存檔通過，正式OA／FRX預覽列印留使用者驗收。交付只更新EXE，正式INI下次啟動自動修復，不回填合成資料；prg／CEF／Mac交付保持。Mac共用改動待macOS重編回歸，Mac入口版本紀錄在Mac同步；本輪.app仍0.1.6。未提交／推送／Tag／發布，SDK與build保留；詳見[進度](PROGRESS.md)W36。

## 2026-11-03：M25 Mac 0.1.7

客戶端Shift+F攔截已取消，本機artifacts/macos-arm64/oaClient2.app已重編為0.1.7，沿用共用W36的INI保存／自動修復。Release／CTest1/1、151項、10份arm64及deep strict簽章通過，純文字頁trusted Shift+F可輸入F；正式OA CPN與其他既有未驗收項目留使用者測試。固定CEF154.0.34 SDK／下載包／build已恢復並保留；只更新本機交付，未安裝／提交／推送／發布，Windows共用變更待目標平台回歸。詳見[進度](PROGRESS.md)。

## W37：Windows 0.1.7取消Shift+F攔截（2026-11-03）

已依使用者要求沿用M25共用來源，重新編譯並更新Windows本機EXE，版本維持0.1.7。MSVC Release／CTest1/1、160項通過；Windows實際Shift+F／大寫F及正式OA由使用者測試，本輪未操作App。沒有再次修改產品來源、INI／Reptool／CEF／prg或Mac產物，SDK／build保留，未提交／推送／發布。前段Windows待重編為本輪前歷史，詳見[進度](PROGRESS.md)W37。


## W38：列印背景圖形預設開啟（2026-11-11）

Windows本機0.1.7已修正MRT輸出頁列印時背景消失／白字變淡：唯一app.cpp在瀏覽器建立前設定Chromium列印偏好isCssBackgroundEnabled=true，每次啟動套用，保留原生完整預覽與使用者手動切換。MSVC Release／CTest1/1、160項，以及交付EXE直接／Blob／清除profile重啟的合成預覽實測通過；已更新artifacts/oaClient2/oaClient2.exe並從檔案總管重開正式OA停在未登入首頁供使用者驗收。正式MRT／印表機未驗收，Mac.app未改、須在macOS重編實測。版本不變、未提交／推送／發布，INI／CEF／prg與SDK保留。詳見[進度](PROGRESS.md)W38。


## W39：Windows0.1.8（2026-11-11）

依使用者要求進版0.1.8，CMake／共用視窗與client_version／Windows啟動版本同步，保留W38列印背景修正。Release／CTest1/1、160項通過並僅更新本機EXE；527份INI／CEF／prg／picture／Mac來源與.app等保護檔案一致。Mac.app仍0.1.7，須macOS接續重編回歸；未提交／推送／發布，SDK及build保留。詳見[進度](PROGRESS.md)W39。

## 2026-11-11：M26 Mac 0.1.8

Mac本機交付已同步Windows0.1.8與W38「列印背景圖形預設開啟」，直接編譯唯一共用來源，Mac產品僅同步入口版本。Release／CTest1/1、151項、10份arm64及簽章通過；直接／Blob／清除profile重啟後原生預覽背景均保留。正式OA／MRT與印表機待使用者驗收；SDK／壓縮檔／build保留，未安裝／提交／推送／發布。詳見[進度](PROGRESS.md)。

## W40：Windows 內建小熊與目前站台通知（2026-11-17）

依使用者本輪指示，pet只內建於oaClient2、登入成功才顯示，登出／切站／關閉即停止，不新增pet網址或獨立程式。Windows工具列MAC左側增加透明、icon only小熊按鈕切換show／hide；訊息泡泡右上角×收起訊息、小熊保留，新通知再彈出。其他App指任何oaClient2以外的App，不限定Excel；外部Chrome／Edge不在整合範圍，不為驗證再額外開啟Excel。

沿用目前站台的api_root及既有chatHub OACS／Socket.IO無資料喚醒，再由原生授權API讀取單據；保留10秒補查、游標、防重複／缺口及編輯保護。Token只在記憶體，來源／登入與導航世代需核對，無loopback橋接。後端上傳與事件掛接見docs/desktop-helper/API-UPLOAD.md，代理本輪不部署。Mac不啟用、不改平台碼／.app，共用介面需macOS回歸。

Windows0.1.8本機EXE已更新；170核心＋15接線及PHP隔離回歸通過，正式登入已由使用者自行完成並觀察小熊顯示。正式通知／單據端到端仍待部署確認與測試，完整限制見PROGRESS.md W40；需要登入或上傳時通知使用者，不代填登入或異動未授權正式單據。未提交／推送／進版／發布，CEF／prg／picture與SDK／build保留。

## W42：Windows0.1.9 pet訊息瀏覽（2026-11-17）

使用者要求雙擊pet展開訊息、↑／↓上一則／下一則並進版。Windows0.1.9已交付；本次登入訊息只存記憶體、最多500則，×／Esc收起後可雙擊重開，登出／切站／關閉清除。只有主動雙擊後取得方向鍵焦點，失焦恢復不搶焦點，不能攔截其他App。單擊泡泡沿用開單及編輯保護，本體單擊／拖曳不開單。178核心＋15接線通過、原生雙擊／重開已測，實體方向鍵／Esc待驗收；Mac交付0.1.8保持、共用改動待macOS回歸。版本／證據見PROGRESS.md W42，W41後端不覆寫、不部署，未提交／推送／發布。

## W43：使用者更正通知為 BSI020010（2026-11-17）

唯一通知目標改為BSI020010客戶詢報價，取代D05／W40／W41原BSI020020訂單範圍。主表qua、單號quano、單據日期quadt，僅後端今天的成功表單新增／修改；點擊開BSI020010並保留編輯保護。真正本機API／快照及Windows0.1.9已更新，原Bsi020010 afterScroll供應商查詢保留；正式主機需再上傳Controller、Util與合併後Bsi020010Event並核對event掛接。重新登入後才測新儲存，先前修改不補發。Release／CTest2/2、PHP兩份各23／71及原生合成驗證通過，未部署／異動正式資料／提交／發布，Mac來源與.app保持。詳細見HANDOFF／PROGRESS及API-UPLOAD最新版本。

## W44：全部小熊動作及CLICK回應（2026-11-17）

使用者已要求呼吸、搖擺、小跳、待機招手、坐下、伸懶腰、走路全部實作，並追加滑鼠CLICK互動。Windows0.1.9已交付：43秒待機循環、左側24像素內來回走路、通知小跳揮手；單擊延至雙擊間隔後播放小跳／歪頭／星光，雙擊仍顯示訊息、拖曳不誤觸，訊息／鍵盤瀏覽停止自主動作。新16格素材內嵌EXE、原圖／透明工具列圖示保留。Windows Release／CTest2/2（186＋16）及原生合成動作／互動／通知回歸通過，後端／Mac保持，正式重開待登入。詳細與未測以HANDOFF／PROGRESS W44為準。

## M27：Mac pet 本機交付（2026-11-18）

使用者已確認Windows停止操作及Dropbox同步，Mac已接入與Windows相同的內建pet及0.1.9，通知目標保持BSI020010。通知session、CEF renderer及動畫已最小抽成唯一app／common來源，Windows保留factory／include接線，Win32實作與EXE保持；共用抽取後Windows MSVC／實機回歸待Windows環境執行。

Mac NSPanel／bundle資源、177核心＋16腳本＋10原生檢查、CTest3/3及arm64／簽章通過；本機artifacts/macos-arm64/oaClient2.app已更新。合成登入／授權／補查／喚醒及正常退出已測；UI工具無法選取獨立pet面板，雙擊／拖曳／單擊／↑↓／Esc與跨App完整操作仍待使用者驗收，正式OA／列印／注音不擴大完成。未安裝／提交／推送／發布／部署，正式個人資料與SDK／build保留，詳細證據與限制見[進度](PROGRESS.md)M27。早期「Mac不啟用pet／仍0.1.8」為本輪前歷史。

## M28：Mac pet 右上角拖曳（2026-11-18）

Mac已修正整個透明面板／Cocoa提早夾限造成無法靠近右上角：靠近選單列時泡泡放小熊下方，其餘位置保留上方泡泡，重排保持小熊錨點，繪圖及命中同步。僅Mac native來源／版面header／原生測試，版本仍0.1.9；共用通知及Windows不改。Release／CTest3/3（177＋16＋20）、原生繪圖／像素與arm64／簽章通過，已經使用者授權正常關閉、更新本機交付並重啟；正式OA目前未登入，實際拖曳待使用者驗收。未安裝／提交／推送／發布，詳細見[進度](PROGRESS.md)M28。

## W45：Windows pet 上緣拖曳（2026-11-18）

Windows已修正整個透明面板夾限造成小熊無法靠近上緣：依小熊腳底錨點選上下泡泡，靠近上緣訊息放下方、重排保持本體位置；繪圖／×／泡泡／雙擊區域同步，回下方恢復上方泡泡。僅Windows native來源及測試，0.1.9交付已更新重開，Release／CTest2/2（194＋16）與合成實際拖曳／通知操作通過；Mac／共用來源／API保持，完整多螢幕／其他DPI與原功能未擴大驗收，詳見PROGRESS W45。

## R04：v0.1.9雙平台正式發布（2026-11-18）

使用者明確要求發布Release且Windows／Mac都發布，已公開v0.1.9正式版並設Latest，提供Windows x64／Mac arm64 ZIP及各自SHA256。Tag固定a121567，主產品來源9cb59e6；Windows W45、Mac M28已測交付直接封裝，不重編／安裝／部署API。四個公開下載與本機一致、CRC／逐檔雜湊及Mac連結／權限通過，舊Release／Tag保持；個人資料及SDK／build保留。Mac封裝依M28清單保留Windows同步省略的4個CEF符號連結，不修改.app內容；未在Windows執行codesign。詳細雜湊、限制與可重現流程見[Release文件](docs/RELEASES.md)，未測項目不因正式發布擴大完成。

## M29：Mac pet 水平邊界（2026-11-18）

Mac已修正左側透明留白阻擋拖曳：靠近左緣時本體使用左側中心並保留短程走路空間，移回其他位置恢復原中心，重排保持錨點且泡泡完整，Sprite／星光／alpha命中一致。僅Mac版面及原生測試，版本0.1.9，共用通知／Windows不改。Release／CTest3/3（177＋16＋29）與原生像素／繪圖、arm64／簽章通過；本機交付已正常重啟，正式OA已載入，實際左拖仍待使用者驗收。公開Release未更新，無提交／推送／安裝／部署；詳見[進度](PROGRESS.md)M29。

## R04／M29：Mac同版重新上傳（2026-11-18）

使用者已回報Mac左拖「可以了」，並要求重新打包上傳Mac Release、不進版。既有v0.1.9原名Mac ZIP／SHA256已更新M29，公開下載與本機及267項內容／權限／連結一致，交付與解壓後簽章通過；Windows／固定Tag／舊版本保持。自動審核拒絕刪除歷史Mac備份後採完全保留方案，.previous-m28遠端兩檔及本機history-m28保留，未執行刪除；原名兩檔為最新版。M29來源仍未提交（本次只有打包／上傳指示），以144b717基準、來源patch與實際二進位雜湊追溯，不以舊Tag冒充新Mac來源。未重編／安裝／部署或寫入個人設定；運作中的INI變動保留、不回寫快照。詳見[發布紀錄](docs/RELEASES.md)。

## W46：Windows pet 休眠喚醒恢復（2026-11-18）

使用者回報休眠後仍已登入，工具列小熊按鈕也無法叫出。靜態確認原Win32 pet未處理電源恢復，Show只依內部visible旗標提前返回，缺少透明表面／動畫計時器及通知觀察重新建立；本輪補齊這些失效恢復路徑，尚未實際讓電腦休眠重現，不將靜態發現宣稱為已證實的唯一根因。

Windows desktop_pet接收WM_POWERBROADCAST的suspend／resume，恢復時重建layered表面、重繪／重新夾限位置並重啟33ms動畫，不取得前景焦點；自動／使用者恢復通知合併，顯示器／DPI／DWM變化也重建畫面。Show可修復內部顯示但原生窗口隱藏的情況，手動隱藏保持。透過選用SetResumeHandler接回唯一app/desktop_helper_session.h：取消舊請求／當次通知Token，更新觀察epoch及Tick generation，重新讀取目前頁面的真實登入狀態並重新授權補查；同scope保留游標與訊息歷史，不重新整理網站、不代登入或持久化憑證。Windows未觀察到登入時按小熊也可重新觀察，仍須真實登入才顯示。Mac pet未啟用此選用介面，但共用session已修改，須在macOS重編／回歸；既有M29平台修改與.app完整保留。

MSVC Release／CTest3/3通過：194核心、18腳本（新增2項觀察重建／過期grant丟棄）、15項實際Win32 pet合成電源／顯示事件。原生檢查包含恢復顯示／layered／真實動畫timer、不搶焦點、合併恢復、保留訊息動作、原生隱藏自修、DWM／顯示器恢復、手動隱藏及已登出保持隱藏。只向隔離測試程式自己的窗口送合成訊息，未讓系統真的休眠。CEF本機合成頁實際操作驗證未登入按鈕仍隱藏、登入出現、修改通知、按鈕hide／show、通知開BSI020010 SYNTHETIC-6、登出隱藏；PET_RESUME_RECHECK記錄確認重新觀察路徑執行。實際硬體休眠／喚醒及正式通知端到端待使用者驗收，不擴大注音／列印／Reptool／多實體螢幕驗收。

僅更新artifacts/oaClient2/oaClient2.exe，仍0.1.9，SHA256 9144462070129ff357f150ed052bfbf7a5063321111a0eac16c8ea8fc641a8e6，與build一致。604份接手保護檔只有5份指定來源／CMake、EXE及正常關閉保存的Config.ini變動；不回寫INI快照，現用站台保留。Mac來源／M29.app、CEF／prg／picture與素材保持，SDK／下載包／build保留。合成程式／server已停止，正式交付已重開且畫面為未登入，需使用者重新登入後實際休眠／喚醒一次。沒有修改／上傳API，未提交／推送／進版或更新Release；公開Windows ZIP仍W45，Mac M29既有發布與備份保持。證據artifacts/verification/windows-w46-pet-resume，含build-final.log、ctest.log、resume-recheck.log、synthetic-history.json、protected-diff.json及results.json。

## R04／W46：休眠恢復驗收與同版發布授權（2026-11-18）

使用者回覆「可以了」，W46休眠喚醒依本次回報記錄使用者驗收通過，不擴大為正式通知端到端或其他功能驗收；另明確要求commit、push及重新打包上傳Windows Release、不進版。版本維持0.1.9，沿用已建置及驗收的EXE，不重新編譯或操作登入中的程式。將W46及先前已驗收／已發布但未提交的M29來源與文件一併保存到Git；只重新封裝Windows ZIP／SHA256，Mac四個資產（含歷史備份）、固定Tag與舊版本保持。

先保留舊Windows ZIP／校驗檔，上傳新包暫名並驗證遠端大小／digest，才把舊檔改名.previous-w45保留、新檔改回原下載名，再從公開原URL無登入下載核對。包內排除個人INI／網站資料／picture／logs／cache／tpl／SDK／build，現用prg4份不補回；不刪除既有歷史資產、不上傳API、不改個人設定，SDK／build保留。後續追加實際提交、雜湊與公開下載結果；前段待驗收／未提交／未發布為本次回報與授權前歷史。

## R04／W46：Windows 0.1.9同版重新發布完成（2026-11-18）

使用者回覆「可以了」，W46休眠喚醒依本次回報記錄使用者驗收通過；另依commit、push及重新打包上傳Windows Release、不進版的指示，來源e345e7f238fde9f762805d2d2f822cb49b48828f已推送核對。提交同時保存先前Mac已驗收／已發布的M29來源及紀錄，沒有修改Mac實作或重建Mac交付。Windows沿用已測EXE重新封裝，版本仍0.1.9，v0.1.9固定Tag a1215673784aa9a4fafb7ae8e2813a68ebbac5ff不動。

既有Release449602031原名Windows ZIP／SHA256已更新，ZIP為192199161 bytes、SHA256 2fd5805f9f8a8ec11bdd1f33c49114a46c7dc5a9b988afcf9ff4164edd159907，EXE仍9144462070129ff357f150ed052bfbf7a5063321111a0eac16c8ea8fc641a8e6；來源提交見上。包內240檔（CEF234、現用prg4、EXE及安全範例），CRC／全部SHA256通過，排除個人INI／網站資料／picture／logs／cache／tpl／SDK／build，不補回prg。沿用W46 MSVC Release／CTest3/3（194核心＋18腳本＋15原生）、CEF合成回歸及使用者休眠回報，不擴大正式通知端到端、注音／列印／Reptool或Mac共用修改驗收。

先以暫名上傳驗證GitHub大小／digest，再將舊Windows兩檔改名.previous-w45保留，新檔換回原下載名。公開原URL不帶登入憑證重新下載ZIP／SHA256均逐位元一致，公開ZIP CRC與240份內容雜湊再次通過。Release目前8個資產，Windows原名兩檔為W46新版，.previous-w45與Mac .previous-m28各兩檔為歷史備份；原Mac全部4資產ID／大小／digest保持，v0.1.8／v0.1.6 Release及Latest／固定Tag保持，沒有刪除遠端或本機備份。

604份本機保護清單核對通過（運作中的個人INI若有正常變動保留，不回寫快照），Windows／Mac交付、來源及素材未因打包修改；SDK／下載包／build保留。未重編、重啟或操作登入中的程式，未安裝或上傳API；W46共用session在Mac仍須目標平台重編回歸，Mac公開下載維持M29。證據artifacts/verification/releases-windows-w46，含package.json、release-before／staged／replaced／final.json、history-w45、public-download及results.json。發布結果文件另提交推送，前段待驗收／未提交／未發布為當時歷史狀態。
