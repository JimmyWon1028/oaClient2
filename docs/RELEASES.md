# 編譯版本下載與Release紀錄

2026-10-13。工作ID：R01（Mac首次公開下載）、R02（Windows後續補齊）。

Repository：[JimmyWon1028/oaClient2](https://github.com/JimmyWon1028/oaClient2)。下載入口：[Releases](https://github.com/JimmyWon1028/oaClient2/releases)。編譯產物透過Release資產提供，SDK／build／個人資料不放Git。

## 本次Mac配套

版本0.1.6，僅Apple Silicon arm64，以初版測試版本發布。下載ZIP內只有完整oaClient2.app，CEF Framework／Helper／原圖都在bundle內；不包含Config.ini、快取、profile、logs、picture或Finder metadata。ZIP：oaClient2-0.1.6-macos-arm64.zip，大小144461135 bytes，SHA256：8f1cdbdf81990f78eebbf9e79be9e7c8001f4fff240a0b4c07d40f3a929a6493。

在下載目錄執行 `shasum -a 256 -c oaClient2-0.1.6-macos-arm64.zip.sha256`，解壓後將.app拖到Applications。Config.ini及執行資料由啟動／設定後建立在Application Support/oaClient2，不由壓縮包提供。更新前正常關閉，再替換完整.app，保留設定與截圖。簽章為ad-hoc，未有Developer ID／公證；實際驗證及待驗收項目見[Mac操作](MACOS-USAGE.md)與[進度](../PROGRESS.md)。

## 可重現打包與發布

Mac依原build／package腳本產出剛建置的.app，再以 `ditto -c -k --norsrc --keepParent artifacts/macos-arm64/oaClient2.app artifacts/releases/oaClient2-0.1.6-macos-arm64.zip` 製作ZIP，建立同名.sha256。發布前檢查內容排除個人組態及全部網站資料，解壓逐檔／連結比較、codesign與全部Mach-O架構核對。發布後以公開URL重新下載，核對GitHub大小／digest及本機SHA256。保留本機CEF SDK／壓縮檔及build，不安裝測試產物。

首次Release用v0.1.6 Tag固定本輪來源，發行說明列出已驗證／未驗收狀態。禁止移動已發布Tag或用其他來源冒充相同binary；後續Windows資產記錄其實際build commit及版本，若版本改變建立對應新Release。保留既有Mac資產，不覆寫或刪除。

## Windows後續

使用者已明確要求Windows先在Windows環境完成W21～W26與共用來源回歸，成功編譯／實機驗證後再補Releases。Windows以ZIP交付，排除個人Config.ini、快取、profile、logs、picture；不從根prg補回使用者已刪除工具。未完成前不發布既有舊Windows產物充當新版。

Releases下載不等於程式內線上更新；U01仍尚未實作，更新來源／版本策略與安裝重啟流程另行設計。


## R01 首次發布結果（2026-10-13）

[v0.1.6初版測試Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)已公開，提供[Mac arm64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-macos-arm64.zip)及同名.sha256。Tag固定來源提交0fe6f357173fb7802cca8504c2ea007dd5e7834d；程式／資源／建置內容與M13提交655a6a1相同，後續提交只補發布文件，不移Tag。

兩個資產的GitHub大小及SHA256 digest與本機相同；不帶登入憑證從公開URL重新下載，ZIP及校驗檔均逐位元一致，ZIP CRC亦通過。ZIP大小144461135 bytes，SHA256：8f1cdbdf81990f78eebbf9e79be9e7c8001f4fff240a0b4c07d40f3a929a6493；無Config.ini、快取、profile、logs、picture或Finder metadata。詳細證據在本機artifacts/verification/releases-v0.1.6/results.json，不納入Git。

Windows本輪沒有Release資產，R02仍待Windows環境成功編譯及實機測試後補齊。GitHub下載入口沒有完成U01程式內線上更新，亦沒有替使用者安裝程式。


## R02 Windows建置／實測已完成（2026-10-13）

Windows W21～W26已在MSVC與真實CEF完成本輪回歸，交付EXE已更新，SHA256：9b60d756ee39ca6dc3725e4e608f3d63ac18f1602b69c9bf43c53d32fc7daed2；結果見[進度](../PROGRESS.md)。本輪功能來源尚未提交，沒有製作Windows ZIP或公開發布。後續依使用者授權提交／推送與製作不含個人INI／快取的ZIP，記錄實際來源提交；既有v0.1.6 Tag與Mac資產保持不動。列印／Microsoft注音／正式OA登出仍待使用者驗收，U01未實作。

## R02 Windows公開發布結果（2026-10-13）

使用者要求先commit、push再打包發布；W21～W27實際Windows建置來源為7958a60fc75a35d4387a028ab8ccfb73e98200c0，已透過Git Credential Manager的HTTPS登入推送至main，與遠端核對一致。完成登入後push成功但本機origin/main更新失敗，之後fetch已恢復一致。後續發布文件／腳本提交不變更應用來源，最新main以Git核對。

既有[v0.1.6初版測試Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)已新增[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)與[SHA256校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)。ZIP大小189879293 bytes，SHA256為4d765e6d5748ce3d5768dd6ef5ed431d27dbcb13f07647f4aa71cc480ec0feb2；主程式SHA256為e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c，取代前段W21～W26的9b60d756交付，版本仍0.1.6。

ZIP根目錄oaClient2/包含240檔：主程式、安全Config.example.ini、234份CEF（含CEF-LICENSE.txt）及既有精簡prg的docto.exe／Reptool.exe／TSCLIB.dll／zint.dll。沒有個人Config.ini、picture、logs、profile、cache、tpl報表範本、SDK／build或Mac資料，不從根prg補回工具。Windows EXE與libcef.dll的AMD64 PE架構核對通過；prg沿用既有工具架構，不宣稱所有舊工具皆為64位元。

本機ZIP CRC及全部240檔SHA256與交付一致；發布後未帶登入憑證重新下載ZIP與.sha256，兩檔與本機逐位元一致，GitHub大小／digest與公開下載CRC通過。既有Mac兩資產的ID／大小／digest不變，本機Mac專屬來源及產物、prg／picture／tpl共275份保護檔案雜湊不變。v0.1.6 annotated Tag物件仍為67e296794c1db526e2afc729e4b170f95d09bf5b，來源仍0fe6f357173fb7802cca8504c2ea007dd5e7834d，沒有移動；Release明列Windows使用後續7958a60來源。證據在artifacts/verification/releases-windows-v0.1.6/results.json／package.json／release-before.json／release-public.json，不納入Git。

可重現打包使用[scripts/create-windows-release.py](../scripts/create-windows-release.py)，僅Python標準函式庫；從目前artifacts/oaClient2讀取安全清單，不修改交付或補回prg。遇到非二進位prg／未知CEF檔案／既有輸出會停止，須核對再另選輸出檔案。首次製作命令如下，已有ZIP不重跑覆寫：

```powershell
python scripts/create-windows-release.py --output artifacts/releases/oaClient2-0.1.6-windows-x64.zip --evidence artifacts/verification/releases-windows-v0.1.6/package.json --source-commit 7958a60fc75a35d4387a028ab8ccfb73e98200c0 --expected-exe-sha256 e56d3d3285bd71a4f0e6791c011a6cf7b45e1eedebdece23e55b90217bbf8b7c
```

下載後以PowerShell執行`Get-FileHash .\oaClient2-0.1.6-windows-x64.zip -Algorithm SHA256`比對.sha256；解壓後執行oaClient2/oaClient2.exe。新安裝HomeUrl空白，從歡迎頁設定；更新前正常關閉，保留自己的INI／picture／prg／範本，不把公開ZIP覆蓋視為設定遷移或程式內線上更新。

本次打包／發布沒有重新編譯或擴大驗收，沿用Windows MSVC Release／CTest1/1、74項與W21～W27實機結果。列印預覽／最新版Microsoft注音、正式OA登入登出／Reptool／hcopen及最終間距待使用者驗收；其他DPI、晚建立Console／一般popup競態未獨立實測。W27共用設定待macOS重編／實測，既有MacZIP未套用；SDK／下載壓縮檔／build保留，U01尚未實作。


## W28本機修正與既有ZIP差異（2026-10-13）

W28儲存密碼提示修正已在Windows建置／合成實測並更新本機EXE，SHA256 fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474，仍為0.1.6。既有Windows ZIP保持W27的e56d3d32、來源7958a60與原ZIP SHA256，本次尚未提交／推送／打包／重新發布，不宣稱下載資產已有W28。v0.1.6 Tag及Mac資產不變，後續版本／發布依使用者授權，不移Tag或靜默覆蓋已公開同名ZIP。

## R02／W28：同版Windows ZIP重新上傳授權（2026-10-13）

使用者明確要求「重新打包上傳，不要進版」：維持0.1.6，提交／推送W28實際來源供發布追溯，重新打包已建置及合成實測的本機EXE，替換既有v0.1.6 Release同名Windows ZIP與.sha256。先完成新ZIP及遠端上傳校驗，才替換指定Windows兩資產；保留舊ZIP及雜湊作歷史證據，更新Release說明與下載校驗結果。Tag不移動、不建立新版本，Mac資產不改，個人INI／網站資料／picture／logs／tpl不打包，現有prg4份不補回。前段「本輪未提交／ZIP仍為W27」是此次重新發布授權前狀態。


## R02／W28 最新下載：0.1.6同版替換結果（2026-10-13）

使用者明確要求同版重新打包上傳，Windows公開同名ZIP與.sha256已替換為W28，版本仍0.1.6，不移動已發布Tag或修改Mac兩資產。Windows實際來源為c5cd54939caf34d14bd7395fb4f7073b6a134e3c，已推送；後續發布文件提交不變更App來源，最新main以Git核對。前段「ZIP仍為W27／未發布」及舊189879293大小、4d765e6d雜湊為歷史。

最新[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)：189879887 bytes，SHA256 **92c371f3560daab3c23de117bb62d11b893be72530b045dbb5b20b8603e24099**。下載[最新校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)比對；EXE SHA256為fb57aac7e2400c22ffcca61e7d00cba22d741fdd59145a0eb9ddc0a4be61f474。相同版本檔案已更新，不能使用舊ZIP的校驗值。

本輪使用既有安全腳本，輸出artifacts/releases/windows-w28/oaClient2-0.1.6-windows-x64.zip，source-commit為c5cd54939caf34d14bd7395fb4f7073b6a134e3c、expected-exe-sha256為上述fb57aac7；完整本機已測EXE／安全範例／CEF234／現用prg4共240檔，CRC及逐檔SHA256通過，不含個人INI／picture／logs／網站資料／tpl／SDK／build。沒有從根prg補回工具或重新建置App。

先以暫名上傳並核對兩檔大小／digest，完成後只刪除原Windows兩資產並將新版改為原名；原Mac兩資產ID／大小／digest不變，Tag仍為67e296794c1db526e2afc729e4b170f95d09bf5b→0fe6f357173fb7802cca8504c2ea007dd5e7834d。新版Windows資產ID635859578／635860492，Release ID411036061不變。原公開URL無登入下載ZIP／校驗檔與本機／GitHub完全一致，公開ZIP CRC及全部240檔SHA256再次通過；證據artifacts/verification/releases-windows-w28/results.json／package.json／release-public.json。

artifacts/releases/oaClient2-0.1.6-windows-x64.zip與.sha256現在也為最新W28。舊W27兩檔保留artifacts/verification/releases-windows-v0.1.6/public-download供追溯；Mac產物／prg／picture／tpl275份雜湊不變，SDK／下載包／build保留。沿用W28 MSVC／CTest1/1、74項及原生／重啟AJAX合成表單結果，正式OA登入及列印／注音等仍待使用者驗收；Mac W27／W28未重編／實測，U01未實作。
