# Windows／macOS 組態與檔案配置

2026-10-12，工作 ID：M04。使用者已確認兩平台的資料位置不同；接續 Windows 開發時須依此表核對，不將 Mac 路徑套用到 Windows。

## 目前核准的配置

| 項目 | Windows | macOS arm64 |
| --- | --- | --- |
| 執行入口 | 使用者放置的 oaClient2.exe；交付在 artifacts/oaClient2 | 拖曳完整 oaClient2.app 到 /Applications 後啟動 |
| Config.ini | EXE 同目錄 | ~/Library/Application Support/oaClient2/Config.ini |
| 瀏覽目錄 | 開啟實際 Config.ini 的父目錄，目前為 EXE 同目錄 | 開啟實際 Config.ini 的父目錄，即 ~/Library/Application Support/oaClient2 |
| 截圖 | EXE 同目錄 picture | ~/Library/Application Support/oaClient2/picture |
| 程式紀錄 | LocalAppData/oaClient2/data/application.log | ~/Library/Application Support/oaClient2/logs/application.log |
| CEF 紀錄 | LocalAppData/oaClient2/data/cef.log | ~/Library/Application Support/oaClient2/logs/cef.log |
| 網站資料 | LocalAppData/oaClient2/data/browser-profile | ~/Library/Application Support/oaClient2/browser-profile |
| 單例 | Windows Local mutex | ~/Library/Application Support/oaClient2/instance.lock 的 flock |
| CEF／圖片 | CEF 在 EXE 旁 cef；OA 圖示與工具列圖片內嵌 EXE | Framework／Helper／圖片在 .app bundle 內 |

`~` 是目前使用者家目錄。正式程式透過平台 API 取得目錄，不硬編碼使用者名稱或 Dropbox 路徑。SDK／中間建置仍放各平台本機開發目錄，Mac 保留 Library/Caches/oaClient2/deps／build，不屬於執行組態資料。

## 共用程式碼如何讀取組態

- src/common/ini.* 維持唯一來源與現有 UTF-8 INI、SysSet／Window／UserSet 格式；它接收呼叫方傳入的路徑，不自行判斷作業系統。
- src/platform/windows/platform.cpp 的 GetAppPaths 提供 EXE 旁 Config.ini，保留 Windows 舊本機 INI 遷移及現有 Reptool 契約。
- src/platform/macos/platform.mm 的 GetAppPaths 提供 Application Support 中的 Config.ini；與 .app 的安裝／搬移位置分開。
- 各平台主入口仍呼叫同一 LoadSettings。目標沒有 Config.ini 時，首次啟動建立預設組態；已有檔案就讀取並保留。網站發送設定或工具列縮放時，沿用同一 INI 保存流程。
- app.cpp 的截圖流程透過平台 PictureDirectory 選路徑；Windows 返回 EXE/picture，Mac 返回 Application Support/oaClient2/picture。沒有新增兩份工具列或 INI 實作。
- AppPaths.application 表示主程式所在目錄；Mac 安裝後為 /Applications。M11 起兩平台「瀏覽目錄」均由共用 app.cpp 開啟 AppPaths.config.parent_path()；目標是實際 Config.ini 所在目錄，與安裝位置分開。F8 仍開啟該 Config.ini 檔案。

Windows 開發與回歸時，必須確認 Windows GetAppPaths／PictureDirectory 的結果，不能把 Config.ini 改放 Mac Application Support，也不能把 Windows 個人設定匯入 Mac。

## Mac 拖曳安裝與資料產生

交付只需完整 oaClient2.app。拖曳至 Applications 即完成程式放置，不需要外部 Config.ini、PNG、CEF 套件或額外安裝腳本。首次啟動自動建立 Application Support/oaClient2 與 logs，並由共用 LoadSettings 建立 Config.ini；截圖時建立 picture，CEF 產生 browser-profile。設定修改保存至相同的 Config.ini。

更新時正常關閉，再替換完整 .app；Application Support 的組態、截圖與紀錄保留。舊 Mac 交付旁 Config.example.ini／Config.ini／picture 已於 M08 依使用者明確授權刪除，交付目錄目前只保留 .app。新版不從 .app 旁讀取組態，也不自動複製 Windows 個人設定；Application Support 現用資料保留。

## 清理與資料保留

兩平台啟動清理只限各自指定的 browser-profile，仍遵守 ClearCache 設定及專用目錄／連結保護；不能清理整個 Application Support、LocalAppData、安裝目錄或 .app bundle。

INI／picture／logs／instance.lock 不在網站清理目標中；舊網站 Cookie／登入 token／密碼不遷移。清理後只從 INI UserSet 程式偏好建立當次偏好 Cookie，沿用原有契約。

## 驗證與其他需求

實作、建置與實機結果見 [PROGRESS](../PROGRESS.md) M04；Windows／Mac 回歸分別記錄，不能用 Mac 編譯結果聲稱 MSVC 已通過。Mac 額外注音浮動組字窗不需測試，一般輸入仍依既有驗收狀態。U01 線上更新與 Mac 報表仍未實作。

詳細操作：[Windows](WINDOWS-USAGE.md)、[Mac](MACOS-USAGE.md)。共用來源邊界：[SHARED-CODE-RULES](SHARED-CODE-RULES.md)。

## M05／W21 首次網址與平台開發環境

Mac 新安裝 HomeUrl 空白；內嵌歡迎頁的 data URL 僅供當次顯示，不寫入 INI。使用者確認有效伺服器網址後才保存；已有網址保持直接載入。Windows 也要求相同歡迎頁，但入口預設調整與驗證待回 Windows 完成，現行 Windows 0.1.6 仍是原預設。

Mac 專屬碼在 macOS 開發，Windows 專屬碼在 Windows 開發。共用 INI／app／welcome 保持一份；另一平台的編譯與實機回歸須另外執行。W22 的 Windows 縮放彈窗需求亦先記錄、回 Windows 再實作。
