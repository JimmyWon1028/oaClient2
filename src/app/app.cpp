#include "app/app.h"
#include "platform/cef_platform.h"
#include "common/welcome.h"

#include <algorithm>
#include <cmath>
#include <charconv>
#include "include/cef_cookie.h"
#include "include/cef_parser.h"
#include "include/cef_request_context.h"
#include "include/cef_frame.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_browser_view_delegate.h"
#include "include/views/cef_display.h"
#include "include/views/cef_box_layout.h"
#include "include/views/cef_fill_layout.h"
#include "include/views/cef_label_button.h"
#include "include/views/cef_panel_delegate.h"
#include "include/views/cef_textfield.h"
#include "include/views/cef_window.h"
#include "include/views/cef_window_delegate.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_task.h"

namespace oa {
namespace {

enum Command { kConsole = 10, kHome, kServer, kMac, kDirectory, kSnapshot, kResetZoom, kZoomOut, kZoomIn };

//2026.10.13 modify by codex, match the legacy website title and display the actual client version.
std::string ApplicationWindowTitle(const std::string& website_title = "") {
  return (website_title.empty() ? "oaClient2" : website_title) + std::string(" [用戶端版本 0.1.6]");
}

class CompletionCallback : public CefCompletionCallback {
 public:
  explicit CompletionCallback(std::function<void()> callback) : callback_(std::move(callback)) {}
  void OnComplete() override { callback_(); }
 private:
  std::function<void()> callback_;
  IMPLEMENT_REFCOUNTING(CompletionCallback);
};

class CookieCallback : public CefSetCookieCallback {
 public:
  explicit CookieCallback(std::function<void(bool)> callback) : callback_(std::move(callback)) {}
  void OnComplete(bool success) override { callback_(success); }
 private:
  std::function<void(bool)> callback_;
  IMPLEMENT_REFCOUNTING(CookieCallback);
};

class DelayedCallback : public CefTask {
 public:
  explicit DelayedCallback(std::function<void()> callback) : callback_(std::move(callback)) {}
  void Execute() override { callback_(); }
 private:
  std::function<void()> callback_;
  IMPLEMENT_REFCOUNTING(DelayedCallback);
};

class LegacyProtocolHandler : public CefResourceRequestHandler {
 public:
  void OnProtocolExecution(CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>,
      CefRefPtr<CefRequest> request, bool& allow_os_execution) override {
    allow_os_execution = IsLegacyOpenProtocol(request->GetURL().ToString());
  }
 private:
  IMPLEMENT_REFCOUNTING(LegacyProtocolHandler);
};

CefRefPtr<CefImage> LoadImage(const AppPaths& paths, const std::string& name) {
  const auto bytes = ReadApplicationImage(paths, name);
  auto image = CefImage::CreateImage();
  if (!bytes.empty()) image->AddPNG(1.0, bytes.data(), bytes.size());
  return image;
}

//2026.10.12 modify by codex, embed the shared welcome page and existing OA icon without storing a local URL in INI.
std::string StartupNavigationUrl(const AppContext& context) {
  if (!context.settings.home_url.empty()) return context.settings.home_url;
  std::string html(kWelcomePage);
  const auto bytes = ReadApplicationImage(context.paths, "oaClient-256.png");
  const std::string icon = "data:image/png;base64," + CefBase64Encode(bytes.data(), bytes.size()).ToString();
  html.replace(html.find("{{OA_ICON}}"), std::string("{{OA_ICON}}").size(), icon);
  return "data:text/html;charset=utf-8;base64," + CefBase64Encode(html.data(), html.size()).ToString();
}

void SetApplicationIcons(CefRefPtr<CefWindow> window, const AppPaths& paths) {
  auto small = CefImage::CreateImage();
  auto large = CefImage::CreateImage();
  for (int size : {16, 32, 256}) {
    const auto bytes = ReadApplicationImage(paths, "oaClient-" + std::to_string(size) + ".png");
    if (bytes.empty()) continue;
    if (size == 256) large->AddPNG(1.0, bytes.data(), bytes.size());
    else small->AddPNG(size / 16.0, bytes.data(), bytes.size());
  }
  if (!small->IsEmpty()) window->SetWindowIcon(small);
  if (!large->IsEmpty()) window->SetWindowAppIcon(large);
}

class HeightDelegate : public CefPanelDelegate {
 public:
  explicit HeightDelegate(int height) : height_(height) {}
  CefSize GetPreferredSize(CefRefPtr<CefView>) override { return CefSize(1, height_); }
 private:
  int height_;
  IMPLEMENT_REFCOUNTING(HeightDelegate);
};

struct ConsoleDock {
  CefRefPtr<CefPanel> panel;
  CefRefPtr<CefWindow> window;
  CefRefPtr<CefBrowser> browser;
  bool opening = false;
  bool closing = false;
};

void ResizeChild(CefRefPtr<CefBrowser> browser, CefRefPtr<CefPanel> panel) {
  if (!browser || !panel || !panel->IsValid() || !panel->GetWindow()) return;
  //2026.10.12 modify by codex, let each platform convert CEF screen coordinates.
  ResizeConsoleBrowser(ConsoleWindowHandle(browser), panel->GetWindow()->GetWindowHandle(),
    panel->GetBoundsInScreen());
}

class BrowserPanelDelegate : public CefPanelDelegate {
 public:
  BrowserPanelDelegate(std::weak_ptr<ConsoleDock> dock, bool console)
    : dock_(std::move(dock)), console_(console) {}
  CefSize GetPreferredSize(CefRefPtr<CefView>) override {
    return CefSize(1, console_ ? 220 : 1);
  }
  void OnLayoutChanged(CefRefPtr<CefView> view, const CefRect&) override {
    if (auto dock = dock_.lock()) {
      ResizeChild(dock->browser, view->AsPanel());
    }
  }
 private:
  std::weak_ptr<ConsoleDock> dock_;
  bool console_;
  IMPLEMENT_REFCOUNTING(BrowserPanelDelegate);
};

class ConsoleClient : public CefClient, public CefLifeSpanHandler {
 public:
  ConsoleClient(std::shared_ptr<ConsoleDock> dock, CefRefPtr<BrowserClient> lifecycle)
    : dock_(std::move(dock)), lifecycle_(lifecycle) {}
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
    lifecycle_->OnAfterCreated(browser);
    dock_->browser = browser;
    dock_->opening = false;
    ResizeChild(browser, dock_->panel);
  }
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
    dock_->browser = nullptr;
    dock_->opening = false;
    dock_->closing = false;
    if (dock_->panel && dock_->panel->IsValid()) {
      dock_->panel->SetVisible(false);
      if (auto window = dock_->panel->GetWindow()) window->Layout();
    }
    lifecycle_->OnBeforeClose(browser);
  }
 private:
  std::shared_ptr<ConsoleDock> dock_;
  CefRefPtr<BrowserClient> lifecycle_;
  IMPLEMENT_REFCOUNTING(ConsoleClient);
};

void EditServerUrl(CefRefPtr<CefBrowser> browser, CefRefPtr<CefWindow> window,
                   const std::shared_ptr<AppContext>& context) {
  IniFile ini;
  std::string error, url;
  if (!ini.Load(context->paths.config, error)) { ShowError(error); return; }
  if (!PromptServerUrl(window->GetWindowHandle(), ini.Get("SysSet", "HomeUrl", context->settings.home_url), url)) return;
  const auto first = url.find_first_not_of(' ');
  if (first == std::string::npos) { ShowError("請輸入伺服器網址。"); return; }
  url = url.substr(first, url.find_last_not_of(' ') - first + 1);
  if (url.find(':') == std::string::npos) url = "https://" + url;
  CefURLParts parts;
  if (url.find_first_of("\r\n") != std::string::npos || !CefParseURL(url, parts) ||
      (CefString(&parts.scheme) != "https" && CefString(&parts.scheme) != "http") ||
      CefString(&parts.host).empty()) { ShowError("請輸入有效的 http 或 https 網址。"); return; }
  // Re-read after the modal to preserve other fields edited while it was open.
  if (!ini.Load(context->paths.config, error)) { ShowError(error); return; }
  ini.Set("SysSet", "HomeUrl", url);
  if (!ini.Save(context->paths.config, error) ||
      !LoadSettings(context->paths.config, context->settings, error)) { ShowError(error); return; }
  browser->GetMainFrame()->LoadURL(context->settings.home_url);
}

class ConsoleWindowDelegate : public CefWindowDelegate {
 public:
  ConsoleWindowDelegate(CefRefPtr<CefBrowserView> view, std::shared_ptr<ConsoleDock> dock,
                        std::shared_ptr<AppContext> context)
    : view_(view), dock_(std::move(dock)), context_(std::move(context)) {}
  void OnWindowCreated(CefRefPtr<CefWindow> window) override {
    dock_->window = window;
    window->SetToFillLayout();
    window->AddChildView(view_);
    auto parent = dock_->panel->GetWindow();
    std::string error;
    if (!AttachConsoleWindow(window->GetWindowHandle(), parent->GetWindowHandle(), error)) {
      ShowError(error);
      window->Close();
      return;
    }
    ResizeChild(dock_->browser, dock_->panel);
    //2026.10.12 modify by codex, keep a late DevTools popup hidden while background shutdown is pending.
    if (!context_->closing_in_background) {
      window->Show();
      ResizeChild(dock_->browser, dock_->panel);
      view_->RequestFocus();
    } else window->Hide();
  }
  cef_runtime_style_t GetWindowRuntimeStyle() override { return CEF_RUNTIME_STYLE_CHROME; }
  bool IsFrameless(CefRefPtr<CefWindow>) override { return true; }
  bool CanResize(CefRefPtr<CefWindow>) override { return false; }
  bool CanMaximize(CefRefPtr<CefWindow>) override { return false; }
  bool CanMinimize(CefRefPtr<CefWindow>) override { return false; }
  CefSize GetPreferredSize(CefRefPtr<CefView>) override { return CefSize(800, 220); }
  CefRefPtr<CefWindow> GetParentWindow(CefRefPtr<CefWindow>, bool*, bool*) override {
    return dock_->panel->GetWindow();
  }
  bool CanClose(CefRefPtr<CefWindow>) override {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    return !browser || browser->GetHost()->TryCloseBrowser();
  }
  void OnWindowDestroyed(CefRefPtr<CefWindow>) override {
    dock_->window = nullptr;
    view_ = nullptr;
  }
 private:
  CefRefPtr<CefBrowserView> view_;
  std::shared_ptr<ConsoleDock> dock_;
  std::shared_ptr<AppContext> context_;
  IMPLEMENT_REFCOUNTING(ConsoleWindowDelegate);
};

class BrowserViewDelegate : public CefBrowserViewDelegate {
 public:
  BrowserViewDelegate(std::shared_ptr<AppContext> context, std::shared_ptr<ConsoleDock> dock)
    : context_(std::move(context)), dock_(std::move(dock)) {}
  cef_runtime_style_t GetBrowserRuntimeStyle() override { return CEF_RUNTIME_STYLE_CHROME; }
  ChromeToolbarType GetChromeToolbarType(CefRefPtr<CefBrowserView>) override { return CEF_CTT_NONE; }
  CefRefPtr<CefBrowserViewDelegate> GetDelegateForPopupBrowserView(CefRefPtr<CefBrowserView>,
      const CefBrowserSettings&, CefRefPtr<CefClient>, bool) override {
    return new BrowserViewDelegate(context_, dock_);
  }
  bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView>, CefRefPtr<CefBrowserView> popup,
      bool is_devtools) override {
    if (!is_devtools) return false;
    //2026.10.12 modify by codex, cancel an asynchronous Console popup after hidden shutdown starts.
    if (context_->closing_in_background) {
      if (auto browser = popup->GetBrowser()) browser->GetHost()->CloseBrowser(true);
      return true;
    }
    CefWindow::CreateTopLevelWindow(new ConsoleWindowDelegate(popup, dock_, context_));
    return true;
  }
 private:
  std::shared_ptr<AppContext> context_;
  std::shared_ptr<ConsoleDock> dock_;
  IMPLEMENT_REFCOUNTING(BrowserViewDelegate);
};

class WindowDelegate : public CefWindowDelegate, public CefButtonDelegate {
 public:
  WindowDelegate(CefRefPtr<CefBrowserView> view, CefRefPtr<BrowserClient> client, std::shared_ptr<AppContext> context,
                  std::shared_ptr<ConsoleDock> dock, bool popup = false)
    : view_(view), client_(client), context_(std::move(context)), dock_(std::move(dock)), popup_(popup) {}

  void OnWindowCreated(CefRefPtr<CefWindow> window) override {
    SetApplicationIcons(window, context_->paths);
    CefBoxLayoutSettings layout_settings;
    layout_settings.horizontal = false;
    auto layout = window->SetToBoxLayout(layout_settings);
    window->AddChildView(view_);
    layout->SetFlexForView(view_, 1);
    dock_->panel = CefPanel::CreatePanel(new BrowserPanelDelegate(dock_, true));
    dock_->panel->SetToFillLayout();
    dock_->panel->SetVisible(false);
    window->AddChildView(dock_->panel);
    CreateToolbar(window);
    window->SetTitle(popup_ ? "oaClient2" : ApplicationWindowTitle());
    if (popup_ || context_->settings.left == -1 || context_->settings.top == -1) {
      window->CenterWindow(CefSize(context_->settings.width, context_->settings.height));
    }
    normal_bounds_ = CefRect(std::max(0, context_->settings.left), std::max(0, context_->settings.top),
      context_->settings.width, context_->settings.height);
    window->SetAccelerator(1, 'P', false, true, false, true);
    window->SetAccelerator(2, 0x7B, false, false, false, true);
    window->SetAccelerator(3, 0x77, false, false, false, true);
    window->Show();
    if (!popup_) window->Maximize();
    ready_ = true;
    context_->main_window = window;
    context_->toggle_console = [this] { ToggleConsole(); };
    view_->SetPreferAccelerators(true);
    view_->RequestFocus();
  }

  void OnWindowBoundsChanged(CefRefPtr<CefWindow> window, const CefRect& bounds) override {
    if (ready_ && !window->IsMaximized() && !window->IsMinimized() && !window->IsFullscreen()) {
      normal_bounds_ = bounds;
    }
  }

  CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override {
    const auto& s = context_->settings;
    if (popup_ || s.left == -1 || s.top == -1) return CefRect();
    return CefRect(s.left, s.top, s.width, s.height);
  }

  CefSize GetPreferredSize(CefRefPtr<CefView> view) override {
    if (view->GetID() >= kConsole && view->GetID() <= kZoomIn) {
      switch (view->GetID()) {
        case kConsole: return CefSize(30, 28);
        case kMac: return CefSize(40, 28);
        case kDirectory: return CefSize(67, 28);
        case kResetZoom: return CefSize(61, 28);
        case kSnapshot: return CefSize(38, 28);
        default: return CefSize(23, 28);
      }
    }
    return CefSize(context_->settings.width, context_->settings.height);
  }

  cef_show_state_t GetInitialShowState(CefRefPtr<CefWindow> window) override {
    return popup_ ? CEF_SHOW_STATE_NORMAL : CEF_SHOW_STATE_MAXIMIZED;
  }

  cef_runtime_style_t GetWindowRuntimeStyle() override { return CEF_RUNTIME_STYLE_CHROME; }

  bool CanClose(CefRefPtr<CefWindow> window) override {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    if (!popup_ && browser && !client_->PrepareWindowClose(browser, window, dock_->window)) return false;
    if (!popup_ && ready_ && normal_bounds_.width > 0 && normal_bounds_.height > 0) {
      std::string error;
      if (!SaveWindowSettings(context_->paths.config, normal_bounds_.x, normal_bounds_.y,
                              normal_bounds_.width, normal_bounds_.height, window->IsMaximized(), error)) {
        AppendLog(context_->paths, "CONFIG_SAVE_FAILED " + error);
        ShowError(error);
      }
    }
    return !browser || browser->GetHost()->TryCloseBrowser();
  }

  void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
    dock_->panel = nullptr;
    dock_->window = nullptr;
    dock_->browser = nullptr;
    toolbar_ = nullptr;
    view_ = nullptr;
    context_->toggle_console = {};
    context_->main_window = nullptr;
  }

  void OnButtonPressed(CefRefPtr<CefButton> button) override {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    if (!browser) return;
    auto window = button->GetWindow();
    std::string error;
    switch (button->GetID()) {
      case kConsole: ToggleConsole(); break;
      case kHome:
        if (LoadSettings(context_->paths.config, context_->settings, error)) {
          browser->GetMainFrame()->LoadURL(StartupNavigationUrl(*context_));
        } else ShowError(error);
        break;
      case kServer: EditServerUrl(browser, window, context_); break;
      case kMac: ShowNetworkInfo(window->GetWindowHandle()); break;
      case kDirectory:
        //2026.10.13 modify by codex, browse the active settings directory on both platforms.
        if (!OpenDirectory(context_->paths.config.parent_path(), error)) ShowError(error);
        break;
      case kSnapshot: {
        std::filesystem::path output;
        //2026.10.12 modify by codex, use the platform path without changing the shared capture flow.
        if (CaptureWindow(window->GetWindowHandle(), PictureDirectory(context_->paths), output, error)) {
          ShowSnapshotResult(window->GetWindowHandle(), output);
        } else ShowError(error);
        break;
      }
      case kResetZoom: browser->GetHost()->SetZoomLevel(0); SaveZoom(); break;
      case kZoomOut: browser->GetHost()->Zoom(CEF_ZOOM_COMMAND_OUT); SaveZoom(); break;
      case kZoomIn: browser->GetHost()->Zoom(CEF_ZOOM_COMMAND_IN); SaveZoom(); break;
    }
  }

  bool OnAccelerator(CefRefPtr<CefWindow> window, int command_id) override {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    if (!browser) return false;
    if (command_id == 1) browser->GetHost()->Print();
    else if (command_id == 2) ToggleConsole();
    else if (command_id == 3) {
      std::string error;
      if (!OpenConfiguration(context_->paths.config, error)) ShowError(error);
    } else return false;
    return true;
  }

 private:
  void SaveZoom() {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    if (!browser) return;
    const auto percent = static_cast<int>(std::lround(100 * std::pow(1.2, browser->GetHost()->GetZoomLevel())));
    IniFile ini;
    std::string error;
    if (!ini.Load(context_->paths.config, error)) { ShowError(error); return; }
    ini.Set("UserSet", "ZoomPercent", std::to_string(percent));
    if (!ini.Save(context_->paths.config, error)) ShowError(error);
    context_->settings.zoom_percent = percent;
  }

  void CreateToolbar(CefRefPtr<CefWindow> window) {
    toolbar_ = CefPanel::CreatePanel(new HeightDelegate(28));
    toolbar_->SetBackgroundColor(0xFFF0F0F0);
    CefBoxLayoutSettings settings;
    settings.horizontal = true;
    settings.cross_axis_alignment = CEF_AXIS_ALIGNMENT_CENTER;
    auto layout = toolbar_->SetToBoxLayout(settings);
    auto add = [&](int id, const char* text, const char* hint, int width) {
      auto button = CefLabelButton::CreateLabelButton(this, text);
      button->SetID(id);
      button->SetTooltipText(hint);
      button->SetAccessibleName(hint);
      button->SetFontList(ToolbarFontList());
      //2026.10.13 modify by codex, reduce inner padding so legacy widths keep complete button labels.
      if (id != kConsole) button->SetInsets(CefInsets(0, 2, 0, 2));
      button->SetMinimumSize(CefSize(width, 28));
      button->SetMaximumSize(CefSize(width, 28));
      button->SetBackgroundColor(0xFFF0F0F0);
      button->SetEnabledTextColors(0xFF222222);
      std::string icon;
      if (id == kConsole) icon = "console";
      else if (id == kHome) icon = "home";
      else if (id == kServer) icon = "server";
      else if (id == kZoomOut) icon = "zoom-out";
      else if (id == kZoomIn) icon = "zoom-in";
      if (!icon.empty()) {
        auto image = LoadImage(context_->paths, "toolbar-" + icon + ".png");
        if (!image->IsEmpty()) {
          button->SetText("");
          button->SetImage(CEF_BUTTON_STATE_NORMAL, image);
          button->SetAccessibleName(hint);
        }
      }
      toolbar_->AddChildView(button);
    };
    add(kConsole, ">_", "開啟／關閉 Console", 30);
    auto space = CefPanel::CreatePanel(nullptr);
    toolbar_->AddChildView(space);
    layout->SetFlexForView(space, 1);
    //2026.10.13 modify by codex, match the legacy DFM widths without changing toolbar actions or images.
    add(kHome, "⌂", "回到首頁", 23);
    add(kServer, "▤", "設定伺服器網址", 23);
    add(kMac, "MAC", "顯示 IP / MAC", 40);
    add(kDirectory, "瀏覽目錄", "瀏覽 Config.ini 所在目錄", 67);
    add(kSnapshot, "截圖", "擷取 oaClient2 視窗", 38);
    add(kResetZoom, "還原比例", "還原比例 100%", 61);
    add(kZoomOut, "−", "縮小", 23);
    add(kZoomIn, "+", "放大", 23);
    window->AddChildView(toolbar_);
  }

  void ToggleConsole() {
    auto browser = view_ ? view_->GetBrowser() : nullptr;
    if (!browser || dock_->closing) return;
    auto host = browser->GetHost();
    if (dock_->opening || host->HasDevTools()) {
      dock_->opening = false;
      dock_->closing = true;
      host->CloseDevTools();
      return;
    }
    auto preferences = CefValue::Create();
    auto dictionary = CefDictionaryValue::Create();
    if (auto current = browser->GetHost()->GetRequestContext()->GetPreference("devtools.preferences")) {
      if (current->GetType() == VTYPE_DICTIONARY) dictionary = current->GetDictionary()->Copy(false);
    }
    dictionary->SetString("panel-selected-tab", "\"console\"");
    preferences->SetDictionary(dictionary);
    CefString error;
    if (!host->GetRequestContext()->SetPreference("devtools.preferences", preferences, error)) {
      AppendLog(context_->paths, "DEVTOOLS_PREFERENCE_FAILED");
    }
    dock_->opening = true;
    dock_->panel->SetVisible(true);
    auto window = dock_->panel->GetWindow();
    window->Layout();
    CefWindowInfo info;
    CefBrowserSettings settings;
    host->ShowDevTools(info, new ConsoleClient(dock_, client_), settings, CefPoint());
    ResizeChild(dock_->browser, dock_->panel);
  }

  CefRefPtr<CefBrowserView> view_;
  CefRefPtr<BrowserClient> client_;
  CefRefPtr<CefPanel> toolbar_;
  std::shared_ptr<AppContext> context_;
  std::shared_ptr<ConsoleDock> dock_;
  CefRect normal_bounds_;
  bool popup_;
  bool ready_ = false;
  IMPLEMENT_REFCOUNTING(WindowDelegate);
};

}  // namespace

void BrowserClient::OnBeforeDevToolsPopup(CefRefPtr<CefBrowser>, CefWindowInfo&,
    CefRefPtr<CefClient>&, CefBrowserSettings&, CefRefPtr<CefDictionaryValue>&,
    bool* use_default_window) {
  // Keep the main website in Views for Chromium-managed IME focus and caret geometry.
  *use_default_window = false;
}

CefRefPtr<CefResourceRequestHandler> BrowserClient::GetResourceRequestHandler(
    CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefRequest>, bool, bool,
    const CefString&, bool&) {
  return new LegacyProtocolHandler();
}

void BrowserClient::RestoreUserSettings(CefRefPtr<CefBrowser> browser) {
  IniFile ini;
  std::string error;
  if (ini.Load(context_->paths.config, error)) {
    browser->GetMainFrame()->ExecuteJavaScript(UserSettingsScript(ini), "", 0);
    browser->GetMainFrame()->ExecuteJavaScript(
      "var $g=$g||{};$g.win_client=true;$g.client_version='oaClient2-0.1.6';", "", 0);
  } else AppendLog(context_->paths, "USER_SETTINGS_READ_FAILED");
}

void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                              TransitionType) {
  CEF_REQUIRE_UI_THREAD();
  if (frame->IsMain() && !browser->IsPopup()) {
    site_ready_ = false;
    RestoreUserSettings(browser);
  }
}

bool BrowserClient::PrepareWindowClose(CefRefPtr<CefBrowser> browser, CefRefPtr<CefWindow> window,
                                      CefRefPtr<CefWindow> console) {
  CEF_REQUIRE_UI_THREAD();
  const auto mode = context_->background_logout_close ? LogoutFlow::Mode::BackgroundGrace : LogoutFlow::Mode::PollForState;
  const auto action = logout_.Begin(site_ready_, mode);
  if (action == LogoutFlow::Action::Close) return true;
  //2026.10.12 modify by codex, dispatch once, hide immediately and keep CEF alive until acknowledgement or deadline.
  if (context_->background_logout_close && action == LogoutFlow::Action::Logout) {
    closing_browser_ = browser;
    closing_window_ = window;
    context_->closing_in_background = true;
    background_close_started_ = std::chrono::steady_clock::now();
    browser->GetMainFrame()->ExecuteJavaScript("if(typeof logout==='function')logout();", "", 0);
    AppendLog(context_->paths, "CLOSE_BACKGROUND_LOGOUT_DISPATCHED");
    if (console) console->Hide();
    window->Hide();
    AppendLog(context_->paths, "CLOSE_WINDOWS_HIDDEN main=" + std::to_string(!window->IsVisible()) +
      " console=" + std::to_string(!console || !console->IsVisible()));
    CefRefPtr<BrowserClient> self = this;
    const auto generation = close_generation_;
    CefPostDelayedTask(TID_UI, new DelayedCallback([self, generation] { self->LogoutTick(generation); }), 3000);
    ProbeLoginState();
    ScheduleLogoutTick();
    return false;
  }
  if (action == LogoutFlow::Action::Probe) {
    closing_browser_ = browser;
    closing_window_ = window;
    AppendLog(context_->paths, "CLOSE_LOGIN_STATE_CHECK");
    ProbeLoginState();
    ScheduleLogoutTick();
  }
  return false;
}

//2026.10.12 modify by codex, finish every owned browser without allowing unload dialogs to extend hidden shutdown.
void BrowserClient::FinishBackgroundClose() {
  CEF_REQUIRE_UI_THREAD();
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::steady_clock::now() - background_close_started_).count();
  AppendLog(context_->paths, std::string(logout_.timed_out() ? "CLOSE_BACKGROUND_DEADLINE" :
    "CLOSE_BACKGROUND_LOGOUT_ACKNOWLEDGED") + " ms=" + std::to_string(elapsed));
  ++close_generation_;
  closing_window_ = nullptr;
  closing_browser_ = nullptr;
  const auto browsers = browsers_;
  for (const auto& browser : browsers) browser->GetHost()->CloseBrowser(true);
}

void BrowserClient::ProbeLoginState() {
  if (!closing_browser_) return;
  closing_browser_->GetMainFrame()->ExecuteJavaScript(
    "(function(){var state=-1;try{if(window.$g&&typeof $g.isLogin==='boolean')"
    "state=$g.isLogin?1:0;if(typeof getLoginState==='function'){var ret=getLoginState();"
    "if(ret===0||ret===1)state=ret;}}catch(e){}console.log('loginState='+state);})();", "", 0);
}

//2026.10.12 modify by codex, allow the hidden shutdown to finish despite a page beforeunload prompt.
bool BrowserClient::OnBeforeUnloadDialog(CefRefPtr<CefBrowser>, const CefString&, bool is_reload,
                                        CefRefPtr<CefJSDialogCallback> callback) {
  CEF_REQUIRE_UI_THREAD();
  if (context_->background_logout_close && context_->closing_in_background && !is_reload) {
    AppendLog(context_->paths, "CLOSE_BACKGROUND_UNLOAD_ALLOWED");
    callback->Continue(true, "");
    return true;
  }
  return false;
}

void BrowserClient::ScheduleLogoutTick() {
  CefRefPtr<BrowserClient> self = this;
  const auto generation = close_generation_;
  CefPostDelayedTask(TID_UI, new DelayedCallback([self, generation] { self->LogoutTick(generation); }), 500);
}

void BrowserClient::LogoutTick(int generation) {
  CEF_REQUIRE_UI_THREAD();
  if (generation != close_generation_ || !closing_browser_ || !closing_window_) return;
  const auto action = logout_.Tick();
  if (action == LogoutFlow::Action::Close) {
    if (context_->background_logout_close) { FinishBackgroundClose(); return; }
    const auto event = logout_.timed_out() ? "CLOSE_LOGOUT_TIMEOUT" :
      (logout_.logout_sent() ? "CLOSE_LOGOUT_CONFIRMED" : "CLOSE_LOGOUT_NOT_REQUIRED");
    AppendLog(context_->paths, event);
    auto window = closing_window_;
    ++close_generation_;
    closing_window_ = nullptr;
    closing_browser_ = nullptr;
    window->Close();
    return;
  }
  if (action == LogoutFlow::Action::Logout) {
    AppendLog(context_->paths, "CLOSE_LOGOUT_SENT");
    closing_browser_->GetMainFrame()->ExecuteJavaScript(
      "if(typeof logout==='function')logout();", "", 0);
  }
  ProbeLoginState();
  ScheduleLogoutTick();
}

bool BrowserClient::OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event,
    CefEventHandle, bool*) {
  if (event.type != KEYEVENT_RAWKEYDOWN) return false;
  if (event.windows_key_code == 0x7B && context_->toggle_console) {
    context_->toggle_console();
    return true;
  }
  if (event.windows_key_code == 0x77) {
    std::string error;
    if (!OpenConfiguration(context_->paths.config, error)) ShowError(error);
    return true;
  }
  return false;
}

void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  browsers_.push_back(browser);
  AppendLog(context_->paths, "BROWSER_CREATED id=" + std::to_string(browser->GetIdentifier()) +
    " popup=" + std::to_string(browser->IsPopup()) + " count=" + std::to_string(browsers_.size()));
  //2026.10.12 modify by codex, do not let a late browser extend completed background shutdown.
  if (context_->closing_in_background && logout_.complete()) {
    browser->GetHost()->CloseBrowser(true);
    return;
  }
  if (!browser->IsPopup()) {
    browser->GetHost()->SetZoomLevel(std::log(context_->settings.zoom_percent / 100.0) / std::log(1.2));
  }
}

void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  if (closing_browser_ && closing_browser_->IsSame(browser)) {
    ++close_generation_;
    closing_browser_ = nullptr;
    closing_window_ = nullptr;
  }
  browsers_.remove_if([&](const auto& item) { return item->IsSame(browser); });
  AppendLog(context_->paths, "BROWSER_CLOSED id=" + std::to_string(browser->GetIdentifier()) +
    " remaining=" + std::to_string(browsers_.size()));
  if (browsers_.empty()) CefQuitMessageLoop();
}

void BrowserClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {
  CEF_REQUIRE_UI_THREAD();
  if (!browser->IsPopup() && context_->main_window) {
    //2026.10.13 modify by codex, keep the local welcome page from replacing the startup software name.
    context_->main_window->SetTitle(ApplicationWindowTitle(
      context_->settings.home_url.empty() ? "" : title.ToString()));
  } else if (auto view = CefBrowserView::GetForBrowser(browser)) {
    if (auto window = view->GetWindow()) window->SetTitle("oaClient2 — " + title.ToString());
  }
}

void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                             int http_status_code) {
  CEF_REQUIRE_UI_THREAD();
  if (frame->IsMain() && !browser->IsPopup()) {
    site_ready_ = true;
    RestoreUserSettings(browser);
    browser->GetHost()->SetZoomLevel(std::log(context_->settings.zoom_percent / 100.0) / std::log(1.2));
    AppendLog(context_->paths, "ZOOM_APPLIED percent=" + std::to_string(context_->settings.zoom_percent));
  }
  if (frame->IsMain() && first_load_) {
    first_load_ = false;
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - context_->started).count();
    AppendLog(context_->paths, "FIRST_MAIN_LOAD ms=" + std::to_string(elapsed) +
              " status=" + std::to_string(http_status_code));
  }
}

bool BrowserClient::OnConsoleMessage(CefRefPtr<CefBrowser> browser, cef_log_severity_t level,
                                     const CefString& message, const CefString& source, int line) {
  CEF_REQUIRE_UI_THREAD();
  const std::string text = message.ToString();
  const auto command = GetCommandField(text, "cmd");
  //2026.10.12 modify by codex, route only an unconfigured main welcome page to the existing URL dialog.
  if (command == "configure-server") {
    if (context_->settings.home_url.empty() && !browser->IsPopup() && context_->main_window &&
        browser->GetMainFrame()->GetURL().ToString().starts_with("data:text/html;charset=utf-8;base64,")) {
      //2026.10.12 modify by codex, leave the renderer console callback before opening a native modal dialog.
      auto context = context_;
      CefPostTask(TID_UI, new DelayedCallback([browser, context] {
        if (context->main_window && context->settings.home_url.empty()) {
          EditServerUrl(browser, context->main_window, context);
        }
      }));
    }
  } else if (text.starts_with("loginState=")) {
    const auto value = GetCommandField(text, "loginState");
    int state = -1;
    const auto result = std::from_chars(value.data(), value.data() + value.size(), state);
    if (result.ec == std::errc() && result.ptr == value.data() + value.size() &&
        (state == 0 || state == 1) && closing_browser_ && closing_browser_->IsSame(browser)) {
      logout_.ReceiveState(state);
      //2026.10.12 modify by codex, do not wait for another polling tick after the hidden browser reports logout.
      if (context_->background_logout_close && logout_.complete()) FinishBackgroundClose();
    }
  } else if (command == "ini") {
    const auto key = GetCommandField(text, "key");
    if (!key.empty()) {
      std::string error;
      if (!SaveUserSetting(context_->paths.config, key, GetCommandField(text, "val"), error)) {
        ShowError(error);
      } else if (GetCommandField(text, "showlog") == "1") {
        browser->GetMainFrame()->ExecuteJavaScript("if(typeof addMessage==='function')addMessage(" +
          QuoteJavaScript("儲存參數: " + key) + ",'success');", "", 0);
      }
    }
  } else if (command == "load-userset") {
    IniFile ini;
    std::string error;
    if (!ini.Load(context_->paths.config, error)) { ShowError(error); return true; }
    browser->GetMainFrame()->ExecuteJavaScript("var $tmp=$tmp||{};$tmp['userSet']=" +
      QuoteJavaScript(SerializedUserSettings(ini)) + ";", "", 0);
    const auto callback = GetCommandField(text, "func");
    if (!callback.empty()) browser->GetMainFrame()->ExecuteJavaScript(callback, "", 0);
  } else if (command == "loginParam") {
    login_parameters_ = GetCommandField(text, "val");
  } else if (command == "clientReady") {
    if (!browser->IsPopup()) site_ready_ = true;
    RestoreUserSettings(browser);
    browser->GetMainFrame()->ExecuteJavaScript(
      "var $g=$g||{}; $g.win_client=true; $g.client_version='oaClient2-0.1.6';", "", 0);
  } else if (text.starts_with("apiUrl")) {
    IniFile ini;
    std::string error;
    if (ini.Load(context_->paths.config, error)) {
      ini.Set("SysSet", "apiUrl", GetCommandField(text, "apiUrl"));
      if (!ini.Save(context_->paths.config, error)) ShowError(error);
    }
  } else if (command == "prt") {
    std::string parameters = text;
    if (!login_parameters_.empty()) {
      auto current_login = login_parameters_;
      std::replace(current_login.begin(), current_login.end(), ';', '|');
      parameters += "|" + current_login;
    }
    const auto config = context_->settings.reptool_config.empty() ? context_->paths.config :
      ResolveApplicationPath(context_->paths.application, context_->settings.reptool_config);
    const auto executable = ResolveApplicationPath(context_->paths.application, context_->settings.reptool_path);
    std::string error;
    if (!LaunchReport(PathUtf8(executable), parameters, config, context_->paths.application, error)) ShowError(error);
    const auto button = GetCommandField(text, "button");
    if (!button.empty()) {
      browser->GetMainFrame()->ExecuteJavaScript(
        "if(window.jQuery){jQuery(" + QuoteJavaScript("#" + button) + ").linkbutton('enable');}", "", 0);
    }
  } else return false;
  return true;
}

void App::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {
  //2026.10.12 modify by codex, keep platform loading details outside shared callbacks.
  ConfigureChildProcess(command_line, context_->paths);
}

void App::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();
  client_ = new BrowserClient(context_);
  CefRefPtr<App> self = this;
  CefCookieManager::GetGlobalManager(new CompletionCallback([self] { self->RestorePreferenceCookies(); }));
}

void App::RestorePreferenceCookies() {
  CEF_REQUIRE_UI_THREAD();
  //2026.10.12 modify by codex, do not create website cookies before a server URL has been configured.
  if (context_->settings.home_url.empty()) { CreateMainWindow(); return; }
  IniFile ini;
  std::string error;
  if (!ini.Load(context_->paths.config, error)) { ShowError(error); CreateMainWindow(); return; }
  const auto values = ini.SectionValues("UserSet");
  pending_preferences_ = static_cast<int>(values.size());
  if (!pending_preferences_) { CreateMainWindow(); return; }
  auto manager = CefCookieManager::GetGlobalManager(nullptr);
  for (const auto& [key, value] : values) {
    CefCookie cookie;
    CefString(&cookie.name) = key;
    CefString(&cookie.value) = EncodeCookieValue(value);
    CefString(&cookie.path) = "/";
    // Fresh preference cookies only; no prior website session is restored.
    cookie.has_expires = false;
    CefRefPtr<App> self = this;
    if (!manager->SetCookie(context_->settings.home_url, cookie,
        new CookieCallback([self](bool success) { self->PreferenceCookieSet(success); }))) {
      PreferenceCookieSet(false);
    }
  }
}

void App::PreferenceCookieSet(bool success) {
  CEF_REQUIRE_UI_THREAD();
  if (!success) AppendLog(context_->paths, "PREFERENCE_COOKIE_FAILED");
  if (--pending_preferences_ == 0) CreateMainWindow();
}

void App::CreateMainWindow() {
  CEF_REQUIRE_UI_THREAD();
  auto dock = std::make_shared<ConsoleDock>();
  CefBrowserSettings settings;
  //2026.10.12 modify by codex, hide the Chrome zoom bubble while retaining native zoom steps and INI persistence.
  if (context_->hide_zoom_bubble) settings.chrome_zoom_bubble = STATE_DISABLED;
  auto view = CefBrowserView::CreateBrowserView(client_, StartupNavigationUrl(*context_), settings,
    nullptr, nullptr, new BrowserViewDelegate(context_, dock));
  CefWindow::CreateTopLevelWindow(new WindowDelegate(view, client_, context_, dock));
  AppendLog(context_->paths, "CEF_CHROME_WINDOW_CREATED");
}

}  // namespace oa
