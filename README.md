# oaClient2

最新公開版本（2026-11-12）：**0.1.8**，[GitHub Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)提供Windows x64與Mac arm64 ZIP／SHA256。兩平台已包含列印背景預設、Shift+F及現行共用修正；公開下載校驗通過，正式報表及其他待驗收範圍見[進度](PROGRESS.md)。以下保留早期狀態，以最新發布及各工作紀錄為準。

最新 Windows（2026-11-11，W39）：本機交付已進版 **0.1.8**，包含W38列印預覽背景圖形修正；Release／CTest1/1、160項通過。Mac本機仍0.1.7，須回macOS重編共用修改；公開ZIP未更新，正式報表驗收範圍見[進度](PROGRESS.md)。

更新：2026-10-30。Windows 本機交付為 **0.1.7／W36**：INI 保存採 UTF-8 BOM，啟動時自動修復既有無 BOM 設定，印表字型 report_font 已完成合成選單保存／重啟及舊 Delphi 讀取驗證；Reptool 不變。Mac 本機交付仍為 0.1.6／M24，共用修改待 macOS 重編回歸。正式 OA 報表及其他功能的驗收範圍以 [PROGRESS.md](PROGRESS.md) 為準。

## Windows 最近修改與 Mac 接續

| 工作 | Windows 本機結果 | Mac 接續 |
| --- | --- | --- |
| W31：附件選檔合併格式 | 預設 Custom Files 合併網頁允許格式，另提供 All Files；原生選檔與關閉清理已測。 | M19 已完成相同附件需求且使用者確認；保留 NSOpenPanel，只回歸必要共用介面，不重做。 |
| W32：外部協定規則 | 支援前綴＋open＋可選後綴，不分大小寫，包含 hcopen、hcopenprint、wjopen；只交 CEF 轉系統，不新增處理器檢查或註冊。 | M20 已沿用共用判斷並通過核心；真實外部啟動未測。 |
| W33：固定亮色 | 標題列／工具列不跟隨系統主題；亮色初驗通過，系統亮暗切換未實測。 | M21 已啟用共用亮色回呼與 Cocoa Aqua；亮色初驗／重啟正常，系統亮暗切換未測。 |
| W34：繁體中文錯誤提示 | Windows 及共用 INI／app 提示已翻譯，重複執行對話框實測正常；保留數字錯誤代碼。 | M22 已翻譯 Mac 自訂錯誤，系統診斷僅留紀錄，顯示中文與數字代碼；個別失敗分支見進度。 |
| W35：匯出前詢問位置 | 下載前設定 download.prompt_for_download=true；GET 匯出已確認跳出「另存新檔」，實際存檔／取消等因 UI 工具限制未測完。 | M23 已沿用共用政策；GET／POST／Blob／新視窗／右鍵、指定路徑、取消、重啟及列印另存 PDF 已測。 |

W32～W35 的 Windows Release／CTest 1/1、143 項通過，本機最新 EXE SHA256 為 `57d1a8d2426525f0ce567efe04809709898bb80e5ade6a4e2794e06970fb2290`。版本未進版，W31～W35 尚未提交／推送或發布，Mac 專屬碼及產物未在這幾輪 Windows 工作中更新；Mac 本輪實際補齊結果見 [PROGRESS](PROGRESS.md) M20～M24，不能以 Windows 結果代替 Mac 驗證。

在 Mac 使用 [2026-10-30 接續提示詞（W32～W35）](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)，先停止 Windows 操作並確認兩台 Dropbox 同步，再沿用同一份來源接續。W30 共用關閉保護列既有回歸；Windows 專屬 Ctrl+W 政策不移植為 Mac Cmd+W。

## 執行 Windows 版本

開啟 `artifacts/oaClient2/oaClient2.exe`。0.1.6依使用者要求不使用沙箱，全部應用功能編入此EXE；CEF版本未變的一般更新只替換EXE，首次交付仍需完整資料夾。CEF 必要 DLL、資源與 locales 集中在 cef/；視窗與工具列圖示已內嵌主程式 EXE。交付仍須包含 cef/，不能只複製 EXE。

- 每次啟動主視窗最大化；未設定網址顯示本機歡迎頁，確認 HTTP／HTTPS 網址後保存，已有網址直接載入。
- `Config.ini` 放在 EXE 同目錄，可手動編輯；首次啟動會建立，若本機有初版 INI，僅在新位置不存在時複製保留。
- 網站資料預設啟動前全部清除，程式設定與截圖保留。
- 下方左側按鈕／F12 開啟或關閉嵌入式 Console；右側依序為首頁、伺服器設定、MAC、瀏覽目錄、截圖、還原比例、縮小、放大。
- 瀏覽目錄開啟實際 Config.ini 所在目錄：Windows 目前為 EXE 同目錄，Mac 為 `~/Library/Application Support/oaClient2/`。截圖只擷取 oaClient2 視窗，存到各平台設定目錄的 `picture/`。
- Ctrl+P 使用 CEF Chrome 內建列印預覽；F8 開啟 Config.ini。

使用者已確認 0.1.2 Microsoft 注音正常，沒有額外浮動組字窗；0.1.3 調整圖示封裝，主網站宿主相同。0.1.0 列印預覽曾通過使用者測試，最新版本尚未再次驗收；詳細證據見 [PROGRESS.md](PROGRESS.md)。

## 執行 Mac 版本

將 `artifacts/macos-arm64/oaClient2.app` 拖曳至 Applications 後開啟，只支援 Apple Silicon arm64。首次啟動顯示本機歡迎頁，HomeUrl 空白；設定確認後才保存網址。在 `~/Library/Application Support/oaClient2/` 建立組態；Config.ini／picture／logs／profile／lock 均放該目錄，Framework／Helper／圖示全部在 bundle。沿用同一 app／common，沒有另建分岔來源。

Mac 本機 .app 已有 W27～W29、Cocoa delegate／背景 reopen 修正及 M18 打包時間；M19 附件選檔已建置並由使用者確認，當時 Release／CTest 1/1、116 項與 arm64 配套／簽章通過，版本仍 0.1.6。本機已補齊 W32～W35，Release／CTest1/1、136項及簽章通過；M24 已修正 Console 焦點 Cmd+Q 的背景殘留並完成複合回歸，系統亮暗切換未測。正式列印預覽／一般注音／OA 其他功能依各自驗收紀錄；公開 Mac ZIP 仍為 M13。本機為 ad-hoc 簽章，正式簽署／公證與自動更新未實作。詳見 [Mac 操作](docs/MACOS-USAGE.md)與 [PROGRESS](PROGRESS.md)。

Mac 注音只驗證一般輸入與焦點；額外浮動組字窗是 Windows 專屬問題，依使用者確認不列入 Mac 測試／待驗收。

## 開發與交接

Mac 專屬程式在 macOS 開發、Windows 專屬程式在 Windows 開發，共用來源仍只有一份。Windows W21～W26已完成入口接線、MSVC Release／74項核心及本輪實機回歸，交付0.1.6已更新：空白歡迎頁、隱藏縮放彈窗、背景登出／三秒退出、設定目錄、動態標題及完整工具列字樣。列印預覽／Microsoft注音與正式OA登出仍待使用者驗收，詳見[進度](PROGRESS.md)。

Windows 與 Mac 的組態位置不同，接續開發先讀[平台路徑對照](docs/PLATFORM-PATHS.md)；共用 INI／UserSet 流程不重寫。

- [Windows 接續提示詞（可直接複製）](docs/WINDOWS-CODEX-PROMPT.md)
- [最新 Mac 接續 Windows 修改提示詞（W32～W35，可直接複製）](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)
- [歷史 Mac 接續提示詞（W27～W29，Mac 已完成）](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)
- [共用程式碼與平台邊界規則](docs/SHARED-CODE-RULES.md)
- [操作與設定](docs/WINDOWS-USAGE.md)
- [環境、版本與建置](docs/ENVIRONMENT.md)
- [目前進度與測試](PROGRESS.md)
- [Mac 接續入口](HANDOFF.md)
- [需求與計畫](PROJECT-PLAN.md)
- [工作紀錄](CHANGELOG.md)
- [協作規則](AGENTS.md)
- [圖示來源](assets/README.md)

技術為 C++20、CEF 154 Chrome runtime、CEF Views 與 CMake。主網站使用 Views Chrome BrowserView；Console 使用獨立 Chrome CefWindow，由 Windows／Cocoa 平台函式定位在下方。來源共用，CEF SDK 與建置輸出放在各系統本機；使用者核准的交付例外為 `artifacts/oaClient2/`，Git 忽略但 Dropbox 仍同步。

Git 為 main 分支，使用者已授權建立公開 repository [JimmyWon1028/oaClient2](https://github.com/JimmyWon1028/oaClient2)，origin 指向該處。未修改舊 oaClient／Reptool。

網址對話框使用單行預選網址及置中確定按鈕；縮放立即保存於 Config.ini 的 UserSet.ZoomPercent，下次啟動與主框架載入完成後套用。

0.1.4新增userid／公司別等UserSet保存與回填、關閉登出等待、hcopen協定回呼，以及隨附prg/Reptool.exe呼叫。53項核心檢查與本機CEF合成設定／重啟／登出測試通過；正式登入／登出、報表及hcopen實測仍由使用者確認。詳細契約見[舊版相容說明](docs/LEGACY-COMPATIBILITY.md)與[prg副本清單](docs/PRG-INVENTORY.md)。


## 下載編譯版本

從 [v0.1.8 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8) 下載 [Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-windows-x64.zip) 或 [Mac arm64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-macos-arm64.zip)，並下載各自的 .sha256 校驗檔。兩平台不含個人 Config.ini、網站資料、快取、截圖或紀錄；Windows包含EXE／cef／安全設定範例與現用精簡prg，Mac只有完整.app。來源Tag固定a3de8b3，既有v0.1.6保留。下載與校驗方式見 [RELEASES](docs/RELEASES.md)，U01程式內線上更新尚未實作。

## 2026-10-30：M24 Mac Cmd+Q 背景殘留修正完成

M24 已重現並修正：Console 有焦點時 Cmd+Q 未進入原生結束入口，之後關閉全部 Browser／Views 仍可能留下 CEF 主迴圈。Mac sendEvent 現在先讓既有原生選單處理精確的 Command+Q，呼叫原 terminate → 共用登出／隱藏／三秒流程；沒有改寫登出或強制結束程序。

最終 arm64 Release／CTest 1/1、136 checks／0 failures、10 份 arm64 與 deep strict 簽章通過；Console 焦點 Cmd+Q、已啟用 beforeunload、附件取消組合的 ACK619ms／無ACK3032ms及實際交付3043ms期限後皆正常 SHUTDOWN_COMPLETE，主程序／Helper 全部退出。 最新本機交付仍為0.1.6，未安裝或發布；正式OA／真實鑰匙圈與其他未驗收範圍見 [PROGRESS](PROGRESS.md)。

## 2026-11-03：M25 Mac 0.1.7

客戶端Shift+F攔截已取消，本機artifacts/macos-arm64/oaClient2.app已重編為0.1.7，沿用共用W36的INI保存／自動修復。Release／CTest1/1、151項、10份arm64及deep strict簽章通過，純文字頁trusted Shift+F可輸入F；正式OA CPN與其他既有未驗收項目留使用者測試。固定CEF154.0.34 SDK／下載包／build已恢復並保留；只更新本機交付，未安裝／提交／推送／發布，Windows共用變更待目標平台回歸。詳見[進度](PROGRESS.md)。

## 2026-11-11：M26 Mac 0.1.8

Mac本機交付已同步Windows0.1.8與W38「列印背景圖形預設開啟」，直接編譯唯一共用來源，Mac產品僅同步入口版本。Release／CTest1/1、151項、10份arm64及簽章通過；直接／Blob／清除profile重啟後原生預覽背景均保留。正式OA／MRT與印表機待使用者驗收；SDK／壓縮檔／build保留，未安裝／提交／推送／發布。詳見[進度](PROGRESS.md)。
