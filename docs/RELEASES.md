# 編譯版本下載與Release紀錄

## R04／W46：Windows 0.1.9同版重新發布完成（2026-11-18）

使用者回覆「可以了」，W46休眠喚醒依本次回報記錄使用者驗收通過；另依commit、push及重新打包上傳Windows Release、不進版的指示，來源e345e7f238fde9f762805d2d2f822cb49b48828f已推送核對。提交同時保存先前Mac已驗收／已發布的M29來源及紀錄，沒有修改Mac實作或重建Mac交付。Windows沿用已測EXE重新封裝，版本仍0.1.9，v0.1.9固定Tag a1215673784aa9a4fafb7ae8e2813a68ebbac5ff不動。

既有Release449602031原名Windows ZIP／SHA256已更新，ZIP為192199161 bytes、SHA256 2fd5805f9f8a8ec11bdd1f33c49114a46c7dc5a9b988afcf9ff4164edd159907，EXE仍9144462070129ff357f150ed052bfbf7a5063321111a0eac16c8ea8fc641a8e6；來源提交見上。包內240檔（CEF234、現用prg4、EXE及安全範例），CRC／全部SHA256通過，排除個人INI／網站資料／picture／logs／cache／tpl／SDK／build，不補回prg。沿用W46 MSVC Release／CTest3/3（194核心＋18腳本＋15原生）、CEF合成回歸及使用者休眠回報，不擴大正式通知端到端、注音／列印／Reptool或Mac共用修改驗收。

先以暫名上傳驗證GitHub大小／digest，再將舊Windows兩檔改名.previous-w45保留，新檔換回原下載名。公開原URL不帶登入憑證重新下載ZIP／SHA256均逐位元一致，公開ZIP CRC與240份內容雜湊再次通過。Release目前8個資產，Windows原名兩檔為W46新版，.previous-w45與Mac .previous-m28各兩檔為歷史備份；原Mac全部4資產ID／大小／digest保持，v0.1.8／v0.1.6 Release及Latest／固定Tag保持，沒有刪除遠端或本機備份。

604份本機保護清單核對通過（運作中的個人INI若有正常變動保留，不回寫快照），Windows／Mac交付、來源及素材未因打包修改；SDK／下載包／build保留。未重編、重啟或操作登入中的程式，未安裝或上傳API；W46共用session在Mac仍須目標平台重編回歸，Mac公開下載維持M29。證據artifacts/verification/releases-windows-w46，含package.json、release-before／staged／replaced／final.json、history-w45、public-download及results.json。發布結果文件另提交推送，前段待驗收／未提交／未發布為當時歷史狀態。

## R04 最新下載：v0.1.9（2026-11-18）

[oaClient2 0.1.9正式版／Latest](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.9)已公開，Tag固定a1215673784aa9a4fafb7ae8e2813a68ebbac5ff。

| 平台 | ZIP／校驗檔 | Bytes | ZIP SHA256 |
| --- | --- | ---: | --- |
| Windows x64 | [ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.9/oaClient2-0.1.9-windows-x64.zip)／[.sha256](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.9/oaClient2-0.1.9-windows-x64.zip.sha256) | 192199161 | `2fd5805f9f8a8ec11bdd1f33c49114a46c7dc5a9b988afcf9ff4164edd159907` |
| Mac arm64 | [ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.9/oaClient2-0.1.9-macos-arm64.zip)／[.sha256](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.9/oaClient2-0.1.9-macos-arm64.zip.sha256) | 146770733 | `fef207bb8dbdb5358dd4dc0dd832fe134c10a7cd9fd43d826fd44b74cd702220` |

Windows EXE SHA256為9144462070129ff357f150ed052bfbf7a5063321111a0eac16c8ea8fc641a8e6；Mac主程式為331e11ad154c1bde34998eba9b59eb965c39db46644c9ef3102ebc3b0bb362bb，對應Windows W46／Mac M29交付。

Mac同日已依使用者「不要進版」要求更新M29左側拖曳修正；Tag維持初次發布值，Mac內容以本次主程式與ZIP雜湊識別。Mac兩個.previous-m28資產是歷史備份，請下載上表原名新版檔案。Mac來源為144b717基準加本機未提交M29差異，patch SHA256 5fc34672d627321985f74298dbc435e813313e813989a02c7fbe0bf9c21195ed，本次未另提交／推送。

以下為R04首次M28封裝命令，保留重現原始發布；M29實際封裝與下載證據見後段同版更新紀錄。Mac新增可重現的跨平台[清單封裝腳本](../scripts/create-macos-release.py)，只接受macOS已驗證交付清單：核對全部實體檔SHA256，保留mode及相對symlink，以Unix ZIP屬性封裝；不以Windows同步目錄直接壓縮而遺失連結。範例：

```powershell
python scripts/create-macos-release.py --delivery artifacts/macos-arm64/oaClient2.app --manifest artifacts/verification/macos-m28-pet-corners/delivery-manifest.json --output artifacts/releases/v0.1.9/oaClient2-0.1.9-macos-arm64.zip --evidence artifacts/verification/releases-v0.1.9/macos-package.json --source-commit a1215673784aa9a4fafb7ae8e2813a68ebbac5ff --expected-executable-sha256 582bccc0919916fe9fb54d257545ab30cacedbbb2302e10d6dfd15b2a024a604
```

清單為本機macOS驗證證據，不納入Git；不存在或不一致即停止。既有輸出不覆寫。Windows沿用原create-windows-release.py，source-commit及expected-exe-sha256使用本節值。此Windows執行環境使用Codex隨附Python 3.12.14，不改產品依賴。

## R04：v0.1.9 Windows／Mac 正式發布完成（2026-11-18）

使用者要求「發布Release」並確認「win, mac都發布」。[v0.1.9正式版／Latest](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.9)已公開，Release ID449602031、draft=false、prerelease=false。新Tag固定已推送來源 `a1215673784aa9a4fafb7ae8e2813a68ebbac5ff`（產品主提交9cb59e6），沒有移動舊Tag。Windows W45與Mac M28的已測交付直接封裝，兩平台版本均0.1.9，未重編／安裝或部署API。

Windows ZIP為192197619 bytes、SHA256 `ef06618bc81b409d161760d2c0250ef237d80ad3980fdced86d2495eb5ef2a4f`；240檔包含主程式、安全範例、CEF234及現用prg4，不補回其他工具。Mac ZIP為146770634 bytes、SHA256 `fdddff41a1f28ad1712d00685016d73e32813e8b3d26b7057e8e042fe6240cdd`；完整.app的263實體檔與M28 macOS交付清單逐一SHA256一致，另依清單保留4個CEF相對符號連結與Unix執行權限，總267項。Windows同步不保留這4個連結，因此ZIP按原清單重建，未修改交付.app；10個Mach-O均薄arm64，簽章資料與已在Mac deep strict驗證的M28保持，Windows不重跑codesign或宣稱重新驗證Mac執行。新跨平台封裝腳本scripts/create-macos-release.py保留清單／權限／連結與逐檔校驗的可重現流程。

先建立草稿、上傳四個ZIP／SHA256並核對GitHub digest及大小後才公開。四個公開URL不帶憑證重新下載與本機逐位元一致，ZIP CRC、Windows全部240檔SHA256、Mac全部267項內容／連結／權限通過；latest端點與新Tag來源核對，v0.1.8／v0.1.6資產ID／大小／digest與Tag均保持。兩包排除個人INI、登入／網站資料、picture、logs、cache、tpl及SDK／build；原交付主程式雜湊不變，prg不補回。

沿用Windows Release／CTest2/2（194＋16）及本機上緣拖曳／通知操作，Mac M28 Release／CTest3/3（177＋16＋20）、原生繪圖與既有簽章結果；發布不擴大正式OA通知端到端、多螢幕／其他DPI、Mac實際拖曳／各平台實體方向鍵、注音／列印／Reptool驗收。Mac仍ad-hoc簽章、未有Developer ID／公證；U01未實作。SDK／下載包／build及個人資料保留。證據artifacts/verification/releases-v0.1.9與artifacts/releases/v0.1.9；發布文件／封裝腳本另提交推送，Tag固定不動。前段「未發布／公開0.1.8」為本輪授權前歷史。

## R03 最新下載：v0.1.8（2026-11-12）

[oaClient2 0.1.8 正式版／Latest](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.8)已公開，來源與Tag固定a3de8b3f8cfd046912bfef19ae7dbf0865df3f6e。Windows W39／Mac M26的同一已測交付檔直接打包，沒有重新編譯；共用功能、變更與未驗收範圍見[進度](../PROGRESS.md)。下方0.1.6段落是歷史發布紀錄，舊資產與Tag保留。

| 平台 | ZIP／SHA256校驗檔 | Bytes | ZIP SHA256 |
| --- | --- | ---: | --- |
| Windows x64 | [ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-windows-x64.zip)／[.sha256](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-windows-x64.zip.sha256) | 189895114 | `335c30631616fa0cac24d7da878d08643ee02c4b705f841a7a1e321198ce8199` |
| Mac arm64 | [ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-macos-arm64.zip)／[.sha256](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.8/oaClient2-0.1.8-macos-arm64.zip.sha256) | 144472509 | `2f5b406cc3acf542c994c5fcb817facec480a73da911ab44874f9594da41f2b8` |

Windows仍以安全清單封裝240檔：主程式、安全Config.example.ini、CEF234及現用prg4；未補回其他工具。Mac ZIP只有完整.app，解壓265份檔案／連結／mode與交付一致、10份arm64與deep strict簽章通過。兩平台均排除個人Config.ini、登入／網站資料、picture、logs、cache、tpl與SDK／build。Mac為ad-hoc簽章、未完成Developer ID／公證；更新前正常關閉，Windows保留自己的設定／截圖／工具／範本，Mac替換完整.app並保留Application Support/oaClient2。

四資產GitHub大小／digest與本機一致，公開URL無登入下載全部一致，ZIP CRC與Windows逐檔SHA256通過；v0.1.6的Release／資產與Tag未改。Windows160項、Mac151項及各自列印背景合成回歸沿用既有證據，正式OA／MRT與印表機留使用者驗收；Mac Blob視窗以右鍵列印完成預覽，Ctrl+P／Cmd+P未驗證通過。本次草稿Tag查詢404，完整遠端雜湊核對在公開後補做通過。詳細ID／本機證據與實際發布過程見[進度](../PROGRESS.md)R03；U01仍未實作。


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

## W29本機編譯待使用者測試（2026-10-13）

最新本機EXE為W29快捷鍵修正，版本仍0.1.6，SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，MSVC／CTest1/1、110項通過。實際按鍵由使用者驗收，本輪未重新打包／上傳，現有GitHub ZIP仍為W28的92c371f3，不宣稱已包含W29；Tag與Mac資產不動。

## W29／R02：使用者驗收與同版重新上傳授權（2026-10-13）

使用者對本機快捷鍵修正回覆「可以了」，Windows W29按本次回報記錄為使用者驗收通過，不擴大為列印／注音／正式OA登入登出或Mac Cmd驗收；代理原未執行的逐項UI矩陣仍標示未執行。使用者另要求重新打包上傳、不要進版：提交／推送W29實際來源，打包已編譯且由使用者測過的0.1.6 EXE，替換既有v0.1.6同名Windows ZIP與.sha256，先上傳校驗再替換；Tag／Mac資產與個人資料保持，舊ZIP保留歷史證據。前段待驗收／未發布為此次回報與授權前狀態。


## W29／R02 最新下載與驗收（2026-10-13）

使用者對W29快捷鍵修正回覆「可以了」，並要求同版重新上傳、不進版。最新[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)已替換，仍為0.1.6；大小189880195 bytes，SHA256 **849a2678ec237a98277ed8dfb1d130d630e165a338b91507ed83aa64166a8046**。請使用[最新校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)，前段W28的92c371f3雜湊及大小為歷史。

實際Windows建置來源6f2833b7f7789509abb8f4b60d9b3ea0e0daa01f已推送，EXE SHA256 b5a5d19b56f0078543351296d455692698a3a6303a1222e125b9153b8e69100a，沿用已建置／110項與使用者測試的同一檔，沒有重新編譯／進版。打包腳本輸出artifacts/releases/windows-w29/oaClient2-0.1.6-windows-x64.zip，source-commit及expected-exe-sha256使用上述值；安全清單240檔（EXE／安全範例／CEF234／現用prg4）CRC與全部SHA256通過，資料排除及不補回prg保持。

先上傳／校驗暫名兩檔，完整後才刪除前Windows兩資產並改為原名，最新版資產ID635910442／635911490；原Release ID411036061、Tag物件67e296794c1db526e2afc729e4b170f95d09bf5b→0fe6f357173fb7802cca8504c2ea007dd5e7834d，以及Mac兩資產ID／大小／digest均未改。原公開URL不帶登入憑證重新下載ZIP／.sha256逐位元一致，GitHub大小／digest與公開ZIP CRC／240檔SHA256通過；證據artifacts/verification/releases-windows-w29/results.json／package.json／release-public.json。

本機artifacts/releases同名兩檔亦已更新；前輪artifacts/releases/windows-w28及public-download歷史副本保留，原OA／SDK／build保持，275份Mac平台／產物與prg／picture／tpl雜湊不變。W29 Windows按使用者回報驗收，代理未執行逐項UI矩陣仍保留原紀錄，不擴大為列印／注音／正式OA登入登出／Reptool／hcopen／間距或Mac Cmd驗收；Mac W27～W29待目標平台重編／實測，U01未實作。發布文件另行提交推送，最新main以Git核對。

## M14～M17 本機 Mac 與公開下載差異（2026-10-13）

本機Mac完整.app已以cb68ba2共用來源加未提交main.mm平台修正建置，包含W27～W29與delegate lifetime／背景reopen，版本仍0.1.6；主執行檔SHA256 879b1e1747f0a59f75afa7cfc0790f257aa3acfe62b72edbd8239226e99c4a7e。Mac Release／111項、合成實機、10份arm64 Mach-O／deep strict及265檔案／連結交付核對見[PROGRESS](../PROGRESS.md)。

本輪先供使用者測試，沒有commit／push、製作或上傳新Mac ZIP、安裝Applications或移Tag；公開Mac ZIP仍為M13／8f1cdbdf，不含本輪修正。Windows公開W29 ZIP／849a2678、v0.1.6 Tag物件67e29679／來源0fe6f35保持。後續Mac同版發布依實際授權，記錄實際來源提交與工作差異；不拿舊Tag來源冒充新binary，不沿用已完成Windows資產替換授權。U01未實作。

## W30／R02：使用者驗收與同版發布授權（2026-10-13）

使用者對本機Ctrl+W修正回覆「可以了」，W30按此回報記錄Windows使用者驗收通過；不擴大為Mac、列印／注音或其他功能驗收。另明確授權commit、push、重新打包上傳、不進版：先提交／推送本次Windows修正與紀錄，再打包已建置／115項及使用者測過的同一EXE，替換既有v0.1.6同名Windows ZIP／.sha256。Tag、Mac兩資產及個人資料保持；先上傳校驗兩個暫名資產才替換，舊ZIP保留本機歷史證據。

Mac M14～M18及D04是接手時已有的未提交差異，保留於工作目錄，本次Windows提交只納入W30及發布紀錄。Mac新共用關閉保護仍須在macOS編譯回歸；U01未實作。前段待驗收／未發布是本次回報及授權前狀態，實際結果另行追加。

## W30／R02：0.1.6 同版更新完成（2026-10-13）

Windows Ctrl+W修正已由使用者回覆「可以了」驗收，來源a56ec05688462400e23137ba87bd63c875444221已提交／推送；沿用MSVC／CTest1/1、115項及使用者測過的同一EXE，沒有重新編譯或進版。EXE SHA256 504b76190af73bdff7c235e410a3b0ba4297017649142be50cf403f566f24b09。本次共用關閉保護仍待macOS編譯回歸，不擴大其他功能驗收。

既有[v0.1.6 Release](https://github.com/JimmyWon1028/oaClient2/releases/tag/v0.1.6)的[Windows x64 ZIP](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip)與[校驗檔](https://github.com/JimmyWon1028/oaClient2/releases/download/v0.1.6/oaClient2-0.1.6-windows-x64.zip.sha256)已替換為W30。ZIP 189880372 bytes，SHA256 **2ca590f6cd878a4a66612d8a4d25d99c46a432c23af26fb53177d64583252d33**；Windows資產ID636632177／636633864。先上傳兩個暫名資產／校驗digest才替換原名，公開原URL無登入重新下載兩檔與本機及GitHub一致，240檔CRC／全部SHA256通過。

ZIP仍只含EXE、安全範例、CEF234及現用prg4；不含個人INI／picture／logs／profile／cache／tpl／SDK／build，不補回工具。本機artifacts/releases同名兩檔已同步，W29歷史副本保留。Mac兩資產ID／大小／digest及固定Tag67e29679→0fe6f35不變，507份Mac平台／產物與CEF／prg等保護檔案雜湊一致。Mac M14～M18及D04既有未提交差異保留於工作目錄，未混入Windows提交；SDK／下載包／build保留。U01未實作。

證據artifacts/verification/releases-windows-w30/results.json／package.json／release-public.json及public-download；發布結果文件另行提交推送，最新main以Git核對。前段W30待驗收／未發布及W29公開雜湊為本次驗收／發布前歷史。

## 2026-11-12：R03 改為正式 Release／Latest

使用者明確要求將v0.1.8改為正式Release，已取消GitHub prerelease標記並設為Latest，更新發行標題與說明首行為正式版。GitHub releases/latest端點確認tag=v0.1.8、draft=false、prerelease=false，Release ID仍442477933；四資產名稱／大小／SHA256 digest與變更前一致，未重編／重打包／重傳、未移動來源Tag或修改其他版本。各功能驗收限制保持，不因正式Release標記擴大驗收。證據artifacts/verification/releases-v0.1.8/before-stable.json、release-notes-stable.md、release-stable.json。前段測試版形式是本次更正前狀態，下載連結不變。

## R04／M29：Mac 0.1.9同版重新上傳完成（2026-11-18）

使用者對M29左側拖曳回覆「可以了」，本項記錄使用者驗收，不擴大其他功能；另依「重新打包上傳Mac版Release，不要進版」已更新既有v0.1.9原名Mac ZIP與.sha256。Release仍449602031、正式版／Latest；版本0.1.9，固定Tag a1215673784aa9a4fafb7ae8e2813a68ebbac5ff不移動，Windows兩資產ID／大小／digest、v0.1.8／v0.1.6 Release保持。沒有重新編譯、操作或安裝App／API，也沒有提交／推送來源。

新Mac ZIP 146770733 bytes，SHA256 fef207bb8dbdb5358dd4dc0dd832fe134c10a7cd9fd43d826fd44b74cd702220；主程式仍為已驗收交付的331e11ad154c1bde34998eba9b59eb965c39db46644c9ef3102ebc3b0bb362bb。完整.app共267項（263實體檔＋4相對symlink），全部SHA256／mode／連結／CRC、10份薄arm64及交付與ZIP解壓後deep strict簽章通過。排除個人INI／網站資料／picture／logs／cache／SDK／build，沿用M29 CTest3/3（177＋16＋29）及本次使用者左拖回報。

先以暫名上傳並校驗GitHub大小／digest，再將舊Mac兩資產改名.previous-m28保留，新檔改回原下載名；不帶登入憑證從原公開URL重新下載兩檔逐位元一致，公開ZIP全部267項再核對通過。新資產ID762415587／762415588，Windows仍762205221／762206804。自動審核拒絕公開校驗後刪除舊備份，理由為未獲使用者授權刪除歷史發布證據；已改為完全保留全部遠端與本機備份，未執行刪除或繞過拒絕。Release目前6個資產，.previous-m28兩檔為歷史，下載表格與原名兩檔均為M29新版。

舊M28 ZIP／校驗檔保留history-m28，原ZIP SHA256 fdddff41a1f28ad1712d00685016d73e32813e8b3d26b7057e8e042fe6240cdd，原遠端ID762206846／762207771內容保持。artifacts/releases/v0.1.9的Mac兩檔已同步新包。M29來源為144b71751765ca67973f8a29a113826cab03bb00基準加本機未提交3檔差異，patch SHA256 5fc34672d627321985f74298dbc435e813313e813989a02c7fbe0bf9c21195ed，source.json／macos-m29-source.patch保存確切內容；Release說明已區分固定Tag與新Mac內容，本次未另要求commit／push，不用基準提交冒充M29來源。證據artifacts/verification/releases-macos-m29，含macos-package.json、release-staged／replaced／final.json、public-verification.json、public-download、history-m28與results.json。保護清單只見運作中的個人Config.ini變動，保留現況、未讀取設定內容或回寫舊快照，其餘來源／素材／Windows及Mac交付一致；SDK／下載包／build保留。

## R04／W46：休眠恢復驗收與同版發布授權（2026-11-18）

使用者回覆「可以了」，W46休眠喚醒依本次回報記錄使用者驗收通過，不擴大為正式通知端到端或其他功能驗收；另明確要求commit、push及重新打包上傳Windows Release、不進版。版本維持0.1.9，沿用已建置及驗收的EXE，不重新編譯或操作登入中的程式。將W46及先前已驗收／已發布但未提交的M29來源與文件一併保存到Git；只重新封裝Windows ZIP／SHA256，Mac四個資產（含歷史備份）、固定Tag與舊版本保持。

先保留舊Windows ZIP／校驗檔，上傳新包暫名並驗證遠端大小／digest，才把舊檔改名.previous-w45保留、新檔改回原下載名，再從公開原URL無登入下載核對。包內排除個人INI／網站資料／picture／logs／cache／tpl／SDK／build，現用prg4份不補回；不刪除既有歷史資產、不上傳API、不改個人設定，SDK／build保留。後續追加實際提交、雜湊與公開下載結果；前段待驗收／未提交／未發布為本次回報與授權前歷史。
