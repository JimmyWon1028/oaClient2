#pragma once

#include <string_view>

namespace oa {

//2026.10.12 modify by codex, keep one embedded local welcome page for both platform builds.
inline constexpr std::string_view kWelcomePage = R"oa(<!doctype html>
<html lang="zh-Hant">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>oaClient2</title>
  <style>
    :root { color-scheme: light; font-family: system-ui, sans-serif; }
    * { box-sizing: border-box; }
    body { margin: 0; min-height: 100vh; display: grid; place-items: center; background: #f5f7fa; color: #243247; }
    main { width: min(480px, calc(100% - 48px)); padding: 44px 32px; text-align: center; background: white; border: 1px solid #e2e7ee; border-radius: 16px; }
    img { width: 64px; height: 64px; }
    .name { margin: 16px 0 28px; font-size: 18px; font-weight: 600; }
    h1 { margin: 0 0 12px; font-size: 24px; }
    p { margin: 0 0 28px; line-height: 1.7; color: #58677b; }
    button { padding: 12px 24px; font: inherit; font-weight: 600; border: 0; border-radius: 8px; background: #1766c7; color: white; cursor: pointer; }
    button:hover { background: #1254a6; }
    button:focus-visible { outline: 3px solid #91bbec; outline-offset: 4px; }
    .hint { margin: 24px 0 0; font-size: 14px; }
  </style>
</head>
<body>
  <main>
    <img src="{{OA_ICON}}" alt="OA">
    <div class="name">oaClient2</div>
    <h1>尚未設定伺服器網址</h1>
    <p>請先設定伺服器網址，開始使用。</p>
    <button type="button" id="configure-server">設定伺服器網址</button>
    <p class="hint">也可以使用下方工具列的網址設定按鈕。</p>
  </main>
  <script>
    document.getElementById('configure-server').addEventListener('click', function () {
      console.log('cmd=configure-server');
    });
  </script>
</body>
</html>)oa";

}  // namespace oa
