#pragma once

#include "include/cef_command_line.h"
#include "include/cef_browser.h"
#include "include/cef_dialog_handler.h"
#include "include/internal/cef_types_wrappers.h"
#include "platform/platform.h"

namespace oa {

//2026.10.12 modify by codex, isolate CEF child loading and native coordinates.
void ConfigureChildProcess(CefRefPtr<CefCommandLine> command, const AppPaths& paths);
void* ConsoleWindowHandle(CefRefPtr<CefBrowser> browser);
void ResizeConsoleBrowser(void* child, void* parent, const CefRect& screen_bounds);
const char* ToolbarFontList();

//2026.10.16 by codex, provide native file filters through the existing platform boundary.
#if defined(OS_MAC) || defined(OS_WIN)
CefRefPtr<CefDialogHandler> PlatformFileDialogHandler();
#else
inline CefRefPtr<CefDialogHandler> PlatformFileDialogHandler() { return nullptr; }
#endif

#if defined(OS_WIN)
//2026.10.16 by codex, finish native dialog workers before unloading CEF during shutdown.
void ShutdownPlatformFileDialogs();
void CancelPlatformFileDialogs(int browser_id);
#else
inline void CancelPlatformFileDialogs(int) {}
#endif

}  // namespace oa
