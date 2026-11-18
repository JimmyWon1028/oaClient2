#pragma once

#import <Cocoa/Cocoa.h>
#include <algorithm>

namespace oa {
inline constexpr double kMacPetWidth = 300, kMacPetHeight = 212;
inline constexpr double kMacPetFeetAbove = 206, kMacPetFeetBelow = 124;

struct MacPetLayout {
  NSPoint origin;
  double feet, bubble_top;
};

//2026.11.18 by codex, move the bubble below near the menu bar while retaining the bear's screen anchor.
inline MacPetLayout PlaceMacPet(NSPoint origin, double previous_feet, NSRect area) {
  const double anchor = origin.y + kMacPetHeight - previous_feet;
  const bool below = anchor + kMacPetFeetAbove > NSMaxY(area);
  const double feet = below ? kMacPetFeetBelow : kMacPetFeetAbove;
  origin.y = anchor - kMacPetHeight + feet;
  origin.x = std::clamp(origin.x, NSMinX(area), std::max(NSMinX(area), NSMaxX(area) - kMacPetWidth));
  origin.y = std::clamp(origin.y, NSMinY(area), std::max(NSMinY(area), NSMaxY(area) - kMacPetHeight));
  return {origin, feet, below ? 133.0 : 1.0};
}
}
