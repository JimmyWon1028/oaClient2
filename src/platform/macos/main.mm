#import <Cocoa/Cocoa.h>

#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include "include/cef_application_mac.h"
#include "include/wrapper/cef_helpers.h"
#include "include/wrapper/cef_library_loader.h"
#include "app/app.h"

//2026.10.12 modify by codex, integrate Cocoa termination with the shared logout flow.
@interface OaApplication : NSApplication <CefAppProtocol> {
  BOOL handlingSendEvent_;
  std::shared_ptr<oa::AppContext> context_;
}
- (void)setContext:(std::shared_ptr<oa::AppContext>)context;
@end

@implementation OaApplication
- (BOOL)isHandlingSendEvent { return handlingSendEvent_; }
- (void)setHandlingSendEvent:(BOOL)value { handlingSendEvent_ = value; }
- (void)setContext:(std::shared_ptr<oa::AppContext>)context { context_ = std::move(context); }
- (void)sendEvent:(NSEvent*)event {
  CefScopedSendingEvent scope;
  [super sendEvent:event];
}
- (void)terminate:(id)sender {
  if (context_) oa::AppendLog(context_->paths, "COCOA_TERMINATE window=" + std::to_string(bool(context_->main_window)));
  if (context_ && context_->main_window) context_->main_window->Close();
}
@end

@interface OaApplicationDelegate : NSObject <NSApplicationDelegate>
@end
@implementation OaApplicationDelegate
- (BOOL)applicationSupportsSecureRestorableState:(NSApplication*)app { return YES; }
- (BOOL)applicationShouldHandleReopen:(NSApplication*)app hasVisibleWindows:(BOOL)visible {
  for (NSWindow* window in app.windows) {
    if (window.parentWindow == nil && window.isVisible) [window makeKeyAndOrderFront:nil];
  }
  return NO;
}
@end

namespace {
class MacApp : public oa::App {
 public:
  explicit MacApp(std::shared_ptr<oa::AppContext> context) : oa::App(context), context_(context) {}
  void OnBeforeCommandLineProcessing(const CefString& type, CefRefPtr<CefCommandLine> command) override {
    //2026.10.12 modify by codex, the shared Views app owns startup instead of a default Chrome window.
    if (type.empty()) command->AppendSwitch("no-startup-window");
  }
  //2026.10.12 modify by codex, handle Mac relaunches without CEF creating a standalone Chrome window.
  bool OnAlreadyRunningAppRelaunch(CefRefPtr<CefCommandLine>, const CefString&) override {
    oa::AppendLog(context_->paths, "MAC_RELAUNCH_HANDLED window=" + std::to_string(bool(context_->main_window)));
    if (context_->main_window && !context_->closing_in_background) {
      context_->main_window->Show();
      context_->main_window->Activate();
    }
    return true;
  }
  CefRefPtr<CefClient> GetDefaultClient() override {
    oa::AppendLog(context_->paths, "CHROME_DEFAULT_CLIENT");
    return oa::App::GetDefaultClient();
  }
 private:
  std::shared_ptr<oa::AppContext> context_;
};
void CreateMenu() {
  NSMenu* menu = [[NSMenu alloc] init];
  NSMenuItem* app_item = [[NSMenuItem alloc] init];
  [menu addItem:app_item];
  NSMenu* app_menu = [[NSMenu alloc] initWithTitle:@"oaClient2"];
  [app_menu addItemWithTitle:@"隱藏 oaClient2" action:@selector(hide:) keyEquivalent:@"h"];
  [app_menu addItem:[NSMenuItem separatorItem]];
  NSMenuItem* quit = [app_menu addItemWithTitle:@"結束 oaClient2" action:@selector(terminate:) keyEquivalent:@"q"];
  quit.target = NSApp;
  app_item.submenu = app_menu;
  NSMenuItem* edit_item = [[NSMenuItem alloc] init];
  [menu addItem:edit_item];
  NSMenu* edit_menu = [[NSMenu alloc] initWithTitle:@"編輯"];
  [edit_menu addItemWithTitle:@"還原" action:@selector(undo:) keyEquivalent:@"z"];
  [edit_menu addItemWithTitle:@"剪下" action:@selector(cut:) keyEquivalent:@"x"];
  [edit_menu addItemWithTitle:@"複製" action:@selector(copy:) keyEquivalent:@"c"];
  [edit_menu addItemWithTitle:@"貼上" action:@selector(paste:) keyEquivalent:@"v"];
  [edit_menu addItemWithTitle:@"全選" action:@selector(selectAll:) keyEquivalent:@"a"];
  edit_item.submenu = edit_menu;
  NSApp.mainMenu = menu;
}
}

//2026.10.12 modify by codex, load the arm64 framework before creating the Cocoa application.
int main(int argc, char* argv[]) {
  CefScopedLibraryLoader library_loader;
  if (!library_loader.LoadInMain()) return 1;
  @autoreleasepool {
    OaApplication* application = [OaApplication sharedApplication];
    CHECK([application isKindOfClass:[OaApplication class]]);
    [application setActivationPolicy:NSApplicationActivationPolicyRegular];
    auto context = std::make_shared<oa::AppContext>();
    //2026.10.12 modify by codex, enable the requested Mac zoom UI policy; Windows adoption is deferred.
    context->hide_zoom_bubble = true;
    //2026.10.12 modify by codex, hide during logout and exit on acknowledgement or the three-second deadline.
    context->background_logout_close = true;
    std::string error;
    if (!oa::GetAppPaths(context->paths, error)) { oa::ShowError(error); return 1; }
    const auto lock_path = context->paths.data / "instance.lock";
    const int lock = open(lock_path.c_str(), O_CREAT | O_RDWR | O_NOFOLLOW, 0600);
    if (lock < 0) { oa::ShowError("無法鎖定 oaClient2 專用資料目錄。"); return 1; }
    if (flock(lock, LOCK_EX | LOCK_NB) != 0) {
      close(lock);
      oa::ShowError("oaClient2 已在執行，請先關閉原視窗。");
      return 0;
    }
    //2026.10.12 modify by codex, generate a blank Mac HomeUrl until the user confirms server settings.
    context->settings.home_url.clear();
    context->settings.allow_empty_home_url = true;
    if (!oa::LoadSettings(context->paths.config, context->settings, error)) {
      oa::ShowError(error); close(lock); return 1;
    }
    CefRefPtr<CefCommandLine> command = CefCommandLine::CreateCommandLine();
    command->InitFromArgv(argc, argv);
    if (command->HasSwitch("url")) context->settings.home_url = command->GetSwitchValue("url").ToString();
    oa::AppendLog(context->paths, "START version=0.1.6 platform=macos-arm64");
    if (context->settings.clear_site_data && !oa::ClearBrowserProfile(context->paths, error)) {
      oa::ShowError(error); close(lock); return 1;
    }
    oa::AppendLog(context->paths, context->settings.clear_site_data ? "SITE_DATA_CLEARED" : "SITE_DATA_RETAINED_BY_INI");
    CefMainArgs args(argc, argv);
    CefSettings settings;
    settings.no_sandbox = 1;
    settings.persist_session_cookies = 0;
    CefString(&settings.root_cache_path) = oa::PathUtf8(context->paths.profile);
    CefString(&settings.cache_path) = oa::PathUtf8(context->paths.profile / "Default");
    CefString(&settings.locale) = context->settings.locale;
    //2026.10.12 modify by codex, keep both Mac logs in the Application Support logs directory.
    CefString(&settings.log_file) = oa::PathUtf8(context->paths.log.parent_path() / "cef.log");
    [application setContext:context];
    OaApplicationDelegate* delegate = [[OaApplicationDelegate alloc] init];
    CefRefPtr<oa::App> app = new MacApp(context);
    int result = 1;
    if (CefInitialize(args, settings, app, nullptr)) {
      //2026.10.12 modify by codex, install Cocoa hooks after Chrome initializes its application controller.
      application.delegate = delegate;
      CreateMenu();
      [application activateIgnoringOtherApps:YES];
      CefRunMessageLoop();
      CefShutdown();
      oa::AppendLog(context->paths, "SHUTDOWN_COMPLETE");
      result = 0;
    } else {
      result = CefGetExitCode();
      oa::AppendLog(context->paths, "INITIALIZE_EXIT code=" + std::to_string(result));
    }
    [application setContext:nullptr];
    application.delegate = nil;
    flock(lock, LOCK_UN);
    close(lock);
    return result;
  }
}
