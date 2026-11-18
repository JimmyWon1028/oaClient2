#pragma once

#include <functional>
#include <memory>
#include <string>
#include "app/desktop_helper.h"

namespace oa {
struct AppContext;
std::shared_ptr<DesktopHelper> CreateMacDesktopHelper(std::shared_ptr<AppContext> context);

//2026.11.18 by codex, keep Cocoa presentation separate from the unique notification session.
class MacDesktopPet {
 public:
  MacDesktopPet();
  ~MacDesktopPet();
  void Show();
  void Hide();
  void CloseMessage();
  void SetBrowseHandlers(std::function<void()> open, std::function<void(int)> navigate);
  void Notify(const std::string& text, std::function<void()> click, std::function<void()> dismiss = {});
  CefRefPtr<CefImage> Icon();
 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};
}
