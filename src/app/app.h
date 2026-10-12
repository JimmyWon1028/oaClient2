#pragma once

#include <chrono>
#include <list>
#include <memory>
#include <functional>
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_request_handler.h"
#include "include/cef_jsdialog_handler.h"
#include "include/views/cef_window.h"
#include "common/ini.h"
#include "common/logout.h"
#include "platform/platform.h"

namespace oa {

struct AppContext {
  Settings settings;
  AppPaths paths;
  //2026.10.12 modify by codex, let each platform opt in after implementing and validating its zoom UI policy.
  bool hide_zoom_bubble = false;
  //2026.10.12 modify by codex, keep Windows shutdown unchanged until its platform adopts the new policy.
  bool background_logout_close = false;
  bool closing_in_background = false;
  CefRefPtr<CefWindow> main_window;
  std::function<void()> toggle_console;
  std::chrono::steady_clock::time_point started = std::chrono::steady_clock::now();
};

class BrowserClient : public CefClient,
                      public CefLifeSpanHandler,
                      public CefDisplayHandler,
                      public CefLoadHandler,
                      public CefKeyboardHandler,
                      public CefRequestHandler,
                      public CefJSDialogHandler {
 public:
  explicit BrowserClient(std::shared_ptr<AppContext> context) : context_(std::move(context)) {}
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override { return this; }
  CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
  CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override { return this; }
  bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message,
                           bool is_reload, CefRefPtr<CefJSDialogCallback> callback) override;
  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser>,
      CefRefPtr<CefFrame>, CefRefPtr<CefRequest>, bool, bool, const CefString&, bool&) override;
  void OnBeforeDevToolsPopup(CefRefPtr<CefBrowser> browser, CefWindowInfo& info,
      CefRefPtr<CefClient>& client, CefBrowserSettings& settings,
      CefRefPtr<CefDictionaryValue>& extra_info, bool* use_default_window) override;
  bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event,
      CefEventHandle event_handle, bool* is_keyboard_shortcut) override;
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
  void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
  void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                 int http_status_code) override;
  void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                   TransitionType transition_type) override;
  bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, cef_log_severity_t level,
                         const CefString& message, const CefString& source, int line) override;
  bool PrepareWindowClose(CefRefPtr<CefBrowser> browser, CefRefPtr<CefWindow> window,
                         CefRefPtr<CefWindow> console = nullptr);

 private:
  std::shared_ptr<AppContext> context_;
  std::list<CefRefPtr<CefBrowser>> browsers_;
  std::string login_parameters_;
  bool site_ready_ = false;
  LogoutFlow logout_;
  int close_generation_ = 0;
  CefRefPtr<CefBrowser> closing_browser_;
  CefRefPtr<CefWindow> closing_window_;
  void RestoreUserSettings(CefRefPtr<CefBrowser> browser);
  void ProbeLoginState();
  void ScheduleLogoutTick();
  void LogoutTick(int generation);
  void FinishBackgroundClose();
  std::chrono::steady_clock::time_point background_close_started_;
  bool first_load_ = true;
  IMPLEMENT_REFCOUNTING(BrowserClient);
};

class App : public CefApp, public CefBrowserProcessHandler {
 public:
  explicit App(std::shared_ptr<AppContext> context) : context_(std::move(context)) {}
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
  void OnContextInitialized() override;
  void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) override;
  CefRefPtr<CefClient> GetDefaultClient() override { return client_; }

 private:
  std::shared_ptr<AppContext> context_;
  CefRefPtr<BrowserClient> client_;
  int pending_preferences_ = 0;
  void RestorePreferenceCookies();
  void PreferenceCookieSet(bool success);
  void CreateMainWindow();
  IMPLEMENT_REFCOUNTING(App);
};

}  // namespace oa
