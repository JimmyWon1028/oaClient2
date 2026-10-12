# Windows 版本接續開發提示詞

更新：2026-10-13（Asia/Taipei）。工作 ID：D04；開發待辦：W21／W22／W23／W24／W25。

使用方式：Mac 停止編輯、建置及 Git 操作，等待 Dropbox 同步完成。在 Windows 的 Codex 開啟同一個 oaClient2 專案，複製下方整段提示詞貼上。

```text
請在 Windows 環境接續開發同一個 oaClient2 專案。使用繁體中文回答，程式碼兩格空白縮排、不用 Tab，新增註解依 AGENTS.md 格式使用英文。

先確認 Mac 已停止編輯、建置及 Git 操作，Dropbox 同步完成；核對 Windows 的 Git 分支、來源衝突與 lock。依序讀取 AGENTS.md、HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md，再讀 docs/ENVIRONMENT.md、docs/WINDOWS-USAGE.md、docs/SHARED-CODE-RULES.md、docs/PLATFORM-PATHS.md、docs/LEGACY-COMPATIBILITY.md，核對實際來源。

Windows 最新交付為 0.1.6。Mac 已完成移植；W21／W22／W23 尚未在 Windows 實作或驗證，W24／W25 共用目錄及標題邏輯已調整但尚未在 Windows 編譯／驗證。Windows 專屬碼只在 Windows 環境修改，Mac 專屬碼由 macOS 環境處理。共用 src/common、src/app 保持唯一來源，不複製或重寫共用功能。

本輪完成：
1. W21：Windows 使用與 Mac 相同的本機歡迎頁，直接沿用 src/common/welcome.h 與 app.cpp。新安裝或未設定 HomeUrl 時保持空白，顯示歡迎頁及「設定伺服器網址」按鈕；沿用原網址對話框，確認有效 HTTP／HTTPS 網址後才保存，取消不改設定。已有個人網址直接載入，不覆蓋。歡迎頁的本機 data URL 不寫入 INI。核對 Windows 入口的 home_url 初值、allow_empty_home_url 及設定範例，做最小接線。
2. W22：隱藏 Chromium 縮放彈窗。沿用現有 AppContext.hide_zoom_bubble 與 CEF chrome_zoom_bubble 設定，在 Windows 入口啟用；保留原放大／縮小階段、還原比例、UserSet.ZoomPercent 保存及重啟套用。
3. W23：Windows 採用最新背景關閉流程。沿用共用 LogoutFlow 的 BackgroundGrace 與 app.cpp，在 Windows 入口啟用 AppContext.background_logout_close；關閉送出 logout 一次後立即隱藏主窗與 Console，收到 loginState=0 回應立即結束，否則最多3秒後完全退出。不重送／不延長期限、不被 beforeunload 阻擋，不以三秒到期宣稱伺服器已登出；Windows 實機驗證所有窗口及程序均結束，不複製關閉邏輯。
4. W24：「瀏覽目錄」的新定義是開啟實際 Config.ini 所在目錄。M11 共用 app.cpp 已改用 paths.config.parent_path()，提示文字為「瀏覽 Config.ini 所在目錄」；Windows 目前 INI 在 EXE 旁，實際位置相同，但仍須在 Windows 編譯／實測並更新交付，不另寫 Windows 工具列或改回 paths.application。
5. W25：使用者已明確要求 Windows 標題與 Mac 相同，先記錄、到 Windows 環境再編譯測試。主視窗標題沿用 M12 共用 app.cpp。未取得網站名稱時顯示「oaClient2 [用戶端版本 0.1.6]」，取得後為「網頁提供的名稱 [用戶端版本 0.1.6]」。名稱由 CEF OnTitleChange 取得 URL 頁面的 document.title，沿用舊版網站資訊流程，不寫死良穎／公司名，不另加 INI 品牌欄位或修改 OA 網頁；版本使用目前實際客戶端版本，不套用參考圖的舊版日期。Windows 編譯／實機驗證歡迎頁及網站名稱動態更新，維持原彈出視窗／Console 行為。

兩平台配置不同：
- Windows：Config.ini、picture 在 EXE 同目錄；網站資料在 %LOCALAPPDATA%/oaClient2/data/browser-profile，application.log／cef.log 在同一 data 目錄。CEF 配套在 EXE 旁 cef/，OA 圖示與工具列圖片內嵌 EXE。
- Mac：oaClient2.app 拖曳至 /Applications；Config.ini、picture、logs、browser-profile、instance.lock 全部在 ~/Library/Application Support/oaClient2/，Framework／Helper／圖片在 bundle 內。
- 共用程式透過 GetAppPaths／PictureDirectory 取得位置，不把 Mac 路徑套用到 Windows，不共用個人 INI 或 CMakeCache。SDK／中間建置各自在本機非同步目錄。
- Windows 交付維持 artifacts/oaClient2；Mac 交付維持 artifacts/macos-arm64，不改動 Mac 產物。

保留 CEF Views 主網站宿主、Windows Console、工具列、UserSet／userid／公司別回填契約；關閉時機依 W23 新要求調整，logout 命令與狀態回報格式沿用。啟動仍清除專用網站資料，只從 INI 回填程式偏好，不保存或還原密碼／登入 token。不使用沙箱，不額外關閉網頁安全檢查。

保留 Windows Reptool 功能、參數與檔案；交付 prg 已由使用者精簡，禁止從根 prg 補回被刪除的工具。線上更新 U01 保留於計畫，仍未實作，本輪不宣稱完成。

完成 Windows MSVC 建置與既有核心測試，實機驗證首次歡迎頁、按鈕／工具列設定、取消、網址保存與重啟、縮放無彈窗及比例還原，背景關閉的 ACK 提早退出／無回應三秒期限／Console 隱藏／beforeunload 與完全退出，並回歸 Mac 移植涉及的共用來源。列印預覽與注音由使用者驗收，Mac 編譯結果不能代替 Windows 驗證。

更新 W21／W22／W23／W24／W25、PROGRESS、HANDOFF、PROJECT-PLAN、CHANGELOG，分別記錄實作、編譯、測試及使用者驗收，未測項目明列。Git 已有2026-10-13使用者授權的首次本機來源提交，無遠端及標籤；後續不自行提交、推送或建立遠端。
```
