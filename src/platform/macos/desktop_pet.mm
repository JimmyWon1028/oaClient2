#import <Cocoa/Cocoa.h>
#include <algorithm>
#include <array>
#include <chrono>
#include <vector>
#include "platform/macos/desktop_pet.h"
#include "platform/macos/desktop_pet_layout.h"
#include "app/desktop_helper_session.h"
#include "common/pet_animation.h"

//2026.11.18 by codex, only intentional browsing makes the otherwise nonactivating panel key.
@interface OaPetPanel : NSPanel
@property BOOL browsing;
@end
@implementation OaPetPanel
- (BOOL)canBecomeKeyWindow { return self.browsing; }
- (BOOL)canBecomeMainWindow { return NO; }
//2026.11.18 by codex, defer native frame clamping until the bear and its bubble choose their visible layout.
- (NSRect)constrainFrameRect:(NSRect)frame toScreen:(NSScreen*)screen { return frame; }
@end

@interface OaPetView : NSView {
 @public
  std::function<void()> paint;
  std::function<void(NSEvent*)> down, drag, up, key;
}
@end
@implementation OaPetView
- (BOOL)isFlipped { return YES; }
- (BOOL)acceptsFirstResponder { return YES; }
- (BOOL)acceptsFirstMouse:(NSEvent*)event { return YES; }
- (void)drawRect:(NSRect)rect { if (paint) paint(); }
- (void)mouseDown:(NSEvent*)event { if (down) down(event); }
- (void)mouseDragged:(NSEvent*)event { if (drag) drag(event); }
- (void)mouseUp:(NSEvent*)event { if (up) up(event); }
- (void)keyDown:(NSEvent*)event { if (key) key(event); }
@end

namespace oa {
namespace {
uint64_t Now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::steady_clock::now().time_since_epoch()).count();
}
NSString* Text(const std::string& value) { return [NSString stringWithUTF8String:value.c_str()]; }
}

struct MacDesktopPet::Impl {
  OaPetPanel* panel = nil;
  OaPetView* view = nil;
  NSTimer* timer = nil;
  id screen_observer = nil, focus_observer = nil;
  __weak NSWindow* previous_key = nil;
  NSRunningApplication* previous_app = nil;
  std::array<NSImage*, 24> frames{};
  std::array<NSRect, 24> bounds{};
  std::array<std::vector<uint8_t>, 24> alpha;
  std::array<int, 24> frame_widths{};
  std::array<double, 2> scales{1, 1};
  std::function<void()> click, dismiss, browse;
  std::function<void(int)> navigate;
  std::string text;
  bool visible = false, dragging = false, moved = false, pressed_message = false;
  NSPoint start{}, origin{};
  uint64_t started = 0, notified = kPetInactive, clicked = kPetInactive, due = kPetInactive;
  PetMotion motion;
  static constexpr double width = kMacPetWidth, height = kMacPetHeight;
  double feet = kMacPetFeetAbove, bubble_top = 1, center = kMacPetCenterRight;

  Impl() {
    Load(@"bear-sprites", 4, 2, 0);
    Load(@"bear-actions", 4, 4, 8);
    panel = [[OaPetPanel alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
      styleMask:NSWindowStyleMaskBorderless | NSWindowStyleMaskNonactivatingPanel
      backing:NSBackingStoreBuffered defer:NO];
    panel.title = @"oaClient2 小熊通知";
    panel.opaque = NO;
    panel.backgroundColor = NSColor.clearColor;
    panel.hasShadow = NO;
    panel.hidesOnDeactivate = NO;
    panel.level = NSFloatingWindowLevel;
    panel.collectionBehavior = NSWindowCollectionBehaviorCanJoinAllSpaces | NSWindowCollectionBehaviorFullScreenAuxiliary;
    panel.releasedWhenClosed = NO;
    panel.appearance = [NSAppearance appearanceNamed:NSAppearanceNameAqua];
    view = [[OaPetView alloc] initWithFrame:NSMakeRect(0, 0, width, height)];
    panel.contentView = view;
    view.accessibilityElement = YES;
    view.accessibilityRole = NSAccessibilityGroupRole;
    view.accessibilityLabel = @"小熊通知：雙擊瀏覽訊息，方向鍵切換，Esc收起";
    view->paint = [this] { Paint(); };
    view->down = [this](NSEvent* event) { Down(event); };
    view->drag = [this](NSEvent*) {
      if (!dragging) return;
      const auto point = NSEvent.mouseLocation;
      const double dx = point.x - start.x, dy = point.y - start.y;
      if (std::abs(dx) > 3 || std::abs(dy) > 3) moved = true;
      if (moved) [panel setFrameOrigin:NSMakePoint(origin.x + dx, origin.y + dy)];
    };
    view->up = [this](NSEvent*) {
      if (!dragging) return;
      dragging = false; Clamp();
      if (!moved && pressed_message && click) { auto callback = click; callback(); }
      else if (!moved && !pressed_message) due = Now() + static_cast<uint64_t>(NSEvent.doubleClickInterval * 1000);
    };
    view->key = [this](NSEvent* event) {
      if (!panel.browsing) return;
      if ((event.keyCode == 126 || event.keyCode == 125) && navigate) navigate(event.keyCode == 126 ? -1 : 1);
      else if (event.keyCode == 53) Dismiss();
    };
    NSRect area = NSScreen.mainScreen.visibleFrame;
    [panel setFrameOrigin:NSMakePoint(NSMaxX(area) - width - 12, NSMinY(area) + 12)];
    screen_observer = [NSNotificationCenter.defaultCenter addObserverForName:NSApplicationDidChangeScreenParametersNotification
      object:nil queue:nil usingBlock:^(NSNotification*) { Clamp(); }];
    focus_observer = [NSNotificationCenter.defaultCenter addObserverForName:NSWindowDidResignKeyNotification
      object:panel queue:nil usingBlock:^(NSNotification*) { EndBrowse(false); }];
  }

  ~Impl() {
    [timer invalidate];
    [NSNotificationCenter.defaultCenter removeObserver:screen_observer];
    [NSNotificationCenter.defaultCenter removeObserver:focus_observer];
    view->paint = {}; view->down = {}; view->drag = {}; view->up = {}; view->key = {};
    [panel orderOut:nil];
    [panel close];
  }

  void Load(NSString* name, int columns, int rows, int offset) {
    NSString* path = [NSBundle.mainBundle pathForResource:name ofType:@"png"];
    NSImage* sheet = [[NSImage alloc] initWithContentsOfFile:path];
    CGImageRef source = [sheet CGImageForProposedRect:nullptr context:nil hints:nil];
    if (!source) return;
    const int sw = CGImageGetWidth(source), sh = CGImageGetHeight(source);
    for (int f = 0; f < columns * rows; ++f) {
      int left = f % columns * sw / columns, top = f / columns * sh / rows;
      int w = (f % columns + 1) * sw / columns - left, h = (f / columns + 1) * sh / rows - top;
      CGImageRef crop = CGImageCreateWithImageInRect(source, CGRectMake(left, top, w, h));
      std::vector<uint8_t> pixels(w * h * 4);
      CGColorSpaceRef color = CGColorSpaceCreateDeviceRGB();
      CGContextRef context = CGBitmapContextCreate(pixels.data(), w, h, 8, w * 4, color,
        static_cast<CGBitmapInfo>(kCGImageAlphaPremultipliedLast) | kCGBitmapByteOrder32Big);
      CGColorSpaceRelease(color);
      if (!context || !crop) { if (context) CGContextRelease(context); if (crop) CGImageRelease(crop); continue; }
      CGContextDrawImage(context, CGRectMake(0, 0, w, h), crop);
      CGImageRelease(crop);
      //2026.11.18 by codex, remove only edge-connected white matte while retaining white details inside the bear.
      std::vector<bool> visited(w * h);
      std::vector<int> queue;
      auto visit = [&](int x, int y) {
        if (x < 0 || y < 0 || x >= w || y >= h || visited[y * w + x]) return;
        visited[y * w + x] = true;
        auto p = &pixels[(y * w + x) * 4];
        if (p[0] > 232 && p[1] > 232 && p[2] > 232) queue.push_back(y * w + x);
      };
      for (int x = 0; x < w; ++x) { visit(x, 0); visit(x, h - 1); }
      for (int y = 0; y < h; ++y) { visit(0, y); visit(w - 1, y); }
      for (size_t i = 0; i < queue.size(); ++i) {
        int x = queue[i] % w, y = queue[i] / w;
        std::fill_n(&pixels[(y * w + x) * 4], 4, 0);
        visit(x - 1, y); visit(x + 1, y); visit(x, y - 1); visit(x, y + 1);
      }
      int x1 = w, y1 = h, x2 = -1, y2 = -1;
      for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
        if (pixels[(y * w + x) * 4 + 3] < 32) continue;
        x1 = std::min(x1, x); x2 = std::max(x2, x); y1 = std::min(y1, y); y2 = std::max(y2, y);
      }
      frame_widths[offset + f] = w;
      alpha[offset + f].resize(w * h);
      for (int i = 0; i < w * h; ++i) alpha[offset + f][i] = pixels[i * 4 + 3];
      CGImageRef image = CGBitmapContextCreateImage(context);
      CGContextRelease(context);
      frames[offset + f] = [[NSImage alloc] initWithCGImage:image size:NSMakeSize(w, h)];
      CGImageRelease(image);
      if (x2 >= x1 && y2 >= y1) bounds[offset + f] = NSMakeRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    }
    if (bounds[offset].size.height > 0) scales[offset == 0 ? 0 : 1] = 100.0 / bounds[offset].size.height;
  }

  void Clamp() {
    NSRect frame = panel.frame;
    NSScreen* screen = panel.screen ?: NSScreen.mainScreen;
    NSRect area = screen.visibleFrame;
    const auto placement = PlaceMacPet(frame.origin, feet, area, center);
    feet = placement.feet; bubble_top = placement.bubble_top; center = placement.center;
    [panel setFrameOrigin:placement.origin];
    view.needsDisplay = YES;
  }

  void Sprite(int index, double alpha, NSCompositingOperation operation) {
    if (!frames[index] || bounds[index].size.height <= 0) index = 0;
    NSRect crop = bounds[index];
    const double scale = scales[index < 8 ? 0 : 1], w = crop.size.width * scale, h = crop.size.height * scale;
    [NSGraphicsContext saveGraphicsState];
    NSAffineTransform* transform = [NSAffineTransform transform];
    [transform translateXBy:center + motion.x yBy:feet + motion.y];
    [transform rotateByDegrees:motion.angle];
    [transform scaleXBy:motion.scale_x yBy:motion.scale_y];
    [transform concat];
    //2026.11.18 by codex, NSImage source coordinates use a bottom-left origin even in a flipped destination view.
    crop.origin.y = frames[index].size.height - NSMaxY(crop);
    [frames[index] drawInRect:NSMakeRect(-w / 2, -h, w, h) fromRect:crop operation:operation
      fraction:alpha respectFlipped:YES hints:nil];
    [NSGraphicsContext restoreGraphicsState];
  }

  void Paint() {
    [NSColor.clearColor setFill]; NSRectFillUsingOperation(view.bounds, NSCompositingOperationCopy);
    const auto now = Now();
    if (!dragging) motion = SamplePetMotion(now - started, notified == kPetInactive ? kPetInactive : now - notified,
      clicked == kPetInactive ? kPetInactive : now - clicked, panel.browsing || !text.empty() || due != kPetInactive);
    if (motion.previous != motion.frame && motion.blend < 1) {
      //2026.11.18 by codex, additive weighted premultiplied layers preserve opacity while cross-fading poses.
      Sprite(motion.previous, 1 - motion.blend, NSCompositingOperationSourceOver);
      Sprite(motion.frame, motion.blend, NSCompositingOperationPlusLighter);
    } else Sprite(motion.frame, 1, NSCompositingOperationSourceOver);
    if (motion.sparkle > 0) {
      [[NSColor colorWithSRGBRed:.92 green:.62 blue:.13 alpha:motion.sparkle] setStroke];
      NSBezierPath* stars = [NSBezierPath bezierPath]; stars.lineWidth = 1.8;
      for (int i = 0; i < 3; ++i) {
        double x = center + (i == 1 ? 40 : -40) + motion.x, y = feet - 68 - i * 19 + motion.y;
        double r = 3 + 3 * motion.sparkle;
        [stars moveToPoint:NSMakePoint(x - r, y)]; [stars lineToPoint:NSMakePoint(x + r, y)];
        [stars moveToPoint:NSMakePoint(x, y - r)]; [stars lineToPoint:NSMakePoint(x, y + r)];
      }
      [stars stroke];
    }
    if (!text.empty()) {
      NSRect bubble = NSMakeRect(1, bubble_top, width - 2, 78);
      [[NSColor colorWithSRGBRed:1 green:.985 blue:.89 alpha:.98] setFill]; NSRectFill(bubble);
      [[NSColor colorWithSRGBRed:.74 green:.53 blue:.18 alpha:1] setStroke];
      [NSBezierPath strokeRect:bubble];
      NSDictionary* attributes = @{NSFontAttributeName:[NSFont systemFontOfSize:13],
        NSForegroundColorAttributeName:[NSColor colorWithSRGBRed:.24 green:.17 blue:.08 alpha:1]};
      [Text(text) drawInRect:NSMakeRect(10, bubble_top + 7, width - 42, 62) withAttributes:attributes];
      [@"×" drawInRect:NSMakeRect(width - 25, bubble_top + 4, 22, 26) withAttributes:@{NSFontAttributeName:[NSFont systemFontOfSize:22]}];
    }
  }

  void BeginBrowse() {
    due = clicked = kPetInactive;
    if (!panel.browsing) { previous_key = NSApp.keyWindow; previous_app = NSWorkspace.sharedWorkspace.frontmostApplication; }
    panel.browsing = YES;
    if (browse) browse();
    [NSApp activateIgnoringOtherApps:YES];
    [panel makeKeyWindow]; [panel makeFirstResponder:view];
  }

  void EndBrowse(bool restore) {
    bool was_key = panel.isKeyWindow;
    NSWindow* restore_key = previous_key;
    NSRunningApplication* restore_app = previous_app;
    panel.browsing = NO;
    if (was_key) [panel resignKeyWindow];
    if (restore && was_key) {
      if (restore_app && restore_app.processIdentifier != NSProcessInfo.processInfo.processIdentifier) [restore_app activateWithOptions:0];
      else [restore_key makeKeyWindow];
    }
    previous_key = nil; previous_app = nil;
  }

  void CloseMessage() {
    text.clear(); click = {}; dismiss = {}; notified = kPetInactive;
    EndBrowse(true); view.needsDisplay = YES;
  }
  void Dismiss() { auto callback = dismiss; CloseMessage(); if (callback) callback(); }

  void Down(NSEvent* event) {
    auto point = [view convertPoint:event.locationInWindow fromView:nil];
    if (!text.empty() && point.x >= width - 30 && point.y >= bubble_top && point.y < bubble_top + 30) { Dismiss(); return; }
    due = kPetInactive;
    if (event.clickCount == 2 && !InBubble(point)) { dragging = false; BeginBrowse(); return; }
    start = NSEvent.mouseLocation; origin = panel.frame.origin;
    dragging = true; moved = false; pressed_message = InBubble(point);
  }

  bool Hit(NSPoint point, int index) {
    if (alpha[index].empty()) return false;
    const double x = point.x - (center + motion.x), y = point.y - (feet + motion.y);
    const double angle = motion.angle * kPetPi / 180, scale = scales[index < 8 ? 0 : 1];
    const double rx = (std::cos(angle) * x + std::sin(angle) * y) / motion.scale_x;
    const double ry = (-std::sin(angle) * x + std::cos(angle) * y) / motion.scale_y;
    const auto crop = bounds[index];
    const int px = static_cast<int>(std::floor(crop.origin.x + rx / scale + crop.size.width / 2));
    const int py = static_cast<int>(std::floor(crop.origin.y + ry / scale + crop.size.height));
    const int w = frame_widths[index], h = static_cast<int>(alpha[index].size()) / w;
    return px >= 0 && px < w && py >= 0 && py < h && alpha[index][py * w + px] >= 32;
  }

  bool InBubble(NSPoint point) const {
    return !text.empty() && NSPointInRect(point, NSMakeRect(0, bubble_top - 1, width, 80));
  }

  void Tick() {
    const auto now = Now();
    if (due != kPetInactive && now >= due) { clicked = now; due = kPetInactive; }
    //2026.11.18 by codex, empty window space passes through without installing global input monitors.
    auto point = [view convertPoint:[panel convertPointFromScreen:NSEvent.mouseLocation] fromView:nil];
    const bool bubble = InBubble(point);
    const bool body = Hit(point, motion.frame) || (motion.blend < 1 && Hit(point, motion.previous));
    panel.ignoresMouseEvents = !dragging && !bubble && !body;
    view.needsDisplay = YES;
  }
};

MacDesktopPet::MacDesktopPet() : impl_(std::make_unique<Impl>()) {}
MacDesktopPet::~MacDesktopPet() = default;
void MacDesktopPet::Show() {
  if (impl_->visible) return;
  impl_->Clamp();
  impl_->visible = true; impl_->started = Now();
  [impl_->panel orderFrontRegardless];

  auto state = impl_.get();
  impl_->timer = [NSTimer timerWithTimeInterval:1.0 / 30 repeats:YES block:^(NSTimer*) { state->Tick(); }];
  [NSRunLoop.mainRunLoop addTimer:impl_->timer forMode:NSRunLoopCommonModes];
  impl_->Tick();
}
void MacDesktopPet::Hide() {
  [impl_->timer invalidate]; impl_->timer = nil;
  impl_->visible = false; impl_->dragging = false; impl_->due = impl_->clicked = kPetInactive;
  impl_->CloseMessage(); [impl_->panel orderOut:nil];
}
void MacDesktopPet::CloseMessage() { impl_->CloseMessage(); }
void MacDesktopPet::SetBrowseHandlers(std::function<void()> open, std::function<void(int)> navigate) {
  impl_->browse = std::move(open); impl_->navigate = std::move(navigate);
}
void MacDesktopPet::Notify(const std::string& text, std::function<void()> click, std::function<void()> dismiss) {
  impl_->text = text; impl_->click = std::move(click); impl_->dismiss = std::move(dismiss);
  impl_->notified = Now(); impl_->due = impl_->clicked = kPetInactive;
  if (!impl_->dragging) impl_->Clamp();
  Show();
}
CefRefPtr<CefImage> MacDesktopPet::Icon() {
  auto icon = CefImage::CreateImage();
  NSImage* image = impl_->frames[0];
  if (!image) return icon;
  NSBitmapImageRep* bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:nullptr pixelsWide:20 pixelsHigh:20
    bitsPerSample:8 samplesPerPixel:4 hasAlpha:YES isPlanar:NO colorSpaceName:NSDeviceRGBColorSpace bytesPerRow:80 bitsPerPixel:32];
  [NSGraphicsContext saveGraphicsState];
  NSGraphicsContext.currentContext = [NSGraphicsContext graphicsContextWithBitmapImageRep:bitmap];
  [image drawInRect:NSMakeRect(-3, -1, 26, 23)];
  [NSGraphicsContext restoreGraphicsState];
  icon->AddBitmap(1, 20, 20, CEF_COLOR_TYPE_RGBA_8888, CEF_ALPHA_TYPE_PREMULTIPLIED, bitmap.bitmapData, 1600);
  return icon;
}
std::shared_ptr<DesktopHelper> CreateMacDesktopHelper(std::shared_ptr<AppContext> context) {
  return std::make_shared<DesktopHelperSession<MacDesktopPet>>(std::move(context));
}
}
