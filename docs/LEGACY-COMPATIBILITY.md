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

### W32：2026-10-20 現行規則

使用者重新指定 `[其他字樣]+open+[其他字樣]:///`，並明確確認 `wjopen:///` 也可以。共用 `IsLegacyOpenProtocol` 僅取第一個冒號前的 scheme，轉小寫後從索引1起找 `open`：前方至少一個字元，後方可空白，不限定 `hc`。`hcopen:///`、`hcopenprint:///`、`wjopen:///`、`wjopenprint:///`、`otheropen:///` 均允許；`open:///`、`openprint:///`、只在一般網址路徑含 `open` 及沒有冒號者不允許由此回呼交給系統。沿用 CEF 原有 URI 流程，不額外限制斜線或解碼內容。

依使用者「只要送出命令就好，不用驗證 windows 註冊」，程式只設定 CEF `allow_os_execution`，沒有登錄查詢、安裝檢查、處理器存在檢查或自行執行命令。Windows Release／CTest1/1、143項通過，已只替換本機交付EXE；外部開啟由使用者測試，Mac待macOS重編／實測。前述檢查及以下舊suffix規則保留歷史，不作為現行要求。

### W17：2026-10-20 修改前的 Windows 檢查

- 現行 `src/common/ini.cpp` 的 `IsLegacyOpenProtocol` 與舊現行 CP950 `fmMainOaClientu.pas` 的 `crmProtocolExecution` 一致：冒號前名稱長於四字元，且不分大小寫以 `open` 結尾。因此 `hcopen:///`、`HCOPEN:///file` 允許；`open:///file`、`mailto:`、一般 HTTPS 不允許由此回呼交給 OS。
- `BrowserClient.GetRequestHandler` → `GetResourceRequestHandler` → `LegacyProtocolHandler.OnProtocolExecution` 接線存在，依判斷設定 `allow_os_execution`。固定 CEF SDK 的回呼文件確認，這會嘗試使用 OS 已登錄的處理器；不是由 oaClient2 解析、解碼或執行 URI 內的檔案／命令。
- 提升權限的唯讀查詢：HKCU／HKLM `Software/Classes/hcopen` 的 Registry64 與 Registry32 均不存在；兩個 view 的 `UrlAssociations/hcopen/UserChoice` 及目前使用者 HKU Classes 路徑亦查無登錄。Windows Shell `AssocQueryStringW` 使用 `ASSOCF_IS_PROTOCOL` 查詢 open command／executable 均回傳 `0x80070483`（沒有對應的應用程式關聯）。目前查詢結果無法取得實際 hcopen 處理器，系統端關聯是後續實測的前置條件。
- 既有 W31 核心測試執行為 **123 checks／0 failures**，含接受／拒絕協定案例。首次受限執行曾有 INI 建立失敗並中止，不列為通過；重新在可使用測試暫存及合成 receiver 的環境執行通過。未修改／重新編譯來源；build 與本機交付 EXE SHA256 均為 `91ffcaceab028182599fb4fd5e0d40ad4cc887869967ffc84fbfb715e5289ee9`。
- 未新增登錄、未啟動 hcopen URI、未操作正式 OA／真正外部工具，CEF 點擊到外部程式的端到端驗證與 Mac 驗證均未執行。保留原「使用者自行測試」範圍；未提交、推送或發布。證據在 `artifacts/verification/windows-w17-hcopen-20261020/`。

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

## W36：印表字型與 FRX／Reptool 相容性查證（2026-10-30）

狀態：依使用者要求查清楚，已完成現行來源對照及隔離編碼重現；尚未修正產品，也未重建／更新交付。使用者補充 FRX 字型由 Reptool.exe 完成，本輪按此邊界追查，不新增宿主 FRX 引擎，不修改舊 oaClient64 或 oaReptool。

### 舊版完整責任鏈

1. 舊 oaClient64 的 fmMainOaClientu.pas:781～787 接收 `cmd=ini|key=report_font|val=字型名稱`，通用寫入 `[UserSet] report_font`，沒有原生字型選單或直接修改 FRX 的專用程式。
2. 同檔:2483～2504 的 OpenReport 把報表命令及當次 loginParam 作為第一個參數，Config.ini 路徑作為第二個參數，ShellExecute 呼叫 Reptool。
3. 現行 oaReptool/fmRepu.pas:1627～1647 在報表類型為 frx／fr3、範本存在時，讀取 `[UserSet] report_font`，預設值為「預設」。若值為「預設」，直接載入原範本；否則以 UTF-8 讀範本，不分大小寫將其中所有 `Arial Unicode MS` 替換為選定名稱，寫入 `tmp-<範本檔名>` 再載入；原範本不在這一步覆寫。
4. 這段不是將所有不同的 Font.Name 一律改寫；範本若沒有 Arial Unicode MS，不會因此換掉其他字型。它也不是 Chromium 網頁列印預覽的字型設定。

### oaClient2 已有的部分與確定缺口

- [app.cpp](../src/app/app.cpp):787～795 已有通用 cmd=ini → SaveUserSetting；[ini.cpp](../src/common/ini.cpp):237～248 寫入原鍵值，沒有排除 report_font。app.cpp:820～831 也已呼叫 LaunchReport，Windows [platform.cpp](../src/platform/windows/platform.cpp):451～466 傳入兩個參數及應用程式工作目錄。缺口不是整段 Reptool 呼叫未實作。
- **確定的編碼相容性缺口：** IniFile::Load:47～59 移除讀入的 UTF-8 BOM；IniFile::Save:71～95 直接寫 UTF-8 內容而不加 BOM。舊 Reptool 的 IUty.pas:279～300 使用 `TMemIniFile.Create(f)`，未指定編碼。本機 Delphi 2010 RTL IniFiles.pas:618～631／714～734 與 SysUtils.pas:22136～22180 證實：有 BOM 才識別 UTF-8，否則用 TEncoding.Default（Windows ACP）。本機 ACP=950，中文字型名稱會解碼錯誤，錯誤名稱再被寫進暫存 FRX，可能導致字型 fallback。
- 隔離 MSVC probe 直接編譯現行 ini.cpp 及 Windows platform.cpp，呼叫真正 SaveUserSetting，沒有替身保存邏輯。原始設定無 BOM／有 BOM 兩例，保存後均無 BOM；oaClient2 自行讀回「標楷體」成功，但同一檔案由 Delphi 21.0 TMemIniFile 讀取均錯誤，模擬原 StringReplace 結果亦不符預期。控制組 UTF-8 無 BOM 失敗，有 BOM 成功；先前 CP950 控制亦成功。證明「客戶端能讀回」不能取代 Reptool 中文相容驗證。
- 只在程式呼叫前手動替正式 INI 加 BOM 並非完整修法：下次 UserSet／Window 等任何保存仍會再次移除 BOM。建議最小方向是在 oaClient2 的唯一 INI 保存契約中採用可被舊 Reptool 識別的 UTF-8 BOM，並回歸內容不變不重寫／metadata／拒寫保護；**此為待實作建議，本輪未套用。** 不改為 CP950 全域儲存，不修改使用者維護的 Reptool／prg。

### 設定檔路徑與交付核對

- 現行 Reptool 的 IUty.StartIUty:115～129 由 Reptool.exe 目錄尋找 Config.ini，找不到才找上一層；其現行來源沒有使用 ParamStr(2) 設定 sAppIni_，儘管兩代宿主都有傳第二個參數。標準根 Config.ini＋prg/Reptool.exe 配置可走上一層，不能宣稱任意 ReptoolConfigIni 都已被舊工具接受。
- 查核時 oaClient2 交付 Config.ini 為 UTF-8 無 BOM、尚無 report_font；ReptoolPath／ReptoolConfigIni 空白（採既有預設），prg/Config.ini 不存在。未複製、輸出或修改其他個人偏好。舊 oaClient64 的根 INI 有 UTF-8 BOM 與 report_font 鍵；不自動匯入舊偏好。
- oaClient2 交付及舊 oaClient64/Bin/prg 的 Reptool.exe SHA256 相同：`0700d31d16b68c34ab2e05ea6ee970ee0d9b449bc2bf1fca5a29aeb6d2debd28`。只證明兩份檔案相同，不聲稱本輪已編譯或端到端驗證該 EXE 的 FRX 行為。

### 證據與未驗證項目

證據在 `artifacts/verification/windows-w36-report-font-audit/`：client_ini_probe.cpp、legacy_ini_probe.dpr、run-probes.ps1、編譯紀錄、probe-results.log 及兩份僅含合成 report_font 的 INI。第一次 CMake 在沙箱暫存目錄被 MSBuild 路徑隔離阻擋，保留失敗 configure 紀錄；改於正常本機暫存目錄後 MSVC Release／Delphi probe 完成。這些是隔離相容性測試，沒有重新編譯產品 EXE，也沒有執行產品 CTest 或啟動 OA／正式 Reptool。

尚未實測正式網頁選定字型 → Console 命令 → INI → Reptool → FRX 預覽／實際列印，不能將編碼缺口宣稱為使用者此次現象的唯一成因；目前 INI 未見 report_font，仍需在實際選定時確認設定命令是否送達。字型安裝狀態、正式範本／外部登入及非標準 INI 配置也未驗證。Mac Reptool 尚無原生替代方案，本輪未修改 Mac 專屬碼或交付，不把此 Windows 編碼重現套用成 Mac 報表已支援。

## W36 修正完成：0.1.7 UTF-8 BOM 與既有 INI 自動修復（2026-10-30）

使用者已明確授權修正、確認report_font保存、編譯供測試，並追加「對於已經產生的config.ini要可以自動修復」「進版」。本輪Windows交付升為0.1.7，取代前段僅查證／未修正的狀態；查證歷史保留。

產品最小差異為唯一共用ini.cpp：Save在UTF-8內容前固定寫一次BOM；LoadSettings讀取既有檔後走同一Save，在使用設定／建立瀏覽器前自動修復原先無BOM的UTF-8檔案。保留所有原鍵值、註解與既有LF保存規則，不從舊INI匯入或填入任何個人字型，也不補造未選定的report_font。已修復、內容相同就不重寫；真正拒寫／唯讀明確回報並停止啟動，不解除屬性或改ACL。CommitSettingsFile未修改，metadata替換、同步鎖fallback及原內容保護保持。

CMake專案版本、共用視窗標題／$g.client_version及Windows START紀錄改為0.1.7，未更改其他命令與事件時序。Mac平台碼／既有0.1.6.app未改；共用INI及版本修改須於macOS重編回歸，Mac入口自己的版本紀錄也留待該平台同步，不能宣稱Mac交付已升版。

Windows MSVC Release／CTest1/1、160 checks／0 failures（原143＋17）通過。新增檢查包含新INI BOM、原有／沒有BOM檔啟動修復、保留既有值與註解、重啟不改mtime、cmd=ini|key=report_font|val=標楷體、視窗保存後重啟、load-userset／$usr回填、「預設」及拒寫保留原位元組／唯讀屬性；原同步鎖／file identity／短內容截尾等測試仍通過。只有進版前後的必要建置，沒有變更CEF版本。

合成實機採獨立本機目錄及INI，tests/pages/report-font.html實際select change送既有Console命令。0.1.7畫面選「標楷體」及「新細明體」後均出現保存PASS、load-userset值一致；磁碟INI具有BOM且report_font=新細明體，其他合成欄位Keep=原值保留。正常Alt+F4關閉後重新啟動，選單、首個腳本偏好Cookie、$usr與load-userset均還原新細明體；兩輪SHUTDOWN_COMPLETE、全部程序退出。相同UI保存出的INI由未修改的Delphi21.0 TMemIniFile讀取，ACP950下MATCH=True、模擬原FRX替換結果正確。原有／無BOM控制經真正保存函式均由失敗轉為正確讀取。這不等於正式OA網頁選單、真正Reptool預覽或印表機已驗收，這些留給使用者測試。

工具前期以Junction提供CEF，遇到libcef載入error126；換成完整CEF測試副本後啟動正常。Computer Use在正常LocalAppData路徑的啟動辨識受Codex套件映射影響，最後依返回的實際視窗／執行路徑完成測試，未放寬profile保護。set_value對select未產生變更，改用可見原生選項點選驗證；不把工具無效操作算產品失敗。沒有將合成INI寫到正式交付。

交付僅替換artifacts/oaClient2/oaClient2.exe，與build一致，SHA256 `ebc31ebb1e8a56085b11c696b6149bf0e1300f420c4a4173197ede1f54899cc4`；528份保護檔案不變，包含正式INI、Reptool／prg／CEF、Mac來源與.app。正式INI仍保留交付前現況，使用者下次啟動0.1.7會自動修復，不需手動改編碼。Reptool來源／EXE／呼叫流程均未修改。測試server已停止，SDK／下載包／build保留，未提交／推送／建立Tag／發布。

證據artifacts/verification/windows-w36-ini-fix：baseline-status、ini-before／core-tests-before、build／build-0.1.7、core-tests.log、fixed-legacy-probe.log、ui-events.jsonl、ui-after-close.ini、ui-delphi-read.log、protected-before／protected-result及results.json。固定harness沿用前輪查證素材，前輪probe目錄的同名輸出為最新重跑結果；修正前結論與來源雜湊留於前輪results.json及本文查證段，不以修後輸出當修前證據。
