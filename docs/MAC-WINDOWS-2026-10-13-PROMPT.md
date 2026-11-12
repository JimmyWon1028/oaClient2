# Mac 接續 Windows 今日共用功能提示詞

> 2026-10-30：此份 W27～W29 接續已由 Mac M14～M19 後續工作完成；最新請改用 [W32～W35 提示詞](MAC-WINDOWS-2026-10-30-PROMPT.md)。下文保留當時基準，不能當作目前 Mac 尚未實作或最新來源。

更新：2026-10-13（Asia/Taipei）。工作 ID：D04；範圍：W27～W29 的 Mac 接續與既有功能回歸。

Mac 已完成 arm64 移植及 M01～M13，這次主要沿用最新共用來源，補齊 Windows 今日新增的連結提示、密碼保存政策與快捷鍵修正，不重做平台移植。歷史見 [HANDOFF](../HANDOFF.md)、[PROGRESS](../PROGRESS.md) 與 [CHANGELOG](../CHANGELOG.md)。

使用方式：Windows 先停止編輯、建置與 Git 操作，等兩台 Dropbox 同步完成，再在 Mac 的 Codex 開啟同一個 oaClient2 專案，把下方整段貼上。本文件建立於 Windows，沒有在 Windows 修改或編譯 Mac 專屬程式。

## 可直接複製的提示詞

```text
請在 macOS 環境接續同一個 oaClient2 專案，把今天 Windows 新增的共用功能補到 Mac 交付版。只支援 Apple Silicon arm64；使用繁體中文回答，程式碼兩格空白縮排、不用 Tab，新增註解依 AGENTS.md 格式使用英文。

先確認 Windows 已停止編輯、建置與 Git 操作，兩台 Dropbox 同步完成。核對 Mac 本機 Git 分支、遠端 SHA、來源差異、conflicted copy 與 lock；不要兩台同時操作同步中的 .git。未提交的提示詞／交接文件須先辨識，不用 reset／checkout 覆蓋尚未核對的變更。

依序讀取 AGENTS.md、HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md；再讀 docs/ENVIRONMENT.md、docs/MACOS-USAGE.md、docs/WINDOWS-USAGE.md、docs/SHARED-CODE-RULES.md、docs/PLATFORM-PATHS.md、docs/LEGACY-COMPATIBILITY.md、docs/RELEASES.md，最後核對實際來源與腳本。歷史的「Mac 尚未實作／Windows 尚待回歸」不可當成目前狀態。

來源基準：
- 分支 main，origin 為 https://github.com/JimmyWon1028/oaClient2.git。
- 最新已確認推送的交接提交：cb68ba20a7c1862cd58f851c3a3c1940cf555a05。
- Windows W29 實際建置來源：6f2833b7f7789509abb8f4b60d9b3ea0e0daa01f；後續 cb68ba2 只補發布文件。
- W27 共用設定來源在 7958a60，W28 在 c5cd549，W29 在 6f2833b；這些已在同一 main，不需逐筆 cherry-pick 或重新複製功能。
- 版本維持 0.1.6，不自行進版。v0.1.6 annotated Tag 物件仍為 67e296794c1db526e2afc729e4b170f95d09bf5b，來源 0fe6f357173fb7802cca8504c2ea007dd5e7834d；不能移 Tag 或把 Tag 舊來源當成最新 binary 的來源。
- Windows 最新 EXE SHA256：b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a；公開 ZIP SHA256：849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046。只供保護 Windows 交付，不是 Mac 建置依賴。
- 若接手已有後續合法提交，以實際 Git／文件核對並記錄，不強制退回上述 SHA。

Mac 現況：
Mac arm64 0.1.6 已完成 M01～M13，包括空白網址歡迎頁、隱藏縮放彈窗、背景 logout／三秒退出、Config.ini 所在目錄、網站動態標題及完整工具列字樣。既有 Mac .app／公開 ZIP 尚未套用 W27～W29；Windows 編譯與使用者驗收不能替代 Mac。不要因這次接續重建平行專案或重寫已完成的功能。

本輪主要完成以下三項，沿用同一份 src/common、src/app：

1. W27：不顯示左下角連結狀態提示。
   共用 src/app/app.cpp 的 App::CreateMainWindow 已設定 CefBrowserSettings.chrome_status_bubble=STATE_DISABLED。直接編譯沿用，不修改 OA 選單 JavaScript、不另建 Mac 選單副本。實測滑鼠移到 javascript:void(0) 選單／子選單與一般連結時沒有 Chrome 左下角提示，點擊原動作仍正常；區分瀏覽器提示與網頁本身的狀態／hint。

2. W28：登入後不跳「要儲存密碼嗎」。
   共用 App::OnContextInitialized 在任何頁面建立前，用 CefRequestContext::GetGlobalContext()->SetPreference 將 credentials_enable_service、credentials_enable_autosignin 設為 false，再建立 client、回填程式偏好 Cookie 和主視窗。設定失敗須明確回報並停止啟動，不靜默保留可保存密碼的政策。
   沿用共用來源，不另寫 Mac 密碼管理器、不修改 OA 登入表單、不加個人 INI 欄位，也不用舊版失效 switch。確認 Mac 固定 CEF 支援這兩個偏好，啟動紀錄有 PASSWORD_SAVING_AND_AUTO_SIGNIN_DISABLED、沒有 PASSWORD_POLICY_FAILED。測試原生表單與 AJAX 送出、重啟後政策再套用，沒有保存／更新密碼提示且表單仍能運作。
   保留 userid、公司別及其他 UserSet 回填；不保存或還原密碼、網站登入 Cookie／token。credentials_enable_service=false 是停用保存詢問，不能單憑此宣稱所有既存密碼填入功能皆已禁用；專用網站資料的啟動清理契約保持。

3. W29：取消與網頁設定衝突的 Chrome 熱鍵，讓網頁收到真實按鍵。
   清單為 F1、F2、F3、F4、F9、Alt+W、Mod+F、Shift+F、Mod+E、Mod+S、Mod+N（包含 Ctrl+N）；Mod 指 Ctrl 或 Cmd。只取消指定客戶端／Chrome 預設動作，不取消 OA 網頁自己的快捷鍵。
   沿用 src/common/keyboard.h 的 IsWebsiteShortcut、src/app/app.cpp／app.h 的 OnPreKeyEvent、OnKeyEvent，以及 SetPreferAccelerators(false)。OnPreKeyEvent 標記指定 shortcut 並回傳 false，讓 renderer／JavaScript 先收到；OnKeyEvent 在網頁有機會處理後才停止指定 Chrome fallback。不可在前置回呼直接吞掉按鍵，也不可 ExecuteJavaScript 人工重送假 keydown。
   Mac 需實測 Cmd+F／E／S／N、Ctrl+F／E／S／N、F1～F4／F9、Option（Alt）+W、Shift+F；功能鍵若需 Fn，記錄實際鍵盤／系統設定，不修改系統設定冒充通過。確認 Cmd+N 不開 Chrome 新視窗、Cmd+F 不開瀏覽器搜尋、Cmd+E 不把焦點送進網址列、Cmd+S 不跳網頁儲存對話框，網頁仍收到事件。
   用網頁會 preventDefault 及不會 preventDefault 兩種情境確認，不只測 JavaScript 取消預設的頁面。回歸文字輸入／Shift+F、焦點、未列出的組合、複製／貼上／全選／還原及正常窗口操作。原 F8、F12、Ctrl+P 高優先功能與工具列命令保留；Mac 既有 Cmd+P 列印行為保持，正式列印預覽仍由使用者驗收。
   若 Cocoa 選單／keyEquivalent 或 Chrome 保留加速鍵在 CEF 回呼前攔走指定組合，先定位事件路徑，再於 macOS 做最小平台修正；不要複製 common/keyboard.h 或重寫 Mac 清單，不擴大成停用全部 macOS 系統快捷鍵。

Windows 已驗證的範圍：
- W27：Windows Release／合成選單與子選單動作正常，沒有狀態提示。
- W28：Windows Release／74 項核心，舊版同一合成表單會提示；修正版原生及重啟 AJAX 送出無提示，正式 OA 登入未因此宣稱通過。
- W29：Windows Release／CTest 1/1、110 checks／0 failures（原 74＋36 項按鍵政策）。使用者要求自行測試，之後回覆「可以了」，只記錄 Windows 熱鍵驗收；代理未完成的逐項 UI 矩陣仍為未執行，Mac Cmd 實機未驗證。
- Windows ZIP 已公開、240 檔 CRC／SHA256 與無登入下載兩檔一致；壓縮／下載核對不是功能驗收。

完成 W27～W29 後回歸既有 Mac 功能，不重寫：
- 空白 HomeUrl 歡迎頁、設定按鈕／網址對話框、X／ESC 取消、不合法網址拒絕、有效 HTTP／HTTPS 確認後保存及重啟；已有個人網址不覆蓋，歡迎頁 data URL 不寫入 INI。
- 放大／縮小無 Chrome 縮放彈窗，100% 還原、UserSet.ZoomPercent 保存及重啟套用。
- 瀏覽目錄仍用 paths.config.parent_path()，開啟實際 Mac Config.ini 所在目錄。
- 標題由 document.title 經 OnTitleChange 更新；未取得名稱為「oaClient2 [用戶端版本 0.1.6]」，取得後為「網站提供的名稱 [用戶端版本 0.1.6]」，不寫死公司名稱或使用舊版日期。
- 右側工具列維持 23／23／40／67／38／61／23／23 DIP，合計 298，內部左右各 2 DIP；完整字樣、左 Console 30 DIP、原圖示／字型／命令保持。
- Console、一般 popup／重新開啟、網址／輸入焦點與最大化保持。主網站仍為 CEF Views Chrome BrowserView，Console 獨立 Chrome CefWindow，不回到原生子視窗宿主，不在同一 Views Window 加第二個 Chrome BrowserView／Alloy DevTools。
- 關閉送出 logout 一次、立即隱藏主窗／Console；loginState=0 ACK 提早完全退出，無回應最多三秒；beforeunload 不阻擋、不重送／延長期限，全部本程式窗口／Helper 結束。三秒到期不代表伺服器登出成功；正式 OA 登出仍依使用者驗收。
- UserSet／userid／公司別、cmd=ini、load-userset／$tmp.userSet／func、$usr 契約保持。啟動清除專用網站資料，只回填 INI 程式偏好，不還原密碼／token，loginParam 不持久保存。

共用測試素材：
- W27：tests/pages/status-hint.html，搭配 tests/serve-contract.py。
- W28：tests/pages/password-save.html，搭配 tests/serve-password-save.py；只用 localhost 合成值，server 丟棄表單值、只記 route／時間，不用正式帳密。
- W29：tests/pages/keyboard-shortcuts.html，搭配 tests/serve-contract.py；?handled=0／1 分別為不取消／取消預設，記錄真實 keydown。
- 回歸：tests/pages/legacy-contract.html、tests/pages/background-close.html。
- 先讀腳本參數；事件檔放 artifacts/verification 的本輪 Mac 子目錄，先建立父目錄。server 綁 127.0.0.1:8765，同時只開一個，完成後正常停止。
- --url= 只覆寫當次測試導航，不能永久改使用者 HomeUrl。結束保留使用者當前設定，不回寫過期快照，不把正式帳密／個人 INI／登入參數存進證據或公開 Git。

平台與交付邊界：
- Mac 完整交付 artifacts/macos-arm64/oaClient2.app，拖曳到 /Applications 是既有安裝方式。本輪先只更新交付，不自動覆蓋已安裝版本；若使用者另授權安裝，再正常關閉並替換完整 bundle。
- Mac Config.ini、picture、logs、browser-profile、instance.lock 全部在 ~/Library/Application Support/oaClient2/，CEF Framework／Helper／圖片在 bundle。不讀 Windows 個人 INI，不補回曾清除的 app 旁 INI／picture／.DS_Store。
- Windows Config.ini／picture 仍在 EXE 旁，CEF 在 cef/，網站資料與紀錄在 %LOCALAPPDATA%/oaClient2/data；不把 Mac 路徑／Cocoa／Framework 配置套用到 Windows。
- Mac 平台碼只在 macOS 修改；Windows 平台碼、artifacts/oaClient2、Windows ZIP、prg 不變。Reptool／原參數及檔案保持，Mac 報表未實作；不在 Mac 執行或把 Windows DLL／prg 當依賴，不補回已刪工具。
- src/common／src/app 保持唯一來源，只需編譯生效就直接沿用；真正需改共用介面時做最小差異、記錄 Windows 回歸待辦，不在 Mac 宣稱 Windows 已重新驗證。
- CEF 沿用已核對的 154.0.34 Chrome runtime arm64 配套。先用 Mac 保留的 SDK／原下載包／build，缺失才下載同版並校驗。不使用沙箱，不額外關閉網頁安全或忽略憑證。
- SDK／中間建置放 Mac 本機非同步目錄，不共用 CMakeCache／二進位／個人設定，不放 Dropbox／Git；完成後保留 SDK、下載包、build，不自動清理。

建置、驗證與紀錄：
核對 native arm64 與本機 CEF_ROOT／OA_BUILD_ROOT，沿用 bash scripts/build-macos.sh（Release／CTest／codesign）及 bash scripts/package-macos.sh，不另寫平行建置流程。核對主程式／全部 Framework／Helper Mach-O 架構、codesign --verify --deep --strict、build／交付逐檔與連結一致；編譯／簽章不是實機行為驗收。

先在 Mac 編譯並處理必要相容差異，再做核心／合成實機測試；項數以實際結果記錄，不套用 Windows 110 或舊 Mac 75。正式列印預覽與一般注音由使用者驗收，Windows 額外浮動注音組字窗不是 Mac 待測項目。若使用者要求「編譯好，我測試」，即交付可測 app，UI 未測項目明列，不能寫成通過。

更新 W27～W29 Mac 回歸、PROGRESS、HANDOFF、PROJECT-PLAN、CHANGELOG、MACOS-USAGE／SHARED-CODE-RULES 等必要文件；沿用穩定工作 ID，新增 Mac ID 前確認未占用。分開記錄實作、編譯、核心測試、Mac 實機、使用者驗收、共用修改的 Windows 回歸、未測／失敗項目與下一步；歷史不全面改寫，最新入口清楚標示 Mac 是否真的更新。

版本維持 0.1.6，完成交付先供使用者測試。先前同版重新上傳授權已執行於 Windows，不據此直接替換 Mac Release 或自動安裝。後續 commit／push／Mac ZIP 上傳依實際使用者授權及 docs/RELEASES.md 處理，不重新詢問已明確授權的同一操作、不移 Tag、不改 Windows 資產。若獲授權發布，ZIP 只含完整 .app，排除個人 INI／cache／profile／picture／logs／Finder metadata，生成 .sha256、核對 bundle／公開下載，明列實際來源提交，不把舊 Tag 來源當成新 binary。

U01 線上更新保留 Windows／Mac 計畫，尚未實作；不因手動 Releases 下載／移植宣稱完成。請先核對上述狀態，完成 Mac 沿用共用來源的編譯、驗證與交付。
```

## 本文件的工作邊界

- W27～W29 共用變更已備妥，Mac 尚未為這三項重編／實測。
- Windows 今日 W21～W26 是 Mac 已有功能的接線／回歸，不是要複製到 Mac 的第二套實作。
- 本文件建立沒有修改程式、CEF、版本、Tag、已安裝 App 或交付產物；Mac 結果以目標平台驗證為準。
