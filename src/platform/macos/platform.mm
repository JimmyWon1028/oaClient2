#import <Cocoa/Cocoa.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>

#include <arpa/inet.h>
#include <copyfile.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <objc/runtime.h>
#include "platform/platform.h"

namespace oa {
namespace {
char console_marker;
NSString* Text(const std::string& value) { return [NSString stringWithUTF8String:value.c_str()]; }
NSURL* FileUrl(const std::filesystem::path& path) { return [NSURL fileURLWithPath:Text(PathUtf8(path))]; }
NSWindow* NativeWindow(void* handle) {
  id object = (__bridge id)handle;
  if ([object isKindOfClass:[NSWindow class]]) return object;
  return [object isKindOfClass:[NSView class]] ? [object window] : nil;
}
bool RejectLinks(const std::filesystem::path& root, std::string& error) {
  std::error_code ec;
  if (std::filesystem::is_symlink(std::filesystem::symlink_status(root, ec))) {
    error = "拒絕清理符號連結瀏覽器目錄。"; return false;
  }
  if (ec) { error = "Cannot inspect profile: " + ec.message(); return false; }
  for (std::filesystem::recursive_directory_iterator it(root, ec), end; !ec && it != end; it.increment(ec)) {
    if (std::filesystem::is_symlink(it->symlink_status(ec))) {
      //2026.10.12 modify by codex, Chromium creates these root links; remove the links without following their targets.
      const auto name = it->path().filename().string();
      if (it->path().parent_path() == root && (name == "SingletonLock" || name == "SingletonSocket" ||
          name == "SingletonCookie" || name == "RunningChromeVersion")) continue;
      error = "拒絕清理含符號連結的瀏覽器目錄。"; return false;
    }
  }
  if (ec) { error = "Cannot inspect profile tree: " + ec.message(); return false; }
  return true;
}
}

std::filesystem::path Utf8Path(const std::string& value) { return std::filesystem::path(value); }
std::string PathUtf8(const std::filesystem::path& value) { return value.string(); }

//2026.10.12 modify by codex, keep all Mac runtime data in user Application Support independently of the bundle.
bool GetAppPaths(AppPaths& paths, std::string& error) {
  NSString* bundle = NSBundle.mainBundle.bundlePath;
  if (![bundle.pathExtension isEqualToString:@"app"]) { error = "oaClient2 必須從 .app 啟動。"; return false; }
  paths.application = Utf8Path(bundle.UTF8String).parent_path();
  NSURL* support = [NSFileManager.defaultManager URLsForDirectory:NSApplicationSupportDirectory inDomains:NSUserDomainMask].firstObject;
  if (!support) { error = "Cannot locate Application Support."; return false; }
  paths.data = Utf8Path(support.path.UTF8String) / "oaClient2";
  std::error_code ec;
  std::filesystem::create_directories(paths.data, ec);
  if (ec || std::filesystem::is_symlink(paths.data) || std::filesystem::is_symlink(paths.data.parent_path())) {
    error = "Cannot use oaClient2 local data directory."; return false;
  }
  paths.data = std::filesystem::canonical(paths.data, ec);
  if (ec) { error = "Cannot resolve local data directory."; return false; }
  paths.config = paths.data / "Config.ini";
  paths.profile = paths.data / "browser-profile";
  paths.log = paths.data / "logs" / "application.log";
  std::filesystem::create_directories(paths.log.parent_path(), ec);
  if (ec || std::filesystem::is_symlink(paths.log.parent_path())) {
    error = "Cannot use oaClient2 log directory."; return false;
  }
  return true;
}

std::filesystem::path PictureDirectory(const AppPaths& paths) { return paths.data / "picture"; }

std::vector<char> ReadApplicationImage(const AppPaths&, const std::string& name) {
  static const std::vector<std::string> names = {"oaClient-16.png", "oaClient-32.png", "oaClient-256.png",
    "toolbar-console.png", "toolbar-home.png", "toolbar-server.png", "toolbar-zoom-in.png", "toolbar-zoom-out.png"};
  if (std::find(names.begin(), names.end(), name) == names.end()) return {};
  NSString* path = [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:Text(name)];
  std::ifstream input(Utf8Path(path.UTF8String), std::ios::binary);
  return std::vector<char>(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

bool ClearBrowserProfile(const AppPaths& paths, std::string& error) {
  std::error_code ec;
  const auto root = std::filesystem::canonical(paths.data, ec);
  if (ec || !root.is_absolute() || std::filesystem::is_symlink(paths.data) ||
      paths.profile.lexically_normal() != (paths.data / "browser-profile").lexically_normal()) {
    error = "Browser profile is not the dedicated oaClient2 profile."; return false;
  }
  const auto status = std::filesystem::symlink_status(paths.profile, ec);
  if (status.type() == std::filesystem::file_type::not_found) return true;
  if (ec || !std::filesystem::is_directory(status) || !RejectLinks(paths.profile, error)) {
    if (error.empty()) error = "Cannot inspect browser profile.";
    return false;
  }
  const auto target = std::filesystem::canonical(paths.profile, ec);
  if (ec || target.parent_path() != root || target.filename() != "browser-profile") {
    error = "Browser profile resolved outside the dedicated app data directory."; return false;
  }
  std::filesystem::remove_all(target, ec);
  if (ec) { error = "Cannot clear site data: " + ec.message(); return false; }
  return true;
}

//2026.10.12 modify by codex, preserve macOS metadata and refuse genuine write denial before rename.
bool CommitSettingsFile(const std::filesystem::path& from, const std::filesystem::path& to, std::string& error) {
  struct stat source{}, original{};
  if (lstat(from.c_str(), &source) != 0 || !S_ISREG(source.st_mode)) {
    error = "Cannot inspect Config.ini.tmp."; return false;
  }
  if (lstat(to.c_str(), &original) == 0) {
    if (!S_ISREG(original.st_mode) || !(original.st_mode & 0222) || access(to.c_str(), W_OK) != 0 ||
        (original.st_flags & (UF_IMMUTABLE | SF_IMMUTABLE))) {
      error = "Config.ini 拒絕寫入；保留原檔及暫存，不修改權限。"; return false;
    }
    if (copyfile(to.c_str(), from.c_str(), nullptr, COPYFILE_METADATA) != 0) {
      error = "Cannot preserve Config.ini metadata."; return false;
    }
  } else if (errno != ENOENT) {
    error = "Cannot inspect Config.ini."; return false;
  }
  const int file = open(from.c_str(), O_RDONLY | O_NOFOLLOW);
  if (file < 0) { error = "Cannot flush Config.ini.tmp."; return false; }
  const bool flushed = fsync(file) == 0;
  close(file);
  if (!flushed || rename(from.c_str(), to.c_str()) != 0) {
    error = "Cannot replace Config.ini; temporary copy retained."; return false;
  }
  return true;
}

bool OpenConfiguration(const std::filesystem::path& path, std::string& error) {
  NSURL* editor = [NSWorkspace.sharedWorkspace URLForApplicationWithBundleIdentifier:@"com.apple.TextEdit"];
  if (!editor) { error = "Cannot locate TextEdit."; return false; }
  [NSWorkspace.sharedWorkspace openURLs:@[FileUrl(path)] withApplicationAtURL:editor
    configuration:[NSWorkspaceOpenConfiguration configuration] completionHandler:^(NSRunningApplication*, NSError* failure) {
      if (failure) ShowError("無法用 TextEdit 開啟 Config.ini。");
    }];
  return true;
}
bool OpenDirectory(const std::filesystem::path& path, std::string& error) {
  if ([NSWorkspace.sharedWorkspace openURL:FileUrl(path)]) return true;
  error = "Cannot open the application directory."; return false;
}

//2026.10.12 modify by codex, keep the Chrome Console native window owned by CEF while docking it with Cocoa.
bool AttachConsoleWindow(void* child, void* parent, std::string& error) {
  NSWindow* console = NativeWindow(child);
  NSWindow* owner = NativeWindow(parent);
  if (!console || !owner || console == owner) { error = "Invalid Console window."; return false; }
  console.hasShadow = NO;
  objc_setAssociatedObject(console, &console_marker, @YES, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  console.collectionBehavior = NSWindowCollectionBehaviorFullScreenAuxiliary;
  if (console.parentWindow != owner) {
    if (console.parentWindow) [console.parentWindow removeChildWindow:console];
    [owner addChildWindow:console ordered:NSWindowAbove];
  }
  return true;
}
void ResizeBrowserChild(void* child, void* parent, int x, int y, int width, int height) {
  NSWindow* console = NativeWindow(child);
  NSWindow* owner = NativeWindow(parent);
  if (!console || !owner || width <= 0 || height <= 0) return;
  // CEF uses top-left screen coordinates; Cocoa uses the primary screen's bottom-left origin.
  const CGFloat top = NSMaxY(NSScreen.screens.firstObject.frame);
  [console setFrame:NSMakeRect(x, top - y - height, width, height) display:YES];
  AppPaths paths;
  std::string error;
  if (GetAppPaths(paths, error)) {
    AppendLog(paths, "CONSOLE_BOUNDS cef=" + std::to_string(x) + "," + std::to_string(y) + "," +
      std::to_string(width) + "," + std::to_string(height) + " native=" +
      std::string(NSStringFromRect(console.frame).UTF8String) + " owner=" +
      std::string(NSStringFromRect(owner.frame).UTF8String));
  }
}

}  // namespace oa

//2026.10.12 modify by codex, provide a single-line URL dialog with ESC and close cancellation.
@interface OaUrlController : NSObject <NSWindowDelegate>
@property(nonatomic, strong) NSWindow* window;
@property(nonatomic, strong) NSTextField* field;
@property(nonatomic) BOOL accepted;
- (void)confirm:(id)sender;
- (void)cancel:(id)sender;
@end
@implementation OaUrlController
- (void)confirm:(id)sender { self.accepted = YES; [NSApp stopModal]; }
//2026.10.12 modify by codex, cancel the URL modal with a normal return instead of aborting its event loop.
- (void)cancel:(id)sender { [NSApp stopModalWithCode:NSModalResponseCancel]; }
- (BOOL)windowShouldClose:(NSWindow*)window { [self cancel:nil]; return NO; }
- (BOOL)control:(NSControl*)control textView:(NSTextView*)view doCommandBySelector:(SEL)command {
  if (command == @selector(cancelOperation:)) { [self cancel:nil]; return YES; }
  return NO;
}
@end

namespace oa {
bool PromptServerUrl(void* owner_handle, const std::string& current, std::string& value) {
  OaUrlController* controller = [[OaUrlController alloc] init];
  controller.window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 580, 160)
    styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable backing:NSBackingStoreBuffered defer:NO];
  controller.window.title = @"伺服器網址";
  controller.window.releasedWhenClosed = NO;
  controller.window.delegate = controller;
  NSTextField* label = [NSTextField labelWithString:@"請輸入伺服器網址："];
  label.frame = NSMakeRect(50, 115, 480, 24);
  label.textColor = NSColor.systemBlueColor;
  [controller.window.contentView addSubview:label];
  controller.field = [[NSTextField alloc] initWithFrame:NSMakeRect(50, 75, 480, 28)];
  controller.field.stringValue = Text(current);
  controller.field.usesSingleLineMode = YES;
  controller.field.delegate = (id<NSTextFieldDelegate>)controller;
  [controller.window.contentView addSubview:controller.field];
  NSButton* confirm = [NSButton buttonWithTitle:@"確定" target:controller action:@selector(confirm:)];
  confirm.frame = NSMakeRect(252, 20, 76, 32);
  confirm.keyEquivalent = @"\r";
  [controller.window.contentView addSubview:confirm];
  NSWindow* owner = NativeWindow(owner_handle);
  if (owner) {
    NSRect frame = owner.frame;
    [controller.window setFrameOrigin:NSMakePoint(NSMidX(frame) - 290, NSMidY(frame) - 80)];
  } else [controller.window center];
  [controller.window makeKeyAndOrderFront:nil];
  [controller.window makeFirstResponder:controller.field];
  [controller.field selectText:nil];
  [NSApp runModalForWindow:controller.window];
  if (controller.accepted) value = controller.field.stringValue.UTF8String;
  [controller.window orderOut:nil];
  [controller.window close];
  if (owner) [owner makeKeyAndOrderFront:nil];
  return controller.accepted;
}

//2026.10.12 modify by codex, capture only the main window and its docked Console, without desktop content.
bool CaptureWindow(void* handle, const std::filesystem::path& directory,
    std::filesystem::path& output, std::string& error) {
  NSWindow* window = NativeWindow(handle);
  if (!window || !window.isVisible || window.isMiniaturized) { error = "請先顯示 oaClient2 視窗再截圖。"; return false; }
  if (@available(macOS 14.0, *)) {
    struct CaptureState {
      std::atomic<bool> done = false;
      __strong NSImage* image = nil;
      __strong NSString* error = nil;
    };
    auto state = std::make_shared<CaptureState>();
    const NSInteger identifier = window.windowNumber;
    const CGFloat scale = window.backingScaleFactor;
    NSMutableArray<NSNumber*>* identifiers = [NSMutableArray arrayWithObject:@(identifier)];
    for (NSWindow* child in window.childWindows) {
      if (child.isVisible && objc_getAssociatedObject(child, &console_marker)) [identifiers addObject:@(child.windowNumber)];
    }
    [SCShareableContent getShareableContentExcludingDesktopWindows:YES onScreenWindowsOnly:YES
      completionHandler:^(SCShareableContent* content, NSError* failure) {
        if (failure) { state->error = failure.localizedDescription; state->done = true; return; }
        NSMutableArray<SCWindow*>* targets = [NSMutableArray array];
        for (NSNumber* number in identifiers) {
          for (SCWindow* item in content.windows) if (item.windowID == number.unsignedIntValue) [targets addObject:item];
        }
        if (!targets.count || targets.firstObject.windowID != identifier) {
          state->error = @"無法定位 oaClient2 截圖視窗。"; state->done = true; return;
        }
        SCWindow* main = targets.firstObject;
        dispatch_group_t group = dispatch_group_create();
        NSMutableArray<NSImage*>* images = [NSMutableArray array];
        for (SCWindow* target in targets) {
          [images addObject:[[NSImage alloc] init]];
          const NSUInteger index = images.count - 1;
          dispatch_group_enter(group);
          SCContentFilter* filter = [[SCContentFilter alloc] initWithDesktopIndependentWindow:target];
          SCStreamConfiguration* config = [[SCStreamConfiguration alloc] init];
          config.width = static_cast<size_t>(target.frame.size.width * scale);
          config.height = static_cast<size_t>(target.frame.size.height * scale);
          config.showsCursor = NO;
          config.ignoreShadowsSingleWindow = YES;
          [SCScreenshotManager captureImageWithFilter:filter configuration:config completionHandler:^(CGImageRef image, NSError* issue) {
            @synchronized(images) {
              if (image) images[index] = [[NSImage alloc] initWithCGImage:image size:target.frame.size];
              else state->error = issue.localizedDescription ?: @"截圖失敗。";
            }
            dispatch_group_leave(group);
          }];
        }
        dispatch_group_notify(group, dispatch_get_main_queue(), ^{
          if (!state->error) {
            NSImage* result = [[NSImage alloc] initWithSize:main.frame.size];
            [result lockFocus];
            [images.firstObject drawInRect:NSMakeRect(0, 0, main.frame.size.width, main.frame.size.height)];
            for (NSUInteger i = 1; i < targets.count; ++i) {
              const CGRect frame = targets[i].frame;
              [images[i] drawInRect:NSMakeRect(frame.origin.x - main.frame.origin.x,
                main.frame.size.height - (frame.origin.y - main.frame.origin.y) - frame.size.height,
                frame.size.width, frame.size.height)];
            }
            [result unlockFocus];
            state->image = result;
          }
          state->done = true;
        });
      }];
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(15);
    while (!state->done && std::chrono::steady_clock::now() < deadline) {
      [NSRunLoop.currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.01]];
    }
    if (!state->done) { error = "截圖逾時；請確認 macOS 螢幕錄製權限。"; return false; }
    if (state->error || !state->image) {
      error = state->error ? state->error.UTF8String : "截圖失敗。"; return false;
    }
    std::error_code ec;
    std::filesystem::create_directories(directory, ec);
    if (ec) { error = "Cannot create picture directory: " + ec.message(); return false; }
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyyMMddHHmmss-SSS";
    output = directory / ("Snapshot" + std::string([formatter stringFromDate:NSDate.date].UTF8String) + ".jpg");
    NSBitmapImageRep* bitmap = [NSBitmapImageRep imageRepWithData:state->image.TIFFRepresentation];
    NSData* jpeg = [bitmap representationUsingType:NSBitmapImageFileTypeJPEG properties:@{NSImageCompressionFactor:@0.9}];
    if (jpeg && [jpeg writeToURL:FileUrl(output) atomically:YES]) return true;
    error = "Cannot save JPG screenshot."; return false;
  }
  error = "視窗截圖目前需要 macOS 14 或更新版本的 ScreenCaptureKit。";
  return false;
}

void ShowSnapshotResult(void*, const std::filesystem::path& path) {
  NSAlert* alert = [[NSAlert alloc] init];
  alert.messageText = @"截圖完成";
  alert.informativeText = [Text(PathUtf8(path)) stringByAppendingString:@"\n是否開啟所在資料夾？"];
  [alert addButtonWithTitle:@"是"];
  [alert addButtonWithTitle:@"否"];
  if ([alert runModal] == NSAlertFirstButtonReturn) [NSWorkspace.sharedWorkspace activateFileViewerSelectingURLs:@[FileUrl(path)]];
}

void ShowNetworkInfo(void*) {
  struct ifaddrs* addresses = nullptr;
  std::ostringstream message;
  if (getifaddrs(&addresses) == 0) {
    for (auto item = addresses; item; item = item->ifa_next) {
      if (!item->ifa_addr || !(item->ifa_flags & IFF_UP) || (item->ifa_flags & IFF_LOOPBACK) || item->ifa_addr->sa_family != AF_INET) continue;
      char ip[INET_ADDRSTRLEN]{};
      auto ipv4 = reinterpret_cast<sockaddr_in*>(item->ifa_addr);
      inet_ntop(AF_INET, &ipv4->sin_addr, ip, sizeof(ip));
      message << item->ifa_name << "\nIP: " << ip << "\nMAC: ";
      for (auto link = addresses; link; link = link->ifa_next) {
        if (!link->ifa_addr || std::string(link->ifa_name) != item->ifa_name || link->ifa_addr->sa_family != AF_LINK) continue;
        auto data = reinterpret_cast<sockaddr_dl*>(link->ifa_addr);
        auto mac = reinterpret_cast<unsigned char*>(LLADDR(data));
        for (int i = 0; i < data->sdl_alen; ++i) {
          if (i) message << '-';
          message << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(mac[i]);
        }
        message << std::dec;
      }
      message << "\n\n";
    }
    freeifaddrs(addresses);
  }
  NSAlert* alert = [[NSAlert alloc] init];
  alert.messageText = @"oaClient2 網路 IP / MAC";
  alert.informativeText = Text(message.str().empty() ? "目前沒有可用的 IPv4 網路介面。" : message.str());
  [alert runModal];
}

bool LaunchReport(const std::string&, const std::string&, const std::filesystem::path&,
    const std::filesystem::path&, std::string& error) {
  error = "macOS 報表方案尚未實作；Windows Reptool.exe 無法原生執行。";
  return false;
}
void ShowError(const std::string& message) {
  NSAlert* alert = [[NSAlert alloc] init];
  alert.messageText = @"oaClient2";
  alert.informativeText = Text(message);
  alert.alertStyle = NSAlertStyleWarning;
  [alert runModal];
}
void AppendLog(const AppPaths& paths, const std::string& message) {
  std::ofstream log(paths.log, std::ios::app);
  const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm utc{};
  gmtime_r(&now, &utc);
  log << std::put_time(&utc, "%Y-%m-%dT%H:%M:%SZ") << ' ' << message << '\n';
}

}  // namespace oa
