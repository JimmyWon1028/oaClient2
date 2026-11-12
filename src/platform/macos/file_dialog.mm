#import <Cocoa/Cocoa.h>
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>

#include "platform/cef_platform.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

//2026.10.16 by codex, offer Chrome's combined Custom Files filter and explicit All Files override.
@interface OaFileTypeFilter : NSObject
@property(nonatomic, weak) NSOpenPanel* panel;
@property(nonatomic, copy) NSArray<UTType*>* types;
- (void)changeFormat:(NSPopUpButton*)sender;
@end

@implementation OaFileTypeFilter
- (void)changeFormat:(NSPopUpButton*)sender {
  self.panel.allowedContentTypes = sender.indexOfSelectedItem == 0 ? self.types : @[];
  self.panel.allowsOtherFileTypes = sender.indexOfSelectedItem != 0;
}
@end

namespace oa {
namespace {

class MacFileDialogHandler : public CefDialogHandler {
 public:
  bool OnFileDialog(CefRefPtr<CefBrowser> browser, FileDialogMode mode,
      const CefString& title, const CefString& default_file_path,
      const std::vector<CefString>& accept_filters,
      const std::vector<CefString>& accept_extensions,
      const std::vector<CefString>&, CefRefPtr<CefFileDialogCallback> callback) override {
    CEF_REQUIRE_UI_THREAD();
    if ((mode != FILE_DIALOG_OPEN && mode != FILE_DIALOG_OPEN_MULTIPLE) || accept_filters.empty()) return false;

    NSMutableArray<UTType*>* types = [NSMutableArray array];
    //2026.10.16 by codex, defer unresolved MIME filters to CEF's second callback instead of guessing extensions.
    if (accept_extensions.size() != accept_filters.size()) return false;
    for (const auto& value : accept_extensions) {
      NSString* extensions = [NSString stringWithUTF8String:value.ToString().c_str()];
      for (NSString* extension in [extensions componentsSeparatedByString:@";"]) {
        if (![extension hasPrefix:@"."] || extension.length < 2) return false;
        UTType* type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
        if (!type) return false;
        if (![types containsObject:type]) [types addObject:type];
      }
    }
    if (!types.count) return false;

    auto view = CefBrowserView::GetForBrowser(browser);
    auto cef_window = view ? view->GetWindow() : nullptr;
    if (!cef_window) return false;
    id native = (__bridge id)cef_window->GetWindowHandle();
    NSWindow* window = [native isKindOfClass:NSWindow.class] ? native :
      ([native isKindOfClass:NSView.class] ? [native window] : nil);
    if (!window || window.attachedSheet) return false;

    NSOpenPanel* panel = [NSOpenPanel openPanel];
    panel.canChooseFiles = YES;
    panel.canChooseDirectories = NO;
    panel.allowsMultipleSelection = mode == FILE_DIALOG_OPEN_MULTIPLE;
    panel.allowedContentTypes = types;
    panel.allowsOtherFileTypes = NO;
    if (!title.empty()) panel.title = [NSString stringWithUTF8String:title.ToString().c_str()];
    if (!default_file_path.empty()) {
      NSString* path = [NSString stringWithUTF8String:default_file_path.ToString().c_str()];
      BOOL directory = NO;
      if ([NSFileManager.defaultManager fileExistsAtPath:path isDirectory:&directory] && directory) {
        panel.directoryURL = [NSURL fileURLWithPath:path isDirectory:YES];
      } else {
        panel.directoryURL = [NSURL fileURLWithPath:path.stringByDeletingLastPathComponent isDirectory:YES];
        panel.nameFieldStringValue = path.lastPathComponent;
      }
    }

    OaFileTypeFilter* filter = [[OaFileTypeFilter alloc] init];
    filter.panel = panel;
    filter.types = types;
    NSPopUpButton* formats = [[NSPopUpButton alloc] initWithFrame:NSMakeRect(0, 0, 220, 26) pullsDown:NO];
    [formats addItemsWithTitles:@[@"Custom Files", @"All Files"]];
    formats.target = filter;
    formats.action = @selector(changeFormat:);
    NSTextField* label = [NSTextField labelWithString:@"Format:"];
    NSStackView* accessory = [NSStackView stackViewWithViews:@[label, formats]];
    accessory.spacing = 8;
    panel.accessoryView = accessory;
    panel.accessoryViewDisclosed = YES;

    //2026.10.16 by codex, cancel the pending callback when its owner closes and retain the filter until dismissal.
    id observer = [NSNotificationCenter.defaultCenter addObserverForName:NSWindowWillCloseNotification
      object:window queue:nil usingBlock:^(NSNotification*) { [panel cancel:nil]; }];
    [panel beginSheetModalForWindow:window completionHandler:^(NSModalResponse response) {
      (void)filter;
      [NSNotificationCenter.defaultCenter removeObserver:observer];
      if (response != NSModalResponseOK || !browser->IsValid()) {
        callback->Cancel();
        return;
      }
      std::vector<CefString> paths;
      for (NSURL* url in panel.URLs) if (url.isFileURL) paths.emplace_back(url.path.UTF8String);
      callback->Continue(paths);
    }];
    return true;
  }

 private:
  IMPLEMENT_REFCOUNTING(MacFileDialogHandler);
};

}  // namespace

CefRefPtr<CefDialogHandler> PlatformFileDialogHandler() { return new MacFileDialogHandler; }

}  // namespace oa
