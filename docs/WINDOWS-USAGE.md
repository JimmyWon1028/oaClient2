# Windows 操作與設定

2026-10-12，Windows x64 簡易版 0.1.6。

Windows 的 Config.ini／picture 在 EXE 旁，這是 Windows 配置。Mac 改用 Application Support，不能套用到 Windows；共用程式讀寫組態前，先核對[兩平台路徑對照](PLATFORM-PATHS.md)。INI 欄位與共用流程仍相同。

## 交付位置與資料

`artifacts/oaClient2/oaClient2.exe`為專案內交付入口，包含應用功能；0.1.6依使用者要求不使用沙箱，採獨立EXE。cef/只保留配套的CEF執行DLL／PAK／locales等原始元件，不混入oaClient2.exe／oaClient2.dll。首次交付保留整個cef/，不能單獨移動EXE。視窗與工具列圖示已編譯進根目錄 oaClient2.exe，不依賴外部 PNG。

| 資料 | 位置 | 保留規則 |
| --- | --- | --- |
| 程式設定 | EXE 同目錄 Config.ini | 保留；可手動編輯 UTF-8，支援 BOM／CRLF，拒絕 UTF-16。 |
| 截圖 | EXE 同目錄 picture/Snapshot*.jpg | 保留；不屬網站清理範圍。 |
| 網站資料 | LocalAppData/oaClient2/data/browser-profile | ClearCache=Y 時，主程序取得單例鎖後、初始化 CEF 前整個刪除。 |
| 執行紀錄 | LocalAppData/oaClient2/data/application.log、cef.log | 不包含在網站 profile 清理範圍。自有 application.log 只記錄階段、狀態和時間，不記錄登入參數。 |

初版 Config.ini 曾在 LocalAppData/oaClient2/data；新位置不存在且舊 INI 存在時，程式複製設定到 EXE 同目錄。已有新 INI 時優先使用它，不覆蓋；打包腳本也不覆蓋交付資料夾的 Config.ini。

使用 Codex 的封裝環境建置時，LocalAppData 可能映射到該應用套件的 LocalCache；實際執行以程式使用者環境為準，不能把開發機的映射絕對路徑硬編碼。

## 工具列

| 按鈕 | 功能 |
| --- | --- |
| 左側 Console | 在網站下方開啟／關閉 DevTools，開啟時選 Console 分頁；F12 同功能。 |
| 首頁圖示 | 重新讀取 INI 的 HomeUrl／HomePage 並載入首頁。 |
| 伺服器圖示 | 單行網址對話框，開啟時全選目前網址；藍色提示、置中確定，X／ESC 取消。確認後驗證 HTTP／HTTPS、寫入 HomeUrl 並立即載入。取消不改設定。 |
| MAC | 顯示目前啟用的 IPv4 網路介面及各自 MAC；只在本機對話框顯示。 |
| 瀏覽目錄 | 開啟實際 Config.ini 所在目錄，目前為 EXE 同目錄。M11 共用來源已調整，Windows 重新編譯／回歸待 W24。 |
| 截圖 | 擷取前景 oaClient2 視窗的可見範圍，含視窗標題與工具列；存成 JPG，詢問是否開啟檔案所在資料夾。不是整個桌面，也不是整份網頁的長截圖。 |
| 還原比例 | 還原至 100%，保存縮放設定。 |
| 縮小／放大 | 使用 Chromium 縮放階段，保存百分比至 INI。 |

Console 區域目前固定 220 DIP 高，尚未提供舊版分隔線拖曳。原本隱藏的錄影／TeamViewer／全螢幕按鈕不在此次可見工具列範圍。

## Config.ini

安全範例：[Config.example.ini](../config/Config.example.ini)。實際 Config.ini 放在主程式同目錄；不是修改範例檔就會套用。

| 欄位 | 意義／預設值 |
| --- | --- |
| SysSet.HomeUrl | https://oa.lysm.com.tw/；純主機名稱補 https://。 |
| SysSet.HomePage | 可選首頁路徑；與 HomeUrl 組合載入。 |
| SysSet.ClearCache | Y；啟動前刪除全部網站 profile。N 明確保留資料，會改變預設全清行為。 |
| SysSet.Locale | zh-TW；CEF 語系。 |
| SysSet.ReptoolPath | 預設prg/Reptool.exe；空白亦用此預設，接受相對主程式根目錄的路徑或本機絕對路徑。 |
| SysSet.ReptoolConfigIni | 可選報表INI的相對／絕對路徑；相對主程式根目錄，空白時傳目前Config.ini。 |
| SysSet.apiUrl | 接收到 OA 的 apiUrl Console 訊息後更新。 |
| Window.Width／Height／Left／Top | 記錄一般視窗大小與位置，還原時使用；寬高有範圍限制。 |
| Window.Maximized | 記錄關閉時狀態；最新要求為每次啟動固定最大化，因此 N 不會取消啟動最大化。 |
| UserSet.ZoomPercent | 預設100；下次啟動及主框架載入完成後套用，讀入範圍 25～500。使用百分比，未直接匯入舊 oaClient 的 ZoomStep 索引。 |

F8 用記事本開啟實際設定。語系、快取選項、Reptool 等於下次啟動套用；首頁按鈕及伺服器設定會重新讀取設定。關閉時只更新視窗欄位，保留其他欄位與註解。

## 目前相容範圍

已實作 `cmd=clientReady`、`cmd=loginParam`、`apiUrl`、`cmd=prt`、`cmd=ini`、`cmd=load-userset`、登入狀態回報與關閉登出；`hcopen:///`承接OS協定處理器。Reptool 呼叫保留原命令、當次登入參數（分號轉 |）及第二個 INI 路徑參數；參數以 Windows 引號規則包裝。登入參數僅保存在記憶體，不寫入 INI。

Reptool 實際啟動、報表列印與完整舊 OA 命令尚未驗收。`scale`、`opendir`、`clearcache`、`openurl`、`printLandscape`與其他未列明命令仍待後續盤點；簡易版不等於全部命令相容。

## 交付結構與內嵌圖片

```text
artifacts/oaClient2/
  oaClient2.exe       # 主程式，含全部應用功能、8張PNG與OA圖標
  Config.ini         # 實際設定，保留
  Config.example.ini # 設定範例
  picture/              # 視窗截圖，保留
  prg/               # Reptool等使用者要求保留的Windows工具
  cef/
    libcef.dll
    chrome_elf.dll
    locales/
    ...              # 其他必要CEF資源
```

PNG 名稱只是程式內嵌資源的識別；不用將原 PNG 複製到程式目錄。Console 的 Windows 宿主實作與一般啟動注意事項見 HANDOFF.md。

## 登入偏好與關閉登出

UserSet支援userid、last_select_database（公司別）、def_lang、user_font、report_font、easyui_theme、easyui_bgcolor、easyui_bgimage等網頁傳入的通用偏好，並非固定欄位白名單。登入userid通常由OA完成登入流程時發送，公司別由選取時發送；沒有匯入舊帳號或保存密碼。

啟動先清舊網站資料，再從INI偏好建立新的當次Cookie，供OA原本的getCookie讀取；load-userset及$usr也可讀回。INI回填不是自動登入，登入參數／token仍不保留。關閉時已登入才呼叫網頁logout並等待狀態0，最多約10秒；逾時仍關閉並記錄，不能把逾時視為伺服器已登出。

Reptool使用隨附prg/Reptool.exe及主程式根目錄作為工作目錄；若報表需要其他範本／外部安裝，以實際工具的需求為準，本輪未複製prg以外的舊資料夾。詳細來源與偏好清單見[相容說明](LEGACY-COMPATIBILITY.md)。

## 0.1.5 設定保存

內容沒有改變時不再重寫Config.ini。同步工具或編輯器若只禁止改名／替換、但允許寫入，程式保留原檔及其屬性寫回；不預先清空原檔，寫入完成後調整長度與flush。真正唯讀／沒有寫入權限仍明確報錯，原資料與暫存予以保留，不自動更改權限。原檔寫回fallback不具原子替換保證；一般情況仍優先採ReplaceFileW。

## 0.1.6 更新與目錄規則

CEF版本及其他外部相依未變時，一般程式功能修改只需正常關閉oaClient2，再替換根目錄oaClient2.exe。Config.ini、picture、prg及使用者其他資料保留，不以設定範例覆蓋個人INI。CEF升級則須連同完整匹配的cef/更新，外部報表工具另有更新時才替換對應prg檔案。

原pict截圖已搬到picture，檔案SHA256核對相同；程式之後只建立／寫入picture。打包不覆蓋或清除兩種截圖目錄；其他部署位置如有舊pict，可保留或自行搬到picture。

使用者明確選擇不使用沙箱，僅作ERP客戶端；不因此加入舊版disable-web-security或allow-file-access-from-files等旗標。Windows透過CEF官方CefScopedLibraryLoader載入cef/libcef.dll，驗證API／版本，主程序和子程序共用同一EXE，子程序明確傳入libcef-path；資源及locales固定指向cef/。

## 壓縮交付

Windows目的資料夾現為artifacts/oaClient2。直接壓縮整個oaClient2資料夾即可包含主程式與CEF／報表工具；解壓縮後從該資料夾開啟oaClient2.exe。程式更新時保留接收端既有的Config.ini、picture及其他使用者資料。

## 交付prg由使用者維護

2026-10-12使用者已刪除Windows交付prg不需要的檔案，並明確指示「不要再補回來」。核對artifacts/oaClient2/prg只保留docto.exe、Reptool.exe、TSCLIB.dll、zint.dll。package-windows.ps1已移除整份來源prg複製，後續打包不補回、不覆蓋或清理交付prg。根prg保留歷史副本，不能用來自動恢復；新交付目錄的工具由使用者另行準備。

## W21／W22：待回 Windows 環境實作

使用者已要求 Windows 與 Mac 使用同一份本機歡迎頁：新安裝／未設定 HomeUrl 顯示歡迎頁及「設定伺服器網址」按鈕，確認後才保存，已有個人網址直接載入。共用 src/common/welcome.h／app.cpp 已準備；Windows 目前 0.1.6 仍沿用原預設網址，需在 Windows 入口啟用空白設定政策並更新／核對範例、編譯與實測。不把 Mac 結果當成 Windows 已交付。

Windows 放大／縮小也須隱藏 Chromium 縮放彈窗，但依使用者最新指示本輪只記錄 W22，到 Windows 再實作。共用 AppContext.hide_zoom_bubble 預設 false；Mac 入口已啟用，Windows 尚未啟用。保留原縮放階段、INI ZoomPercent 保存及重啟還原。

平台專屬程式碼由對應環境開發：Mac 在 macOS、Windows 在 Windows；Windows EXE 旁 Config.ini／picture 與 LocalAppData 配置不因以上需求改變。Windows 交付 EXE／cef／prg／個人 INI 本輪未更新。


## W25：Windows 相同標題需求確認（2026-10-13）

使用者明確要求 Windows 標題列與 Mac 相同：軟體名稱從 URL 頁面的 document.title 取得，顯示「網頁軟體名稱 [用戶端版本 0.1.6]」；尚未取得名稱時顯示「oaClient2 [用戶端版本 0.1.6]」。共用 M12 實作已備妥，Windows 編譯／實機測試及交付更新留到 Windows 環境。本輪只補記需求與交接，未修改程式或交付、未編譯／測試／安裝，不將 Mac 結果當成 Windows 驗證。
