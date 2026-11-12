# Windows 附件選檔格式修正提示詞

日期：2026-10-16（Asia/Taipei）。工作 ID：D04／W31；Mac 對應修正：M19。

使用者回報 Windows 有相同的附件選檔問題，要求建立本提示詞。本文在 Mac 建立，只整理 Windows 待辦，沒有修改、建置或更新 Windows 程式。

使用方式：Mac 先停止編輯、建置與 Git 操作，等待兩台 Dropbox 同步完成，再在 Windows 開啟同一個 oaClient2 專案，把以下提示詞交給 Windows 的 Codex。Windows 的實際專案路徑須在當地確認，不套用 Mac 絕對路徑。

## 可直接複製的提示詞

```text
請在 Windows 環境修正 oaClient2 的附件選檔格式問題（W31），編譯並更新本機 Windows 交付版供我測試。版本維持 0.1.6；這次不提交、不推送、不移 Tag、不打包上傳 GitHub Release。用繁體中文回覆，程式碼使用兩格空白縮排、不使用 Tab；新增註解格式為 //yyyy.mm.dd by codex, reason in english。

先確認 Mac 已停止編輯、建置與 Git 操作，兩台 Dropbox 同步完成。依序讀 AGENTS.md、HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md，再讀 docs/SHARED-CODE-RULES.md、docs/PLATFORM-PATHS.md、docs/ENVIRONMENT.md、docs/WINDOWS-USAGE.md。核對實際來源、Git 分支與未提交差異、conflicted copy／lock，不用 reset／checkout 覆蓋現有工作，也不要把 Mac 尚未提交的 M14～M19 及交接文件混成 Windows 新修改。

本文建立時本機 main HEAD 為 8d104ba7af6c75b91527a14a6d2b6ed64d03dc2b；M19 選檔修正與部分 Mac 歷史工作仍在工作目錄，不能只取 HEAD、遠端或 v0.1.6 Tag 而漏掉它們。這個 SHA 是接手定位資訊，不是要求退回該版本；以同步完成後的實際狀態核對並記錄。

問題與預期：
1. OA 的產品資料 BSI010010 → 工具列「圖檔」→「加入」→ 系統選檔視窗。網頁允許 pdf、png、jpg、xls 等多種格式，在 Chrome 操作正常；使用者回報 Windows oaClient2 也有只能選部分格式的相同問題。
2. 使用者提供的 Chrome 參考圖只有兩個格式選項：Custom Files（預設）、All Files。Custom Files 必須一次合併網頁允許的全部格式，不把每個 JPG／PNG／PDF／Excel 分成必須逐一切換的篩選器，也不預設只選第一個副檔名。All Files 是使用者明確選擇後解除格式篩選的選項。
3. 不把 pdf/png/jpg/xls 寫死為全站清單。每次都依該 input／CEF 回呼提供的 accept／副檔名及 MIME 展開結果建立篩選；不同頁面或欄位可以有不同限制。單選／多選、取消、回傳給原網頁的 FileList 與原 change 行為保持。All Files 不等於修改網站的檢核或允許伺服器接受所有格式。
4. 先在 Windows 實際重現，核對 input accept、CEF OnFileDialog 參數與原生格式清單／預設值，確認故障點；Mac 的原生對話框原因不能直接當成 Windows 根因。先查明後做最小修正，不修改正式附件資料來證明能選檔。

目前 Mac 已完成的參考（M19）：
- Mac 原 CEF 預設 JPEG image；格式選項藏在 Show Options，切到 PDF document 仍不可選，改所有檔案才可選。修正後以 NSOpenPanel 合併格式，預設 Custom Files，另提供 All Files，格式選項直接可見。
- Mac 已實測 .jpg/.png/.pdf/.xls/.xlsx 五檔同時選取與回傳；MIME image/*、application/pdf、XLSX 的展開／篩選；PNG 單選、All Files 選 TXT、取消／再次開啟與既有無限制／目錄流程。使用者回覆「我剛剛測試 oaclient2 附件 正確」，只代表本次 Mac 附件修正驗收，不代表 Windows 已通過。
- Mac Release／CTest1/1、116 checks／0 failures、arm64／簽章及本機交付核對通過。這些核心測試項數不是 Windows 目前預期項數，也不是選檔 UI 驗證的替代品。
- Mac 已更新 artifacts/macos-arm64/oaClient2.app；主執行檔 SHA256 為 9388faa75d04e2aaf8df5e4105b0fcd6632ac4b901aec8f55f6b0ee82190b3e2，版本 0.1.6，未更新公開 Mac ZIP。證據在 artifacts/verification/macos-m19/results.json 與紀錄；UI 截圖在原對話工具結果，沒有另外保存 PNG。

現有接線與實作邊界：
- src/app/app.h 的 BrowserClient::GetDialogHandler 已呼叫 PlatformFileDialogHandler()，沿用這份共用接線，不再造 Windows BrowserClient 或附件／工具列副本。
- src/platform/cef_platform.h 目前只有 OS_MAC 宣告平台 factory，其他平台 inline 回傳 nullptr；所以目前 Windows 仍沿用 CEF 預設選檔，不會因 Mac M19 已完成而自動修正。
- src/platform/macos/file_dialog.mm 與 Mac CMake 的 UniformTypeIdentifiers 是 Mac 專屬參考，只讀、不修改、不複製到 Windows。共用 app／INI／UserSet／命令／登出保持唯一來源。
- Windows 實作放 src/platform/windows，透過既有 factory 接回；僅對平台宣告／Windows CMake 來源清單等必要共用介面做最小調整，保持 Mac declaration／實作及建置分支可沿用。不要讓 Windows 仍走 inline nullptr，也不要引入重複定義或把 Win32／COM 放進共用 app。
- 優先核對固定 CEF 可支援的最小修正。若需要 Windows 原生 IFileOpenDialog，建立合併的 Custom Files filter（例如把回呼展開出的副檔名以分號組合）與 All Files，預設第一項，保留 Unicode 檔名／路徑、正確 owner、檔案存在條件與原多選 mode；取消不得誤送空檔名或成功回呼。
- 先讀本機固定 CEF 的 cef_dialog_handler.h。OnFileDialog 可能在 MIME 展開前／後各回呼一次；accept_extensions 尚未完整時交回 CEF 等待展開，不自行猜測 MIME 清單，也不因空／不認識的格式靜默放寬 Custom Files。非本次處理範圍交回原流程。
- 保留儲存檔案／列印 PDF 的 Save 對話框、選目錄及無 accept 限制的既有行為。原生視窗／非同步 CEF callback 的執行緒、生命週期與單次完成要正確；不可用阻塞等待迴圈卡住 CEF UI。實測取消後可再開，不殘留對話框或卡住程式。
- 不修改 OA 網頁、附件資料表或共享 JavaScript；本次修正在 oaClient2 客戶端。若有真正必要的額外行為變更，先提出具體差異，不能藉此重寫上傳功能或調整無關設定。

建置與實機驗證：
- 沿用 docs/ENVIRONMENT.md 的 C++20、MSVC x64 Release、固定 CEF 154.0.34 Chrome runtime，以及現有 Windows build／package 腳本；先核對腳本參數與本機 SDK 路徑。不升級 CEF、不開啟沙箱或改主網站宿主。SDK／下載包／build 放 Windows 本機非同步目錄，完成後保留。
- 沿用 tests/pages/file-dialog.html 作為同一份跨平台測試頁，不複製成 Windows 版本。依 tests/serve-contract.py 的實際參數啟動 localhost；該頁不傳輸檔案，只顯示檔名。準備明確的本機拋棄式副檔名素材，不用正式敏感附件；不要把檔名篩選測試說成內容解碼或正式上傳成功。
- 真正以 Windows 新建置的 EXE 開啟選檔視窗，確認 Custom Files／All Files 兩項及正確預設、五種允許格式同時可選、未允許 TXT 預設不可選、MIME 類型正確展開、PNG 單選與多格式多選、All Files 可選其他格式、取消／ESC與重開、檔名回到原 input。加入中文檔名／含空白路徑，確認文字未損壞。
- 回歸無格式限制／選目錄／原儲存對話框，並測選檔期間關閉父視窗或結束程式的 callback 清理，不造成重複回呼、卡住或殘留程序。若對相關路徑未做實測，明列未執行。
- 核心 CTest 與實際 checks 數、Windows 原生 UI、正式 OA 使用者驗收分開記錄；Mac 116 checks 與 Mac 使用者回報不能替代 Windows 結果。合成測試不送出正式 OA 附件，BSI010010 實際業務操作由使用者驗收。
- 測試不要永久修改 HomeUrl、不注入合成 UserSet／個人 INI；先確認隔離／命令列測試方式可用。保持正常關閉後的實際設定現況，不回寫過期快照。若需要重啟原 OA，說明既有啟動清理會清除網站登入狀態。

交付與資料保留：
- 先正常關閉正在使用的 Windows oaClient2，再更新 artifacts/oaClient2/oaClient2.exe；CEF 版本不變時原則上只更新 EXE，不混入新 CEF DLL。比對 build／交付 EXE SHA256，確認實際測的是本輪 x64 新版，維持 0.1.6。
- Windows Config.ini／picture 在 EXE 旁，CEF 在 cef/，專用網站資料／紀錄在 LocalAppData；不得改成 Mac Application Support 配置。保留個人 INI、picture、tpl、下載與既有檔案；prg 由使用者維護，不補回、不覆蓋、不刪除工具，Reptool 原呼叫契約保持。
- Mac 平台碼、.app、Mac ZIP／公開資產保持；必要共用 header 修改要記錄 Mac 編譯回歸待辦，不在 Windows 宣稱 Mac 已重新驗證。不得在 Windows 修改 Mac 專屬實作。
- 更新 W31 的 HANDOFF.md、PROGRESS.md、PROJECT-PLAN.md、CHANGELOG.md 與必要操作文件，記錄涉及檔案、原因、實際建置／核心／Windows UI、使用者驗收、保護檔核對、未測／失敗項目及下一步。不要把本提示詞當成 Windows 已實作或交付。
- 未提交的 Mac 工作與既有文件差異保留。此次只交付本機 EXE，沒有新的 Git／Release 授權；不自行提交、推送、重新發布或移 Tag。其他列印／注音／OA／Reptool 待驗收及 U01 線上更新未實作狀態保持。

請在 Windows 完成查證、最小修正、編譯／實測與本機交付，讓我測試附件功能。
```

## 相關檔案

- [目前交接](../HANDOFF.md)、[進度與 M19 證據範圍](../PROGRESS.md)。
- [平台 handler 介面](../src/platform/cef_platform.h)、[共用 BrowserClient 接線](../src/app/app.h)。
- [Mac 參考實作](../src/platform/macos/file_dialog.mm)、[共用測試頁](../tests/pages/file-dialog.html)。
- [Windows 建置環境](ENVIRONMENT.md)、[平台資料路徑](PLATFORM-PATHS.md)、[共用來源規則](SHARED-CODE-RULES.md)。
