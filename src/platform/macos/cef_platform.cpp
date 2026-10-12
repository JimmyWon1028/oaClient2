#include "platform/cef_platform.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"

namespace oa {

//2026.10.12 modify by codex, use bundled Helpers and Cocoa point coordinates.
void ConfigureChildProcess(CefRefPtr<CefCommandLine>, const AppPaths&) {}

void ResizeConsoleBrowser(void* child, void* parent, const CefRect& bounds) {
  ResizeBrowserChild(child, parent, bounds.x, bounds.y, bounds.width, bounds.height);
}

const char* ToolbarFontList() { return "PingFang TC, Helvetica, 13px"; }
//2026.10.12 modify by codex, resize the Views window rather than the macOS inner WebContents window.
void* ConsoleWindowHandle(CefRefPtr<CefBrowser> browser) {
  auto view = CefBrowserView::GetForBrowser(browser);
  auto window = view ? view->GetWindow() : nullptr;
  return window ? window->GetWindowHandle() : nullptr;
}

}  // namespace oa
