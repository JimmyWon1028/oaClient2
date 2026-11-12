# Mac 接續 Windows 修改提示詞（W32～W35）

建立：2026-10-30（Asia/Taipei）。工作 ID：D04；本文件只整理交接，尚未執行 Mac 修改、編譯或驗證。

Windows 先停止編輯、建置與 Git 操作，等兩台 Dropbox 同步完成，再在 Mac 開啟同一份 oaClient2 專案，把下方提示詞貼給 Codex。先前 [2026-10-13 提示詞](MAC-WINDOWS-2026-10-13-PROMPT.md) 是 W27～W29 的歷史接續；目前 Mac 已有 M14～M19，不要依舊提示重新移植或重做附件選檔。

## 可直接複製的提示詞

```text
請在 macOS 環境接續同一份 oaClient2 專案，把 Windows 最近的 W32～W35 修改套用到 Mac arm64 交付版。使用繁體中文回答及更新文件，程式碼用兩格空白縮排、不使用 Tab；版本維持 0.1.6。

接手前先確認 Windows 已停止編輯、建置與 Git，兩台 Dropbox 同步完成。依序讀取 AGENTS.md、HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md，再讀 README.md、docs/SHARED-CODE-RULES.md、docs/PLATFORM-PATHS.md、docs/ENVIRONMENT.md、docs/MACOS-USAGE.md、docs/LEGACY-COMPATIBILITY.md 與 docs/RELEASES.md，核對實際來源，不僅依據舊對話或檔案時間。

Windows 於 2026-10-30 建立提示詞時，分支 main，HEAD 為 8d104ba7af6c75b91527a14a6d2b6ed64d03dc2b；W31～W35、Mac M14～M19 與交接文件仍有未提交差異。這是核對參考，不是要求 reset 到該提交。請先核對 Mac 的分支、HEAD、status、Git lock、conflicted copy 與實際來源，保留所有已核對的未提交修改；不要以 pull、reset、checkout 或 cherry-pick 覆蓋 Dropbox 同步過來的最新工作。若有衝突先釐清，不能兩台同時操作 .git。

共用 src/common 與 src/app 保持唯一來源，已存在的功能直接編譯沿用；不複製 Mac 專屬的 INI、命令、UserSet、下載政策、登出或工具列。Mac 專屬修改只放 src/platform/macos；不要修改 Windows 專屬實作、交付 EXE、cef、prg 或公開 Windows ZIP。必要共用修改只做最小差異，記錄 Windows 尚待回歸；不在 Mac 接續修改 Windows 平台碼。

目前基準：
- Windows 最新本機 EXE 是 W35，版本 0.1.6，SHA256 為 57d1a8d2426525f0ce567efe04809709898bb80e5ade6a4e2794e06970fb2290。W32～W35 已有 Windows Release／CTest 1/1、143 checks／0 failures；這不是 Mac 的測試結果或預定檢查數。
- Mac 最新本機交付紀錄為 M19：附件格式已由使用者回覆「我剛剛測試 oaclient2 附件 正確」，當時 arm64 Release／CTest 1/1、116項及簽章通過。Mac 主執行檔歷史 SHA256 為 9388faa75d04e2aaf8df5e4105b0fcd6632ac4b901aec8f55f6b0ee82190b3e2；接手若已有後續合法修改，以實際核對為準。
- 依現有發布紀錄，公開 Windows ZIP 是 W30，公開 Mac ZIP 是 M13；本機新版本不能當成 GitHub 已更新。此次不移動 v0.1.6 Tag，也不自行提交、推送、發布或安裝到 /Applications。
- Mac 已有 W27～W29、M17 delegate／reopen、M18 打包時間及 M19 原生上傳選檔。W31 是 Windows 對應的附件修正，Mac 只回歸原 NSOpenPanel，不移植 Windows 的 IFileOpenDialog／STA worker。W30 的共用關閉回呼保護保留並回歸；Windows 專屬 Ctrl+W 政策不在 Mac 啟用，原 Cmd+W 行為保持。

本輪完成以下四項：

1. W32：外部協定為「前綴＋open＋可選後綴」，不分大小寫。
  src/common/ini.cpp 的 IsLegacyOpenProtocol 已從冒號前的 scheme、索引 1 起找 open；直接沿用，不重寫 Mac 判斷。hcopen:///、hcopenprint:///、wjopen:///、大小寫混合及其他同型名稱應放行；bare open:///、openprint:///、一般 HTTPS 路徑內含 open、沒有冒號與空字串不應放行。
  保持共用 LegacyProtocolHandler 透過 CEF allow_os_execution 交給系統。依使用者要求，不新增 Windows 登錄或 Mac LaunchServices 處理器／外部程式存在檢查，不自行註冊、解析或執行 URI 內容。核心案例與 Mac 編譯都要驗證；真正啟動外部程式只有在本機已有適當處理器且已實測時才能寫通過，否則列待使用者確認。

2. W33：標題列與下方工具列固定亮色，不跟隨系統主題變色。
  src/app/app.h 的 AppContext.fixed_light_window_appearance 預設 false，Windows 入口已設 true，Mac main.mm 尚未啟用。請在 macOS 入口啟用相同旗標，直接沿用共用 app.cpp 的 force-light-mode、RequestContext Chrome LIGHT，以及工具列主題回呼重套 #F0F0F0 背景／#222222 文字。
  不另建 Mac 工具列，不改按鈕尺寸、順序、圖示、文字或 OA 的 UserSet 主題。若原生 Cocoa 標題列仍隨系統變色，先定位，再以 Mac 平台層最小 NSAppearance 等系統差異補齊，不改全系統外觀、不注入 OA CSS。
  Mac 需實際檢查亮色／暗色環境、既有視窗及重開時的標題列與下方工具列；不能以只看啟動截圖宣稱切換已通過。Windows 當時只完成亮色初驗，系統亮暗切換未執行，也不能借用 Windows 結果。

3. W34：所有應用程式自訂錯誤提示使用繁體中文。
  src/common/ini.cpp 的讀寫、編碼及 UserSet 錯誤，與 src/app/app.cpp 的密碼政策等共用錯誤已翻譯，直接沿用。不要複製翻譯流程，也不要將共用訊息改回英文。
  請逐一檢查 src/platform/macos 的入口、platform.mm、file_dialog.mm 與錯誤顯示路徑，將現有英文提示翻成繁體中文，涵蓋 Application Support、專用 browser-profile 清理保護、INI 暫存／metadata／替換／寫入、TextEdit、開啟設定所在目錄、Console、截圖及未支援報表的提示。重複執行／鎖定訊息已有中文，核對即可。
  特別檢查 std::error_code::message()、NSError.localizedDescription 及截圖非同步 state->error，不直接把依系統語言可能為英文的原始說明附在使用者訊息。以繁體中文說明加必要的數字代碼供查修，原始診斷可留在程式紀錄；保留檔名、設定鍵與產品名。
  不改錯誤發生條件、清理界線或 INI 保存策略，不清除唯讀或修改 ACL；不把錯誤冒充成功，也不修改 macOS 語言或權限設定來達到翻譯。保留 macOS Reptool 尚未實作的明確提示，不新增 Windows 報表相容層。
  能安全觸發的讀寫／編碼／錯誤目錄拒絕等使用隔離測試資料驗證；未實際觸發的分支分別標示靜態核對或未執行。macOS 原生系統介面／OA 網頁文字與應用程式自訂提示要辨識來源，不宣稱改程式即可翻譯其他軟體的訊息。

4. W35：匯出／下載每次跳出「另存新檔」指定路徑。
  共用 App::OnContextInitialized 已在建立任何瀏覽器前將全域 RequestContext 的 download.prompt_for_download 設 true；沿用這份程式，不另寫 Mac 下載管理器、不把路徑寫死，也不新增 INI 開關繞過要求。
  原生儲存對話框保留建議檔名；每次匯出都要能選擇路徑及檔名，取消就不儲存，不能退回直接存預設目錄。政策成功記錄 DOWNLOAD_PROMPT_REQUIRED，失敗記錄 DOWNLOAD_PROMPT_POLICY_FAILED、顯示繁體中文錯誤並停止啟動；保留密碼政策與 Cookie 回填的既有時序。
  Mac 需實測 HTTP GET attachment、POST 匯出、Blob／download 屬性、新視窗匯出與右鍵另存連結；確認每次詢問、兩個不同目錄、中文／空白檔名、實際檔案內容、取消不產生檔案、再次匯出仍詢問、重啟後政策再套用。回歸內建 PDF／列印另存流程，但不得以 PDF 檢視器或自製畫面取代完整 Chrome 列印預覽。
  Windows 只實測合成 GET 匯出跳出原生對話框、保留中文建議檔名，確認前該測試檔未出現在檢查的下載位置。UI 工具無法操作對話框，因此選路徑後存檔、取消、POST／Blob／popup、右鍵另存、PDF／列印與重啟 UI 均未完成實測，正式 OA 匯出亦未宣稱驗收。不能把這些寫成已通過。
  若 Dropbox 已同步 artifacts/verification/windows-w35/serve-downloads.py，可沿用作 localhost 合成素材，僅綁 127.0.0.1:18765；它在 Git 忽略的 artifacts 中，不保證 Git clone 會帶入。不存在時可在 Mac 建立等效拋棄式素材，不改正式 OA，不把有該按鈕或測試頁當成已驗證。測試網址只用 --url 當次覆寫，不保存到個人 INI；使用隔離測試 home／資料並核對 Cocoa 實際位置，避免清理或寫入個人資料。

建置與資料邊界：
- 只用 native Apple Silicon arm64 與既有固定 CEF 154.0.34+g14c5a08+chromium-154.0.8037.98 macosarm64 SDK，不升級 CEF、不做 Intel／Universal。依 docs/ENVIRONMENT.md 核對 SDK 與下載包；缺少時先恢復同版並校驗，不藉此更換框架。
- SDK、原下載壓縮檔與 build 放 Mac 本機非同步目錄，完成後全部保留。沿用 scripts/build-macos.sh／scripts/package-macos.sh；維持不使用沙箱，保留主網站 CEF Views 與獨立 Console Window，不放第二個 Chrome BrowserView 或 Alloy DevTools 到主 Window。
- Mac Config.ini、picture、logs、browser-profile、instance.lock 全部仍在 ~/Library/Application Support/oaClient2；CEF／Helper／圖示在 bundle。Windows Config.ini／picture 仍在 EXE 旁，不改成 Mac 配置。
- 啟動清理只限專用 browser-profile；保留 Config.ini、picture、下載檔、prg、報表範本、紀錄及其他瀏覽器資料。UserSet 偏好可按既有契約回填，不能還原網站登入 Cookie／token／密碼；loginParam 僅當次記憶體。
- 回歸 M19 Custom Files／All Files 附件篩選、UserSet 保存、縮放、Console、動態標題、主視窗 reopen、背景 logout 一次／ACK立即退出／無ACK最多三秒及全部程序退出。一般注音與正式列印驗收依實際狀態；Windows 額外浮動組字窗不列 Mac 測試。
- 執行 Mac Release／CTest，記錄實際項數及結果；檢查 bundle／Helper／Framework 都是 arm64、codesign --verify --deep --strict、build與交付一致並記錄主執行檔 SHA256。編譯、簽章及實機測試分別列結果，不互相替代。
- 本輪只更新 artifacts/macos-arm64/oaClient2.app，不安裝 /Applications、不補回已刪的外部 Config.ini／picture。Windows EXE／cef／prg／ZIP 與 Mac 現用個人資料需保護核對。不要自行 commit、push、改 Tag、發布或重新上傳 ZIP。
- 完成後同步 AGENTS.md、README.md、PROGRESS.md、HANDOFF.md、PROJECT-PLAN.md、CHANGELOG.md 與相關操作文件，沿用 W32～W35 關聯並分配未使用的 Mac 工作 ID，列出修改檔、共用差異、實際建置／實測、未測項與 Windows 回歸需求。U01 線上更新仍未實作，正式 OA／外部協定／列印等未驗收項目不擴大完成。

以上範圍可以開始在 Mac 實作、建置與測試；本提示詞本身不代表 Mac 已完成。若缺少同步確認或遇到來源衝突，先釐清該阻礙，再進行依賴它的修改。
```

詳細結果與後續差異以 [進度](../PROGRESS.md)、[交接](../HANDOFF.md) 及實際來源為準；平台配置見 [路徑對照](PLATFORM-PATHS.md)。
