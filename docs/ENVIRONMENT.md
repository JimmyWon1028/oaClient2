# Windows 開發環境

2026-10-12，工具準備不計入兩小時實作時間。

- 作業系統：Windows x64，核心版本 10.0.26200。
- 沿用既有 Visual Studio Build Tools 2022 17.14.40；沒有重裝完整 IDE。
- MSVC：工具目錄 14.44.35207，cl 19.44.35228。
- Windows SDK：10.0.26100.0。
- CMake：3.31.6-msvc6；Ninja：1.12.1。實際建置使用 Visual Studio 17 2022 x64 generator。
- CEF：154.0.34+g14c5a08+chromium-154.0.8037.98，stable，Windows x64 standard。
- 套件來源：[CEF 官方自動建置](https://cef-builds.spotifycdn.com/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_windows64.tar.bz2)。
- 官方索引 SHA1：8c705a2ef1ce5f7b9655729a2d3de5d033a24d8b，已校驗一致。
- 本機 SHA256：51ebf99f026c5901bb1c647053a00dc4abebed70fe24f5d9bcfaa0016b3f774b。
- 套件目錄：`%LOCALAPPDATA%/oaClient2/deps/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_windows64`。
- CEF 官方 cefsimple Release 範例已編譯成功；產物在 `%LOCALAPPDATA%/oaClient2/build/environment-check/tests/cefsimple/Release`。
- 沒有 ATL／Doxygen；這兩項為範例建置的非必要警告，不影響 cefsimple 編譯結果。
- CEF 154 的 Windows sandbox 採官方 bootstrap EXE 載入應用 DLL；不是舊版直接連結 cef_sandbox.lib 的方案。

## 計時

- 環境完成與實作起算：2026-10-12 11:25:29（Asia/Taipei）。
- 兩小時只計實作與必要建置；功能測試另列時段。若進入測試後需修正來源，另記實作耗時。
- 0.1.0 第一次實作／建置完成於 11:35:44，約 10 分 15 秒；其後使用者測試另計。
- 0.1.1 工具列、INI／圖示與 Console 調整在後續實作／測試交錯進行；最新建置約 12:27 完成，詳見 CHANGELOG.md，不捏造逐秒累計工時。

## 建置

在專案根目錄執行 `scripts/build-windows.ps1`，可用 `-CefRoot` 指定本機 CEF 路徑，或設定 `CEF_ROOT` 環境變數。預設建置輸出位於 `%LOCALAPPDATA%/oaClient2/build/windows-x64`，不寫進同步中的來源目錄。

Mac 後續使用 arm64 套件、Mac 本機工具鏈及獨立 build 目錄，不能共用 Windows CMakeCache 或二進位檔。目前 Mac 的入口與 Helper app 打包尚未實作。

## 本輪交付與可重現命令

本輪為避免覆蓋使用者正在執行的初版，另用 `LocalAppData/oaClient2/build/windows-x64-toolbar` 建置目前0.1.3；預設腳本目錄仍是 windows-x64。

```powershell
# 在專案根目錄；CEF_ROOT 指向本機解壓 SDK。
./scripts/build-windows.ps1 -CefRoot $env:CEF_ROOT -BuildRoot "$env:LOCALAPPDATA/oaClient2/build/windows-x64-toolbar" -RunTests
./scripts/package-windows.ps1 -BuildRoot "$env:LOCALAPPDATA/oaClient2/build/windows-x64-toolbar"
```

完整交付在專案 `artifacts/oaClient2/`，依使用者批准可同步；不把中間產物或 CEF SDK 移入專案。打包排除測試／圖示建置工具及 LIB／EXP／PDB，且不覆蓋交付目錄已有的 Config.ini。執行前先正常關閉正在使用的同路徑版本，避免 DLL 鎖定。

本機 Codex 執行環境的輸出實體位於 `C:/Users/Lenovo/AppData/Local/Packages/OpenAI.Codex_2p2nqsd0c76g0/LocalCache/Local/oaClient2/build/windows-x64-toolbar`；這只是本次環境紀錄，不作為共享建置預設或程式硬編碼。

0.1.1 已沿用 OA 圖示修改 bootstrap 的 ICON 資源。CEF 官方允許客製該資源；正式發行需另處理程式碼簽署，本輪沒有加入憑證或修改 sandbox 程式碼。參考：[CEF sandbox／bootstrap 文件](https://github.com/chromiumembedded/cef/blob/master/docs/sandbox_setup.md)。

CEF Views Chrome Window 僅支援一個 Chrome BrowserView；DevTools 154 強制 Chrome style。現行主網站為 Views Chrome BrowserView，Console 獨立 Chrome CefWindow 由 Windows 嵌入下方，詳見 HANDOFF.md；不可在 Mac 直接複製 Windows 視窗座標／HWND 操作。

## 0.1.2／0.1.3 封裝更新

CEF SDK／工具鏈版本未變。建置 Release 根目錄輸出 launcher oaClient2.exe，CEF bootstrap／應用 DLL／CEF runtime 在 Release/cef。launcher.rc 將8張PNG編入 EXE 的 RCDATA，platform ReadApplicationImage 只將 EXE 載入為資料資源，不執行它或解析匯入。

0.1.3 最新 Release／CTest 1/1 通過。交付腳本不再複製PNG，僅移除指定8張舊圖的交付副本，保留Config.ini／pict與 assets 來源。Codex封裝宿主的 LocalAppData 重導向曾使網站目錄校驗拒絕啟動；檔案總管啟動驗證正常，保留清理保護。

## 0.1.4 建置／交付

工具鏈與CEF154版本不變；Release／CTest1/1及53項核心檢查通過，新增Windows合成報表receiver與本機CEF設定／登出頁。package-windows.ps1另外複製根prg到Windows交付；測試exe、捷徑及合成INI不作產品交付。

## 0.1.5 驗證

CEF與工具鏈版本不變；Release／CTest1/1、62項核心通過。交付目錄INI實際縮放保存及一般／最大化關閉、重啟均正常，本輪沒有更改作業系統或資料夾權限。

## 0.1.6 現行建置配置

工具鏈／CEF154版本不變；現在使用windows-x64-standalone建置目錄（本機LocalAppData及同一Codex封裝映射），不再交付windows-x64-toolbar的launcher／DLL產物。新命令將-BuildRoot指定為LocalAppData/oaClient2/build/windows-x64-standalone，其他參數相同；打包使用該建置的Release。

USE_SANDBOX=OFF依使用者明確要求，Windows目標為單EXE，沒有bootstrap／應用DLL，官方CefScopedLibraryLoader從cef載入；根目錄不必放chrome_elf.dll。Release／CTest1/1、62項通過，CEF runtime共234份與原SDK SHA256一致；第一次完整交付仍需cef/，固定CEF版本的一般應用修改只換EXE。正式簽署仍未做。

## Windows交付目錄更新

2026-10-12使用者已將Windows交付目錄改為artifacts/oaClient2，package-windows.ps1後續只向此目錄交付；可直接壓縮整個oaClient2資料夾。Mac仍使用artifacts/macos-arm64；本機建置及CEF SDK的位置不變。舊紀錄中的artifacts/windows是改名前的實測位置。

## M01：Mac arm64 實際環境（2026-10-12）

- macOS 26.7.1（25G241），native arm64；Xcode 27.0（27A266a）、macOS SDK 27.0，Apple Clang 21.0.0（clang-2100.3.34.2）。
- CMake 4.4.0，Unix Makefiles，GNU Make 3.81；Ninja 未安裝，不因為缺 Ninja 重裝工具。
- Python 3.14.7 用於無第三方依賴的 ICNS 包裝腳本，只把共用原 PNG 封入 ICNS，沒有重畫圖示。
- CEF 與 Windows 同版：154.0.34+g14c5a08+chromium-154.0.8037.98，stable macosarm64 standard，官方檔案大小 307,056,359 bytes，索引時間 2026-10-05。
- [官方套件](https://cef-builds.spotifycdn.com/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_macosarm64.tar.bz2)，[官方索引](https://cef-builds.spotifycdn.com/index.json)。SHA1：b7e1bc1c719f1b8907b0398d8666339471a316c8，已與索引一致；SHA256：2e4a60880addad09c85d9ea27f4df09cb803069e1709377576e9cf62169648fe。
- 固定發行提交 [14c5a08 的 patch.cfg](https://github.com/chromiumembedded/cef/blob/14c5a08/patch/patch.cfg) 包含 mac_print_preview_modal；[修補原始碼](https://github.com/chromiumembedded/cef/blob/14c5a08/patch/patches/mac_print_preview_modal.patch) 涵蓋 [#3410](https://github.com/chromiumembedded/cef/issues/3410) 的 PDF 儲存 browser 關聯與 modal 焦點／尺寸。這是固定發行來源核對，不等於 Mac 實機列印驗收。
- SDK：使用者 Library/Caches/oaClient2/deps/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_macosarm64；build：Library/Caches/oaClient2/build/macos-arm64；不是 Dropbox／Git 內容。
- 官方 cefsimple 的 wrapper／五種 Helper 先成功，ibtool 因 Xcode 外掛未初始化失敗；執行 xcodebuild -runFirstLaunch 完成工具準備後，cefsimple Release 全部成功。沒有下載另一版 CEF 或修改 SDK 原始碼。
- Mac 實作起算 19:28:26；首輪 Release／CTest 完成 19:34:25。工具準備與 UI／合成測試另計；之後修正與測試交錯，不虛構逐秒累計。

### Mac 可重現命令

```sh
# CEF_ROOT 是該 Mac 本機路徑，不保存到共用個人 presets。
export CEF_ROOT="$HOME/Library/Caches/oaClient2/deps/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_macosarm64"
bash scripts/build-macos.sh
bash scripts/package-macos.sh
```

建置腳本拒絕 SDK／build 位於來源目錄；CMake 拒絕 x86_64／Universal／非 native arm64，並檢查 Framework 架構。可用 OA_BUILD_ROOT 指定其他本機非同步目錄，不能共用 Windows CMakeCache。

主網站直接編譯同一 app.cpp／ini.cpp；平台使用 ObjC++、CefAppProtocol、官方 loader、五種 Helper 與 Framework 版本目錄。八張 PNG 及 ICNS 放 Resources，INI／picture 放 .app 外。USE_SANDBOX=OFF，主程序 no_sandbox=1；沒有關閉網頁安全檢查。

官方 COPY_MAC_FRAMEWORK 巨集用 ln -sf，重複建置會追蹤既有 directory symlink 而生成多餘內部連結；本專案在執行該巨集前僅重建輸出 .app 的 Framework 子目錄，不改 SDK、不清除 app 旁資料。最終重複建置後無斷裂連結、整體 ad-hoc codesign strict 驗證通過。ad-hoc 簽署會更新複製 runtime 的簽章，SDK／下載包雜湊不變；不宣稱正式 Developer ID／公證完成。

Mac 截圖採 ScreenCaptureKit 的 macOS 14 API；CEF technical deployment target 12.0，僅 macOS 26.7.1 實測，其他版本的完整產品支援待驗證。Windows 共用來源回歸未執行。列印／注音與正式登入／登出驗收狀態見 PROGRESS。

## M04 Mac 資料位置與拖曳安裝（2026-10-12）

Mac 交付仍是 artifacts/macos-arm64/oaClient2.app，將完整 .app 拖曳到 Applications 即可。組態與執行資料由首次啟動產生，全部在 ~/Library/Application Support/oaClient2：Config.ini、picture、logs/application.log／cef.log、browser-profile、instance.lock。不需要安裝腳本或外部個人 INI；SDK／中間 build 仍在 Library/Caches/oaClient2/deps／build。

M04 起 package-macos.sh 只複製 .app；舊交付旁的 INI／picture 不覆蓋、不刪除，新版不再讀取。Windows 的 EXE 旁 INI／picture 及 LocalAppData 布局保持不變，接續請讀 [PLATFORM-PATHS](PLATFORM-PATHS.md)。本輪共用截圖呼叫最小平台介面抽取，Windows 回歸待執行；實際測試見 PROGRESS M04。


## 2026-10-13：M01／M11 SDK 準備與保留

M11 開始時本機 SDK 已不存在，初次 CMake 配置失敗；重新下載相同154.0.34 macosarm64套件，大小／SHA1／SHA256均與上列固定值一致，解壓後完成 Release／CTest1/1、75項及 bundle簽章核對。沒有更換 CEF 版本。

使用者明確要求編譯後保留本機 CEF SDK。解壓 SDK、原始 tar.bz2及 build/macos-arm64 都保留在本機 Library/Caches/oaClient2；不因交付完成自動刪除，也不移至同步專案。後續直接沿用此 SDK／建置目錄。Mac交付只更新 artifacts/macos-arm64/oaClient2.app，不安裝到 Applications；M11實機結果見 PROGRESS。


## 2026-10-13：Windows W21～W26 接續結果

Windows入口已啟用空白HomeUrl／allow_empty_home_url、hide_zoom_bubble及background_logout_close；W24設定父目錄、W25網站動態title與0.1.6版本、W26右側298 DIP／完整字樣直接編譯原共用app.cpp。共用來源沒有複製或重寫，Mac專屬碼與交付未改。

Windows MSVC Release／CTest1/1、74項與本輪歡迎頁、網址／縮放重啟、ACK／三秒期限／Console／beforeunload／全部退出、UserSet／網站儲存、目錄／動態標題／完整字樣實測已完成；詳見[最新Windows結果](../PROGRESS.md)。正式列印／Microsoft注音／OA登出／Reptool及間距待使用者驗收，未測情境以進度為準，U01未實作。

交付artifacts/oaClient2/oaClient2.exe與安全範例已更新；Windows INI／picture仍在EXE旁，CEF仍在cef/，prg不補回／覆蓋。正式INI最後正常關閉更新Window後保留現況；不宣稱逐位元不變。SDK／壓縮檔／build保留。本輪未提交／推送／發布，固定v0.1.6 Tag不動，後續Git／R02仍依使用者授權。前段Windows「尚未啟用／待回歸」是此次接續前狀態。
