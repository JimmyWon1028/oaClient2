#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <algorithm>
#include <array>
#include <vector>
#include "platform/windows/desktop_pet.h"
#include "platform/windows/desktop_pet_layout.h"
#include "platform/windows/pet_animation.h"
#include "platform/windows/resources.h"

namespace oa {
using namespace Gdiplus;

struct DesktopPet::Impl {
  HWND window = nullptr;
  ULONG_PTR gdiplus = 0;
  std::array<std::unique_ptr<Bitmap>, 24> frames;
  std::array<Rect, 24> bounds;
  std::array<float, 2> sprite_scale{1, 1};
  std::wstring text;
  std::function<void()> click;
  std::function<void()> dismiss;
  std::function<void()> browse;
  std::function<void(int)> navigate;
  std::function<void()> resume;
  HWND previous_foreground = nullptr;
  bool keyboard_mode = false, pressed_message = false;
  POINT start{}, position{};
  bool dragging = false, moved = false, visible = false, suspended = false;
  ULONGLONG last_resume = 0;
  ULONGLONG animation_started = 0;
  ULONGLONG notified_at = kPetInactive, clicked_at = kPetInactive, click_due = kPetInactive;
  PetMotion current_motion;
  int width = kWindowsPetWidth, height = kWindowsPetHeight;
  WindowsPetLayout layout{{}, kWindowsPetFeetAbove, 1};

  Impl() {
    GdiplusStartupInput input;
    if (GdiplusStartup(&gdiplus, &input, nullptr) != Ok) return;
    LoadFrames(IDR_PNG_DESKTOP_BEAR, 4, 2, 0);
    LoadFrames(IDR_PNG_DESKTOP_BEAR_ACTIONS, 4, 4, 8);
    WNDCLASSW cls{};
    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = Procedure;
    cls.hInstance = GetModuleHandleW(nullptr);
    cls.lpszClassName = L"oaClient2.DesktopPet";
    cls.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&cls);
    window = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
      cls.lpszClassName, L"oaClient2 小熊通知", WS_POPUP, 0, 0, width, height,
      nullptr, nullptr, cls.hInstance, this);
    if (window) {
      const auto monitor = MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY);
      MONITORINFO info{sizeof(info)};
      GetMonitorInfoW(monitor, &info);
      SetWindowPos(window, HWND_TOPMOST, info.rcWork.right - width - 12,
        info.rcWork.bottom - height - 12, width, height, SWP_NOACTIVATE);
    }
  }

  ~Impl() {
    if (window) DestroyWindow(window);
    for (auto& frame : frames) frame.reset();
    if (gdiplus) GdiplusShutdown(gdiplus);
  }

  void LoadFrames(int resource_id, int columns, int rows, int offset) {
    const auto module = GetModuleHandleW(nullptr);
    const auto resource = FindResourceW(module, MAKEINTRESOURCEW(resource_id), RT_RCDATA);
    if (!resource) return;
    const auto size = SizeofResource(module, resource);
    const auto data = LockResource(LoadResource(module, resource));
    HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, size);
    if (!memory) return;
    auto destination = GlobalLock(memory);
    if (!destination) { GlobalFree(memory); return; }
    memcpy(destination, data, size);
    GlobalUnlock(memory);
    IStream* stream = nullptr;
    if (FAILED(CreateStreamOnHGlobal(memory, TRUE, &stream))) { GlobalFree(memory); return; }
    {
      Bitmap sheet(stream);
      for (int frame = 0; frame < columns * rows && sheet.GetLastStatus() == Ok; ++frame) {
        const int left = (frame % columns) * sheet.GetWidth() / columns;
        const int top = (frame / columns) * sheet.GetHeight() / rows;
        const int right = (frame % columns + 1) * sheet.GetWidth() / columns;
        const int bottom = (frame / columns + 1) * sheet.GetHeight() / rows;
        frames[offset + frame].reset(sheet.Clone(left, top, right - left, bottom - top, PixelFormat32bppARGB));
        auto& image = *frames[offset + frame];
        //2026.11.17 by codex, remove only edge-connected near-white matte from the original confirmed sprite.
        const int w = image.GetWidth(), h = image.GetHeight();
        Rect full(0, 0, w, h);
        BitmapData locked{};
        if (image.LockBits(&full, ImageLockModeRead | ImageLockModeWrite, PixelFormat32bppARGB, &locked) != Ok) continue;
        auto pixel = [&](int x, int y) -> UINT32& {
          return reinterpret_cast<UINT32*>(static_cast<BYTE*>(locked.Scan0) + y * locked.Stride)[x];
        };
        std::vector<bool> visited(w * h);
        std::vector<int> queue;
        auto visit = [&](int x, int y) {
          if (x < 0 || x >= w || y < 0 || y >= h || visited[y * w + x]) return;
          visited[y * w + x] = true;
          Color color(pixel(x, y));
          if (color.GetR() > 232 && color.GetG() > 232 && color.GetB() > 232) queue.push_back(y * w + x);
        };
        for (int x = 0; x < w; ++x) { visit(x, 0); visit(x, h - 1); }
        for (int y = 0; y < h; ++y) { visit(0, y); visit(w - 1, y); }
        for (size_t i = 0; i < queue.size(); ++i) {
          const int x = queue[i] % w, y = queue[i] / w;
          pixel(x, y) = 0;
          visit(x - 1, y); visit(x + 1, y); visit(x, y - 1); visit(x, y + 1);
        }
        //2026.11.17 by codex, align cropped poses by a common scale and foot baseline instead of stretching seated frames.
        int x1 = w, y1 = h, x2 = -1, y2 = -1;
        for (int y = 0; y < h; ++y) {
          for (int x = 0; x < w; ++x) {
            if ((pixel(x, y) >> 24) < 32) continue;
            x1 = std::min(x1, x); y1 = std::min(y1, y);
            x2 = std::max(x2, x); y2 = std::max(y2, y);
          }
        }
        image.UnlockBits(&locked);
        if (x2 >= x1 && y2 >= y1) bounds[offset + frame] = Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
      }
      if (bounds[offset].Height > 0) sprite_scale[offset == 0 ? 0 : 1] = 100.0f / bounds[offset].Height;
    }
    stream->Release();
  }

  void DrawSprite(Graphics& graphics, int frame, float alpha, const PetMotion& motion) {
    if (alpha <= 0) return;
    if (!frames[frame] || bounds[frame].Height == 0) frame = 0;
    const auto& crop = bounds[frame];
    const float scale = sprite_scale[frame < 8 ? 0 : 1];
    const float w = crop.Width * scale, h = crop.Height * scale;
    const float center = width - 56.0f + motion.x, feet = layout.feet + motion.y;
    const auto saved = graphics.Save();
    graphics.TranslateTransform(center, feet);
    graphics.RotateTransform(motion.angle);
    graphics.ScaleTransform(motion.scale_x, motion.scale_y);
    ColorMatrix opacity = {{{1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0},
      {0, 0, 0, alpha, 0}, {0, 0, 0, 0, 1}}};
    ImageAttributes attributes;
    attributes.SetColorMatrix(&opacity);
    graphics.DrawImage(frames[frame].get(), RectF(-w / 2, -h, w, h), static_cast<REAL>(crop.X),
      static_cast<REAL>(crop.Y), static_cast<REAL>(crop.Width), static_cast<REAL>(crop.Height), UnitPixel, &attributes);
    graphics.Restore(saved);
  }

  void Clamp() {
    RECT rect;
    GetWindowRect(window, &rect);
    MONITORINFO info{sizeof(info)};
    const POINT anchor{rect.left + width - 56, rect.top + layout.feet};
    GetMonitorInfoW(MonitorFromPoint(anchor, MONITOR_DEFAULTTONEAREST), &info);
    layout = PlaceWindowsPet({rect.left, rect.top}, layout.feet, info.rcWork);
    SetWindowPos(window, HWND_TOPMOST, layout.origin.x, layout.origin.y,
      width, height, SWP_NOACTIVATE);
  }

  void Paint() {
    if (!window || !frames[0]) return;
    HDC screen = GetDC(nullptr);
    HDC dc = CreateCompatibleDC(screen);
    BITMAPINFO info{};
    info.bmiHeader = {sizeof(BITMAPINFOHEADER), width, -height, 1, 32, BI_RGB};
    void* pixels = nullptr;
    HBITMAP bitmap = CreateDIBSection(screen, &info, DIB_RGB_COLORS, &pixels, nullptr, 0);
    if (!bitmap) { DeleteDC(dc); ReleaseDC(nullptr, screen); return; }
    auto previous = SelectObject(dc, bitmap);
    {
      Bitmap canvas(width, height, width * 4, PixelFormat32bppPARGB, static_cast<BYTE*>(pixels));
      Graphics graphics(&canvas);
      graphics.Clear(Color(0, 0, 0, 0));
      graphics.SetSmoothingMode(SmoothingModeAntiAlias);
      graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
      const auto now = GetTickCount64();
      if (!dragging) current_motion = SamplePetMotion(now - animation_started,
        notified_at == kPetInactive ? kPetInactive : now - notified_at,
        clicked_at == kPetInactive ? kPetInactive : now - clicked_at,
        keyboard_mode || !text.empty() || click_due != kPetInactive);
      if (current_motion.previous != current_motion.frame && current_motion.blend < 1) {
        //2026.11.17 by codex, blend premultiplied pixels linearly so overlapping poses do not become translucent.
        DrawSprite(graphics, current_motion.previous, 1, current_motion);
        std::vector<BYTE> next_pixels(width * height * 4);
        {
          Bitmap next(width, height, width * 4, PixelFormat32bppPARGB, next_pixels.data());
          Graphics layer(&next);
          layer.Clear(Color(0, 0, 0, 0));
          layer.SetInterpolationMode(InterpolationModeHighQualityBicubic);
          DrawSprite(layer, current_motion.frame, 1, current_motion);
        }
        graphics.Flush(FlushIntentionSync);
        auto target = static_cast<BYTE*>(pixels);
        const unsigned blend = static_cast<unsigned>(current_motion.blend * 256);
        for (size_t i = 0; i < next_pixels.size(); ++i) {
          target[i] = static_cast<BYTE>((target[i] * (256 - blend) + next_pixels[i] * blend) / 256);
        }
      } else {
        DrawSprite(graphics, current_motion.frame, 1, current_motion);
      }
      if (current_motion.sparkle > 0) {
        //2026.11.17 by codex, keep click feedback quiet and local to the pet with transparent vector sparkles.
        Pen star(Color(static_cast<BYTE>(230 * current_motion.sparkle), 235, 157, 32), 1.8f);
        for (int i = 0; i < 3; ++i) {
          const float x = width - 56.0f + (i == 1 ? 40 : -40) + current_motion.x;
          const float y = layout.feet - 68.0f - i * 19 + current_motion.y;
          const float radius = 3 + 3 * current_motion.sparkle;
          graphics.DrawLine(&star, x - radius, y, x + radius, y);
          graphics.DrawLine(&star, x, y - radius, x, y + radius);
        }
      }
      if (!text.empty()) {
        SolidBrush background(Color(250, 255, 251, 227)), foreground(Color(255, 62, 44, 20));
        Pen border(Color(255, 189, 135, 46), 1);
        graphics.FillRectangle(&background, 1, layout.bubble_top, width - 2, 78);
        graphics.DrawRectangle(&border, 1, layout.bubble_top, width - 3, 77);
        Font font(L"Microsoft JhengHei UI", 13, FontStyleRegular, UnitPixel);
        StringFormat format;
        format.SetTrimming(StringTrimmingEllipsisCharacter);
        graphics.DrawString(text.c_str(), -1, &font,
          RectF(10, static_cast<REAL>(layout.bubble_top + 7), static_cast<REAL>(width - 42), 68), &format, &foreground);
        Pen close(Color(255, 87, 66, 36), 1.5f);
        graphics.DrawLine(&close, width - 21, layout.bubble_top + 9, width - 11, layout.bubble_top + 19);
        graphics.DrawLine(&close, width - 11, layout.bubble_top + 9, width - 21, layout.bubble_top + 19);
      }
    }
    RECT rect;
    GetWindowRect(window, &rect);
    POINT point{rect.left, rect.top}, zero{};
    SIZE size{width, height};
    BLENDFUNCTION blend{AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    UpdateLayeredWindow(window, screen, &point, &size, dc, &zero, 0, &blend, ULW_ALPHA);
    SelectObject(dc, previous);
    DeleteObject(bitmap);
    DeleteDC(dc);
    ReleaseDC(nullptr, screen);
  }

  //2026.11.17 by codex, accept arrow keys only after an intentional double-click, never through a global hook.
  void BeginBrowse() {
    click_due = clicked_at = kPetInactive;
    if (!keyboard_mode) previous_foreground = GetForegroundWindow();
    keyboard_mode = true;
    SetWindowLongPtrW(window, GWL_EXSTYLE, GetWindowLongPtrW(window, GWL_EXSTYLE) & ~WS_EX_NOACTIVATE);
    if (browse) browse();
    SetForegroundWindow(window);
    SetFocus(window);
  }

  void EndBrowse(bool restore) {
    keyboard_mode = false;
    SetWindowLongPtrW(window, GWL_EXSTYLE, GetWindowLongPtrW(window, GWL_EXSTYLE) | WS_EX_NOACTIVATE);
    if (restore && GetForegroundWindow() == window && IsWindow(previous_foreground)) {
      SetForegroundWindow(previous_foreground);
    }
    previous_foreground = nullptr;
  }

  void CloseMessage() {
    text.clear(); click = {}; dismiss = {}; notified_at = kPetInactive;
    EndBrowse(true);
    Paint();
  }

  //2026.11.18 by codex, rebuild the layered surface and native timer after power or display recovery without taking focus.
  void RestoreVisuals() {
    if (!window || !visible || suspended) return;
    dragging = false;
    if (GetCapture() == window) ReleaseCapture();
    click_due = clicked_at = kPetInactive;
    EndBrowse(false);
    KillTimer(window, 1);
    ShowWindow(window, SW_HIDE);
    const auto style = GetWindowLongPtrW(window, GWL_EXSTYLE);
    SetWindowLongPtrW(window, GWL_EXSTYLE, style & ~WS_EX_LAYERED);
    SetWindowLongPtrW(window, GWL_EXSTYLE, style | WS_EX_LAYERED | WS_EX_NOACTIVATE);
    animation_started = GetTickCount64();
    Clamp();
    Paint();
    SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0,
      SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetTimer(window, 1, 33, nullptr);
  }

  void Resume() {
    suspended = false;
    RestoreVisuals();
    const auto now = GetTickCount64();
    //2026.11.18 by codex, coalesce the automatic and user-present resume broadcasts but still repair visuals on both.
    if (last_resume == 0 || now - last_resume >= 1500) {
      last_resume = now;
      if (resume) resume();
    }
  }

  static LRESULT CALLBACK Procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    auto self = reinterpret_cast<Impl*>(GetWindowLongPtrW(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
      self = static_cast<Impl*>(reinterpret_cast<CREATESTRUCTW*>(lparam)->lpCreateParams);
      SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }
    if (!self) return DefWindowProcW(window, message, wparam, lparam);
    if (message == WM_POWERBROADCAST) {
      if (wparam == PBT_APMSUSPEND) {
        self->suspended = true;
        self->last_resume = 0;
        self->click_due = self->clicked_at = kPetInactive;
        KillTimer(window, 1);
        return TRUE;
      }
      if (wparam == PBT_APMRESUMEAUTOMATIC || wparam == PBT_APMRESUMESUSPEND || wparam == PBT_APMRESUMECRITICAL) {
        self->Resume();
        return TRUE;
      }
    }
    if (message == WM_MOUSEACTIVATE) return self->keyboard_mode ? MA_ACTIVATE : MA_NOACTIVATE;
    if (message == WM_KILLFOCUS) self->EndBrowse(false);
    if (message == WM_KEYDOWN && self->keyboard_mode) {
      if ((wparam == VK_UP || wparam == VK_DOWN) && self->navigate) {
        self->navigate(wparam == VK_UP ? -1 : 1);
        return 0;
      }
      if (wparam == VK_ESCAPE) {
        auto dismiss = self->dismiss;
        self->CloseMessage();
        if (dismiss) dismiss();
        return 0;
      }
    }
    if (message == WM_LBUTTONDBLCLK && self->layout.InBody(HIWORD(lparam))) {
      self->dragging = false;
      ReleaseCapture();
      self->BeginBrowse();
      return 0;
    }
    if (message == WM_TIMER) {
      const auto now = GetTickCount64();
      if (self->click_due != kPetInactive && now >= self->click_due) {
        self->clicked_at = now;
        self->click_due = kPetInactive;
      }
      self->Paint();
      return 0;
    }
    if (message == WM_LBUTTONDOWN) {
      if (!self->text.empty() && LOWORD(lparam) >= self->width - 30 &&
          HIWORD(lparam) >= self->layout.bubble_top && HIWORD(lparam) < self->layout.bubble_top + 30) {
        auto dismiss = self->dismiss;
        self->CloseMessage();
        if (dismiss) dismiss();
        return 0;
      }
      GetCursorPos(&self->start);
      RECT rect;
      GetWindowRect(window, &rect);
      self->position = {rect.left, rect.top};
      self->dragging = true; self->moved = false;
      self->click_due = kPetInactive;
      self->pressed_message = !self->text.empty() && self->layout.InBubble(HIWORD(lparam));
      SetCapture(window);
      return 0;
    }
    if (message == WM_MOUSEMOVE && self->dragging) {
      POINT point;
      GetCursorPos(&point);
      const int dx = point.x - self->start.x, dy = point.y - self->start.y;
      if (abs(dx) > 3 || abs(dy) > 3) self->moved = true;
      if (self->moved) SetWindowPos(window, HWND_TOPMOST, self->position.x + dx,
        self->position.y + dy, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
      return 0;
    }
    if (message == WM_LBUTTONUP && self->dragging) {
      self->dragging = false;
      ReleaseCapture();
      self->Clamp();
      self->Paint();
      if (!self->moved && self->pressed_message && self->click) { auto click = self->click; click(); }
      else if (!self->moved && !self->pressed_message) {
        //2026.11.17 by codex, defer single-click feedback until the system double-click window has elapsed.
        self->click_due = GetTickCount64() + GetDoubleClickTime();
      }
      return 0;
    }
    if (message == WM_CAPTURECHANGED) self->dragging = false;
    if (message == WM_DISPLAYCHANGE || message == WM_DPICHANGED || message == WM_DWMCOMPOSITIONCHANGED) {
      self->Clamp();
      self->RestoreVisuals();
      return 0;
    }
    if (message == WM_CLOSE) return 0;
    return DefWindowProcW(window, message, wparam, lparam);
  }
};

DesktopPet::DesktopPet() : impl_(std::make_unique<Impl>()) {}
DesktopPet::~DesktopPet() = default;
CefRefPtr<CefImage> DesktopPet::Icon() {
  auto image = CefImage::CreateImage();
  if (!impl_->frames[0]) return image;
  std::vector<BYTE> pixels(20 * 20 * 4);
  Bitmap bitmap(20, 20, 80, PixelFormat32bppPARGB, pixels.data());
  {
    Graphics graphics(&bitmap);
    graphics.Clear(Color(0, 0, 0, 0));
    graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    graphics.DrawImage(impl_->frames[0].get(), -3, -1, 26, 23);
  }
  image->AddBitmap(1, 20, 20, CEF_COLOR_TYPE_BGRA_8888, CEF_ALPHA_TYPE_PREMULTIPLIED,
    pixels.data(), pixels.size());
  return image;
}
void DesktopPet::Show() {
  if (!impl_->window) return;
  if (impl_->visible) {
    if (!IsWindowVisible(impl_->window)) impl_->RestoreVisuals();
    return;
  }
  //2026.11.17 by codex, repeated login observations must not restart the animation timer or its monotonic timeline.
  impl_->visible = true;
  impl_->RestoreVisuals();
}
void DesktopPet::Hide() {
  if (!impl_->window) return;
  KillTimer(impl_->window, 1);
  impl_->visible = false;
  impl_->click_due = impl_->clicked_at = kPetInactive;
  ShowWindow(impl_->window, SW_HIDE);
  impl_->CloseMessage();
}
void DesktopPet::CloseMessage() { impl_->CloseMessage(); }
void DesktopPet::SetBrowseHandlers(std::function<void()> open, std::function<void(int)> navigate) {
  impl_->browse = std::move(open);
  impl_->navigate = std::move(navigate);
}
void DesktopPet::SetResumeHandler(std::function<void()> resume) { impl_->resume = std::move(resume); }
void DesktopPet::Notify(const std::string& text, std::function<void()> click, std::function<void()> dismiss) {
  const int length = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
  impl_->text.resize(length);
  MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), impl_->text.data(), length);
  impl_->click = std::move(click);
  impl_->dismiss = std::move(dismiss);
  if (!impl_->dragging) impl_->Clamp();
  impl_->notified_at = GetTickCount64();
  impl_->click_due = impl_->clicked_at = kPetInactive;
  Show();
}
}
