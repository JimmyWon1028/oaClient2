#import <Cocoa/Cocoa.h>
#include <iostream>
#include "platform/macos/desktop_pet.h"
#include "platform/macos/desktop_pet_layout.h"
#include "include/wrapper/cef_library_loader.h"

//2026.11.18 by codex, verify native panel ownership and offscreen output without synthetic input or ERP access.
int main(int argc, char* argv[]) {
  CefScopedLibraryLoader loader;
  if (!loader.LoadInMain()) return 1;
  @autoreleasepool {
    [NSApplication sharedApplication];
    int failures = 0, checks = 0;
    auto check = [&](bool ok, const char* label) {
      ++checks; if (!ok) ++failures;
      std::cout << (ok ? "PASS " : "FAIL ") << label << '\n';
    };
    const NSRect area = NSMakeRect(0, 77, 1312, 746);
    auto bottom = oa::PlaceMacPet(NSMakePoint(1000, 100), oa::kMacPetFeetAbove, area);
    check(bottom.feet == oa::kMacPetFeetAbove && bottom.origin.y == 100 && bottom.bubble_top == 1,
      "lower-screen placement retains the existing bear and bubble layout");
    auto upper = oa::PlaceMacPet(NSMakePoint(1100, 900), oa::kMacPetFeetAbove, area);
    check(upper.feet == oa::kMacPetFeetBelow && upper.origin.x == 1012 && upper.origin.y == 611,
      "top-right drag reaches the work-area corner with the bubble below");
    check(NSMaxY(area) - (upper.origin.y + oa::kMacPetHeight - upper.feet + 100) == 24,
      "upper bear no longer reserves the empty message area above its head");
    auto reflow = oa::PlaceMacPet(NSMakePoint(1000, 620), oa::kMacPetFeetAbove, area);
    check(reflow.origin.y + oa::kMacPetHeight - reflow.feet == 626 && reflow.bubble_top == 133,
      "switching to a lower bubble preserves the bear screen anchor");
    auto again = oa::PlaceMacPet(reflow.origin, reflow.feet, area);
    check(NSEqualPoints(again.origin, reflow.origin) && again.feet == reflow.feet,
      "repeated notification layout does not drift the bear position");
    auto lower = oa::PlaceMacPet(NSMakePoint(1000, 500), oa::kMacPetFeetBelow, area);
    check(lower.feet == oa::kMacPetFeetAbove && lower.origin.y + 6 == 588,
      "dragging back down restores an upper bubble without moving the bear anchor");
    NSRect secondary = NSMakeRect(-1920, -200, 1920, 1080);
    auto other = oa::PlaceMacPet(NSMakePoint(-100, 1000), oa::kMacPetFeetAbove, secondary);
    check(other.origin.x == -300 && other.origin.y == 668 && other.feet == oa::kMacPetFeetBelow,
      "corner placement respects a secondary display with negative coordinates");
    auto left = oa::PlaceMacPet(NSMakePoint(-400, 100), oa::kMacPetFeetAbove, area);
    check(left.origin.x == NSMinX(area) && left.center == oa::kMacPetCenterLeft,
      "left drag places the bear at the left side instead of reserving the empty message width");
    check(left.center - 24 - 50 >= 6,
      "left placement reserves enough transparent canvas for the existing short walk");
    auto left_reflow = oa::PlaceMacPet(NSMakePoint(-20, 300), oa::kMacPetFeetAbove, area);
    check(left_reflow.origin.x + left_reflow.center == 224,
      "left reflow retains the bear screen anchor before reaching the work-area edge");
    auto left_again = oa::PlaceMacPet(left.origin, left.feet, area, left.center);
    check(NSEqualPoints(left_again.origin, left.origin) && left_again.center == left.center,
      "repeated left notifications do not drift the bear position");
    auto return_right = oa::PlaceMacPet(NSMakePoint(300, 100), left.feet, area, left.center);
    check(return_right.center == oa::kMacPetCenterRight && return_right.origin.x + return_right.center == 380,
      "moving away from the left edge restores the original layout without an anchor jump");
    auto upper_left = oa::PlaceMacPet(NSMakePoint(-400, 900), oa::kMacPetFeetAbove, area);
    check(upper_left.origin.x == NSMinX(area) && upper_left.origin.y == 611 &&
      upper_left.center == oa::kMacPetCenterLeft && upper_left.feet == oa::kMacPetFeetBelow,
      "top-left placement combines a left bear with a complete lower bubble");
    auto secondary_left = oa::PlaceMacPet(NSMakePoint(-2400, 100), oa::kMacPetFeetAbove, secondary);
    check(secondary_left.origin.x == NSMinX(secondary) && secondary_left.center == oa::kMacPetCenterLeft,
      "left placement uses the supplied negative-coordinate screen edge");
    {
      oa::MacDesktopPet pet;
      NSWindow* panel = nil;
      for (NSWindow* candidate in NSApp.windows) {
        if ([candidate.title isEqualToString:@"oaClient2 小熊通知"]) panel = candidate;
      }
      check(panel && !panel.visible, "pet starts hidden before login");
      check(!panel.opaque && panel.backgroundColor.alphaComponent == 0 && !panel.hasShadow,
        "panel retains a transparent background without a rectangular window shadow");
      check(panel.level == NSFloatingWindowLevel && !panel.parentWindow && !panel.hidesOnDeactivate,
        "pet is an independent floating panel across other apps and main-window minimization");
      check(!panel.canBecomeKeyWindow && !panel.canBecomeMainWindow,
        "passive notifications cannot steal keyboard focus");
      pet.Show();
      check(panel.visible, "successful session can show the native panel");
      auto render = [&](NSString* name) {
        NSView* view = panel.contentView;
        NSBitmapImageRep* image = [view bitmapImageRepForCachingDisplayInRect:view.bounds];
        [view cacheDisplayInRect:view.bounds toBitmapImageRep:image];
        size_t opaque = 0, clear = 0;
        for (NSInteger y = 0; y < image.pixelsHigh; ++y) for (NSInteger x = 0; x < image.pixelsWide; ++x) {
          CGFloat alpha = [image colorAtX:x y:y].alphaComponent;
          if (alpha > .9) ++opaque;
          if (alpha < .01) ++clear;
        }
        if ([name isEqualToString:@"native-upper-notification.png"]) {
          const double sx = image.pixelsWide / view.bounds.size.width, sy = image.pixelsHigh / view.bounds.size.height;
          check([image colorAtX:20 * sx y:20 * sy].alphaComponent < .01 &&
            [image colorAtX:20 * sx y:150 * sy].alphaComponent > .9,
            "native upper layout paints its bubble below the bear rather than reserving space above it");
        }
        if ([name isEqualToString:@"native-left-idle.png"]) {
          const double sx = image.pixelsWide / view.bounds.size.width, sy = image.pixelsHigh / view.bounds.size.height;
          check([image colorAtX:oa::kMacPetCenterLeft * sx y:156 * sy].alphaComponent > .9 &&
            [image colorAtX:oa::kMacPetCenterRight * sx y:156 * sy].alphaComponent < .01,
            "native left placement paints the bear on the left and leaves the old right anchor transparent");
        }
        if (argc > 1) {
          NSString* directory = [NSString stringWithUTF8String:argv[1]];
          NSData* png = [image representationUsingType:NSBitmapImageFileTypePNG properties:@{}];
          [png writeToFile:[directory stringByAppendingPathComponent:name] atomically:YES];
        }
        return std::pair(opaque, clear);
      };
      auto idle = render(@"native-idle.png");
      check(idle.first > 1000 && idle.second > 10000, "idle render contains an opaque bear and clear surrounding pixels");
      pet.Notify("新增詢報價：SYNTHETIC-6\n1 / 2　↑ 上一則　↓ 下一則", [] {});
      auto notice = render(@"native-notification.png");
      check(notice.first > idle.first + 10000 && notice.second > 1000,
        "notification adds a readable bubble while preserving transparent body surroundings");
      check(!panel.isKeyWindow, "showing a message keeps the native panel non-key");
      pet.CloseMessage();
      auto closed = render(@"native-dismissed.png");
      check(closed.first < notice.first && panel.visible, "dismissing the bubble keeps the bear visible");
      NSRect work = (panel.screen ?: NSScreen.mainScreen).visibleFrame;
      [panel setFrameOrigin:NSMakePoint(NSMaxX(work) - oa::kMacPetWidth, NSMaxY(work) - 130)];
      check(panel.frame.origin.y == NSMaxY(work) - 130,
        "Cocoa does not clamp the hidden upper message area before pet placement can reflow it");
      pet.Notify("新增詢報價：SYNTHETIC-6\n1 / 2　↑ 上一則　↓ 下一則", [] {});
      auto upper_notice = render(@"native-upper-notification.png");
      check(NSContainsRect(work, panel.frame) && upper_notice.first > 10000 && upper_notice.second > 1000,
        "upper-screen native notification keeps its complete panel inside the work area");
      pet.CloseMessage();
      render(@"native-upper-idle.png");
      [panel setFrameOrigin:NSMakePoint(NSMinX(work) - 200, NSMinY(work) + 100)];
      pet.Notify("新增詢報價：SYNTHETIC-6\n1 / 2　↑ 上一則　↓ 下一則", [] {});
      auto left_notice = render(@"native-left-notification.png");
      check(panel.frame.origin.x == NSMinX(work) && NSContainsRect(work, panel.frame) && left_notice.first > 10000,
        "left native placement keeps the complete message panel visible");
      pet.CloseMessage();
      render(@"native-left-idle.png");
      pet.Hide();
      check(!panel.visible, "logout hides the panel");
    }
    std::cout << checks << " checks, " << failures << " failures\n";
    return failures ? 1 : 0;
  }
}
