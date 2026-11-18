#include <windows.h>
#include <iostream>
#include <string>
#include "platform/windows/desktop_pet.h"

namespace {
int checks = 0, failures = 0, ticks = 0;
WNDPROC original = nullptr;

void Check(bool value, const char* label) {
  ++checks;
  std::cout << (value ? "PASS " : "FAIL ") << label << '\n';
  if (!value) ++failures;
}

LRESULT CALLBACK CountTimer(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
  if (message == WM_TIMER && wparam == 1) ++ticks;
  return CallWindowProcW(original, window, message, wparam, lparam);
}

HWND OwnPetWindow() {
  HWND found = nullptr;
  EnumThreadWindows(GetCurrentThreadId(), [](HWND window, LPARAM output) -> BOOL {
    wchar_t name[64]{};
    GetClassNameW(window, name, 64);
    if (std::wstring(name) != L"oaClient2.DesktopPet") return TRUE;
    *reinterpret_cast<HWND*>(output) = window;
    return FALSE;
  }, reinterpret_cast<LPARAM>(&found));
  return found;
}

void PumpFor(DWORD milliseconds) {
  const auto end = GetTickCount64() + milliseconds;
  MSG message{};
  while (GetTickCount64() < end) {
    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessageW(&message);
    }
    Sleep(5);
  }
}
}

int main() {
  //2026.11.18 by codex, send synthetic power messages only to a window owned by this isolated test process.
  oa::DesktopPet pet;
  const auto window = OwnPetWindow();
  Check(window != nullptr && !IsWindowVisible(window), "native pet starts hidden");
  if (!window) return 1;
  int resumes = 0, opened = 0;
  pet.SetResumeHandler([&] { ++resumes; });
  const auto foreground = GetForegroundWindow();
  pet.Notify("SYNTHETIC-RESUME", [&] { ++opened; });
  Check(IsWindowVisible(window) != FALSE, "native pet can show a message before suspend");
  original = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(CountTimer)));
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMSUSPEND, 0);
  ShowWindow(window, SW_HIDE);
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC, 0);
  Check(IsWindowVisible(window) && resumes == 1, "automatic resume restores native visibility and notifies the session");
  Check((GetWindowLongPtrW(window, GWL_EXSTYLE) & (WS_EX_LAYERED | WS_EX_NOACTIVATE)) ==
    (WS_EX_LAYERED | WS_EX_NOACTIVATE), "resume restores layered rendering without activation");
  Check(GetForegroundWindow() == foreground, "resume does not take foreground focus");
  const int before = ticks;
  PumpFor(180);
  Check(ticks >= before + 2, "resume restarts the real native animation timer");
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMRESUMESUSPEND, 0);
  Check(resumes == 1, "paired resume broadcasts do not restart the notification session twice");
  SendMessageW(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(15, 15));
  SendMessageW(window, WM_LBUTTONUP, 0, MAKELPARAM(15, 15));
  Check(opened == 1, "message action survives power recovery");
  ShowWindow(window, SW_HIDE);
  pet.Show();
  Check(IsWindowVisible(window) != FALSE, "show repairs a lost native window despite an already-visible intent flag");
  auto style = GetWindowLongPtrW(window, GWL_EXSTYLE);
  SetWindowLongPtrW(window, GWL_EXSTYLE, style & ~WS_EX_LAYERED);
  SendMessageW(window, WM_DWMCOMPOSITIONCHANGED, 0, 0);
  Check((GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_LAYERED) != 0 && IsWindowVisible(window),
    "composition recovery rebuilds the layered surface");
  SetWindowPos(window, nullptr, -5000, -5000, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
  SendMessageW(window, WM_DISPLAYCHANGE, 32, 0);
  RECT rect{};
  GetWindowRect(window, &rect);
  Check(rect.top > -5000 && rect.left > -5000, "display recovery returns an off-screen pet to an available monitor");
  pet.Hide();
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMSUSPEND, 0);
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC, 0);
  Check(!IsWindowVisible(window) && resumes == 2, "user-hidden pet stays hidden while its session may recheck login");
  SendMessageW(window, WM_DISPLAYCHANGE, 32, 0);
  Check(!IsWindowVisible(window), "display recovery does not unhide a user-hidden pet");
  SetWindowLongPtrW(window, GWL_EXSTYLE, GetWindowLongPtrW(window, GWL_EXSTYLE) & ~WS_EX_LAYERED);
  pet.Show();
  Check(IsWindowVisible(window) && (GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_LAYERED),
    "show rebuilds the surface even when the pet was intentionally hidden during sleep");
  pet.SetResumeHandler([&] { pet.Hide(); });
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMSUSPEND, 0);
  SendMessageW(window, WM_POWERBROADCAST, PBT_APMRESUMEAUTOMATIC, 0);
  Check(!IsWindowVisible(window), "login recheck can keep a logged-out pet hidden after resume");
  SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original));
  std::cout << checks << " checks, " << failures << " failures\n";
  return failures ? 1 : 0;
}
