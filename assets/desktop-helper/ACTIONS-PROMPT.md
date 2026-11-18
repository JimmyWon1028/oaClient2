# W44 小熊動作素材產生紀錄

日期：2026-11-17。使用內建 imagegen，以 bear-sprites.png 為角色參考產生新 bear-actions.png，不覆蓋原圖。

透明輸出的兩次候選有背景雜點而未採用；最終使用下列白底提示產生，交由既有原生邊緣連通去白底流程顯示透明。工具原始輸出保留，僅最後候選複製進專案。工具沒有使用CLI或額外API金鑰。

## 最終提示詞

```text
Use case: stylized-concept. Asset: NEW production 16-pose animation sprite sheet matching the reference golden 3D bear. Preserve exact bear identity and smooth round 3D rendering: large pale golden head, orange small round ears, brown glossy eyes and nose, round pink cheeks, smiling tongue, golden body, cream belly, short limbs. Canvas is pure solid WHITE (#FFFFFF), absolutely no shadows, NO glow, NO speckles, NO texture, NO noise, NO gray gradients, no checkerboard. Exactly 4 columns by 4 rows of equal square cells, no cell borders, no text. Characters fully inside each cell, same head size and camera, generous 12% margins, centered, feet baseline at88% cell height. Layout left to right top to bottom: row1: 0 front standing neutral; 1 half crouch lowering into sit; 2 seated on bottom feet extended forward paws resting; 3 same seated with eyes shut. Row2: 4 half rising from seated; 5 standing with both arms partly raised preparing stretch; 6 happy full stretch both arms above head eyes closed; 7 stretch leaning gently sideways. Row3: 8 stretch recovery arms lowered; 9 walking RIGHT three quarter view left foot forward right foot back arms opposite; 10 walking right passing pose feet together; 11 walking right right foot forward left foot back. Row4: 12 right walking opposite passing pose; 13 walking LEFT three quarter view left foot forward; 14 left walking passing pose; 15 left walking opposite stride. Distinct seated silhouette, true articulated stretching and walking. Do not redesign character, keep consistent between frames. Background MUST be completely plain flat WHITE, no cast shadow or glow. No extra objects.
```
