# oaClient2

更新：2026-10-12。Windows 簡易版 0.1.6 已可執行；Mac arm64 0.1.6 已建置交付，列印預覽／注音待使用者驗收。

## 執行 Windows 版本

開啟 `artifacts/oaClient2/oaClient2.exe`。0.1.6依使用者要求不使用沙箱，全部應用功能編入此EXE；CEF版本未變的一般更新只替換EXE，首次交付仍需完整資料夾。CEF 必要 DLL、資源與 locales 集中在 cef/；視窗與工具列圖示已內嵌主程式 EXE。交付仍須包含 cef/，不能只複製 EXE。

- 每次啟動主視窗最大化，載入 `https://oa.lysm.com.tw/`。
- `Config.ini` 放在 EXE 同目錄，可手動編輯；首次啟動會建立，若本機有初版 INI，僅在新位置不存在時複製保留。
- 網站資料預設啟動前全部清除，程式設定與截圖保留。
- 下方左側按鈕／F12 開啟或關閉嵌入式 Console；右側依序為首頁、伺服器設定、MAC、瀏覽目錄、截圖、還原比例、縮小、放大。
- 瀏覽目錄開啟實際 Config.ini 所在目錄：Windows 目前為 EXE 同目錄，Mac 為 `~/Library/Application Support/oaClient2/`。截圖只擷取 oaClient2 視窗，存到各平台設定目錄的 `picture/`。
- Ctrl+P 使用 CEF Chrome 內建列印預覽；F8 開啟 Config.ini。

使用者已確認 0.1.2 Microsoft 注音正常，沒有額外浮動組字窗；0.1.3 調整圖示封裝，主網站宿主相同。0.1.0 列印預覽曾通過使用者測試，最新版本尚未再次驗收；詳細證據見 [PROGRESS.md](PROGRESS.md)。

## 執行 Mac 版本

將 `artifacts/macos-arm64/oaClient2.app` 拖曳至 Applications 後開啟，只支援 Apple Silicon arm64。首次啟動顯示本機歡迎頁，HomeUrl 空白；設定確認後才保存網址。在 `~/Library/Application Support/oaClient2/` 建立組態；Config.ini／picture／logs／profile／lock 均放該目錄，Framework／Helper／圖示全部在 bundle。沿用同一 app／common，沒有另建分岔來源。

正式網站、Console、設定／縮放、截圖及兩輪合成網站清理／登出已測；列印預覽與注音由使用者測試。Windows 共用來源回歸待執行；本機 ad-hoc 簽章，正式簽署／公證與自動更新未實作。詳見 [Mac 操作](docs/MACOS-USAGE.md)與 [PROGRESS](PROGRESS.md)。

Mac 注音只驗證一般輸入與焦點；額外浮動組字窗是 Windows 專屬問題，依使用者確認不列入 Mac 測試／待驗收。

## 開發與交接

Mac 專屬程式在 macOS 開發、Windows 專屬程式在 Windows 開發，共用來源仍只有一份。Windows W21～W26已完成入口接線、MSVC Release／74項核心及本輪實機回歸，交付0.1.6已更新：空白歡迎頁、隱藏縮放彈窗、背景登出／三秒退出、設定目錄、動態標題及完整工具列字樣。列印預覽／Microsoft注音與正式OA登出仍待使用者驗收，詳見[進度](PROGRESS.md)。

Windows 與 Mac 的組態位置不同，接續開發先讀[平台路徑對照](docs/PLATFORM-PATHS.md)；共用 INI／UserSet 流程不重寫。

- [Windows 接續提示詞（可直接複製）](docs/WINDOWS-CODEX-PROMPT.md)
- [Mac 接續提示詞（可直接複製）](docs/MAC-CODEX-PROMPT.md)
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

從 [GitHub Releases](https://github.com/JimmyWon1028/oaClient2/releases) 下載編譯好的ZIP；Mac壓縮包只包含完整oaClient2.app，不含Config.ini、快取、profile、截圖或紀錄。先提供macOS arm64初版測試版本，Windows在Windows環境完成編譯／測試後再補齊。下載與校驗方式見[RELEASES](docs/RELEASES.md)。這不是程式內線上更新功能，U01尚未實作。
