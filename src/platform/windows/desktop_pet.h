#pragma once

#include <functional>
#include <memory>
#include <string>
#include "app/desktop_helper.h"
#include "include/cef_app.h"

namespace oa {
struct AppContext;
std::shared_ptr<DesktopHelper> CreateWindowsDesktopHelper(std::shared_ptr<AppContext> context);
CefRefPtr<CefApp> CreatePetRenderer();

//2026.11.17 by codex, own a desktop window without making it an owned child of the main browser.
class DesktopPet {
 public:
  DesktopPet();
  ~DesktopPet();
  void Show();
  void Hide();
  void CloseMessage();
  void SetBrowseHandlers(std::function<void()> open, std::function<void(int)> navigate);
  void SetResumeHandler(std::function<void()> resume);
  void Notify(const std::string& text, std::function<void()> click, std::function<void()> dismiss = {});
  CefRefPtr<CefImage> Icon();
 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};
}
