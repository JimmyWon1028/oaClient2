# Windows 內建 pet 角色素材

- `bear-sprites.png`：本對話使用內建 imagegen 產生且使用者確認的 3D 金黃色小熊八格圖，1774 × 887，4 欄 × 2 列。
- `preview-idle-wave.gif`：白底循環動作示意，供 Windows 接續比對；不代表 oaClient2 原生視窗已實作。
- 圖格由左至右、由上至下：待機、眨眼、舉手中、舉手、向外揮、向內揮、放下中、回待機。
- 原圖為白底，未採用有背景雜點的透明輸出。Windows 實作須建立乾淨透明效果並實測邊緣，不以整張白色矩形覆蓋桌面。
- pet 本體目標視覺大小約 100 × 100 像素；圖格比例與 Windows DPI 由實作核對，勿把整張八格圖直接當作單張角色。
- 沿用 oaClient2 目前資源內嵌方式，主程式 CEF 宿主及既有圖示保持。

此處只保存圖像資源，不含舊獨立 pet EXE、C# 程式或安裝腳本。

## W44 新增完整動作（2026-11-17）

- bear-actions.png：1241×1267，4欄×4列，共16格；新增坐下、伸懶腰、左右走路。原8格bear-sprites.png不覆蓋。
- 順序與SHA256見[ACTIONS-MANIFEST.json](ACTIONS-MANIFEST.json)，內建imagegen最終提示詞與候選取捨見[ACTIONS-PROMPT.md](ACTIONS-PROMPT.md)。
- 最終圖為乾淨白底，Windows沿用邊緣連通去白底顯示透明，已在本機原生視窗確認。兩次透明候選有雜點、未納入專案或交付。
- 呼吸／搖擺／小跳／歪頭與星光由原生繪圖變形及向量效果完成；素材保留真正坐姿、伸展與交替腿，走路不靠靜態整張圖平移代替。新資源內嵌EXE，交付不散放PNG；Mac本輪未接入。
