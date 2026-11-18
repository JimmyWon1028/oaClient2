#pragma once

#include <windows.h>
#include <algorithm>

namespace oa {
inline constexpr int kWindowsPetWidth = 300, kWindowsPetHeight = 212;
inline constexpr int kWindowsPetFeetAbove = 206, kWindowsPetFeetBelow = 124;

struct WindowsPetLayout {
  POINT origin;
  int feet, bubble_top;

  bool InBubble(int y) const { return y >= bubble_top - 1 && y < bubble_top + 79; }
  bool InBody(int y) const { return y >= feet - 122 && y < feet + 6; }
};

//2026.11.18 by codex, place the message below near the screen top and retain the bear's screen-space foot anchor.
inline WindowsPetLayout PlaceWindowsPet(POINT origin, int previous_feet, RECT area) {
  const LONG anchor = origin.y + previous_feet;
  const bool below = anchor - kWindowsPetFeetAbove < area.top;
  const int feet = below ? kWindowsPetFeetBelow : kWindowsPetFeetAbove;
  origin.y = anchor - feet;
  origin.x = std::clamp<LONG>(origin.x, area.left - kWindowsPetWidth + 128,
    (std::max)(area.left - kWindowsPetWidth + 128, area.right - kWindowsPetWidth));
  origin.y = std::clamp<LONG>(origin.y, area.top, (std::max)(area.top, area.bottom - kWindowsPetHeight));
  return {origin, feet, below ? 133 : 1};
}
}
