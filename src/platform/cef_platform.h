#pragma once

#include "include/cef_command_line.h"
#include "include/cef_browser.h"
#include "include/internal/cef_types_wrappers.h"
#include "platform/platform.h"

namespace oa {

//2026.10.12 modify by codex, isolate CEF child loading and native coordinates.
void ConfigureChildProcess(CefRefPtr<CefCommandLine> command, const AppPaths& paths);
void* ConsoleWindowHandle(CefRefPtr<CefBrowser> browser);
void ResizeConsoleBrowser(void* child, void* parent, const CefRect& screen_bounds);
const char* ToolbarFontList();

}  // namespace oa
