# oaClient2 內建 pet 資料

## W46：Windows pet 休眠喚醒恢復（2026-11-18）

Windows0.1.9本機EXE已補上電源恢復時的透明表面／動畫計時器重建，重新確認當前頁面登入並恢復通知連線；不刷新網站，手動隱藏保持。Release／CTest3/3（194核心＋18腳本＋15原生）及CEF合成通知／按鈕／登入登出回歸通過，實際硬體休眠／喚醒待使用者測試。正式交付已重開，目前未登入，需要重新登入；不用上傳API。本輪未提交／推送／發布，Windows公開ZIP仍W45。共用session有修改，Mac須目標平台重編回歸；既有M29來源與.app保留。詳見[進度](../../PROGRESS.md)W46。

## W45：Windows 上緣拖曳修正

2026-11-18 Windows0.1.9已修正透明訊息預留區造成的上緣限制：靠近上方時泡泡改放小熊下方，拖回下方恢復上方泡泡，重排保持小熊位置。下方泡泡的×、點擊開單及上緣雙擊已實測；Mac與API本輪不改，詳細見[進度](../../PROGRESS.md)W45。

## M27：Mac 0.1.9（2026-11-18）

Mac本機交付已包含相同24格動作、通知與訊息歷史，共用工作階段／CEF bridge／動畫保持唯一來源。平台使用透明NSPanel、bundle圖片及原生焦點／滑鼠穿透；MAC左側透明圖示可顯示／隱藏，登入後才顯示，登出／切站／關閉清除。單擊小跳歪頭星光、雙擊展開、↑／↓瀏覽，×／Esc收起保留記憶體訊息；拖曳不誤觸開單，泡泡沿用BSI020010編輯保護。

Mac Release／CTest3/3（177＋16＋10）、原生繪圖／透明度及簽章通過，合成CEF授權／補查／WebSocket喚醒與正常退出已測。獨立面板的滑鼠／方向鍵／Esc、跨App／最小化完整UI與正式OA通知待驗收；未部署API、安裝或發布。Windows抽取後MSVC／實機須另回歸，原EXE保持。完整[驗證範圍](../../PROGRESS.md)M27；下列「Mac不啟用」屬之前工作狀態。

## W44：小熊全部動作與滑鼠互動

Windows0.1.9已更新：呼吸、搖擺、待機招手、坐下／起身、伸懶腰、短程走路，43秒輪播；走路在原位置左側24像素內來回，閱讀訊息時停止自主動作。通知小跳揮手8秒。單擊本體在系統雙擊間隔後小跳、歪頭並出現星光，1.5秒後恢復；雙擊仍開訊息窗、拖曳只移動。登入後出現，登出／隱藏／關閉停止計時器。

素材與Windows資源已內嵌EXE，無新增後端協定或網址。Release／CTest2/2（186＋16）及原生合成動作／點擊／拖曳／通知開單驗證通過；實體方向鍵／Esc、多螢幕／其他DPI、長時間效能與正式通知端到端未重測，Mac不啟用。新圖[來源與提示詞](../../assets/desktop-helper/ACTIONS-PROMPT.md)及[雜湊](../../assets/desktop-helper/ACTIONS-MANIFEST.json)。

## W43：通知目標更正（2026-11-17，優先於早期範圍）

使用者明確更正為 **BSI020010 客戶詢報價**。主表 `qua`、單號 `quano`、單據日期 `quadt`；只通知後端今天的成功新增／修改，點擊亦開啟 BSI020010。更正取代原 BSI020020／ordno／orddt 範圍，不同時監看訂單。真正本機 API、快照及 Windows 0.1.9 已更新，正式主機未由代理部署；此次三份 PHP 都需上傳，重新登入後再測新儲存，先前修改不補發。檔案與限制見 [API-UPLOAD.md](API-UPLOAD.md)。

## W42：0.1.9 訊息操作

- 雙擊小熊本體展開泡泡；沒有訊息時顯示「目前沒有訊息」。
- 雙擊後以↑／↓切換上一則／下一則，到首尾不循環，泡泡顯示目前則數／總數。
- ×或Esc收起泡泡，保留本次登入的訊息以便雙擊回看；訊息只存記憶體，最多500則，登出／切站／關閉全部清除。
- 鍵盤瀏覽只在主動雙擊後取得焦點；切到其他地方後恢復不搶焦點，不攔截其他App的方向鍵。單擊訊息泡泡沿用開單及未儲存保護；本體單擊／拖曳不開單。
- Windows 0.1.9已建置交付；雙擊／重開已在原生合成頁確認，實體方向鍵及Esc仍待使用者驗收。Mac／後端／公開Release本輪保持，參閱[W42交接](../../HANDOFF.md)。

工作 ID：D05。日期：2026-11-17（Asia/Taipei）。

Windows 接續時可直接複製 [整合提示詞](WINDOWS-INTEGRATION-PROMPT.md) 全文。需要的素材與後端參考已放在本專案內。

## 最後確認的需求

- pet 整合為 oaClient2 內建功能，只有目前站台登入成功後才出現；未登入不顯示、登出立即隱藏，關閉 oaClient2 一起結束。
- 直接沿用 oaClient2 設定及目前載入的站台／API，不另設 pet 網址，不帶入前一版獨立程式的預設站台。
- 約 100 像素的小熊，右下角、可拖曳、透明置頂、待機眨眼、通知揮手；切到 Excel 或最小化主程式仍可通知。
- 只通知 BSI020010 單據日期為後端今天的 ERP 表單新增／修改；外部匯入與直接 SQL 不在範圍。

## 資源位置

| 資源 | 位置 |
| --- | --- |
| Windows 整合提示詞 | [WINDOWS-INTEGRATION-PROMPT.md](WINDOWS-INTEGRATION-PROMPT.md) |
| 小熊八格動作圖 | [bear-sprites.png](../../assets/desktop-helper/bear-sprites.png) |
| 動作示意 | [preview-idle-wave.gif](../../assets/desktop-helper/preview-idle-wave.gif) |
| 素材說明 | [assets README](../../assets/desktop-helper/README.md) |
| API 上傳清單／協定／路由 | [API-UPLOAD.md](API-UPLOAD.md) |
| 後端程式／測試快照 | [server/](server/) |
| 複製檔案 SHA-256 | [RESOURCE-MANIFEST.json](RESOURCE-MANIFEST.json) |

## 目前狀態

W40 已在 Windows 實作內建小熊、MAC 左側透明圖示 show／hide、泡泡右上角 ×、CEF 登入觀察與原生通知工作。實際建置／交付及未測項目見 [進度](../../PROGRESS.md)；Mac 專屬碼及 .app 不啟用、不變更。

後端協定仍使用原 3 個 PHP 檔與路由；W40 依追加要求在 `DesktopHelper.php` 加入既有 OACS 的無資料喚醒，並更新隔離測試。代理本輪未部署正式站。先前獨立 pet 的 C# 程式、EXE、安裝腳本、安裝包與 OA loopback 橋接不再使用，也不放入此接續包。

後端 W40 的 14 個測試、32 個斷言為前輪隔離結果；W41 已更新真正 API 來源及快照，兩份各在 PHP 8.2.33 通過 21 個測試、66 個斷言，另有 OACS／路由契約 6 項與既有客戶端腳本 15 項通過。`server/api/tests/Feature` 是 Laravel 測試快照；本專案 `tests/run-desktop-helper-php.ps1` 搭配唯讀 vendor 及獨立測試根目錄，不載入正式 .env。原始 D05 雜湊保留於 [RESOURCE-MANIFEST.json](RESOURCE-MANIFEST.json)；W41 後端現況見 [BACKEND-MANIFEST.json](BACKEND-MANIFEST.json)。

W41 只補齊真正 API 的無內容廣播與快取寫入失敗保護，保留原 Controller、事件、路由與 Windows 產品來源／EXE。使用者已登入的是正式站，本輪依指示只做隔離測試，不部署或操作正式單據；完整端到端仍待授權測試站。需上傳的三個 PHP、路由合併與 OACS 配套見 [API 上傳清單](API-UPLOAD.md)。

小熊只在 oaClient2 內使用；其他 App 只涉及背景通知、不搶焦點，不限定 Excel，也不整合外部 Chrome。隱藏小熊不登出；點 × 收起當次待顯示訊息，小熊仍在，新事件可再顯示。登入前點工具列不顯示，登出／切站／關閉立即停止當次通知；API 不可用不影響原 OA 功能。正式 API／OACS 與單據端到端仍待上傳及使用者登入驗收。
