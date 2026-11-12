# oaClient2 進度表

最新公開發布 R03（2026-11-12）：[v0.1.8正式版／Latest](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)已提供Windows x64／Mac arm64 ZIP及SHA256，公開下載校驗通過。Tag固定a3de8b3，v0.1.6保持，詳見末段及[Release文件](docs/RELEASES.md)。

最新 Mac M26（2026-11-11）：已沿用Windows W38列印背景預設並更新本機arm64 0.1.8 App。Release／151項／簽章及直接、Blob、重啟原生預覽實測通過，正式OA／印表機待驗收，未安裝／發布。詳見末段。

最新 Mac M25（2026-11-03）：已取消客戶端 Shift+F 攔截並更新本機 arm64 0.1.7 App。Release／CTest1/1、151項、簽章及純文字頁大寫F實測通過；正式CPN留使用者驗收，未安裝／發布。詳見末段。

最新 Mac M24（2026-10-30）：Console 焦點 Cmd+Q 背景殘留已定位並修正，最終 Release／136項、ACK／三秒與複合交付回歸通過；只更新本機 .app，未安裝／發布。詳見本文末段。

最新文件 D04（2026-10-30）：已將 Windows W32～W35 修改彙整於 AGENTS／README，新增 [Mac 接續提示詞](docs/MAC-WINDOWS-2026-10-30-PROMPT.md)。本輪只更新文件，Mac 尚未實作／建置；W35 的 Windows 實測限制保持，詳見末段。


最新 W35（2026-10-29）：Windows 匯出／下載啟用每次詢問儲存位置，沿用 Chromium 原生另存新檔。Release／CTest1/1、143項及 GET 匯出對話框跳出實測通過，選路徑後存檔／取消等因UI工具限制未完成實測；本機0.1.6 EXE已更新，未提交／發布。Mac需目標平台重編回歸，詳見本文末段。


最新 W34（2026-10-28）：Windows 與共用來源的自訂錯誤提示已改為繁體中文；Release／CTest1/1、143項及重複啟動對話框實測通過，本機0.1.6 EXE已更新。Mac專屬訊息待macOS處理，未提交／發布；詳見本文末段。


最新 W31：Windows 附件已修正並更新本機0.1.6 EXE；MSVC／CTest1/1、123項及原生實測通過，正式 BSI010010 待使用者驗收。沒有提交／推送／Release更新；詳見末段。

2026-10-16：M19 Mac 附件選檔修正已建置、更新本機交付，使用者回覆「我剛剛測試 oaclient2 附件 正確」。預設 Custom Files 合併網頁允許格式，另提供 All Files；版本仍0.1.6，未提交／推送／發布。詳見末段。

最新Windows W30已由使用者驗收、提交／推送並同版更新公開ZIP；版本0.1.6、Tag與Mac資產保持，詳見末段。Mac新共用關閉保護仍須在macOS編譯回歸。

更新：2026-10-13。Mac M14～M17已沿用W27～W29共用來源建置、合成實機回歸與更新本機完整.app；Release／CTest1/1、111項通過，版本仍0.1.6，詳見末段。尚未安裝、提交／推送或替換公開MacZIP；正式列印／一般注音／OA驗收仍待使用者。Windows W29使用者回覆「可以了」，MSVC／110項及來源6f2833b的同版公開ZIP保持；固定Tag與U01未實作狀態不變。

## 工作項目

| ID | 工作 | 狀態與證據 | 下一步 |
| --- | --- | --- | --- |
| W31 | Windows 附件合併篩選 | 已重現／修正；MSVC x64／123項及原生 UI、關閉清理通過，本機0.1.6 EXE已更新。 | 使用者驗收BSI010010；Mac共用介面回歸待執行，未提交／發布。 |
| W30 | Windows Ctrl+W與關閉保護 | 使用者驗收；MSVC／115項與合成實機通過，0.1.6同名ZIP已更新、公開下載核對。 | Mac共用關閉保護待目標平台編譯回歸；其他既有待驗收與U01保持。 |
| D01 | 閱讀舊 oaClient／Reptool | 已完成第一輪來源盤點；本輪核對 PAS／DFM 工具列並操作舊版 Console 開關。 | 逐一核對其他命令契約。 |
| D02 | 列印預覽技術查證 | 已確認 Electron 不符內建預覽要求；Windows 採 CEF Chrome。 | Mac 核對 #3410 正式配套及實測。 |
| D03 | Git／GitHub | W29提交6f2833b已透過HTTPS推送；遠端SHA核對一致，固定v0.1.6仍指向0fe6f35。 | 發布結果文件另行提交推送，最新main以Git核對；不移動Tag。 |
| D04 | 計畫／紀錄／跨平台交接 | 已新增 [Mac 接續 Windows 今日功能提示詞](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)，以已推送cb68ba2／W29來源6f2833b整理W27～W29、Mac Cmd／密碼政策與既有功能回歸；首次移植提示保留為歷史。 | 停止Windows編輯／建置／Git並確認同步後，Mac沿用共用來源編譯／實測；本輪只寫文件，未提交／推送。 |
| D05 | 時間與平台範圍 | 排除環境準備及測試；Mac 固定 arm64。 | 記錄測試後修正。 |
| D06 | 網站／資料／INI 決策 | 兩平台初始URL空白、設定後保存；Windows EXE旁INI，Mac Application Support，網站全清、程式設定保留。 | W21 Windows歡迎頁／保存／重啟已實測，正式網站由使用者驗收。 |
| D07 | 共用來源與平台邊界 | 已核對現行來源，新增共用程式碼規則及Mac提示詞：共用功能不重寫、不複製，平台差異獨立；Windows子程序DLL配置及Console handle／座標已透過平台介面最小抽取。 | Mac接手按平台介面最小調整，記錄兩平台回歸狀態。 |
| W01 | Windows 環境 | 已完成；Build Tools 17.14.40、MSVC 14.44.35207、SDK 10.0.26100.0、CEF 154.0.34 校驗、官方範例編譯。 | 不需重裝完整 Visual Studio。 |
| W02 | 網站與 INI | 已實作／建置；實機 OA 首頁載入，HTTP 200；UTF-8 INI、位置／大小保存。 | 0.1.4已補UserSet／userid等保存回填；正式登入對話框由使用者測試。 |
| W03 | 內建列印預覽 | 0.1.0 由使用者測試回報正常；最新版本尚未重新驗收。 | 使用者驗證 OA 列印／取消／PDF／印表機情境。 |
| W04 | 注音與啟動 | 0.1.1 發生浮動組字窗；0.1.2 已恢復 Views 主網站，使用者確認 Microsoft 注音正常。已有初次主框架 load 記錄，非完整網站初始化時間。 | 同條件比較舊版；記錄輸入法與焦點情境。 |
| W05 | 網站資料清理 | 已實作；單例、專用目錄校驗、拒絕reparse；兩輪真實CEF合成網站Cookie／LocalStorage／IndexedDB／Service Worker／cache清理回歸通過，INI偏好仍回填。 | 正式OA登入資料清理由使用者驗收；不還原密碼／token。 |
| W06 | 既有 Reptool 呼叫 | 0.1.4已隨附prg，預設相對Reptool路徑；合成程序核對兩參數／中文／引號／工作目錄通過。 | 實際 Reptool 啟動、參數／報表尚未驗收。 |
| W07 | Windows 交付 | 0.1.6入口在artifacts/oaClient2/oaClient2.exe；CEF在cef/、圖示內嵌。本機交付保留使用者資料，公開ZIP以安全清單排除個人INI／picture／logs／profile／tpl。 | 公開ZIP與下載校驗見R02；正式簽署／安裝包未做。 |
| W08 | 舊版工具列與 Console | 0.1.2 保留原圖示／順序；主網站為 Views，Console 獨立 Chrome CefWindow 嵌入下方；0.1.3 圖示內嵌。 | Console 開關／分頁、網址對話框、縮放保存、MAC 與截圖已實測；目錄完整路徑 UI 確認未完成。 |
| W09 | INI 同目錄／最大化／OA 圖示 | 已實作；實際 INI 已建立於交付目錄，主視窗最大化，標題 OA 圖示顯示。 | Mac 最新改為 Application Support；見 M04。 |
| W10 | Microsoft 注音浮窗修正 | 0.1.2 使用者確認「已正常，沒有額外浮動組字窗」。 | 多螢幕／DPI／其他輸入法待測。 |
| W11 | CEF 集中與啟動 | 0.1.6不使用沙箱，主程式為獨立EXE；cef/只保留234份原始CEF執行元件，SHA256一致。 | Mac Framework／Helper 已實作；見 M02。 |
| W12 | URL 對話框 | Win32單行預選網址、藍字、置中確定；W21歡迎／工具列入口、X／ESC取消、無效協定拒絕、HTTP確認保存與重啟通過。 | HTTPS及正式網站完整使用者操作待驗收。 |
| W13 | 縮放重啟保存 | 0.1.2 125%→150% 保存並重啟套用，測後恢復125%；0.1.3 一般啟動100%→110%→100%均寫回INI。 | Mac 已沿用相同設定契約並測試；見 M03。 |
| W14 | 圖檔內嵌 EXE | 0.1.3 八張 RCDATA 與原 PNG 逐位元比對相同；root PNG 已移除，一般啟動圖示正常。 | Mac bundle 資源及 ReadApplicationImage 已實作；見 M02。 |
| W15 | UserSet／userid相容 | cmd=ini、load-userset與$usr已實作；本機CEF首載偏好Cookie、回呼及重啟保存通過。 | 正式登入對話框與完整偏好由使用者確認。 |
| W16 | 關閉登出 | 登入狀態查詢、logout一次、非阻塞輪詢、超時保護；兩次合成CEF關閉均等待完成。 | 真正OA登入後關閉由使用者確認。 |
| W17 | hcopen協定 | 已核對舊協定suffix規則，CEF回呼已實作；核心判斷通過。 | 使用者表示自行測試；工具環境未查到Windows登錄，不自行安裝。 |
| W18 | prg複製／Reptool | 原12份副本已核對；使用者精簡交付為4份，打包停止同步來源prg，不補回已刪除檔案；原呼叫契約測試通過。 | prg由使用者維護；實際報表與印表機未驗收。 |
| W19 | 關閉INI error5修正 | 0.1.5保存修正、62項核心及交付目錄關閉／重啟通過；使用者回覆「可以」。 | 本次關閉錯誤修正已確認；其他功能依各自驗收紀錄。 |
| W20 | picture／單EXE更新 | 0.1.6改picture，舊圖搬移雜湊一致；應用功能全編入EXE、CEF不混雜；Release／62項通過，實機首頁、截圖與Console核對。 | 注音／列印仍由使用者測試；Mac 狀態另列 M01～M03。 |
| U01 | Windows／Mac線上更新 | 使用者要求保留；尚未實作、未測試，沒有可用的自動更新模組。 | 設計更新來源、版本、CEF配套及平台替換／重啟流程，共用邏輯保持一份。 |
| M01 | Mac 工具與 arm64 CEF | 已完成：native arm64、Xcode 27.0、Clang 21、CMake 4.4、官方 CEF 154.0.34 standard 雜湊核對及 cefsimple 建置。 | 依 ENVIRONMENT.md 重現。 |
| M02 | Mac 平台／建置 | 已實作／Release 建置：沿用 common／app；Cocoa 入口、Framework／五種 Helper、Console 父子視窗、資源與 .app 封裝。 | Windows 共用來源回歸待執行；正式簽署／公證未做。 |
| M03 | Mac 功能／交付驗證 | CTest 1/1、61 項通過；正式 OA、Console、INI 縮放、網址 ESC、JPG、兩輪真實 CEF 儲存／合成登出通過；交付 artifacts/macos-arm64。 | 列印預覽／一般注音輸入由使用者驗收；Windows 專屬注音浮窗不需在 Mac 測試。正式登入／登出、hcopen、其他 Mac／多螢幕尚待驗證。 |
| M04 | Mac 組態與拖曳安裝 | 已實作／建置；/Applications 首次產生 Support INI、110% 保存、JPG 截圖、重啟清 profile 並保留 INI／picture／logs 均實測。 | Windows 回歸待執行；路徑見 PLATFORM-PATHS。 |
| M05 | Mac 空白網址與共用歡迎頁 | 已實作／Release／68 項通過；空白 HomeUrl、歡迎頁按鈕、ESC、工具列設定、確認後保存／HTTP200、設定網址重啟已測。 | 最終 /Applications 歡迎頁、設定 ESC、截圖及正常退出已測；Windows 另列 W21。 |
| M06 | Mac 隱藏縮放彈窗 | 已實作、建置及放大／縮小實測；使用 CEF chrome_zoom_bubble，保留 INI 保存。僅 Mac 入口啟用。 | 最後版本歡迎頁放大／縮小亦已實測；Windows 另列 W22。 |
| M07 | Mac 額外 Chromium 視窗 | 已實作 Mac relaunch 回呼及 URL modal 正常取消；修正後主視窗正常退出／重啟、Finder 再開啟保持 oaClient2。 | 歡迎頁取消後正常退出已測；CEF relaunch 回呼分支仍待直接觸發。 |
| M08 | Mac 交付舊檔清理 | 依使用者授權刪除交付旁兩份 INI、舊 picture 及 .DS_Store；目前只剩 oaClient2.app。主程式、Windows 交付及 Mac 現用 INI／截圖雜湊不變。 | 本輪未改程式、未重新編譯／執行功能測試；打包仍只交付 .app。 |
| M09 | Mac 重新完整編譯 | 官方固定 CEF 重新下載／雜湊一致；全新 Release 建置、227 個物件編譯、CTest1/1／68項通過，簽章與 arm64 配套核對。已更新交付 .app。 | 依使用者指示未安裝、未啟動；本輪實機／列印／輸入驗證未執行。 |
| M10 | Mac 隱藏背景登出／三秒退出 | 已實作／Release／CTest1/1、75項；最後合成實機 ACK 951ms／無回應3029ms，主窗與 Console 隱藏、beforeunload 允許、正常退出。 | 正式 OA 登出待使用者驗收；Windows 另列 W23，共用修改回歸待執行。 |
| M11 | 瀏覽 Config.ini 所在目錄 | 共用 app.cpp 已調整；Mac Release／CTest1/1、75項通過，Finder 實際開啟 Support 內的設定目錄。交付已更新。 | 未安裝；Windows 編譯／實機回歸另列 W24。 |
| M12 | 網頁軟體資訊與客戶端版本標題 | 共用 app.cpp 已調整；Mac Release／CTest1/1、75項，歡迎頁及兩個網站動態名稱實測通過，交付已更新。 | 未安裝；Windows 編譯／實機回歸另列 W25。 |
| M13 | 右側工具列舊版間距／完整文字 | 共用按鈕寬度採舊 DFM，右側346→298 DIP；減少內部留白，Mac完整文字實測及Release／75項通過，交付已更新。 | 保留測試視窗供使用者驗收；Windows另列W26，未安裝；使用者已授權本機提交。 |
| M14 | Mac W27連結狀態提示 | 唯一app.cpp的chrome_status_bubble直接編譯；JavaScript選單／子選單及HTTP連結實機無泡泡，動作／導航正常。 | 正式OA選單由使用者驗收；本機.app已更新，公開ZIP未更新。 |
| M15 | Mac W28密碼保存政策 | 原共用RequestContext偏好成功；原生POST及重啟AJAX正常、無保存提示，啟動政策紀錄通過。 | 正式OA登入由使用者驗收；不擴大成所有既存密碼填入皆已停用。 |
| M16 | Mac W29網頁快捷鍵／共用回歸 | 15組指定鍵在handled／unhandled均有trusted事件；編輯／F12 Console及兩輪UserSet／網站清理通過，111項核心／完整arm64配套核對。 | 使用者實體鍵盤／Fn、正式列印／一般注音與OA功能驗收保留；不移Tag、不發布。 |
| M17 | Mac delegate生命週期／background reopen | main.mm僅保留弱delegate的強參照並檢查關閉狀態；最終Finder background=1兩次、期限3019ms／ACK1418ms與Console／beforeunload／全部退出通過。 | 沒有共用／Windows碼變動；最小Mac修正與未測窗口操作詳見末段。 |
| M18 | Mac交付.app系統打包時間 | 已修正package-macos.sh，外層mtime為當次系統13:43:20；265份內容不變／簽章及Shell語法通過。 | Finder顯示交付時間；實際編譯及功能驗收仍按各自證據，不改Windows。 |
| W21 | Windows 相同歡迎頁 | Windows 入口已啟用空白 HomeUrl／allow_empty_home_url；沿用 welcome.h／app.cpp。MSVC／74項通過，空白頁、兩個設定入口、ESC／X、無效網址拒絕、HTTP保存／重啟已實測。 | 列印／注音及正式使用者驗收待確認；保留既有個人網址。 |
| W22 | Windows 隱藏縮放彈窗 | 入口 hide_zoom_bubble=true；MSVC／74項，網站及歡迎頁110%→100%、還原100%、網站重啟110%實測，無Chromium彈窗。 | 其他DPI／多螢幕未測；比例保存契約不變。 |
| W23 | Windows 隱藏背景登出／三秒退出 | 入口 background_logout_close=true；合成ACK649ms、一般桌面ACK1117ms、無回應3007ms；logout一次、主窗／Console隱藏、beforeunload放行及全部程序退出通過。 | 正式OA登出待使用者驗收；到期不代表伺服器登出成功；晚建立窗口競態未獨立重現。 |
| W24 | Windows 設定目錄瀏覽回歸 | 沿用 paths.config.parent_path()；建置與正式交付位置的按鈕／提示實測，Explorer Shell確認實際Config.ini父目錄。 | 已更新交付EXE；Windows INI仍在EXE旁。 |
| W25 | Windows 網頁資訊標題回歸 | 歡迎頁預設、正式OA名稱及合成document.title動態更新實測；版本0.1.6。共用標題來源未重寫。 | 正式登入後公司名稱切換由使用者驗收；未新增INI品牌欄位。 |
| W26 | Windows 工具列間距／完整文字 | M13共用298 DIP／左右2 DIP設定已在Windows編譯，MAC／瀏覽目錄／截圖／還原比例完整顯示、原圖示與順序核對。 | 使用者最終間距驗收、其他DPI／多螢幕未測。 |
| W27 | 隱藏連結狀態提示 | 共用CefBrowserSettings.chrome_status_bubble=STATE_DISABLED；Windows Release／CTest1/1通過。真實CEF合成JavaScript選單／子選單無左下角提示，原動作正常；EXE已更新及重開OA。 | 正式OA選單由使用者驗收；Mac須在macOS重新編譯／實測，Mac產物未改。 |
| W28 | 停用儲存密碼提示 | 共用RequestContext在建立瀏覽器前停用保存／自動登入；MSVC／CTest1/1／74項，舊版提示正向重現、修正版原生及重啟AJAX無提示通過。本機EXE與同版公開ZIP已更新，來源c5cd549。 | 正式OA登入由使用者驗收；Mac W27／W28重編／實測未執行，Tag保持。 |
| W29 | Chrome衝突熱鍵交回網頁 | 共用按鍵政策及CEF網頁優先／OnKeyEvent fallback已實作，MSVC／110項通過；使用者回覆「可以了」，本機與同版公開ZIP已更新，來源6f2833b。 | 使用者回報只適用Windows熱鍵；代理逐項UI矩陣未執行、Mac Cmd實機未驗證，其他功能不擴大驗收。 |
| R01 | Mac ZIP Releases | v0.1.6初版測試Release已公開；ZIP只有.app，GitHub大小／digest、無登入公開下載ZIP與校驗檔逐位元一致。 | 列印／一般注音等仍待使用者驗收；Windows補齊見R02。 |
| R02 | Windows Release補齊 | 依同版更新授權，v0.1.6同名Windows x64 ZIP／.sha256已替換為W29；240檔CRC／SHA256及無登入公開下載一致，ZIP 189880195 bytes／SHA256 849a2678。 | 其他使用者驗收及Mac W27～W29回歸保持；Tag／Mac資產未變，U01未實作。 |

## 已完成的驗證

- Release 編譯成功，CTest 1/1 通過；當時核心測試共29項（0.1.6為62項），涵蓋 INI 建立／UTF-8、手動設定、未知鍵與註解保留、視窗／縮放偏好、命令字串、專用 profile 全刪／錯誤目錄拒絕及 UTF-16 錯誤。
- 使用者明確回報 0.1.0「測試正常」，對應其自行驗證的預覽列印與注音；未取得每個輸入法／DPI／最小化情境的逐項結果。
- 0.1.1 OA 首頁實機成功載入；application.log 的一次首次主框架 load 為 1725 ms、HTTP 200。這不是冷啟動基準或已證明更快；不包含完整 OA 後續初始化。
- 專案交付 EXE 確認可啟動，Config.ini 位於 EXE 同目錄；下方原圖示工具列與主視窗最大化實際呈現。
- 舊版 Console 已操作開啟／關閉並比對下方位置。
- 0.1.1 Console 初次開啟選中 Console panel，再次點擊關閉後網頁高度還原。伺服器對話框顯示實際 HomeUrl，確認相同 URL 後成功保存並重新載入。
- 放大 100%→110%、縮小 110%→100%、還原比例 110%→100%，Config.ini ZoomPercent 值逐次核對一致。
- MAC 按鈕顯示啟用網路的 IP／MAC；未在工作紀錄保存實際識別資訊。
- 截圖按鈕於 12:35 產生 pict/Snapshot20261012123501-330.jpg，52,589 bytes；已開圖確認只含 oaClient2 視窗、標題與工具列，沒有桌面外部區域。測試圖保留於交付資料夾，不納入 Git。
- 曾嘗試在同一 Views Window 加入 Alloy DevTools；CEF 154 強制 Chrome style 且影響主視窗。該方案已移除，0.1.1 曾改為原生 Chrome 子視窗；0.1.2 因注音回歸問題恢復 Views 主網站、只嵌入獨立 Console Window，未以失敗試驗充當完成。

## 待驗證／限制

最新列印預覽需使用者再次回歸；Microsoft 注音的浮動組字窗已於 0.1.2 通過使用者確認。完整 Reptool、真實網站儲存逐項清理、下載／協定／全部 OA 命令、多螢幕 DPI、實體印表機／PDF 輸出、效能比較、Mac 已執行項目另列於本文件 M01～M03；列印／注音待使用者驗收。Console 高度固定 220 DIP，尚無可拖曳分隔線。

## 計時

環境完成／兩小時實作起算：11:25:29。初版第一次實作及建置完成：11:35:44，約 10 分 15 秒；其後測試另計。使用者測試、交付位置討論與本輪增補交錯進行；本輪實作／測試分段見 CHANGELOG.md，沒有逐秒累計，不捏造精確工時。

目前未建立 Git 提交、遠端或標籤，未修改舊 oaClient／Reptool。

## 0.1.1 歷史交付核對

0.1.1 EXE SHA256：B0D887A6303E8D695469BA799F71744C1B0752E82AD968FE87CA4EE9F9475FC5。
DLL SHA256：05D2CA471D465D2D4D69CEAE510E1F7336CACF1922D42D8C1FF5E283886727A5。

瀏覽目錄按鈕已觸發 Shell 開啟，完整地址的檔案總管 UI 讀取遭 Computer Use app approval timed out；不將該項列為完整路徑驗收通過。原始碼使用實際 EXE 的父目錄，不使用工作目錄或固定 Dropbox 路徑。首頁獨立按鈕與伺服器「取消」路徑尚未逐項實測；伺服器「確認」保存與首頁載入已測。

最後文件／交付核對於 13:05 後進行；12:37～13:05 的介面工具與檔案讀取等待不視為程式實作工時。文字檔已檢查 UTF-8、無 Tab／替代字元，Git 未建立提交。

## 0.1.2／0.1.3 最新交付與驗證

- 0.1.2 Release／CTest 1/1、29 項核心檢查通過；主網站 Views、下方 Console、URL 展示／ESC 取消及 zoom 重啟實測完成。使用者實測 Microsoft 注音正常。
- 0.1.2 一次首次主框架載入為1769 ms、HTTP 200，當時啟動套用150%；不是完整冷啟動或速度比較基準。
- 0.1.3 Release／CTest 1/1 通過。EXE 8 張內嵌 PNG 與 assets 原圖逐位元核對一致；交付 root 不含 PNG，檔案總管啟動後 OA 標題圖標與工具列圖示正常。
- Codex 宿主啟動的程序發生 LocalAppData 重導向：data 與 browser-profile 的實體父路徑不一致，清理保護正確拒絕。未放寬目錄校驗；加入 PROFILE_PATH_REJECTED 記錄，改由檔案總管啟動驗證正常。
- 13:44 曾出現設定寫回 Windows error 5；工具讀取當下呈唯讀，後續一般啟動實测110%／100%均成功保存。沒有修改使用者檔案屬性；不宣稱永久唯讀，亦不把工具環境錯誤當成產品驗收。
- 0.1.3 launcher EXE SHA256：A2E8E3AEFABFD3451BE34A80F4A17B057B48091668C4B8633328326AE4D4C207。
- 0.1.3 cef/oaClient2.dll SHA256：1E5CF1F3AC526344DF6FB43B9F52DB99A4C4661654C551253C600094C4A34552。
- 交付根目錄的舊 debug.log 尚保留；保存失敗曾留下 Config.ini.tmp，後續正常保存後已不再存在，未另行匯入暫存設定。當前實際 INI 縮放為100%，圖示驗證後已恢復。

## 0.1.4 最新交付與驗證

- Release／CTest1/1通過，核心53項（含UserSet、空值清除、UTF-8特殊字元、其他設定保留、hcopen規則、登出流程及Windows合成報表兩參數）。
- 約14:26～14:30本機CEF測試：首載在網頁腳本前建立userid／公司別偏好Cookie；cmd=ini寫入，load-userset回呼及$usr回填通過；重啟讀到SYNTHETIC-PERSISTED。均為合成資料，未操作正式登入欄位。
- 合成logout延遲600ms；主程式查狀態、僅發一次logout，收到state0後退出；兩次啟動／關閉事件見artifacts/verification/events.jsonl（不納入Git）。
- 新版列印／注音未重新驗收，Windows網站登入對話框／真正登出、Reptool報表及外部hcopen仍待使用者實測；使用者已表示hcopen由其測試。
- 舊0.1.3退出時再次出現Config.ini寫回error5，確認提示後正常退出；合成本機建置INI保存正常。不據此宣稱正式交付INI權限問題已完全解決，若新版實測仍出現須按實際檔案屬性／權限查明。
- 0.1.4 cef/oaClient2.dll SHA256：C8412C8A83F89B90196B5CA2A6E016FBBC7FD952DE492835E1207C1881B80F3F。launcher未改，SHA256仍為A2E8E3AEFABFD3451BE34A80F4A17B057B48091668C4B8633328326AE4D4C207。
- 未匯入舊個人INI、不保存登入參數／密碼／token；網站舊profile仍清除後才重建INI偏好Cookie。

- 最後0.1.4由檔案總管啟動交付入口並載入正式OA首頁；觀察原交付INI新增def_lang，證明正式頁面的cmd=ini已實際寫回語言偏好，沒有匯入合成userid。舊0.1.3的error5保留為歷史及若再現時的診斷線索；真正登入userid／公司別與登出仍由使用者驗證。

## 0.1.5 關閉保存修正驗證

- 使用者回報0.1.4關閉時Cannot replace Config.ini／Windows error5。當時原檔與tmp的SHA256相同，屬性無readonly；不把未知拒絕原因直接認定為readonly或確定是Dropbox持鎖。
- Save先比較完整輸出bytes，未變不再替換；Windows既有檔優先ReplaceFileW，替換因access／sharing／lock受阻但仍可讀寫時保留原檔寫回、縮短EOF並flush，失敗嘗試還原及保留暫存。未調整使用者屬性／ACL，沒有隱藏真正寫入失敗。
- Release／CTest1/1，62項核心通過。新增禁止delete的reader、變更內容成功保存、檔案identity保留、短內容完整截尾、同內容readonly無須寫入、真正readonly拒寫保留原值等。
- 約15:20～15:24，實際artifacts/windows保存100%→110%，一般視窗關閉成功且Maximized=N；重啟視覺套用110%，恢復100%再從最大化關閉成功、Maximized=Y，兩次未見錯誤提示，最後tmp不存在。未操作登入欄位。
- 0.1.5 DLL SHA256：BD202BFB6C7CECD4FB179FBC2FCF6C33C31FB4B3FD6F50DF46C16A567904C59F。WindowsUserSet、網站資料清理、登出、Reptool與hcopen契約保留；本輪不擴大為其全部重新驗收。

- 2026-10-12使用者在0.1.5關閉修正交付後回覆「可以」，記錄為本次修正可用的確認，不擴大為Reptool、hcopen、列印或Mac驗收。

## 0.1.6 獨立EXE與picture

- 使用者先要求應用檔移出cef，後續明確選擇不使用沙箱（只用來跑ERP）；先前根目錄chrome_elf副本方案已撤銷、未實作。
- CMake改WIN32 EXE、USE_SANDBOX=OFF；wWinMain先用官方CefScopedLibraryLoader載入cef/libcef.dll及驗證版本／API，主程序no_sandbox=1，子程序明確libcef-path。CEF資源及locales從cef載入，保持Views／IME主網站宿主。
- 根EXE包含應用功能、OA圖示、8張PNG及manifest；移除launcher及bootstrap圖示工具。八張RCDATA與assets逐位元相同。交付cef共234個檔案SHA256與SDK相同，無oaClient2.exe／DLL；根目錄也不放chrome_elf.dll。
- 新本機建置目錄windows-x64-standalone；Release／CTest1/1、既有62項核心檢查通過。交付腳本正常清理指定舊應用EXE／DLL，不覆蓋Config.ini／截圖／prg／tpl。
- 實機正常載入OA、最大化、圖示及工具列顯示；子程序命令列確認no-sandbox及libcef-path，主程序libcef／chrome_elf均從cef載入。
- picture保留原Snapshot20261012123501-330.jpg（SHA256一致）；新截圖Snapshot20261012163733-172.jpg為53,779bytes，已開圖核對只含oaClient2視窗。Console開啟並選Console分頁、關閉已核對。
- EXE SHA256：9062525D2414DB87E68CB0D71A044A512B5E0DDD583BF46650946501534340D8。CEF版本不變時一般功能更新只替換根EXE。注音、列印預覽、真登入／登出、報表、hcopen本輪未重新驗收；Mac未開始。

- 0.1.6本輪實機正常關閉，無INI錯誤／tmp殘留；交付Config.ini與原設定SHA256一致。未登入，不能把此次關閉擴大為正式伺服器登出驗收。

- 0.1.6正常關閉後由檔案總管再次啟動，OA首頁與工具列正常；最新版目前已開啟供使用者測試。

## Windows交付資料夾改名

2026-10-12使用者已將artifacts/windows改名為artifacts/oaClient2，方便直接壓縮資料夾。已確認新EXE與cef／picture／prg／tpl／Config.ini存在，舊目錄不存在；package-windows.ps1與現行文件／Mac提示詞改用新位置。歷史測試路徑維持原記錄。本輪只更新打包設定及文件，未重新打包、編譯、啟動、壓縮或修改個人INI；應用版本仍0.1.6。

## 交付prg由使用者維護

2026-10-12使用者已刪除Windows交付prg不需要的檔案，並明確指示「不要再補回來」。核對artifacts/oaClient2/prg只保留docto.exe、Reptool.exe、TSCLIB.dll、zint.dll。package-windows.ps1已移除整份來源prg複製，後續打包不補回、不覆蓋或清理交付prg。根prg保留歷史副本，不能用來自動恢復；新交付目錄的工具由使用者另行準備。

## M01～M03：macOS arm64 首次移植（2026-10-12）

- 使用者確認 Windows 已停止操作且 Dropbox 同步完成；本機 main、無提交／遠端／標籤，接手未找到 conflicted copy 或 Git lock。Dropbox UI 最初逾時，沒有將檔案存在當成同步完成證據。
- 工具／CEF 準備另計：官方套件 SHA1 一致，Xcode -runFirstLaunch 解決 ibtool 外掛初始化後 cefsimple 完成；實作起算 19:28:26，首輪 Release／CTest 完成 19:34:25。其後測試與來源修正交錯，工具首度喚起曾等待約 10 分鐘；未虛構逐秒累計。兩輪合成測試約 20:03:21～20:06:15，與實作分列。
- common/ini.cpp、common/logout.h 及 app.h 完全沿用。app.cpp 只接平台子程序、Console handle／座標、字型及不含值的 browser 生命週期診斷；未複製 INI／UserSet／登出／工具列。新增 Windows cef_platform.cpp 保持原 libcef-path、DIP 轉換、字型及 HWND。Windows platform.cpp、main.cpp、打包腳本／交付未改；Windows 編譯與實機回歸未執行。
- Mac 使用 Cocoa Application／CefAppProtocol、官方 Framework loader／五種 Helper、不使用沙箱。Mac no-startup-window 僅避免 Chromium 自建起始視窗，沒有 disable-web-security 或忽略憑證旗標。
- Console 以獨立 Chrome CefWindow 的 Cocoa NSWindow 做父子視窗定位，主網站仍是 Views BrowserView。實測發現 BrowserHost 的內層 WebContents NSView 不是外層 Window，改取 Views Window handle 後顯示／焦點／1+1=2／F12 關閉正常。含 Console 的主視窗關閉可一併退出。多螢幕、移動／縮小、焦點切換完整回歸未執行。
- Cocoa 結束選單明確 target NSApp，沿用共用登入狀態／logout；主視窗關閉及結束選單均正常退出。早期診斷版本曾殘留 Chromium 新分頁並以 SIGTERM 清理自建測試程序，這不是正常退出通過的證據；最終版本已另行觀察 SHUTDOWN_COMPLETE。
- profile 根層 RunningChromeVersion／SingletonLock／SingletonCookie／SingletonSocket 是 Chromium 建立的連結；只允許移除這四種根層連結本身，不追蹤目標。任意根 profile 連結或子目錄連結仍拒絕；平台測試核對外部檔案保留。
- CTest 1/1、61 項通過，含共用設定／命令／UserSet／logout、Mac metadata／xattr 保留、真正拒寫不改權限與 profile 保護。Windows 專屬測試移至 tests/windows_tests.cpp，原案例保留。
- 實機正式 HTTPS OA 首頁 HTTP 200、最大化、圖示／工具列、URL 預選與 ESC、100%→110% 保存→重啟套用→100%還原、單一視窗 JPG 均已觀察。主框架載入樣本 4401／27120／16564ms，後兩次在重新簽章／診斷期間；不能當穩定啟動基準或宣稱更快。
- 兩輪 localhost CEF 測試：首次腳本前 INI 偏好 Cookie 就緒，cmd=ini／load-userset／$usr／func 成功；重啟讀回合成 userid／公司別及 125% 縮放。第二次頁面確認舊 Cookie、Local Storage、IndexedDB、Cache Storage、Service Worker 消失；INI／picture marker 保留。兩輪 logout 各送一次、延遲約 600ms 完成、收到 state=0 後退出，第二輪有 Console。未操作正式帳密／登入。
- hcopen 的共用協定判斷及 CEF OS 回呼保留；LaunchServices 唯讀查詢本機沒有處理器，未註冊／安裝替代。實際外部程式未執行。Mac LaunchReport 明確回報未實作，不執行 Windows Reptool。
- 交付 bundle 與 build 逐檔相同，八張 PNG 與 assets 相同、Framework 無斷裂連結、codesign --verify --deep --strict 通過。主程式 SHA256：cccec870451e13a8b4afeecb74f5de9d6bbe22679eb58e58a0bfae0a7849b8b8。本機 ad-hoc 簽章；沒有 Developer ID／公證／安裝包。Chromium 曾輸出 ad-hoc validation category 警告，未將其當成正式發行簽署通過。
- 證據在 artifacts/verification/macos-arm64/events.jsonl、website-window.jpg、hashes.json。合成 INI／測試 bundle 留在本機 build 的 verification，不交付給使用者。測試伺服器 PID7559 已停止。
- 列印預覽／PDF 儲存／實體印表機與注音未由 Codex 操作，交由使用者驗收；#3410 的固定發行修補已核對，不等於實機驗收。正式 OA 登入／登出、hcopen 外部程式與 Mac 報表未驗收；U01 線上更新仍未實作。

### M03 交付位置實測追加

- 約20:08:34從artifacts/macos-arm64/oaClient2.app啟動，確認實際程序來自此路徑，獨立Config.ini建立在app旁，不含合成userid；正式OA載入HTTP200、100%縮放。
- 此次首次主框架載入41710ms；與其他樣本差異大，未宣稱啟動更快。初次bundle啟動、簽章、網路／頁面等因素尚未分離，效能基準與原因分析仍待執行。
- 交付版本的網路資訊對話框、Finder完整路徑（artifacts/macos-arm64）已觀察，不將IP／MAC值寫入專案紀錄。20:19成功把JPG寫到交付旁picture，確認位置不在bundle。
- 交付版目前保持正式首頁開啟供使用者列印預覽／注音驗收，測試伺服器已停止。沒有開啟登入欄位或改Windows個人INI。

### M03 注音驗證範圍更正（2026-10-12）

使用者明確確認：注音額外浮動組字窗只屬於 Windows 版本問題，Mac 不需測試或列為待驗收。Mac 一般注音輸入／焦點的驗證仍保留；這是測試範圍更正，不是新增 Mac 驗收結果。本輪只更新文件，未修改程式、重建或執行功能測試。

## M04～M07 本輪結果與 Windows 待辦（2026-10-12）

- M04 實作／建置：Mac GetAppPaths、CEF logs、PictureDirectory 及單 .app 打包。/Applications 首次啟動在 Application Support 建立 Config.ini／logs／profile／lock；110% 保存，Snapshot20261012210849-570.jpg 只含本窗口。關閉後重啟清除專用合成 marker，INI 與 picture 雜湊保持、log 追加，舊 app 旁 INI／picture 保留。63 項平台／共用檢查通過。
- M05 實作：共用 welcome.h 直接內嵌單一 HTML／原 OA logo，app.cpp 顯示 data URI 並沿用原 URL 對話框；Mac 入口啟用空白 HomeUrl，共用 INI 不存本機頁 URL。五項 Mac 空白／手動網址回歸新增，Release／CTest1/1、68 checks／0 failures；Windows 預設尚未改，核心仍驗證原 Windows 預設。
- M05 實機：首次 INI HomeUrl 空白、歡迎頁按鈕／工具列帶空白網址、ESC 不寫 URL；確認合成 localhost 後保存且 HTTP200，正常關閉再啟動直接載入設定網址。測試 URL 最後清空，不帶入交付或留給使用者；INI 備份保留在 Mac 專用資料根。
- M06 實作／建置／實測：CEF 固定 14c5a08 的 cef_types.h 及本機 SDK 均有 chrome_zoom_bubble；共用旗標預設 false、只由 Mac 入口設 true。最後版本歡迎頁 110%→125%→110% 與測試網站放大／縮小均未顯示彈窗；比例立即寫入 INI，重啟紀錄確認 110%。測後回復本輪測試前的 250% 偏好，HomeUrl 保持空白。參考 [固定版 API](https://github.com/chromiumembedded/cef/blob/14c5a08/include/internal/cef_types.h)。
- M07 實作／實測：使用者及工具均曾看到額外 Chromium 新分頁。Mac OnAlreadyRunningAppRelaunch 返回已處理並顯示既有主窗；歡迎頁按鈕離開 Console 回呼後才開 native modal，Cocoa ESC／X 採 stopModalWithCode 正常取消。修正前本輪 PID10729 正常結束失敗，僅停止該已核對的自建程序；不將它記成正常退出。修正後測試網站與歡迎頁兩輪正常 CLOSE_LOGOUT_NOT_REQUIRED→BROWSER_CLOSED→SHUTDOWN_COMPLETE，重新啟動及 Applications Finder 再次開啟保持含工具列的 oaClient2。CEF singleton relaunch 回呼未直接觸發，不能將一般 Finder 再開啟當成該分支已測。參考 [固定版 relaunch 契約](https://github.com/chromiumembedded/cef/blob/14c5a08/include/cef_browser_process_handler.h)。
- 最終交付與安裝均為本輪 native arm64 .app，SHA256（主執行檔）：f7eccbcd7f6737fd7ffb861fb7a877948fcc8676bd151d390c036ae7ca894a24；codesign deep／strict 通過，八張 PNG 與 assets 原圖逐位元一致。截圖與合成結果在 artifacts/verification/macos-m04-m07/welcome.jpg／results.json，不含個人 INI 或登入資料。
- 最終程序正常關閉；臨時 127.0.0.1:8766 伺服器已停止。新的組態／圖片在 Application Support，舊交付個人資料未刪除；Windows artifacts/oaClient2／INI／prg 未改。macOS 實作、編譯、實機結果與使用者驗收分開，沒有虛構逐秒工時或完成百分比。
- W21 相同歡迎頁與 W22 隱藏縮放彈窗均為使用者已確認、待 Windows 環境實作／MSVC 建置／實機驗證；Windows 專屬來源在最新分工要求後未再修改。共用來源修改的 Windows 回歸仍待執行。列印預覽／一般注音、正式 OA 登入登出、hcopen 外部程式仍依 M03 狀態；Mac 不測 Windows 注音浮窗，Mac 報表／U01 未實作。Git main 無提交／遠端／標籤。

## M09：重新編譯，只交付不安裝（2026-10-12）

- 使用者要求 Mac 重新編譯，並明確指定「編譯好不要幫我安裝」。本輪沒有修改程式碼，沒有寫入 Applications、沒有啟動主程式或更改現用組態。
- 開始核對時本機 SDK／build 及 Mac 交付 app 均已不存在；重新取得固定官方 CEF 154.0.34+g14c5a08+chromium-154.0.8037.98 macosarm64 standard。307,056,359 bytes、SHA1 b7e1bc1c719f1b8907b0398d8666339471a316c8、SHA256 2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe，均與原紀錄一致。SDK／全新建置仍在 Mac 本機 Library/Caches/oaClient2/deps／build/macos-arm64。
- 已完整 Release 建置，實際編譯 227 個 C++／ObjC++ 物件（含共用 app.cpp／ini.cpp、Mac 入口及 CEF wrapper）；CTest1/1、68 checks／0 failures。build-macos.sh／package-macos.sh shell 語法及建置／交付 codesign deep／strict 通過。
- 交付 artifacts/macos-arm64/oaClient2.app 與剛建置 bundle 的 265 份檔案／連結一致，10 份 Mach-O 均為 arm64，包含 Framework／五種 Helper，無斷裂連結，PNG 與 assets 原圖一致。主執行檔 SHA256：f7eccbcd7f6737fd7ffb861fb7a877948fcc8676bd151d390c036ae7ca894a24。重編譯後 SHA 與前次相同是檔案內容一致，實際完整編譯由 build.log 證明。
- 交付沒有補回舊 INI／picture，清除 Finder 自動重生的 .DS_Store；驗證時交付只含 .app。來源、Windows 整份交付、Mac 現用設定／截圖及 Applications 既有程式狀態與建置前雜湊一致。Windows 未編譯，W21／W22 及既有共用修改回歸待執行。
- 此輪準備／建置／驗證紀錄時間為 2026-10-12T22:04:44.822451+08:00 至 2026-10-12T22:10:04.711742+08:00（Asia/Taipei），沒有新增功能實作工時。結果與完整編譯紀錄存 artifacts/verification/macos-m09/results.json／build.log／package.log。主程式實機、列印預覽與輸入測試本輪未執行，不擴大前輪驗收。版本仍0.1.6，Git main 未提交／推送／建立遠端或標籤。

## M10：新的背景關閉契約與最後結果

- 使用者確認是 logout，先隱藏、收到登出回應立即退出，否則最多3秒。common/logout.h 新增可選 BackgroundGrace 模式，保留 Windows 預設 PollForState；背景模式立即送出一次、重複關閉不重送／不延長期限，使用 steady_clock。app.cpp 接回原關閉入口，CEF 延遲任務與既有 loginState 回報；Mac 入口啟用，沒有複製共用關閉邏輯或修改 Windows 專屬碼。
- Mac 主視窗與 Console 都立即 Hide，背景期不因 relaunch 顯示主窗；晚建立的 Console／瀏覽器不延長完成關閉。收到 loginState=0 時不等下一次輪詢，立即結束；無回應使用3000ms任務。完成時關閉全部本程式瀏覽器，仍由 CefShutdown 正常清理，不使用強制終止程序作為產品關閉流程。
- 初輪合成 ACK／無回應測試通過；加入有效使用者互動的 beforeunload 後曾發現離開頁面提示阻擋退出，該輪明確失敗並手動離開。另啟動的冗餘單例測試已停止；不把它當成成功退出。修正 OnBeforeUnloadDialog 後，僅背景關閉期間自動允許離開，其他模式維持原行為。
- 最終 Release／CTest1/1、75 checks／0 failures。最後兩輪真實 CEF localhost：紅色關閉按鈕 ACK 951ms；原生結束選單、Console 開啟且沒有登出回應3029ms。兩輪主窗／Console 隱藏、logout 各一次、已觸發的 beforeunload 無提示阻擋、全部 Browser 關閉及 SHUTDOWN_COMPLETE 均核對，程序 exit0。測試頁設定600ms回應，但背景計時實際會延後，因此記錄實測951ms，不宣稱固定600ms。
- 核對 Windows 專屬來源／整份交付、Applications 既有主程式、現用 INI／picture 雜湊不變；沒有保存 localhost URL、登入 token 或測試偏好。臨時伺服器與最後測試程序均已停止。個人 INI 包含最大化狀態仍逐位元一致，不需回寫測試備份。
- 最後交付 artifacts/macos-arm64/oaClient2.app 與建置 bundle 一致，native arm64、codesign deep／strict 通過；主執行檔 SHA256：27355abf79bf5a440fd2940d4e2d6ab1aa9213dc4b4e9447b451961c053ee75d。未安裝，版本仍0.1.6。證據 artifacts/verification/macos-m10/results.json／application.log／events.jsonl／build.log。
- 正式 OA 登出、列印／一般注音本輪未驗收；三秒上限到期只表示結束客戶端，不代表伺服器收到／完成登出。晚建立瀏覽器／Console 的保護已實作，特定競態未獨立重現。Windows W23 未實作／未建置／未實測，共用來源 Windows 回歸待執行；W21／W22 及 U01 狀態不變。Git 未提交／推送／建立遠端或標籤。


## M11／W24：瀏覽設定目錄（2026-10-13）

- 使用者重新定義 Mac 與 Windows 的「瀏覽目錄」為實際 Config.ini 所在目錄；共用 app.cpp 只改目標為 paths.config.parent_path() 及提示文字，不加入平台分支、不更改 INI／UserSet／截圖或其他工具列流程。Windows 專屬來源及交付未改，W24 待 Windows 編譯／實機回歸。
- 首次建置因本機 CEF SDK 已不存在而在 CMake 配置失敗；重新下載相同官方154.0.34 arm64套件，大小307056359、SHA1與SHA256均與 ENVIRONMENT 固定值一致，未升級。使用者追加要求：編譯後保留本機 SDK；本輪保留解壓 SDK、下載壓縮檔及 build，後續不自動清除。
- 實作為 app.cpp 三行差異；環境準備、編譯與實機測試另列，不編造累計工時。最終 Release／CTest1/1、75 checks／0 failures、arm64與codesign deep／strict通過。
- 從本機 build 啟動，--url=只在當次記憶體顯示歡迎頁。點「瀏覽目錄」後 Finder 顯示完整 Application Support/oaClient2 路徑及 Config.ini，按鈕的可存取名稱為「瀏覽 Config.ini 所在目錄」。測試 App 正常關閉，3027ms背景期限後 SHUTDOWN_COMPLETE，程序exit0。沒有操作正式登入、列印或注音。
- 交付 .app 與 build 逐檔／連結一致；主執行檔 SHA256：6c8994441d509d97c5597ec3a7f47938f8a54dac26ec2da058c4fe508da78f12。沒有安裝 Applications；254份受保護 Windows 專屬來源／交付、Applications 既有主程式及 Mac 現用 INI／picture 雜湊不變。清除交付旁 Finder 重生的 .DS_Store，交付仍只含 .app。證據在 artifacts/verification/macos-m11/results.json／application.log／build.log／package.log。
- 已更新協作、平台路徑、兩平台操作、Windows 接續提示詞與共用規則；Windows W21～W24／其他共用回歸待執行，正式 OA 登出／列印／一般注音仍待使用者驗收，U01線上更新仍未實作。Git未提交／推送／建立遠端或標籤。


## M12／W25：網頁軟體名稱與版本標題（2026-10-13）

- 依使用者圖片要求加入「[用戶端版本 …]」，並依追加澄清移除固定良穎名稱。未取得網頁名稱時顯示oaClient2，載入後直接從document.title取得；沿用舊crmTitleChange與OA doSetTitle，網站資訊／getDBCaption流程未改。
- 實作只改共用app.cpp的主視窗建立及OnTitleChange，歡迎頁不覆蓋預設名稱；維持原彈出視窗與Console流程，INI／UserSet／網頁client_version回傳契約不改。Windows專屬碼未改，W25待Windows建置／實機回歸。
- 最終Release／CTest1/1、75 checks／0 failures、native arm64及codesign deep strict通過。直接沿用既有本機SDK與build增量編譯，SDK／下載壓縮檔／build保留。
- 初次測試啟動被使用者已開啟的交付App單例鎖阻擋，桌面讀取兩次逾時；該待啟動程序已取消exit130，不列為通過。正常關閉原交付App後，最終歡迎頁標題「oaClient2 [用戶端版本 0.1.6]」已觀察並正常退出exit0。
- 從本機build以當次--url載入公開OA，HTTP200，實際標題為「良穎資訊系統 [用戶端版本 0.1.6]」。使用者接著在App切換網站，標題變成「炬塔資訊系統 [用戶端版本 0.1.6]」，證明不是固定公司名稱。沒有修改OA來源或由Codex操作登入；使用者目前操作中的測試視窗保留開啟，不把本輪稱為完整登入／關閉驗收。
- 交付已更新、未安裝，SHA256：50844de4a8455e943f6e34d725c8f8eae9fa94a21e41696b1514179dc2cb9a7f，build／交付逐檔及連結一致。Windows來源／整份交付、Applications既有主程式及Mac picture雜湊不變；現用Config.ini在使用者操作期間變更，保留使用者當前內容，不回寫／撤回。證據artifacts/verification/macos-m12/results.json／build.log／package.log／core-tests.log／application.log，不收錄個人INI。
- 協作、計畫、進度、交接、Mac操作、相容契約、共用規則與Windows提示詞已同步。Windows W21～W25未因此完成，列印／一般注音及正式OA登入登出仍待使用者驗收，U01仍未實作。未提交／推送／建立遠端／標籤；Intel支援仍只討論，未修改arm64限制。


## W25：Windows 相同標題需求確認（2026-10-13）

使用者明確要求 Windows 標題列與 Mac 相同：軟體名稱從 URL 頁面的 document.title 取得，顯示「網頁軟體名稱 [用戶端版本 0.1.6]」；尚未取得名稱時顯示「oaClient2 [用戶端版本 0.1.6]」。共用 M12 實作已備妥，Windows 編譯／實機測試及交付更新留到 Windows 環境。本輪只補記需求與交接，未修改程式或交付、未編譯／測試／安裝，不將 Mac 結果當成 Windows 驗證。


## D03：首次本機提交（2026-10-13）

使用者明確指示 commit，授權建立 main 的首次本機來源提交。提交共用及 Windows／macOS arm64來源、原圖資源、共用設定範例、腳本、測試與工作文件；不納入 artifacts、prg、個人Config.ini、CEF SDK／壓縮檔、建置、profile或快取。Git身分使用既有本機設定，實際SHA以git log取得，未建立遠端／標籤或推送。

本輪僅提交與同步Git交接狀態，沒有修改功能、重新編譯／安裝／操作App；既有Mac75項測試結果與Windows W21～W25待回歸狀態保留。歷史無提交記錄不全面改寫。


## M13／W26：工具列間距與完整文字（2026-10-13）

- 使用者要求新版右下角間距同舊版，並追加不能隱藏字樣。唯讀核對舊DFM各SpeedButton尺寸，採原23／23／40／67／38／61／23／23 DIP，共用app.cpp固定尺寸與偏好尺寸一致，不改字型／圖示／順序／工具功能、INI格式或平台來源。
- 首輪Release及75項通過，但實機MAC與還原比例顯示省略號，該UI結果失敗。核對固定CEF154的CefView.SetInsets後，將右側按鈕左右留白各減為2 DIP；保留左Console原配置，不用縮字或取消文字。
- 最終增量Release／CTest1/1、75 checks／0 failures，Mac真實畫面確認完整MAC／瀏覽目錄／截圖／還原比例，八個右側工具仍可見，合計298 DIP。視覺結果已核對，使用者最終間距驗收仍待確認；首輪測試程序正常exit0，最後build視窗保留開啟。測試--url=只在當次記憶體顯示歡迎頁。
- 交付artifacts/macos-arm64/oaClient2.app與build逐檔及連結一致，arm64及codesign deep strict通過，SHA256：9bc544d13be3e6b0474d3921ced2a7f510728731b778f8f739ec7f2f2c812258；未安裝，SDK／壓縮檔／build保留。驗證紀錄在artifacts/verification/macos-m13/results.json／build.log／package.log／core-tests.log／application.log。
- Windows專屬來源／整份交付、Applications既有主程式與Mac picture雜湊不變；現用Config.ini在實機期間雜湊變更，原關閉／視窗保存流程未改，保留現值，不回寫測前資料、不宣稱設定檔逐位元不變。本輪沒有修改設定保存來源或由Codex輸入新網址。
- 更新協作、計畫、進度、交接、Mac操作、共用規則及Windows提示詞；W26為共用修改的Windows編譯／實機回歸待辦。W21～W25、正式OA登入登出／列印／一般注音與U01狀態保留；Git HEAD ddf1bf9，本輪未提交／推送。


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


## W21～W26：Windows 接線、建置與實機回歸（2026-10-13）

- 接手：使用者確認Mac已停止編輯／建置／Git且Dropbox同步完成。main與遠端同為59a323a38d8e64122522882b0cb06649c1729e0d，來源乾淨，沒有lock、未合併來源或衝突副本；v0.1.6 annotated Tag的來源仍是0fe6f357173fb7802cca8504c2ea007dd5e7834d。初次受限網路DNS查詢失敗，唯讀提升查詢後核對成功。
- 實作：src/platform/windows/main.cpp僅新增五行設定／註解，啟用home_url.clear、allow_empty_home_url、hide_zoom_bubble與background_logout_close；config/Config.example.ini改空白HomeUrl。src/common與src/app沒有新增副本或重寫，Windows直接編譯Mac接續後的同一份共用來源；Mac專屬來源與交付未修改。tests/windows_tests.cpp增加五項Windows啟動INI政策檢查，background-close.html增加動態標題按鈕供真實OnTitleChange測試。
- 建置：沿用固定MSVC、SDK與CEF154.0.34，本機windows-x64-standalone增量Release成功，CTest1/1；74 checks／0 failures。包括共用BackgroundGrace重複關閉不重送／不重設期限、Windows INI metadata／拒寫及Reptool合成兩參數／中文／引號／工作目錄案例。ATL／Doxygen及不需要的DELAYLOAD警告不影響成功結果，未升級CEF。
- W21：缺少INI建立空白HomeUrl由核心案例驗證；UI使用隔離空白INI，歡迎頁／原圖、正確預設版本標題、歡迎按鈕／工具列入口、ESC取消與無效ftp拒絕均實測。取消／拒絕後INI與範例SHA256相同；有效HTTP localhost確認後才保存，重啟直接載入。歡迎data URL未存INI。首輪啟動曾依既有相容流程遷移舊本機INI到測試EXE旁，之後改用合成設定，沒有更動正式個人網址。
- W22：網站100%→110%→100%，再110%關閉重啟確認ZOOM_APPLIED percent=110，還原按鈕保存100%；畫面無Chromium縮放彈窗。09:48～09:49另以一般桌面環境補測歡迎頁100%→110%→100%，亦無彈窗且HomeUrl仍空白；網址對話框X取消後INI雜湊不變。其他DPI／多螢幕未執行，不能用Mac測試替代。
- W23：合成ACK649ms（Codex啟動環境）及一般桌面ACK1117ms；無回應3007ms觸發三秒任務。兩個含Console案例均記CLOSE_WINDOWS_HIDDEN main=1 console=1，logout各一次、實際點擊啟用beforeunload後記UNLOAD_ALLOWED、兩個Browser全部關閉及SHUTDOWN_COMPLETE；CIM核對全部oaClient2程序消失。3007ms包含CEF任務排程誤差，不表示伺服器已登出。晚建立窗口的特定競態與一般彈出窗口本輪未獨立重現，原共用保護／彈出流程保留。
- W24：按鈕的可存取名稱為「瀏覽 Config.ini 所在目錄」，實際Explorer Shell目錄與測試EXE旁Config.ini父目錄一致；正式交付也開啟artifacts/oaClient2，沒有改用Mac路徑。W25：歡迎標題oaClient2、公開OA標題良穎資訊系統、頁面按鈕改document.title後立即變「動態軟體名稱 [用戶端版本 0.1.6]」。W26：右側23／23／40／67／38／61／23／23 DIP與各側2 DIP保留，Windows真實畫面完整顯示MAC／瀏覽目錄／截圖／還原比例及原圖示，未縮字或藏字。
- 共用回歸：兩輪原legacy-contract.html真實CEF，首載Cookie在網頁腳本前就緒，cmd=ini／load-userset原func／$usr、合成userid／公司別保存通過；第二次boot-SYNTHETIC-PERSISTED、preferences-pass及site-data-clean。上輪Cookie／Local Storage／IndexedDB／Service Worker／Cache Storage由程式啟動清理消失，INI偏好保留；合成報表由74項核心測試驗證，正式Reptool報表未測。
- 環境失敗另列：從Codex封裝宿主重啟曾兩次因LocalAppData root／profile實體不同而PROFILE_PATH_REJECTED，不算成功、不放寬校驗。Computer Use檔案總管狀態授權曾逾時；改由既有Explorer程序的Shell啟動建置實體路徑後成功，並經該Shell讀取一般桌面application.log；兩種環境紀錄分別保存。Console輸入嘗試未產生可核對的結果，不將1+1列為通過；Console開啟／Console分頁及含Console退出已通過。
- 交付：只更新artifacts/oaClient2/oaClient2.exe與安全設定範例，EXE和build一致，SHA256 9b60d756ee39ca6dc3725e4e608f3d63ac18f1602b69c9bf43c53d32fc7daed2。CEF234份與build逐檔SHA256一致，沒有更新CEF／補回prg／增加外部PNG；正式交付已啟動OA、核對目錄並正常退出。Mac產物、prg／picture／tpl等275份受保護檔案不變；正式INI在最後正常關閉經既有Window保存流程後雜湊改變，保留現況，不回寫測前設定、不聲稱INI逐位元不變。測試INI還原為首輪遷移內容，兩個本輪localhost伺服器及全部oaClient2程序已停止。
- 證據：artifacts/verification/windows-w21-w26的build.log、core-tests.log、background-events.jsonl、legacy-events.jsonl、application.log（一般桌面）、application-packaged.log、dynamic-title.png、welcome-zoom.png、legacy-first.png／legacy-restart.png、delivery.png及目錄／保護雜湊JSON；不含個人INI或登入參數，驗證目錄不納入Git。
- 時間：本輪開始接線09:13:47，入口／範例／測試第一批完成約09:14:13，建置約09:14～09:15；UI測試約09:16起，合成動態標題測試素材約09:22增補，屬測試後實作另列。UI工具等待與平台映射定位另計，不編造精確累計或把整段等待算成實作。SDK／壓縮檔／build全部保留。
- 使用者驗收：本輪未驗收列印預覽／Microsoft注音／正式OA登入登出／Reptool／hcopen／最終工具列間距。舊0.1.2注音浮窗確認保留為歷史，未擴大成此交付新驗收；U01線上更新仍未實作。沒有本輪Git提交／推送／Tag操作／公開Release發布，R02後續依授權接續。

- 最後補測09:48～09:49：歡迎頁110%／100%無縮放彈窗，X取消INI不變；歡迎頁沒有logout函式時3014ms期限正常退出、全部程序停止。本機測試INI再次還原，正式INI未被此輪補測改寫。最後原始碼／文件靜態核對另列，未重新執行Mac編譯。
- 09:52～09:53靜態核對：16份本輪追蹤檔案嚴格UTF-8／LF、無Tab／替代字元、文件相對連結及git diff --check通過；共用實作未變。275份其他受保護檔案與原SHA256一致，正式INI的預期視窗保存變化另列；EXE雜湊仍與建置一致。final-runtime.json確認AppProcesses=0／TestServers=0、SDK與build仍存在，來源差異另存source-changes.patch，不納入Git。


## W27：隱藏滑鼠移到選單時的左下角JavaScript提示（2026-10-13）

- 使用者圖片中的javascript:void(0)是Chrome連結狀態泡泡。核對固定CEF154 SDK的chrome_status_bubble官方欄位，在唯一共用src/app/app.cpp的CreateMainWindow新增STATE_DISABLED與英文日期註解，共兩行；未修改OA HTML／JavaScript或另寫平台選單。
- 約09:59:16核對SDK，09:59:50實作完成；09:59～10:00 Windows MSVC增量Release成功、CTest1/1通過（既有74項套件），沒有新增僅鏡像設定的測試。10:01～10:03真實CEF localhost合成選單／子選單：滑鼠停留在javascript:void(0)連結時左下角無提示，menu-action／submenu-action事件及畫面PASS確認JavaScript動作仍正常。建置與UI測試分開記錄，未擴大其他功能驗收。
- 正常關閉使用者當時開啟的舊交付版後，只替換artifacts/oaClient2/oaClient2.exe；SHA256 e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c，與build一致，仍為0.1.6。INI／picture／prg／CEF配置不變；合成URL僅--url當次記憶體覆寫，未保存。INI的既有關閉Window保存流程保留，不回寫使用者目前偏好。
- 275份Mac專屬來源／產物、使用者精簡prg／picture／tpl與測前SHA256一致；沒有修改Mac專屬碼、重編Mac或更新Mac.app。共用設定已準備，Mac要在macOS重新編譯及實測後才會有新行為；本輪Windows結果不當成Mac已完成。
- 本輪localhost伺服器已停止，合成頁完全正常退出；原OA網址已從更新後正式EXE重開供使用者確認實際選單。SDK／壓縮檔／build保留；未提交／推送／移Tag／發布Release，U01仍未實作，列印／注音及正式OA驗收不擴大。
- 證據在artifacts/verification/windows-w27/build.log、events.jsonl、status-disabled.png、application.log與protected-results.json／results.json；只含本機合成頁與階段紀錄，不收錄個人INI或登入參數。

## D03／R02：使用者授權先提交推送、再打包發布（2026-10-13）

使用者已明確授權打包／發布，並指定先commit、push。先提交W21～W27來源、共用安全範例、測試及本輪文件；不納入個人INI、artifacts、prg或CEF SDK。W27合成選單素材另保留同內容的tests/pages/status-hint.html供Mac接續，與已實測素材SHA256一致，沒有重新修改功能。main／遠端提交前皆為59a323a，v0.1.6仍固定0fe6f35；推送完成與ZIP發布結果另行追加，不移Tag、不動Mac資產。


## D03／R02：Windows x64公開發布結果（2026-10-13）

- W21～W27已提交7958a60fc75a35d4387a028ab8ccfb73e98200c0；Windows首次HTTPS push因尚未登入失敗，使用者自行完成Git Credential Manager device授權後推送成功，遠端SHA一致。本機origin/main更新一度失敗，fetch已恢復；沒有force或移Tag。
- 既有v0.1.6初版測試Release新增Windows ZIP與.sha256，來源7958a60，EXE仍0.1.6／x64，SHA256 e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c。ZIP 189879293 bytes，SHA256 4d765e6d5748ce3d5768dd6ef5ed431d27dbcb13f07647f4aa71cc480ec0feb2，內容為EXE＋安全範例＋CEF234檔＋現有prg4檔，共240檔。
- scripts/create-windows-release.py以安全清單打包及全部SHA256／CRC核對，不讀根prg、不改交付，排除個人INI／picture／logs／profile／cache／tpl／SDK／build。GitHub大小／digest與無登入公開重新下載ZIP及校驗檔皆一致，公開ZIP CRC通過。
- Mac既有兩資產ID／大小／digest及v0.1.6來源0fe6f35未變；本機Mac專屬來源／產物及prg／picture／tpl共275份雜湊不變，SDK／壓縮檔／build保留。原OA視窗保留供使用者操作，本輪沒有再改設定或建置App。
- 證據artifacts/verification/releases-windows-v0.1.6/results.json／package.json／release-public.json，下載／校驗與重現流程見[RELEASES](docs/RELEASES.md)。發布紀錄及腳本另行提交推送，最新main以Git核對；個人資料和產物不納入Git。
- 實作／編譯／合成實機結果仍依W21～W27；本輪發布不增加功能驗收。列印／Microsoft注音／正式OA登入登出／Reptool／hcopen／最終間距待使用者；其他DPI及延遲Console／popup競態未獨立重現，Mac W27未重編／實測，U01未實作。


## W28：登入時不跳儲存密碼提示（2026-10-13）

- 接手main／origin/main為80402ed，乾淨且無Git lock；沿用使用者已確認的Mac停止操作／Dropbox同步交接，未動Mac平台碼或產物。
- 使用者圖片及舊交付視窗重現Chromium密碼提示。共用App::OnContextInitialized先以CEF SetPreference停用credentials_enable_service及credentials_enable_autosignin，再建立client／回填偏好Cookie／主視窗；兩項成功才記錄PASSWORD_SAVING_AND_AUTO_SIGNIN_DISABLED，失敗回報並結束message loop。不改網站JS／UserSet／INI／password或token保存流程，不加入安全停用參數。
- Windows增量MSVC Release成功，CTest1/1、74 checks／0 failures。相同localhost合成表單在舊e56d3d32版本會顯示儲存提示；修正版原生POST→303結果頁無提示。重啟後AJAX POST→204／移除表單亦無提示，兩次啟動紀錄確認政策在頁面建立前套用，表單仍正常送出。未使用正式帳密，伺服器丟棄表單值，只記錄route／時間；可共用素材tests/pages/password-save.html與tests/serve-password-save.py，後者GET／303／204核對通過。
- 第一個測試server在沙箱內使正常CEF連線逾時，改由已授權的localhost程序啟動後成功；一次座標未命中及一次geometry unavailable未列為通過，重新觀察後確認POST事件及結果頁。CTest文字紀錄含Windows本機編碼，74項結果以ASCII bytes核對，未用有替代字元的解碼覆寫來源。
- 正常關閉舊版後僅更新artifacts/oaClient2/oaClient2.exe，與build相同，SHA256 fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474，版本仍0.1.6 x64。INI既有關閉Window保存保留，測試URL只在記憶體覆寫、未存INI；275份Mac專屬來源／產物與prg／picture／tpl雜湊不變，未補回工具，SDK／壓縮檔／build保留。
- 合成App正常退出，server停止；修正版原OA已重開供使用者自行登入驗收，不把合成成功當作正式OA驗收。證據artifacts/verification/windows-w28/results.json／build.log／application.log／baseline.txt／native-disabled.txt／ajax-disabled.txt／events.jsonl，不含正式帳密或個人INI。
- 本輪未提交／推送／移Tag／重新發布；既有v0.1.6 Windows公開ZIP仍是W27的e56d3d32，尚無W28修正。Mac W27／W28未重編或實測；列印／注音及其他待驗收、U01未實作保持。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## R02／W28：維持0.1.6重新打包上傳結果（2026-10-13）

- 依使用者明確授權不進版，先提交／推送W28來源c5cd54939caf34d14bd7395fb4f7073b6a134e3c，再打包既有已測EXE；沒有重新編譯或改版本。main／遠端SHA已核對，origin/main快取替換一度失敗，核對舊SHA後僅以Git刪除／重建該追蹤ref，已恢復一致；本機main、遠端及Tag歷史未變。
- 新ZIP 189879887 bytes，SHA256 92c371f3560daab3c23de117bb62d11b893be72530b045dbb5b20b8603e24099；EXE fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474。以既有安全清單打包240檔：EXE／安全範例／CEF234／現用prg4，CRC及全部SHA256通過，不含個人Config.ini／網站資料／picture／logs／tpl／SDK／build，不補回根prg。
- 先上傳暫名資產並核對GitHub大小／digest，兩檔完整才替換指定同名Windows ZIP／.sha256；新版資產ID635859578／635860492，Release仍411036061／v0.1.6初版測試。原公開URL無登入重新下載兩檔與本機逐位元一致，新ZIP CRC與240檔SHA256再次通過，Release明列實際來源c5cd549及同版替換。
- Mac兩資產ID／大小／digest及固定Tag物件67e29679／來源0fe6f35不變；Mac專屬來源／產物與prg／picture／tpl275份雜湊不變，原OA保持，SDK／壓縮檔／build保留。舊Windows ZIP／校驗檔仍存前輪public-download作歷史證據，本機artifacts/releases同名檔已更新為W28。
- 證據artifacts/verification/releases-windows-w28/results.json／package.json／release-before.json／release-public.json；同步Release／進度／交接／計畫／操作與README，結果文件另行提交推送，最新main以Git核對。公開上傳未增加正式OA／列印／Microsoft注音／Reptool／hcopen／間距驗收；Mac W27／W28回歸未執行，U01未實作。

## W29：Chrome衝突熱鍵交回網頁（2026-10-13）

使用者要求取消oaClient2內建Chrome的F1／F2／F3／F4／F9、Alt+W、Mod+F、Shift+F、Mod+E／S／N（Mod=Ctrl或Cmd，包含Ctrl+N），不是移除網頁自己的設定。共用common/keyboard.h精確匹配，app.cpp改為網頁優先接收一般加速鍵，OnPreKeyEvent不吞掉事件、OnKeyEvent在網頁處理後攔下指定Chrome預設動作；原F8／F12／Ctrl+P高優先功能及工具列保持。

Windows MSVC Release／CTest1/1、110 checks／0 failures（原74＋36項政策檢查）通過，包含Ctrl／Cmd正向及未列出的組合。共用合成頁tests/pages/keyboard-shortcuts.html已載入。使用者隨後要求「你編譯好，我測試」，因此未繼續逐項實機熱鍵矩陣，Chrome搜尋／儲存／新視窗及真實網頁按鍵接收均待使用者驗收，不宣稱UI熱鍵已通過；Cmd實機亦須在Mac回歸。

本機交付EXE已更新、與build一致，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，版本仍0.1.6 x64。合成server／App已停止，原OA已重開供使用者測試；測試URL只在當次記憶體，未保存INI。使用者新增的f1.js清單保留、不執行／修改／納入Git，Mac專屬碼／產物及prg不改，SDK／build保留。此次未提交／推送／移Tag／重新發布，GitHub ZIP仍為W28；Mac W27～W29需回macOS重編／實測，U01未實作。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## W29／R02：使用者驗收與同版發布結果（2026-10-13）

- 使用者回覆「可以了」，W29 Windows Chrome衝突熱鍵依本次回報驗收通過；不把代理未執行的逐項UI矩陣補記為已測，也不擴大Mac Cmd／列印／注音／其他功能驗收。
- W29來源6f2833b7f7789509abb8f4b60d9b3ea0e0daa01f已透過HTTPS推送，與遠端一致；打包沿用已編譯／110項及使用者測試EXE，不重建或進版。新ZIP 189880195 bytes，SHA256 849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046，EXE b5a5d19b。
- 240檔安全清單只含EXE、安全範例、CEF234與現用prg4，不含個人INI／網站資料／picture／logs／tpl／SDK／build，不補回根prg。先上傳暫名兩檔並核對digest，再替換指定Windows原名資產；新ID635910442／635911490，Release保持411036061／v0.1.6。
- 原公開URL無登入重新下載ZIP／校驗檔均與本機／GitHub大小及SHA256一致，公開ZIP CRC／全部240檔SHA256通過。Mac兩資產ID／大小／digest與Tag物件67e29679／來源0fe6f35不變，275份本機保護檔案一致。
- 本機artifacts/releases同名檔更新，歷史W28打包與public-download保留；新證據artifacts/verification/releases-windows-w29/results.json／package.json／release-public.json。原OA及SDK／build保留，f1.js接手時已不存在、未補回，不將其當成來源衝突。
- 發布文件／README與操作／工作紀錄已同步，結果文件另行提交推送；Mac W27～W29未編譯／實測，其他待驗收與U01未實作保持。

## D04：Mac接續Windows今日功能提示詞（2026-10-13）

依使用者要求將Mac接續提示寫成.md，新增[MAC-WINDOWS-2026-10-13-PROMPT.md](docs/MAC-WINDOWS-2026-10-13-PROMPT.md)。基準main／已推送cb68ba2、Windows實際W29來源6f2833b；核心範圍W27連結狀態提示、W28密碼保存政策及W29 Chrome衝突熱鍵（包含Mac Cmd）。Mac已完成M01～M13，不重做平台移植，W21～W26只作既有共用功能回歸；版本維持0.1.6、共用來源唯一、平台路徑／SDK隔離／交付與未驗收範圍明列。

原MAC-CODEX-PROMPT.md新增最新提示入口並保留首次移植歷史，README／交接入口同步。提示詞包含Windows停止操作／Dropbox同步、Git差異核對、Mac固定CEF／Release／核心測試／簽章／實機、保留SDK及個人設定、先更新交付不自動安裝／發布，以及不把Windows熱鍵驗收當成Mac Cmd已通過。

本輪只建立／更新文件，沒有修改程式、建置／操作App、更新SDK或產物、提交／推送／移Tag／發布。文件UTF-8／LF與相對連結核對；Mac W27～W29仍待目標平台編譯／實測，其他未驗收及U01未實作保持。切換Mac前仍須停止Windows編輯／建置／Git，等待兩台Dropbox同步；未提交文件須辨識保留。

## M14～M17：Mac 接續 W27～W29 與交付（2026-10-13）

- 接手：使用者確認Windows停止編輯／建置／Git、兩台Dropbox同步完成。本機main與唯讀ls-remote均為cb68ba20a7c1862cd58f851c3a3c1940cf555a05，origin正確；Tag物件67e29679／來源0fe6f35不變。沒有conflicted copy／Git lock。六份未提交文件及新Mac提示詞已辨識為D04工作，保留，不reset／checkout。最初受限DNS查詢失敗，唯讀提升後成功，不當成來源不一致。
- 來源：src/common／src/app沒有修改或複製，直接沿用W27狀態泡泡、W28 RequestContext密碼政策及W29 keyboard.h／網頁優先／OnKeyEvent。Windows專屬碼、Windows交付／ZIP／prg不改。唯一產品差異為M17的src/platform/macos/main.mm：NSApplication的weak delegate使用objc_precise_lifetime強參照維持至CEF message loop結束；既有Cocoa reopen回呼只啟用共用main_window，closing_in_background時返回已處理。沒有保留嘗試的Apple Event替換、沒有另一份按鍵清單。
- 建置：native arm64／macOS26.7.1，保留的154.0.34 SDK／原下載包／build均存在，壓縮檔SHA256仍2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe。沿用build-macos.sh，初輪及最終Release／CTest1/1成功，實際111 checks／0 failures。codesign deep strict通過；不把編譯當成UI驗收。新增平台修正後只重測相關reopen／關閉及設定回歸，共用來源與原核心案例保持。
- M14：原status-hint.html選單及子選單兩個event／畫面PASS，停留無javascript:void(0)泡泡；本輪證據目錄副本另加普通HTTP連結，停留無泡泡，點擊後URL變/normal-link。原OA JavaScript未改；網站自己的hint不在停用範圍。
- M15：固定CEF Mac成功設定兩個偏好；原生POST→303結果頁、重啟AJAX→204／移除表單均正常，畫面無保存／更新密碼詢問。啟動有PASSWORD_SAVING_AND_AUTO_SIGNIN_DISABLED，沒有PASSWORD_POLICY_FAILED。僅合成值、server丟棄表單內容，正式OA登入未測；false不被解讀為所有既存密碼填入功能都停用。
- M16快捷鍵：Computer Use native pressKey送F1／F2／F3／F4／F9、Option+W、Shift+F及Cmd／Ctrl+F／E／S／N，共15組；網頁不preventDefault與會preventDefault兩輪各15組trusted=true，handled輪15個cancelled事件。原keyboard-shortcuts頁先測，因目前注音來源Ctrl鍵的event.key是注音符號，證據副本補記code／keyCode／isTrusted並用KeyF等實體位置取消預設；KeyF／E／S／N與70／69／83／78皆正確。沒有人工JavaScript重送key事件。畫面無搜尋／儲存／新視窗／網址列焦點；Shift+F及未列出的Shift+A可輸入，Cmd+A／C／V／Z實測複製貼上再還原，F12開關Console、native輸入1+1=2通過。Console貼上被DevTools正常阻擋後改用鍵盤輸入，沒有解除保護。未列出的Cmd+R有網頁事件，但未確認Chrome重新載入，不記為reload通過；F8、Ctrl+P／Cmd+P本輪UI未執行。工具直接送功能鍵，實體鍵盤／Fn設定未查改或驗收，一般注音仍留使用者。
- 既有回歸：在/private/tmp隔離home啟動同一app，CFFIXED_USER_HOME只供本輪程序，已核對實際Cocoa INI／profile／logs在隔離Application Support。沒有產品路徑override功能或個人INI副本。空白HomeUrl歡迎頁／預設版本標題、兩個URL入口、全選網址、ESC／X取消與ftp拒絕、有效HTTP／HTTPS保存及各自重啟直接載入通過；data URL沒有寫入INI。110%保存／重啟ZOOM_APPLIED110，縮小與100%還原無泡泡。Finder目錄等於該次實際Config.ini父目錄，完整工具列／原圖／最大化正常；一般popup開啟與關閉、document.title動態名稱及公開OA名稱更新通過。隔離home不替代正式資料位置驗收；正常使用仍是使用者Application Support，平台路徑沒有修改。
- 兩輪legacy-contract：首輪boot-SYNTHETIC-INITIAL，重啟boot-SYNTHETIC-PERSISTED；各有preferences-pass／site-data-clean／site-data-created。首個網站腳本前Cookie、cmd=ini、load-userset的$tmp.userSet／func／$usr、userid／公司別及特殊字元通過。前輪網站Cookie／LocalStorage／IndexedDB／ServiceWorker／CacheStorage皆清除，INI偏好仍回填；--url覆寫localhost後隔離INI的HomeUrl仍HTTPS，正式個人設定未注入合成值。
- M17失敗與修正：舊交付及初輪build在背景期限前重新啟用曾生成Chrome新分頁；全部CEF browser回呼關閉後仍持鎖，該輪失敗，僅SIGTERM已核對的殘留PID37325／37478／37791。採樣仍在NSApplication run／CEF loop；固定CEF runner等待全部Chrome Browser keepalive退出。Cocoa delegate原區域值在ARC下可能於最後使用點提前釋放，最終以明確lifetime保留，並用既有reopen回呼保持隱藏。最終真實Finder重新開啟有MAC_REOPEN_HANDLED background=0；關閉中Cmd+O再開啟有background=1兩次，無新browser／窗口，不延長期限。timeout3019ms／ACK1418ms、logout各一次、main=1 console=1隱藏、beforeunload允許、SHUTDOWN_COMPLETE／exit0與全部Helper消失通過。中間AppleEvent嘗試的3034ms結果保留為診斷，不當作最終來源；正式OA伺服器登出未驗收。
- 交付：package-macos.sh更新完整artifacts/macos-arm64/oaClient2.app，主執行檔SHA256 **879b1e1747f0a59f75afa7cfc0790f257aa3acfe62b72edbd8239226e99c4a7e**；build／交付265份檔案與連結／mode一致、無斷鏈、10份Mach-O全部arm64、codesign deep strict通過。未安裝Applications／製作或上傳新ZIP；272份Windows來源／交付／既有Releases／prg保護項目不變，SDK／壓縮檔／build保留。現用個人INI保留正常Window保存現況，不回寫快照，不宣稱整檔逐位元不變。
- 證據：artifacts/verification/macos-m14-m16（M17同批），build*.log／core-tests.log、各合成event與runtime、application.log／application-isolated.log、bundle-manifest.json／delivery-results.json／source差異。UI圖像見本輪Computer Use回傳；未另儲存PNG，不把不存在的截圖列為檔案證據。所有測試app／server已停止。伺服器以Ctrl+C正常結束，exit130／KeyboardInterrupt屬測試server停止，不是建置或驗證中斷。
- 時間：環境與交接唯讀核對後，約13:05首次建置／核心；13:07～13:31合成實機與工具等待另列。平台修正與建置約13:18～13:20、最小lifetime版約13:25～13:26，屬測試後實作／必要建置；13:31交付核對。沒有精確累計，不將UI等待算成兩小時實作。
- 待驗收／未執行：正式列印預覽／PDF／印表機、一般注音／實體Fn、正式OA登入登出／實際選單與快捷鍵、hcopen／Mac報表、F8／列印快捷鍵本輪UI、最小化／多螢幕／其他系統、延遲Console建立特定競態。Mac使用者尚未回報本輪驗收；Windows原W29回報保持，沒有Mac修改的共用來源需要另行承接。U01未實作。尚未commit／push／移Tag／公開Mac同版替換，舊Mac公開ZIP仍為M13，不能拿它測W27～W29。

## M18：Finder 時間問題與修正（2026-10-13）

使用者截圖顯示oaClient2.app為上午05:06。核對確認系統為Asia/Taipei／UTC+8，外層.app目錄mtime為05:06:07，內部主執行檔為13:26:11；不是時區差異或舊binary。增量建置只改內部檔案，而package-macos.sh的rsync -a保留build外層舊目錄時間，導致Finder顯示早期時間。

依使用者要求，scripts/package-macos.sh於交付簽章核對成功後新增touch -m，只將交付.app外層修改時間設為目前系統打包時間。現有交付已更新為2026-10-13 13:43:20（UTC+8），當次系統時間同為13:43:20。265份內部檔案／連結內容未變，codesign deep strict及bash -n通過；證據artifacts/verification/macos-m18/results.json。沒有重新編譯、執行功能測試、安裝、提交／推送或發布，版本仍0.1.6；SDK／build／Windows資料保持。Finder此欄代表交付打包時間，不能作為編譯時間或功能驗收證據。

## W30：Windows Ctrl+W 交回網頁與關閉回呼保護（2026-10-13）

使用者回報Windows連續Ctrl+W當機，後續明確選定「取消Chrome關閉動作，保留OA網頁自己的Ctrl+W處理」。Windows事件17:40:38／17:41:42皆為oaClient2.exe的0xc0000005、RVA0x1053e；原交付EXE與app.obj反組譯對照到PrepareWindowClose中GetMainFrame()回傳物件後的解參照。application.log在兩次當機前已記BROWSER_CLOSED，沒有SHUTDOWN_COMPLETE，確認Chrome關閉分頁先銷毀主瀏覽器，後續窗口關閉回呼仍嘗試對失效main frame執行logout。

Windows入口啟用AppContext.disable_chrome_ctrl_w，common/keyboard.h精確保留Ctrl+W給網頁；app.cpp沿用W29的OnPreKeyEvent／OnKeyEvent，網頁先接收，未處理才抑制Chrome預設關閉。沒有吞掉OA自己的事件，也沒有新增網頁分頁邏輯。Mac政策預設false，Cmd+W未加入攔截；Mac專屬來源及交付保持。共用CanClose／PrepareWindowClose／ProbeLoginState檢查browser／main frame有效性，避免已關閉瀏覽器再次解參照；原背景登出一次、ACK／三秒期限及UserSet／INI契約保持。

Windows增量MSVC Release／CTest1/1、115 checks／0 failures通過（新增5項Ctrl+W及其他修飾鍵界線）。tests/pages/close-shortcut.html兩種模式各3次真正Ctrl+W，網頁不preventDefault及有preventDefault皆收到isTrusted=true的事件且窗口保留；輸入工具產生的code為空，以keyCode=87核對，未人工重送JS事件。初輪合成頁僅比對code而未計數已修正測試素材，未改產品政策。正常Alt+F4合成ACK1434ms（另一次含Console1525ms）、無ACK3019ms、logout一次、主窗／Console隱藏、beforeunload自動放行與全部oaClient2程序退出通過；驗證後無新增當機事件。這些是逐次按鍵測試，正式OA關閉內部分頁與實體高速連按／長按仍待使用者驗收。

本機交付僅更新EXE，版本仍0.1.6，SHA256：504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09。與本機Release一致，Mac／CEF／prg等507份保護雜湊不變。使用者確認Mac停止操作／同步完成；接手main／origin/main為cb68ba2，保留Mac M14～M18及D04未提交差異，無lock／conflicted來源。本輪未提交／推送／移Tag／發布，公開Windows ZIP仍是W29，公開Mac ZIP仍M13。本機SDK／下載包／build保留；合成URL僅當次命令列，不寫入INI，正常Window保存現況保留。證據在artifacts/verification/windows-w30；實作／必要建置與實機測試分開記錄，不虛構逐秒工時。

Mac M14～M18既有結果保持；本次共用關閉保護需要後續macOS增量編譯／回歸才能進入Mac交付，不能以Windows測試代替。列印／注音與其他既有待驗收保持，U01仍未實作。

## W30／R02：使用者驗收與同版發布授權（2026-10-13）

使用者對本機Ctrl+W修正回覆「可以了」，W30按此回報記錄Windows使用者驗收通過；不擴大為Mac、列印／注音或其他功能驗收。另明確授權commit、push、重新打包上傳、不進版：先提交／推送本次Windows修正與紀錄，再打包已建置／115項及使用者測過的同一EXE，替換既有v0.1.6同名Windows ZIP／.sha256。Tag、Mac兩資產及個人資料保持；先上傳校驗兩個暫名資產才替換，舊ZIP保留本機歷史證據。

Mac M14～M18及D04是接手時已有的未提交差異，保留於工作目錄，本次Windows提交只納入W30及發布紀錄。Mac新共用關閉保護仍須在macOS編譯回歸；U01未實作。前段待驗收／未發布是本次回報及授權前狀態，實際結果另行追加。

## W30／R02：0.1.6 同版更新完成（2026-10-13）

Windows Ctrl+W修正已由使用者回覆「可以了」驗收，來源a56ec05688462400e23137ba87bd63c875444221已提交／推送；沿用MSVC／CTest1/1、115項及使用者測過的同一EXE，沒有重新編譯或進版。EXE SHA256 504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09。本次共用關閉保護仍待macOS編譯回歸，不擴大其他功能驗收。

既有[v0.1.6 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)的[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)與[校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)已替換為W30。ZIP 189880372 bytes，SHA256 **2ca590f6cd878a4a66612d8a4d25d99c46a432c23af26fb53177d64583252d33**；Windows資產ID636632177／636633864。先上傳兩個暫名資產／校驗digest才替換原名，公開原URL無登入重新下載兩檔與本機及GitHub一致，240檔CRC／全部SHA256通過。

ZIP仍只含EXE、安全範例、CEF234及現用prg4；不含個人INI／picture／logs／profile／cache／tpl／SDK／build，不補回工具。本機artifacts/releases同名兩檔已同步，W29歷史副本保留。Mac兩資產ID／大小／digest及固定Tag67e29679→0fe6f35不變，507份Mac平台／產物與CEF／prg等保護檔案雜湊一致。Mac M14～M18及D04既有未提交差異保留於工作目錄，未混入Windows提交；SDK／下載包／build保留。U01未實作。

證據artifacts/verification/releases-windows-w30/results.json／package.json／release-public.json及public-download；發布結果文件另行提交推送，最新main以Git核對。前段W30待驗收／未發布及W29公開雜湊為本次驗收／發布前歷史。

## 2026-10-16：M19 Mac 附件選檔修正

狀態：已實作、Mac arm64 Release建置／實機測試、更新交付，使用者回覆「我剛剛測試 oaclient2 附件 正確」，本次附件修正驗收通過。

涉及src/app/app.h、src/platform/cef_platform.h、src/platform/macos/CMakeLists.txt、新增file_dialog.mm及tests/pages/file-dialog.html。共用端僅平台handler接線；Cocoa選檔與格式UI只在Mac，Windows仍採CEF預設nullptr，不修改Windows專屬來源或交付，Windows編譯回歸未執行。

- Custom Files合併CEF提供的所有允許副檔名，預設顯示格式選項；All Files另行解除格式篩選，與使用者Chrome參考圖相同兩選項。MIME使用CEF展開結果，不猜測、不寫死OA格式。單選／多選按原mode；儲存／選目錄／無限制不攔截。
- 實際CEF合成頁：JPG／PNG／PDF／XLS／XLSX五檔同選並回傳名稱；TXT預設不可選。MIME image/*＋PDF＋XLSX可同選PDF及XLSX，未列XLS／TXT不可選。PNG預設只允許PNG；All Files可選TXT且仍只回一個檔案。再次開啟重設Custom Files；ESC保留原五個選檔，Cancel正常。無限制／目錄CEF視窗開啟取消正常；儲存／pending sheet父窗關閉未獨立實測。
- 固定CEF154.0.34 SDK／下載包原本不存在，重新下載同版並核對既有SHA256；SDK／壓縮檔／build保留於本機非同步目錄。Release／CTest1/1、116 checks／0 failures；10份Mach-O arm64及codesign deep strict通過。這116項是既有核心回歸，選檔結果另以實機UI為證，不將核心測試當成選檔UI證明。
- artifacts/macos-arm64/oaClient2.app與build265項內容／連結／mode一致，主EXE SHA256 9388faa75d04e2aaf8df5e4105b0fcd6632ac4b901aec8f55f6b0ee82190b3e2。原.app回復副本在/private/tmp/oaClient2-m19-before.app。版本0.1.6，未安裝或公開發布；WindowsEXE／平台來源及既有main.mm差異保持。
- 測試使用/private/tmp隔離Cocoa home並核對實際紀錄；副檔名素材不驗證文件解碼／正式上傳。server已停止，沒有向正式OA送出代理測試附件；使用者自行實測回報按其範圍記錄。原INI正常關閉更新現況，不宣稱逐位元不變，無合成偏好／網址回寫。
- 舊交付已收到登出ACK且全部Browser關閉但未完成程序退出，核對後SIGTERM結束，未修改登出碼。隔離新建置正常3005ms期限與SHUTDOWN_COMPLETE；UI工具其後重新啟動build版至正常OA，使用者於修正版驗收，保留該視窗、不再操作。build／交付逐項一致。

證據：artifacts/verification/macos-m19/results.json、build.log、package.log、isolated-application.log；實機圖像與AX狀態在本對話工具回傳。正式列印／一般注音、其他原待驗收及U01未實作保持；共用W30關閉保護已隨此次Mac重編，僅本次正常無ACK退出有回歸，不擴大為W30完整Mac驗證。

## 2026-10-16：D04／W31 Windows 附件修正交接文件

使用者回報 Windows 同樣有附件選檔問題，已依要求建立[Windows 附件選檔修正提示詞](docs/WINDOWS-FILE-DIALOG-2026-10-16-PROMPT.md)，可直接貼到 Windows Codex 接續。W31 目前為待實作／Windows 建置及實機驗證未執行；提示詞明列 Chrome Custom Files／All Files 目標、Mac M19 參考及驗收邊界、既有 factory 的 Windows nullptr、平台實作／共用來源邊界、測試素材、資料保留與本機 EXE 交付。

只新增 UTF-8／LF Markdown 並核對相對連結、更新交接／計畫／變更紀錄；未修改程式、測試頁、SDK、個人設定、Windows EXE 或 Mac .app，未建置／操作 App、提交／推送／發布。M19 使用者驗收與 U01 等其他狀態保持。

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

## 2026-10-20：W32 外部協定改為前綴＋open＋可選後綴

- 使用者最終要求 `[其他字樣]+open+[其他字樣]:///`，明確包含 `hcopen:///`、`hcopenprint:///`、`wjopen:///`；不限定hc，open前至少一個字元、後方可空、不分大小寫。先前未編譯的hcopen限定方案已由此規則取代。
- 只修改唯一共用src/common/ini.cpp的IsLegacyOpenProtocol及tests/core_tests.cpp。取第一個冒號前的scheme，從索引1起找open；不把一般HTTP路徑內的open當協定、不放行bare open／openprint或沒有冒號的字串。CEF原有GetRequestHandler／GetResourceRequestHandler／OnProtocolExecution接線不改，不自行解析、解碼或執行URI內命令。
- 依使用者「只要送出命令就好，不用驗證 windows 註冊」，應用程式沒有新增任何登錄、處理器或外部程式存在檢查。使用者提出此前的W17唯讀系統查詢只是本輪最初檢查，不是新功能啟動條件，未註冊或修改系統。
- Windows既有SDK／MSVC x64 Release編譯成功，CTest1/1、143 checks／0 failures；22項協定正反案例涵蓋hcopen、wjopen、不同大小寫、其他前後綴、bare open／openprint、一般HTTPS路徑、缺冒號及空字串。建置有CEF既有未使用delay-load DLL之LNK4199警告，無編譯錯誤。未重新執行UI矩陣或正式OA／外部命令，實際外部開啟由使用者測試。
- 以package-windows.ps1 -ExecutableOnly只更新artifacts/oaClient2/oaClient2.exe，版本仍0.1.6；與build SHA256一致：3a03b124a48864af570f6ba070b332fb25c95b9a1d84d076394ca11c2df1e6f3。交付其餘檔案與Mac專屬來源253項保護雜湊不變；沒有啟動OA／改寫正式INI／清除網站資料，CEF、prg、picture、Mac.app與公開ZIP均未更新，SDK／下載包／build保留。
- 接手main HEAD仍8d104ba7af6c75b91527a14a6d2b6ed64d03dc2b，保留先前未提交W31／Mac／文件差異。未commit／push／移Tag／發布。共用規則需回macOS重編及回歸才套用Mac交付；其他既有未驗收與U01未實作保持。
- 證據：artifacts/verification/windows-w32/build.log、core-tests.log、protected-before.json、results.json。最初舊規則受限核心執行曾INI建立失敗且中止，隨後原W31版本123項通過；新規則最終143項通過，不混用兩次結果。實作／建置與核心測試分開記錄，未虛構累計工時。

## 2026-10-20：W33 視窗標題列與工具列固定亮色

- 使用者明確指系統主題，要求上下兩處都不要跟著變色；本輪Windows採固定亮色。新增AppContext.fixed_light_window_appearance預設false，由Windows main.cpp啟用；Mac入口／產物不改，不在Windows啟用Mac政策。
- src/app/app.h／app.cpp沿用唯一App與工具列：OnBeforeCommandLineProcessing在瀏覽器初始化前移除force-dark-mode、加入CEF文件指定的force-light-mode，停止原生系統亮暗主題追隨；OnContextInitialized對全域RequestContext指定Chrome LIGHT／預設色，避免Chrome配色再跟隨系統。這固定CEF色彩模式，沒有修改OA的主題偏好或CSS；不宣稱網頁prefers-color-scheme仍跟隨Windows。
- CEF文件明確指出SetBackgroundColor在OnThemeChanged時會重設，故HeightDelegate於啟用時重套工具列背景，WindowDelegate於按鈕主題回呼重套底色與字色。原淺灰#F0F0F0、文字#222222、圖示、尺寸／排列與按鈕命令保留，未改網站宿主、INI／UserSet／登出／W32協定或Mac專屬碼。
- Windows MSVC x64 Release成功，CTest1/1、143 checks／0 failures；沒有新增鏡像固定值的單元測試，UI結果另記。既有CEF未使用delay-load DLL之LNK4199警告仍在，無編譯錯誤。以computer-use在空白網址／ClearCache=N的拋棄式Config.ini啟動新版，標題列／工具列亮色、完整文字與圖示正常；Alt+F4後測試程序退出。無正式OA登入／正式資料操作，正式Config.ini雜湊不變。
- 系統亮／暗模式切換實測未執行：SystemSettings.exe未出現可控制視窗，沒有改系統設定；不可把亮色視窗檢查當作已驗收完整切換矩陣。最初AppData路徑測試版未出現可控制視窗；改用workspace拋棄式副本，CEF junction首次權限不足，建立完成後啟動成功。背景擷取曾回傳其他前景，該檔已捨棄；重新選取／啟用目標後才保存有效JPG，不把工具失敗當產品通過。
- package-windows.ps1 -ExecutableOnly僅更新artifacts/oaClient2/oaClient2.exe，版本0.1.6；build／交付SHA256一致：3890581dc08216046c3c7dab87b0bef945ce7b22fda3e0886608eb17821b3d53。253項交付其他檔案與Mac平台來源保護雜湊不變，CEF／prg／picture／Mac.app／公開ZIP未改，SDK／下載包／build保留。共用新增介面需macOS編譯回歸，Mac顏色政策尚未啟用；既有未驗收及U01保持。
- 未提交／推送／移Tag／發布，保留前輪所有工作差異。證據artifacts/verification/windows-w33/build.log、core-tests.log、window-light.jpg、protected-before.json、results.json；實作與編譯／工具準備／UI測試分別記錄，不虛構精確累計工時。

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

使用者讀取歷史 10/13 提示後，明確補充「只要mac 版少的 都要補齊」，並確認 Windows 已停止編輯／建置／Git、Dropbox 同步完成。本機 main／HEAD 8d104ba，無 Git lock 或衝突副本；接手已有 M14～M19、W31～W35 與文件差異，均保留，未 reset／pull／checkout。W27～W29 已完成，不重做；Windows 專屬 Ctrl+W 不套用到 Mac。

| ID | 修改與狀態 | 實際驗證與限制 |
| --- | --- | --- |
| M20／W32 | 直接編譯唯一共用 IsLegacyOpenProtocol，前綴＋open＋可選後綴，不分大小寫；CEF 系統轉交流程保持。 | 核心正反向案例通過；未啟動真實外部協定，不新增處理器查詢、註冊或 URI 執行。 |
| M21／W33 | Mac main.mm 啟用 fixed_light_window_appearance；MacApp 的 OnBeforeCommandLineProcessing 呼叫共用基底，保留原 no-startup-window，讓 force-light-mode 生效；NSApplication 使用 Aqua，原生標題與對話框沿用亮色。 | 主窗／工具列／原圖／完整字樣與多次重啟初驗正常，啟動有 WINDOW_APPEARANCE_FIXED_LIGHT。未變更系統外觀，系統亮暗切換與暗色環境未實測，不宣稱通過。 |
| M22／W34 | platform.mm 的 Application Support、profile、INI 暫存／metadata／替換、TextEdit、目錄、Console、截圖提示繁體中文化。檔案系統／POSIX 錯誤附數字代碼，fsync 失敗先保存 errno；NSError 的 localizedDescription 只用 NSLog 記診斷，不直接顯示，非同步截圖亦相同。既有中文報表未支援提示保持。 | 錯誤字串及資料流靜態核對；核心實際涵蓋唯讀拒寫／原檔保留、符號連結清理拒絕、錯誤目錄、UTF-16；UI 確認 ftp 無效網址中文提示。未逐一觸發所有原生磁碟／截圖／TextEdit 失敗。第二個測試程序未能由 UI 工具個別選取，重複啟動中文對話框本輪不列通過。 |
| M23／W35 | 直接沿用共用 download.prompt_for_download=true 與停止啟動的錯誤政策，不新增 Mac 下載管理器或 INI 欄位。 | 真實 CEF GET／POST／Blob／新視窗／右鍵另存每次均出現原生 Save；中文建議檔名、兩個目錄、中文／空白新檔名、5 份內容逐位元一致。Blob 取消不落檔，再次匯出仍詢問；重啟 GET 仍詢問並可取消。Ctrl+P 完整 Chrome 預覽與原生 PDF 另存成功，PDF 105108 bytes；未測正式 OA 匯出、內嵌 PDF 檢視器及實體列印。 |

本輪產品差異只有 src/platform/macos/main.mm、platform.mm；src/common／src/app／共用介面及 Windows 專屬來源未再修改或複製。Mac 沿用最新共用來源建置，沒有新增需 Windows 承接的共用修改，也未在 Mac 建置 Windows。

建置：沿用保留的固定 CEF154.0.34 macosarm64 SDK／下載包／本機 build。下載包 SHA256 仍 2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe。既有 build-macos.sh Release／CTest 1/1、**136 checks／0 failures**；package-macos.sh 交付 265 個檔案／連結／mode 與 build 一致，10 份 Mach-O 全 arm64、codesign --verify --deep --strict 通過。主執行檔 SHA256 **6797e8a69846e43d0e0b5e11a27292fefbd3fe0c0c342129696af6aa313c01f0**。

合成回歸使用 /private/tmp 隔離 Cocoa home，核對實際 INI／profile／logs 均在隔離 Application Support；未複製個人 INI，也未向正式 OA 上傳。110% 保存／重啟還原、密碼政策、動態標題、Console 開關與原生附件 Custom Files／All Files／ESC 正常。UserSet／公司別／特殊字元、$tmp.userSet／func／$usr、首個腳本前偏好 Cookie，以及 Cookie／Local Storage／IndexedDB／Service Worker／Cache Storage 的重啟清理通過。首輪是空白合成 INI 且在程序中途導航，未先種入測試頁要求的初始偏好，因此 cookies-fail／preferences-fail 保留為測試前置不足；頁面保存合成偏好後正常重啟得到 boot-SYNTHETIC-PERSISTED／preferences-pass／site-data-clean，沒有為此修改產品流程。

關閉回歸：初輪已登出 ACK 29ms、合成登入 ACK 1509ms 均正常 SHUTDOWN_COMPLETE；實際交付版單獨無 ACK 3012ms、開關 Console 後無 ACK 3011ms，logout 各一次並完整退出。一次包含附件取消、beforeunload 啟用、Console 與快捷鍵的複合測試，在期限 3034ms／CLOSE_BACKGROUND_UNLOAD_ALLOWED／全部 BROWSER_CLOSED 後主程序仍留在 CEF／NSApplication loop；已保留短堆疊，最後僅 SIGTERM 核對的測試 PID93040。這次不是正常退出，不宣稱原因已定位或修正；最小回歸通過不抹除該失敗。記為 **M24：複合退出殘留待定位**，M19 也曾有類似症狀，但不據此斷定同一原因。Cmd+P／Cmd+Q 本輪工具輸入未造成可見動作，Ctrl+P 與主窗關閉按鈕已實測；未擴大為 Mac Command 快捷鍵驗收。

保護：301 份 Windows 平台來源／交付／公開 ZIP／prg、共用來源及 Mac 個人 Config.ini／picture 雜湊與接手一致。僅更新 artifacts/macos-arm64/oaClient2.app，不安裝 /Applications、不製作 ZIP、不提交／推送／移 Tag／發布，公開 Mac 仍 M13。SDK／下載包／build 全保留，未補回已清除交付外部檔案。正式 OA／一般注音／外部協定／Mac 報表及原未驗收範圍保持，U01 未實作。

證據在 artifacts/verification/macos-m20：baseline.patch／baseline-status.txt、build.log、core-tests.log、package.log、application-isolated.log、regression-events.jsonl、requests.jsonl、delivery-results.json、bundle-manifest.json、protected-before.json、close-sample.txt、指定路徑中的合成下載／PDF 與 runtime 紀錄；UI 圖像／AX 在本輪 Computer Use 回傳，未另存 PNG。初次受限建置無法寫本機 Cache、受限 localhost bind 失敗，提升後完成；8765 已被既有程序使用，本輪改用 18766，未停止既有服務。約 12:29～12:31 實作／建置，12:31～12:44 測試與工具等待另列，後續文件核對另計，不捏造累計工時。

## 2026-10-30：M24 Mac Cmd+Q 背景殘留修正完成

使用者要求繼續查明 M24，修好後重新編譯 Mac。本輪延續已確認的 Windows 停止／Dropbox 同步狀態；main／HEAD 8d104ba，保留全部既有未提交差異，未發現 Git lock 或來源衝突。

**定位與對照：** 舊交付在單獨 beforeunload 啟用時正常退出；加入附件取消、Console 焦點 Cmd+Q 後可重現殘留。再移除附件，僅保留 beforeunload／Console／Cmd+Q 亦能重現；相同情境不送 Cmd+Q 則完整退出。失敗輪沒有 COCOA_TERMINATE，後續按主窗關閉後已有全部 BROWSER_CLOSED、CefQuitMessageLoop 呼叫返回與 Views 主窗銷毀，但 CefRunMessageLoop／NSApplication loop 沒有返回。這將問題縮小到 Console 焦點下 Command-Q 進入 Chrome 處理路徑、未先走本程式原生結束入口；不再將附件或 beforeunload 單獨視為原因。

**最終修改只有 src/platform/macos/main.mm 的 sendEvent 六行。** 在 CefScopedSendingEvent 範圍內，僅對 KeyDown、Command 且沒有 Control／Option／Shift，以及 charactersIgnoringModifiers 小寫為 q 的事件，先呼叫既有 mainMenu.performKeyEquivalent；原生選單確實處理時才返回，否則保留原 super.sendEvent。這讓原「結束 oaClient2」選單呼叫既有 terminate，繼續用唯一共用主窗關閉、logout 一次、立即隱藏、ACK 或三秒期限流程。未新增 exit／kill／強制停止 RunLoop 的產品 fallback，也未變更其他 Chrome／OA 快捷鍵、INI、UserSet、路徑或 CEF 版本。

暫時的共用關閉診斷、Mac native window observer／stop／timer、附件 completion 參照調整都已撤回；附件參照調整未解決同一殘留，不留入產品。最終 src/app/app.cpp、app.h、src/platform/cef_platform.h、Mac file_dialog.mm 與本輪接手內容逐位元一致；Windows 專屬碼／交付未改。本次沒有需另一平台承接的共用產品差異，未在 Mac 建置 Windows。

**修正後實測：**

| 情境 | 結果 |
| --- | --- |
| build：beforeunload 啟用＋Console 焦點 Cmd+Q、無 ACK | COCOA_TERMINATE → logout 一次；主窗及 Console 立即隱藏，3032ms 到期後全部 Browser 關閉、SHUTDOWN_COMPLETE；主程序及 Helper 消失。 |
| build：附件開啟／取消＋beforeunload 啟用＋Console 焦點 Cmd+Q、有 ACK | 原 Custom Files 選檔／Cancel 正常；ACK619ms 即完成關閉，未等三秒；有 SHUTDOWN_COMPLETE、全部退出。 |
| 實際交付：附件開啟／取消＋beforeunload 啟用＋Console 焦點 Cmd+Q、無 ACK | 3043ms 期限後全部關閉與 SHUTDOWN_COMPLETE；最後 ps 核對沒有本程式主程序或任何 Helper。 |

每輪只有一次 logout-start-1；beforeunload 依原背景關閉政策允許，不出現阻擋。第一輪修正版關閉中的 UI 工具重新啟用觸發 MAC_REOPEN_HANDLED background=1，仍隱藏且期限不延長。UI 工具於程式正常隱藏／退出後取 AX 的 timeout 不當作產品失敗，實際以紀錄、程序退出與 Helper 狀態交叉核對。

**環境限制與排除：** 新 ad-hoc 簽章測試版曾在 SecItemCopyMatching／系統鑰匙圈等待，尚未建立 Browser，已與原退出殘留分開辨識。系統 SecurityAgent 的 UI 不允許工具操作，沒有操作授權或讀出／記錄／修改鑰匙圈內容。後續本機合成測試只透過啟動參數 --use-mock-keychain，沿用固定 SDK tests/shared/browser/client_app_browser.cc 同樣的官方測試方式，搭配 /private/tmp 隔離 Cocoa home 與 localhost；這個參數沒有編入程式、沒有寫進 INI／bundle／打包腳本，正式程式的鑰匙圈政策保持。未經系統鑰匙圈授權的正常啟動／正式 OA 登出仍待使用者驗收，不能以 mock 測試宣稱真實鑰匙圈已驗收。

**建置與交付：** 最終 build-macos.sh arm64 Release／CTest1/1、136 checks／0 failures 通過；package-macos.sh 已更新 artifacts/macos-arm64/oaClient2.app，版本仍0.1.6。265項檔案／連結／mode與build一致、無斷鏈，10份Mach-O全arm64、codesign --verify --deep --strict通過。主執行檔 SHA256：b8715817e17036d7b05e830db48433232e6293c286a4390a9769f00a48ccd862。299份Windows來源／交付／Releases／prg、common及Mac個人INI／picture與接手一致；共用app／介面亦另外比對不變。SDK／下載包／build保留，未安裝／提交／推送／移Tag／發布，公開Mac ZIP仍M13。系統亮暗切換與其他原未驗收項目、U01未實作狀態保持。

證據：artifacts/verification/macos-m24 的 baseline.patch／baseline-status.txt、build-fixed.log、core-tests.log、package.log、application-isolated.log、events.jsonl、cmdq-before-close.log、diagnostics來源副本、各輪runtime、results.json／delivery-results.json／bundle-manifest.json／protected-result.json；UI／AX在本輪Computer Use回傳，未另存PNG。隔離測試server及所有測試App／Helper最後停止。初期失敗輪僅對已核對的本輪殘留或鑰匙圈等待PID發SIGTERM，不將其列為正常退出；沒有將此做法寫入產品。約12:54～13:08定位與診斷／測試／環境排除，13:08～13:09最小修正與重編，其後修正版實測／交付／文件另列，不虛構精確實作累計。

## 2026-10-30：W36 印表字型／FRX／Reptool 查證

狀態：查證完成，產品修正及正式端到端驗證未執行。使用者指出選定印表字型後應由 Reptool.exe 設定 FRX；已核對舊 oaClient64、oaReptool 現行來源及 oaClient2，未修改舊專案或產品來源。

舊鏈路為 cmd=ini 保存 UserSet.report_font → cmd=prt 呼叫 Reptool → Reptool 讀 INI，frx／fr3 範本中的 Arial Unicode MS 被替換成指定字型，寫 tmp- 範本後載入。oaClient2 已有通用偏好保存及報表啟動，沒有排除 report_font；確定缺口是 UTF-8 無 BOM 保存／移除原 BOM，與舊 Delphi TMemIniFile 無 BOM 時採 Windows ACP 的讀法不相容。

隔離 probe 直接編譯現行 ini.cpp／Windows platform.cpp，真正 SaveUserSetting 保存「標楷體」：原有／沒有 BOM 兩例保存後均無 BOM；客戶端讀回正確，但本機 ACP950 的 Delphi21.0 TMemIniFile 讀錯、FRX 字串替換結果不符。UTF-8 有 BOM 控制正確，無 BOM 控制失敗，CP950控制先前正確。MSVC／Delphi probe 建置通過；第一次沙箱 CMake 路徑隔離失敗保留，正常本機暫存重跑成功。未重建產品／跑產品CTest／操作正式OA或Reptool，不能寫成報表實測通過。

交付 INI 查核時沒有 report_font 且無 BOM，未改個人設定或匯入舊偏好；兩代交付 Reptool.exe SHA256 相同。另發現現行 Reptool 源碼以EXE旁／上一層定位 INI，沒有讀第二命令列參數，非標準 ReptoolConfigIni 相容性仍待確認。詳細來源行號、限制及最小修正建議見 [相容性文件 W36](docs/LEGACY-COMPATIBILITY.md)。

下一步為修正 oaClient2 INI 輸出編碼相容性並驗證正式選單命令、保存／重啟、真正 FRX 預覽及列印；本輪依查證範圍尚未實作。文件同步 PROJECT-PLAN／HANDOFF／CHANGELOG；驗證素材在 artifacts/verification/windows-w36-report-font-audit。產品 EXE／Mac.app／prg／設定／SDK／build保留，未提交／推送／發布；其他未驗收與U01保持。

## 2026-10-30：W36 修正及0.1.7 Windows交付完成

使用者授權修正INI相容性與確認印表字型保存、編譯供測試，追加既有Config.ini自動修復並進版。Windows本機版本升為0.1.7；共用ini.cpp採UTF-8 BOM保存，LoadSettings啟動先修復既有無BOM的UTF-8檔，再沿用原設定。鍵值／註解不重設、相同內容不重寫，拒寫不解readonly或改ACL；CommitSettingsFile未改，未修改Reptool。CMake、共用標題／client_version、Windows START同步進版。

MSVC Release／CTest1/1、160 checks／0 failures（原143＋17）通過。隔離CEF實機select選「標楷體」「新細明體」均透過原cmd=ini保存report_font及load-userset回呼；磁碟INI具BOM、其他合成設定保留。關閉重啟後選單／$usr／偏好Cookie／load-userset均還原新細明體。UI同份INI由舊Delphi21.0 TMemIniFile在ACP950正確讀取，FRX替換模擬結果正確；真正Reptool、正式OA網頁／FRX預覽及印表機未測，供使用者驗收。

自動修復／新建、原有或沒有BOM、重啟mtime不變、視窗保存、中文／預設字型及拒寫原資料保護已測；原同步鎖fallback等亦通過。UI測試前期CEF Junction造成error126，改完整測試runtime後成功；套件路徑映射／select set_value無效的工具情形已另記，未改產品CEF／profile保護。

已用package-windows.ps1 -ExecutableOnly更新artifacts/oaClient2/oaClient2.exe，build一致；SHA256 ebc31ebb1e8a56085b11c696b6149bf0e1300f420c4a4173197ede1f54899cc4。528份保護檔案不變，含正式INI、Reptool／prg、CEF、Mac來源及交付；正式INI保留現況，下次使用新版啟動自動修復，不注入合成偏好。兩輪正常關閉／SHUTDOWN_COMPLETE／全部程序退出，localhost server停止。

Mac專屬碼／0.1.6.app不改，共用來源須macOS重編／實測，Mac平台自己的版本紀錄需於Mac同步；公開ZIP仍0.1.6。本輪未提交／推送／Tag／發布；SDK／下載包／build保留，U01及其他待驗收保持。詳細限制見[相容性文件](docs/LEGACY-COMPATIBILITY.md)W36修正段；證據artifacts/verification/windows-w36-ini-fix。約20:55～20:58實作／初建置、後續進版必要重建，21:02～21:05實機與工具處理，文件核對另計，不虛構精確累計。

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

## 2026-11-03：W37 Windows取消Shift+F攔截並同版重編完成

依使用者「重新編譯Windows版，移除Shift+F攔截，版本維持0.1.7，編譯好讓我測試」要求，直接沿用Mac M25已修改的唯一src/common/keyboard.h及core_tests.cpp，不重寫或再次修改產品來源。Shift+F現在不被IsWebsiteShortcut視為客戶端快捷鍵，一般文字輸入交回網頁；其他按鍵政策與W36的INI BOM／啟動修復保持。

固定CEF154.0.34及既有MSVC x64 Release建置成功，CTest1/1、160 checks／0 failures，含Shift F remains normal text input檢查。使用者要求編譯後自行測試，本輪Windows UI／大寫F輸入、正式OA頁面及其他熱鍵實機未執行，不把Mac實測或核心政策檢查當成Windows UI驗收。

package-windows.ps1 -ExecutableOnly只更新artifacts/oaClient2/oaClient2.exe；版本維持0.1.7，build／交付SHA256均為76d28963b6a585039a7992860f9e21f21d05e759f669c29d85cd763b117b6a32。567份受保護檔案與接手一致，涵蓋產品來源／測試／腳本、正式INI／CEF／Reptool／prg及Mac交付；未改個人資料、啟動或關閉App。接手main，保留既有未提交來源與文件，未發現Git lock或來源衝突副本。

證據artifacts/verification/windows-w37-shift-f：baseline-status.txt、protected-before.json、build.log、core-tests.log、results.json。SDK／壓縮檔／build保留，未提交／推送／改Tag／發布；其他未驗收與U01未實作保持。下一步由使用者開啟本機EXE測試Shift+F／大寫F及正式OA，前段Windows待重編為本輪前狀態。
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

## 2026-11-12：R03 公開發布 v0.1.8（Windows／Mac）

使用者明確要求publish release，沿用既有測試版形式，新增[oaClient2 v0.1.8 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)，提供Windows x64／Mac Apple Silicon arm64 ZIP及各自.sha256，共4個資產。來源與v0.1.8 Tag固定a3de8b3f8cfd046912bfef19ae7dbf0865df3f6e；前輪G01已實際commit／push並核對遠端一致。本輪直接打包既有各平台已建置的0.1.8交付檔，不重編、不擴大正式OA／MRT／印表機等驗收，也不安裝App。

Windows ZIP 189895114 bytes，SHA256 335c30631616fa0cac24d7da878d08643ee02c4b705f841a7a1e321198ce8199；240檔為EXE、安全範例、CEF234及現用精簡prg4，不補回其他工具。Mac ZIP 144472509 bytes，SHA256 2f5b406cc3acf542c994c5fcb817facec480a73da911ab44874f9594da41f2b8；只有完整.app，解壓265份檔案／連結／mode與交付一致、10份arm64 Mach-O及deep strict簽章通過。兩平台排除個人INI／網站登入與儲存／picture／logs／快取／tpl／SDK／build，Mac未做Developer ID簽署或公證。沿用Windows160項及Mac151項與原生預覽實測，詳細限制保留各工作紀錄及Release說明。

四個公開資產的GitHub大小／digest與本機一致；未帶登入憑證從公開URL重新下載ZIP／校驗檔，全部逐位元相同，兩ZIP CRC及Windows240檔SHA256通過。既有v0.1.6 Release／4資產ID、大小、digest及固定Tag67e29679→0fe6f35保持不變，522份交付／個人設定保護檔雜湊不變。草稿Tag API查詢曾回傳404，該步完整遠端雜湊核對實際在公開後補做通過，不能把它寫成發布前已完成。

本次Release ID 442477933，資產ID／下載URL／校驗及保護結果見artifacts/verification/releases-v0.1.8/results.json；本機ZIP保留artifacts/releases/v0.1.8，SDK／原壓縮檔／build保留。舊Release與Tag不移動，發布結果文件另行提交推送、v0.1.8仍指向實際App來源a3de8b3；U01程式內線上更新未實作。前段「未發布／公開仍0.1.6」為本次授權前歷史。

## 2026-11-12：R03 改為正式 Release／Latest

使用者明確要求將v0.1.8改為正式Release，已取消GitHub prerelease標記並設為Latest，更新發行標題與說明首行為正式版。GitHub releases/latest端點確認tag=v0.1.8、draft=false、prerelease=false，Release ID仍442477933；四資產名稱／大小／SHA256 digest與變更前一致，未重編／重打包／重傳、未移動來源Tag或修改其他版本。各功能驗收限制保持，不因正式Release標記擴大驗收。證據artifacts/verification/releases-v0.1.8/before-stable.json、release-notes-stable.md、release-stable.json。前段測試版形式是本次更正前狀態，下載連結不變。
