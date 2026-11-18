#pragma once

#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_process_message.h"
#include "include/cef_image.h"

namespace oa {

//2026.11.17 by codex, keep optional desktop integration independent of platform startup and legacy commands.
class DesktopHelper {
 public:
  virtual ~DesktopHelper() = default;
  virtual void Stop() = 0;
  virtual bool Toggle() = 0;
  virtual CefRefPtr<CefImage> Icon() = 0;
  virtual void Loaded(CefRefPtr<CefBrowser> browser) = 0;
  virtual bool Message(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
    CefProcessId source, CefRefPtr<CefProcessMessage> message) = 0;
};

}
