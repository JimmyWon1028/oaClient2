# Windows prg 外部工具副本

2026-10-12 曾依使用者明確要求，從舊 oaClient64 的 Bin/prg 完整複製至本專案 prg。未修改舊工具；下列為當時12份副本的SHA256歷史清單，不是目前交付清單。

prg 不納入 Git，但仍由 Dropbox 同步；Mac 不執行這些 Windows 工具，也不以它們作為 Mac 建置依賴。oaClient2 的 cmd=prt 預設只呼叫 prg/Reptool.exe。

## 目前交付清單與維護規則

使用者已自行刪除不需要的交付檔案，並明確要求不要補回。2026-10-12核對 artifacts/oaClient2/prg 只保留以下四份：

- docto.exe
- Reptool.exe
- TSCLIB.dll
- zint.dll

package-windows.ps1 不再複製來源根prg；打包保留交付prg現況，不自動補回、覆蓋或清理。根prg的12份歷史副本仍保留，不能將其當作需要恢復的交付內容。若建立全新交付目錄，prg由使用者另行準備；腳本不自動帶入工具。

## 最初完整副本的歷史雜湊

| 檔案 | bytes | SHA256 |
| --- | ---: | --- |
| docto.exe | 1,763,328 | `291a46bcdaa7306e7dab9230435c798f8cbc5ea60f2e5ef3795005356d2021af` |
| output.xlsm | 13,478 | `bfa79113ae81229902c287039d58756828aecdd73bbb3181d01aa55dcbbc8184` |
| output.xlsx | 13,460 | `45cc680e46291b800cad82a1cdea8f98bf131a0f8a2ba7c0c7a624653aa4151b` |
| PDFtoPrinter.exe | 9,973,664 | `f6827d6c3e38e70dcbb888ffb84f56407b125c0c497e11ebd262e1d2f3477a02` |
| PDFtoPrinterSelect.exe | 9,973,664 | `f6827d6c3e38e70dcbb888ffb84f56407b125c0c497e11ebd262e1d2f3477a02` |
| Reptool-tei.exe | 7,123,456 | `21299e3c4c090bd7b5a8e984c54aa01ee9f9e80d85651c204e40a54f1c857736` |
| Reptool-zhuyu.exe | 11,256,320 | `66e914e28c24e62613530c4d84c0b9c1f75492ceb4f7e6534f2a7a4c693fa9f4` |
| Reptool.exe | 11,288,576 | `0700d31d16b68c34ab2e05ea6ee970ee0d9b449bc2bf1fca5a29aeb6d2debd28` |
| TeamViewer6.0.exe | 2,925,059 | `8a9fe752578c6ed3ec33f307e6a6a83f6912a2df8dd3938dee7f6fb4688e72e2` |
| TSC_DLL_instruction_C.pdf | 343,010 | `f09cc727f4510e9b647fcc499dc1f1ca1ad15e0e469f4b29203fe7e15a7ba8f8` |
| TSCLIB.dll | 190,976 | `d0bfd5186d26838287662586ae50edbf521d118bb2063a1da1abf341c3c07b1a` |
| zint.dll | 786,432 | `238fac4512ab8b0870a72a995eac9f0cc378f824429cd76f940f90c293342567` |
