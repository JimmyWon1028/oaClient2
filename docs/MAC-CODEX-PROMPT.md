# Mac 版本接續開發提示詞

> 狀態更新（2026-10-12）：以下是首次 Mac 移植前的歷史提示詞。Mac arm64 已完成初輪移植／建置／交付與部分實測；接續先依 HANDOFF／PROGRESS 讀取最新 M01～M03，不要重做已完成的平台來源。列印／注音待使用者驗收，Windows 回歸／效能／其他未測項目另列。

更新：2026-10-12。使用同一份 Dropbox 專案；Windows 目前為 0.1.6，Mac 尚未實作。

使用方式：Windows 停止編輯與建置，兩台電腦都等 Dropbox 同步完成。在 Mac 的 Codex 開啟同步後的 oaClient2 專案資料夾，建立新對話，複製下方整段文字貼上。

```text
請接續開發 oaClient2 的 macOS 版本，僅支援 Apple Silicon arm64。
使用繁體中文回答，程式碼使用兩個空白縮排，不使用 Tab。

先依序讀取：
AGENTS.md
HANDOFF.md
PROGRESS.md
PROJECT-PLAN.md
CHANGELOG.md

再讀 docs/ENVIRONMENT.md、docs/WINDOWS-USAGE.md、
docs/LEGACY-COMPATIBILITY.md，核對實際原始碼。

Windows 最新版本為 0.1.6；Mac 尚未實作，
目前 CMake 明確拒絕非 Windows，必須補上 Mac 平台支援。
請沿用同一專案與共用程式碼，保留 Windows 功能，
平台差異放在 src/platform/macos，不另建分岔專案。

務必讀取 docs/SHARED-CODE-RULES.md，遵守「共用部分不要重寫」。
直接沿用 src/common 及 src/app，禁止複製出 Mac 專用的共用功能版本。
現有 Windows DLL／子程序設定須以最小介面抽取移至平台層，
不全面重構或改變現有流程、時機、設定格式及回傳契約。

先檢查 Dropbox 同步狀態、Git 分支及來源衝突，
準備 Mac 編譯工具及 arm64 CEF，再開始實作。
CEF 優先核對目前 154 系列的 arm64 配套與列印預覽修補；
記錄實際採用的版本、來源與雜湊，不只依主分支狀態判定。
完成 Mac 入口、CMake 平台分支、Framework／Helper 及 .app 封裝。

需求沿用：
- 載入 https://oa.lysm.com.tw/，網址可在 INI 設定。
- 使用瀏覽器內建的完整列印預覽，不以自製 PDF 預覽替代。
- 正常注音輸入，保持 CEF Views 主網站宿主並實機驗證；依 2026-10-12 使用者補充，注音額外浮動組字窗是 Windows 專屬問題，Mac 不需測試或列為待驗收。
- 每次啟動最大化。
- 啟動前清除本程式專用的全部網站資料，保留程式設定及截圖。
- 不使用沙箱，只用來跑 ERP；不額外關閉網頁安全檢查。
- Mac 交付單一 oaClient2.app，拖曳到 Applications 即可使用，不需要額外安裝腳本。首次啟動建立 ~/Library/Application Support/oaClient2/Config.ini，可手動修改；不寫入 app bundle。
- 只擷取 oaClient2 視窗，截圖存入 ~/Library/Application Support/oaClient2/picture。紀錄在 logs、網站資料在 browser-profile、單例鎖為 instance.lock，皆在同一資料根。
- OA 圖示及工具列圖片封裝在 .app 內，不散放在程式旁。
- 保留工具列、Console 開關、網址對話框及 INI 縮放重啟還原。
- 保留 UserSet／userid／公司別等偏好保存、回填及關閉登出契約。
- 清除舊網站資料後只回填 INI 程式偏好，不保存密碼或登入 token。
- hcopen 沿用作業系統協定處理方式，在 Mac 查證並記錄實際支援情形。

Console 的 Windows HWND／SetParent 實作不能直接搬到 Mac，
須實作及驗證 Cocoa 對應；不得改回已撤回的主網站宿主。
遇到無法沿用的介面，先查清楚並提出具體差異。

CEF SDK、建置產物、快取及瀏覽器 profile 放在 Mac 本機非同步目錄。
Mac 交付放 artifacts/macos-arm64；Windows 交付保留 artifacts/oaClient2。
不要共用兩平台的 CMakeCache 或個人 Config.ini。
Windows 的 EXE、DLL、prg 不作為 Mac 建置依賴；
Reptool 的 Mac 方案暫不實作，也不刪除 Windows 的報表功能及檔案。
Windows 交付 prg 已由使用者精簡，禁止從根 prg 自動補回被刪除的工具。

保留線上更新功能於工作計畫，目前尚未實作。
未來更新流程保持唯一共用來源，平台只處理程式替換及重啟差異。
更新來源、版本及安裝策略待設計，本輪先完成 Mac 移植，
不得把尚未實作的線上更新宣稱完成或因移植而移除需求。

每輪更新工作紀錄、進度與交接文件，保留穩定工作 ID。
區分實作、編譯、測試及使用者驗收；未測項目清楚標示。
共用來源有修改時，標示 Windows 回歸待執行。
列印預覽及注音由我測試；其餘執行適當的自動與實機驗證。
Git 已有2026-10-13使用者授權的首次本機來源提交，無遠端及標籤；後續不自行提交、推送或建立遠端。

可以開始準備環境及開發。
```

詳細接續狀態以 [HANDOFF.md](../HANDOFF.md) 與 [PROGRESS.md](../PROGRESS.md) 為準；提示詞的版本資訊日後應隨實際交付更新。

M04 最新要求：Windows 的 EXE 旁 INI／picture 與 Mac 的 Application Support 配置不同，詳細見 [PLATFORM-PATHS](PLATFORM-PATHS.md)。SDK／中間建置仍放本機非同步開發目錄；不可把 Mac 目錄套用到 Windows，共用 INI／命令／UserSet 保持唯一來源。

## 最新追加需求（M05～M07／W21～W22）

- Mac 專屬碼在 macOS 環境開發，Windows 專屬碼在 Windows 環境開發；共用來源保持唯一，另一平台回歸另列。
- Mac 新安裝 HomeUrl 空白，顯示內嵌本機歡迎頁及設定網址按鈕；確認後才保存。Windows 相同頁面 W21 待回 Windows 接線及實測。
- Mac 隱藏 Chromium 縮放彈窗，維持 INI 比例保存與重啟。Windows 相同需求 W22 先記錄，到 Windows 再做。
- Mac 重複開啟顯示既有 oaClient2 視窗，不建立標準 Chrome 新分頁；保持 Views 主網站，不改回已撤回宿主。實際結果與未測分支見 PROGRESS。
