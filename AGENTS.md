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
