# 舊版登入、設定、登出及外部工具契約

2026-10-12，oaClient2 Windows 0.1.4。以舊oaClient64現行fmMainOaClientu.pas（CP950）核對，未修改舊來源或匯入個人INI。

## 保存與回填

| 舊來源 | 契約 | oaClient2對應 |
| --- | --- | --- |
| crmConsoleMessage，約781～803行 | cmd=ini\|key=名稱\|val=資料，寫UserSet；空值亦保存；showlog=1提示保存的鍵名 | SaveUserSetting，只改指定鍵，保留其他設定／註解；提示不記錄值。 |
| crmLoadStart，約1389～1419行 | UserSet偏好以Cookie提供給網頁 | 首次建立BrowserView前，等CEF Cookie manager完成當次INI偏好Cookie，使用UTF-8百分比編碼；不是還原舊會話。 |
| IniUserSet，約2356～2385行；crmLoadEnd | 非空UserSet值回填$usr | UserSettingsScript；載入與clientReady時回填，保留鍵名大小寫及特殊資料字串。 |
| DoLoadUserSet，約2916～2945行 | $tmp.userSet為key=value以\|連接；接著執行func原腳本 | SerializedUserSettings；先賦值，再按原契約執行func，不把腳本當資料跳脫。 |
| cmd=loginParam | 當次登入資料供報表參數 | 僅記憶體保存，不寫INI或log。 |

公開OA前端my.func.js也已唯讀核對：setUserSet發送cmd=ini；公司別onSelect保存last_select_database，登入完成回呼保存userid。登入對話框讀getCookie('userid')及公司別偏好；密碼／驗證碼於開啟時清空。loader.js在初始化讀easyui_theme與def_lang，因此需要在首次網站腳本前準備偏好Cookie。

舊UserSet既有鍵名（僅查名稱，沒有複製值）：userid、last_select_database、last_select_itemtype、def_lang、user_font、report_font、useEscQuit、lay_message_visible、billboard_top、billboard_left、msgbox_top、msgbox_left、easyui_theme、easyui_bgcolor、easyui_bgimage、ZoomStep、DropboxRoot。舊原生程式另讀user_ip。新版採通用鍵保存；ZoomPercent是新版縮放欄位，未自行轉換舊ZoomStep索引。

啟動仍先清除全部舊網站profile；之後只從UserSet程式偏好建立新的當次Cookie，不恢復登入Cookie／session／token／密碼。此回填是使用者最新要求的設定保存功能。沒有將舊Bin/Config.ini值自動匯入，也沒有新增自動登入。

## 關閉登出

舊FormCloseQuery（約1740～1816行）在_clientReady後呼叫getLoginState，等待500ms；狀態1時呼叫logout，最多20輪500ms查狀態0，才關閉瀏覽器。

新版WindowDelegate.CanClose→BrowserClient.PrepareWindowClose→common/logout.h沿用查狀態／logout／等待上限，透過CEF延遲任務不阻塞UI。重複關閉不重複送logout；getLoginState不存在時從$g.isLogin讀狀態，這是因目前公開腳本的發布方式提供相同狀態來源。收到狀態0才確認登出，超時記CLOSE_LOGOUT_TIMEOUT後關閉；未知／尚未就緒的頁面不強行呼叫logout。沒有新增舊版離開確認框，也沒有複製Sleep／ProcessMessages迴圈或force-close清理流程。

53項核心檢查與本機CEF合成測試通過；合成logout延遲600ms，觀察先送一次logout、完成及state0後才退出，重啟UserSet仍存在。正式登入／登出由使用者實測，不以合成回報冒充伺服器驗收。

## hcopen與其他…open協定

舊crmProtocolExecution（約1495～1519行）預設拒絕OS執行；scheme長度大於open且不分大小寫以open結尾才允許。所以hcopen:///符合，而open:///、mailto:等不符合。原碼沒有解析檔案路徑、URL解碼或自己執行hcopen內的命令，處理交由作業系統已登錄的程式。

新版CefRequestHandler→LegacyProtocolHandler.OnProtocolExecution沿用此規則，不新增登錄、不重新定義URI。兩次唯讀工具查詢未查到Windows hcopen登錄；使用者表示「這個我測試」。核心判斷與建置已通過，真正外部程式啟動仍待使用者確認。

## Reptool與prg

使用者要求舊Bin/prg全部複製到此專案；12份檔案共55,651,423bytes逐一SHA256一致，見[副本清單](PRG-INVENTORY.md)。根prg保留歷史副本；使用者後續已精簡Windows交付prg並要求不補回，打包不再同步來源，交付工具由使用者維護。不納入Git，不作為Mac可執行依賴。

cmd=prt保留原命令，附加當次loginParam（分號換成\|），成為第一個完整參數；第二個參數為Config.ini或指定ReptoolConfigIni。預設／空白ReptoolPath用prg/Reptool.exe，相對路徑以主程式目錄解析，工作目錄亦為主程式目錄。報表完成呼叫後回復原button的enable契約。

Windows合成receiver測試已實際用ShellExecute接收兩參數，核對中文、內部引號、尾端反斜線及工作目錄。沒有呼叫正式Reptool產生報表，也未把prg之外的tpl、xmlrep等舊資料夾加入本輪複製；正式報表及外部依賴需由使用者實測。

## 測試與平台限制

- 核心：CTest1/1、53項；INI、序列化／跳脫、Cookie編碼、協定判斷、非阻塞登出狀態與合成報表參數。
- CEF：tests/pages/legacy-contract.html與tests/serve-contract.py，僅127.0.0.1的合成userid／公司別，沒有真正登入或帳密欄位；首載、回呼、重啟、兩次登出等待通過。
- Mac：同專案接續，共用設定與CEF流程；平台主入口仍未實作，Windows結果不能代替Mac驗證。Mac處理器／Reptool替代方案仍待討論。

## M03 Mac 初輪驗證（2026-10-12）

Mac arm64 0.1.6 直接編譯原 common／app；兩輪 localhost 真實 CEF 測試已確認首次偏好 Cookie、cmd=ini／load-userset／$usr／func、重啟合成 userid／公司別及延遲登出。第二次開啟舊 Cookie／Local Storage／IndexedDB／Service Worker／Cache Storage 均消失；INI／picture 保留。正式 OA 登入／登出仍未測，列印／注音由使用者驗收。

hcopen 回呼沿用同一 OS 處理器規則；Mac LaunchServices 查詢本機沒有處理器，未自行註冊或改 URI。Mac LaunchReport 明確未支援，不執行 Windows 工具，不影響其原呼叫契約或交付 prg。Windows 共用來源回歸待執行。

## M10／W23 最新關閉時機（2026-10-12）

使用者最新指示取代 Mac 舊最多10秒等待：送出 logout 一次後立即隱藏主窗與 Console；背景收到原 loginState=0 回報即退出，未收到最多3秒後完成退出。共用 LogoutFlow 增加 BackgroundGrace 模式，Mac 入口啟用，Windows 原 PollForState 尚留且 W23 待 Windows 環境處理，不宣稱 Windows 已改。

狀態回報格式／網頁 logout 函式沿用，不改 userid／UserSet／Cookie 清理或 INI。背景關閉期間自動允許 beforeunload，重複關閉不重送；不根據網站回應無限等待，也不把客戶端期限到期當成伺服器登出成功。最後兩輪合成951ms／3029ms及程序正常退出已驗證，正式 OA 登出仍待使用者驗收。


## M12／W25 標題資訊（2026-10-13）

舊 fmMainOaClientu.pas 的 crmTitleChange（1720～1732行）使用 CEF title 加上用戶端版本；OA my.main.js 的 doSetTitle（956行）寫 document.title，getDBCaption 回應及 sys_title 都透過它更新。新 app.cpp 沿用 OnTitleChange，網站提供名稱、本程式提供客戶端版本；沒有新增軟體資訊命令、修改 OA JS 或持久保存公司名稱。主視窗標題為「網頁提供的軟體名稱 [用戶端版本 0.1.6]」。名稱從 URL 頁面的 document.title 經 CEF OnTitleChange 取得，沿用舊版 crmTitleChange，不寫死良穎或其他公司名稱；網頁更新名稱時跟著更新。尚未設定網址／尚未取得標題時使用「oaClient2 [用戶端版本 0.1.6]」，本機歡迎頁不覆蓋這個預設。0.1.6為目前實際客戶端版本，不使用參考圖中舊 oaClient 的2026.10.11.1。

只改主視窗標題；原彈出視窗及 Console 流程維持。Mac 已實測兩個網站名稱，Windows 共用來源回歸待 W25，未宣稱 Windows 交付已更新。


## 2026-10-13：Windows W21～W26 接續結果

Windows入口已啟用空白HomeUrl／allow_empty_home_url、hide_zoom_bubble及background_logout_close；W24設定父目錄、W25網站動態title與0.1.6版本、W26右側298 DIP／完整字樣直接編譯原共用app.cpp。共用來源沒有複製或重寫，Mac專屬碼與交付未改。

Windows MSVC Release／CTest1/1、74項與本輪歡迎頁、網址／縮放重啟、ACK／三秒期限／Console／beforeunload／全部退出、UserSet／網站儲存、目錄／動態標題／完整字樣實測已完成；詳見[最新Windows結果](../PROGRESS.md)。正式列印／Microsoft注音／OA登出／Reptool及間距待使用者驗收，未測情境以進度為準，U01未實作。

交付artifacts/oaClient2/oaClient2.exe與安全範例已更新；Windows INI／picture仍在EXE旁，CEF仍在cef/，prg不補回／覆蓋。正式INI最後正常關閉更新Window後保留現況；不宣稱逐位元不變。SDK／壓縮檔／build保留。本輪未提交／推送／發布，固定v0.1.6 Tag不動，後續Git／R02仍依使用者授權。前段Windows「尚未啟用／待回歸」是此次接續前狀態。
