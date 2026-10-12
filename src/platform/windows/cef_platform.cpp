#include "platform/cef_platform.h"
#include "include/views/cef_display.h"

namespace oa {

//2026.10.12 modify by codex, preserve Windows loading and DIP conversion at the platform boundary.
void ConfigureChildProcess(CefRefPtr<CefCommandLine> command, const AppPaths& paths) {
  command->AppendSwitchWithValue("libcef-path", PathUtf8(paths.application / L"cef" / L"libcef.dll"));
}

void ResizeConsoleBrowser(void* child, void* parent, const CefRect& screen_bounds) {
  const auto bounds = CefDisplay::ConvertScreenRectToPixels(screen_bounds);
  ResizeBrowserChild(child, parent, bounds.x, bounds.y, bounds.width, bounds.height);
}

const char* ToolbarFontList() { return "Microsoft JhengHei, Segoe UI, 13px"; }
void* ConsoleWindowHandle(CefRefPtr<CefBrowser> browser) { return browser->GetHost()->GetWindowHandle(); }

}  // namespace oa
