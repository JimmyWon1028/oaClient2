# 圖示來源

2026-10-12 依使用者要求沿用既有 oaClient 圖示，未修改舊專案。

- `oaClient.ico`：從現行 oaClient.res 的 MAINICON 群組原樣重建，包含原始 128 × 128 圖示。
- `oaClient-16.png`、`oaClient-32.png`、`oaClient-256.png`：由該圖示產生，供 CEF Views 視窗與工作列使用；0.1.3起已內嵌EXE；0.1.6編入主程式RCDATA，不再以外部 PNG 交付。
- `toolbar-*.png`：從 fmMainOaClientu.dfm 的 btnDevTools、btnHomeUrl、btnServerIP、btnZoomDown、btnZoomUp Glyph 匯出，沿用原色與 Delphi 透明背景。
- 0.1.6 Windows EXE直接以application_images.rc編入OA圖示與PNG；先前bootstrap圖示修改工具與launcher已移除，沒有修改CEF官方runtime檔。依使用者要求不使用沙箱，正式程式碼簽署仍待處理。

來源定位見 [AGENTS.md](../AGENTS.md)。Mac 接續可沿用 PNG 圖示，另產生 macOS bundle 圖示資源。

0.1.6的application_images.rc內嵌全部8張PNG；resources.h 使用301～308作為資源ID，Windows ReadApplicationImage 由主程式EXE讀取。原始PNG仍留在此目錄，供重建及Mac資源封裝使用。
