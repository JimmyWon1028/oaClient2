# oaClient2 進度表

更新：2026-10-13。Windows 0.1.6 已完成 W21～W26 接線、MSVC 與本輪實機回歸，交付已更新；Mac arm64 0.1.6 已建置交付，列印預覽／注音待使用者驗收。使用者新增工具列、同目錄 INI／picture、啟動最大化及沿用圖示需求已納入。

## 工作項目

| ID | 工作 | 狀態與證據 | 下一步 |
| --- | --- | --- | --- |
| D01 | 閱讀舊 oaClient／Reptool | 已完成第一輪來源盤點；本輪核對 PAS／DFM 工具列並操作舊版 Console 開關。 | 逐一核對其他命令契約。 |
| D02 | 列印預覽技術查證 | 已確認 Electron 不符內建預覽要求；Windows 採 CEF Chrome。 | Mac 核對 #3410 正式配套及實測。 |
| D03 | Git／GitHub | 接手main／origin/main皆為59a323a，乾淨且無lock／來源衝突；固定v0.1.6指向0fe6f35。本輪功能及文件尚未提交／推送。 | 後續提交、推送與發布依使用者授權；不移動Tag。 |
| D04 | 計畫／紀錄／跨平台交接 | 已整理 Mac 接續入口，Windows W21／W22 提示詞已存 [WINDOWS-CODEX-PROMPT.md](docs/WINDOWS-CODEX-PROMPT.md)，包含平台開發分工、共用來源與組態路徑差異。 | 回 Windows 先核對同步與來源，再實作／編譯／回歸；Windows 本輪未改。 |
| D05 | 時間與平台範圍 | 排除環境準備及測試；Mac 固定 arm64。 | 記錄測試後修正。 |
| D06 | 網站／資料／INI 決策 | Windows 現行預設 OA；Mac 初始 URL 空白、設定後保存。Windows EXE 旁 INI，Mac Application Support；網站全清、設定保留。 | Windows 相同歡迎頁 W21 待 Windows 環境實作。 |
| D07 | 共用來源與平台邊界 | 已核對現行來源，新增共用程式碼規則及Mac提示詞：共用功能不重寫、不複製，平台差異獨立；Windows子程序DLL配置及Console handle／座標已透過平台介面最小抽取。 | Mac接手按平台介面最小調整，記錄兩平台回歸狀態。 |
| W01 | Windows 環境 | 已完成；Build Tools 17.14.40、MSVC 14.44.35207、SDK 10.0.26100.0、CEF 154.0.34 校驗、官方範例編譯。 | 不需重裝完整 Visual Studio。 |
| W02 | 網站與 INI | 已實作／建置；實機 OA 首頁載入，HTTP 200；UTF-8 INI、位置／大小保存。 | 0.1.4已補UserSet／userid等保存回填；正式登入對話框由使用者測試。 |
| W03 | 內建列印預覽 | 0.1.0 由使用者測試回報正常；最新版本尚未重新驗收。 | 使用者驗證 OA 列印／取消／PDF／印表機情境。 |
| W04 | 注音與啟動 | 0.1.1 發生浮動組字窗；0.1.2 已恢復 Views 主網站，使用者確認 Microsoft 注音正常。已有初次主框架 load 記錄，非完整網站初始化時間。 | 同條件比較舊版；記錄輸入法與焦點情境。 |
| W05 | 網站資料清理 | 已實作；單例、專用目錄校驗、拒絕 reparse；核心合成資料測試通過。 | 真實 Cookie／IndexedDB／Service Worker 逐項重啟回歸未完成。 |
| W06 | 既有 Reptool 呼叫 | 0.1.4已隨附prg，預設相對Reptool路徑；合成程序核對兩參數／中文／引號／工作目錄通過。 | 實際 Reptool 啟動、參數／報表尚未驗收。 |
| W07 | Windows 交付 | 0.1.6入口在 artifacts/oaClient2/oaClient2.exe；CEF在cef/，圖示內嵌；打包保留Config.ini／picture及使用者資料。 | 可直接壓縮整個oaClient2資料夾；正式簽署／安裝包未做。 |
| W08 | 舊版工具列與 Console | 0.1.2 保留原圖示／順序；主網站為 Views，Console 獨立 Chrome CefWindow 嵌入下方；0.1.3 圖示內嵌。 | Console 開關／分頁、網址對話框、縮放保存、MAC 與截圖已實測；目錄完整路徑 UI 確認未完成。 |
| W09 | INI 同目錄／最大化／OA 圖示 | 已實作；實際 INI 已建立於交付目錄，主視窗最大化，標題 OA 圖示顯示。 | Mac 最新改為 Application Support；見 M04。 |
| W10 | Microsoft 注音浮窗修正 | 0.1.2 使用者確認「已正常，沒有額外浮動組字窗」。 | 多螢幕／DPI／其他輸入法待測。 |
| W11 | CEF 集中與啟動 | 0.1.6不使用沙箱，主程式為獨立EXE；cef/只保留234份原始CEF執行元件，SHA256一致。 | Mac Framework／Helper 已實作；見 M02。 |
| W12 | URL 對話框 | Win32 單行預選網址、藍字、置中確定、X／ESC；展示與 ESC 取消已測。 | 最新確認／錯誤輸入路徑未重測。 |
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
| W21 | Windows 相同歡迎頁 | Windows 入口已啟用空白 HomeUrl／allow_empty_home_url；沿用 welcome.h／app.cpp。MSVC／74項通過，空白頁、兩個設定入口、ESC／X、無效網址拒絕、HTTP保存／重啟已實測。 | 列印／注音及正式使用者驗收待確認；保留既有個人網址。 |
| W22 | Windows 隱藏縮放彈窗 | 入口 hide_zoom_bubble=true；MSVC／74項，網站及歡迎頁110%→100%、還原100%、網站重啟110%實測，無Chromium彈窗。 | 其他DPI／多螢幕未測；比例保存契約不變。 |
| W23 | Windows 隱藏背景登出／三秒退出 | 入口 background_logout_close=true；合成ACK649ms、一般桌面ACK1117ms、無回應3007ms；logout一次、主窗／Console隱藏、beforeunload放行及全部程序退出通過。 | 正式OA登出待使用者驗收；到期不代表伺服器登出成功；晚建立窗口競態未獨立重現。 |
| W24 | Windows 設定目錄瀏覽回歸 | 沿用 paths.config.parent_path()；建置與正式交付位置的按鈕／提示實測，Explorer Shell確認實際Config.ini父目錄。 | 已更新交付EXE；Windows INI仍在EXE旁。 |
| W25 | Windows 網頁資訊標題回歸 | 歡迎頁預設、正式OA名稱及合成document.title動態更新實測；版本0.1.6。共用標題來源未重寫。 | 正式登入後公司名稱切換由使用者驗收；未新增INI品牌欄位。 |
| W26 | Windows 工具列間距／完整文字 | M13共用298 DIP／左右2 DIP設定已在Windows編譯，MAC／瀏覽目錄／截圖／還原比例完整顯示、原圖示與順序核對。 | 使用者最終間距驗收、其他DPI／多螢幕未測。 |
| W27 | 隱藏連結狀態提示 | 共用CefBrowserSettings.chrome_status_bubble=STATE_DISABLED；Windows Release／CTest1/1通過。真實CEF合成JavaScript選單／子選單無左下角提示，原動作正常；EXE已更新及重開OA。 | 正式OA選單由使用者驗收；Mac須在macOS重新編譯／實測，Mac產物未改。 |
| R01 | Mac ZIP Releases | v0.1.6初版測試Release已公開；ZIP只有.app，GitHub大小／digest、無登入公開下載ZIP與校驗檔逐位元一致。 | 列印／一般注音等仍待使用者驗收；Windows補齊見R02。 |
| R02 | Windows Release補齊 | W21～W26的Windows建置／實機回歸已完成，新EXE已交付；本輪尚未製作ZIP或公開發布。 | 後續依使用者授權準備不含個人INI／快取的ZIP、提交與發布；不移動Tag。 |

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
