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
