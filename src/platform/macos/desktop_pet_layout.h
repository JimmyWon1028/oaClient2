#pragma once

#import <Cocoa/Cocoa.h>
#include <algorithm>

namespace oa {
inline constexpr double kMacPetWidth = 300, kMacPetHeight = 212;
inline constexpr double kMacPetFeetAbove = 206, kMacPetFeetBelow = 124;
inline constexpr double kMacPetCenterRight = 244, kMacPetCenterLeft = 80;

struct MacPetLayout {
  NSPoint origin;
  double feet, bubble_top, center;
};

//2026.11.18 by codex, move the bubble below near the menu bar while retaining the bear's screen anchor.
inline MacPetLayout PlaceMacPet(NSPoint origin, double previous_feet, NSRect area,
    double previous_center = kMacPetCenterRight) {
  //2026.11.18 by codex, reflow the bear toward the left edge without shifting its screen anchor or clipping its short walk.
  const double anchor_x = origin.x + previous_center;
  const double center = anchor_x - kMacPetCenterRight < NSMinX(area) ? kMacPetCenterLeft : kMacPetCenterRight;
  origin.x = anchor_x - center;
  const double anchor = origin.y + kMacPetHeight - previous_feet;
  const bool below = anchor + kMacPetFeetAbove > NSMaxY(area);
  const double feet = below ? kMacPetFeetBelow : kMacPetFeetAbove;
  origin.y = anchor - kMacPetHeight + feet;
  origin.x = std::clamp(origin.x, NSMinX(area), std::max(NSMinX(area), NSMaxX(area) - kMacPetWidth));
  origin.y = std::clamp(origin.y, NSMinY(area), std::max(NSMinY(area), NSMaxY(area) - kMacPetHeight));
  return {origin, feet, below ? 133.0 : 1.0, center};
}
}
