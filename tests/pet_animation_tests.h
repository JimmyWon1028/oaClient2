#pragma once
#include "common/pet_animation.h"

inline void RunPetAnimationTests(void (*Check)(bool, const char*)) {
  //2026.11.17 by codex, keep every idle action reachable and bounded while notifications and explicit clicks interrupt safely.
  unsigned actions = 0;
  bool bounded = true;
  for (uint64_t ms = 0; ms < 43000; ms += 17) {
    const auto motion = oa::SamplePetMotion(ms);
    actions |= 1u << static_cast<unsigned>(motion.action);
    bounded = bounded && motion.frame >= 0 && motion.frame < 24 && motion.previous >= 0 && motion.previous < 24 &&
      motion.x >= -24.01f && motion.x <= 0.01f && motion.y >= -2 && motion.y <= 0.01f &&
      motion.blend >= 0 && motion.blend <= 1 && std::isfinite(motion.angle);
  }
  Check((actions & 63) == 63, "pet idle cycle reaches breathing, sway, wave, sit, stretch and walk");
  Check(bounded, "pet poses remain within the local animation area and valid sprite range");
  const auto interrupted = oa::SamplePetMotion(35000, 325);
  Check(interrupted.action == oa::PetAction::Notify && interrupted.x == 0 && interrupted.y < -15,
    "new notification interrupts walking with a local hop and wave");
  Check(oa::SamplePetMotion(35000, 8000).action == oa::PetAction::Walk,
    "notification animation expires after eight seconds");
  const auto clicked = oa::SamplePetMotion(35000, 1000, 325, true);
  Check(clicked.action == oa::PetAction::Click && clicked.y < -13 && clicked.sparkle > 0,
    "explicit pet click reacts even while a notification is visible");
  Check(oa::SamplePetMotion(35000, oa::kPetInactive, 1500, true).action == oa::PetAction::Breathe,
    "click feedback ends without restarting walking while reading a message");
  Check(oa::SamplePetMotion(35000, oa::kPetInactive, oa::kPetInactive, true).x == 0 &&
    oa::SamplePetMotion(24000, oa::kPetInactive, oa::kPetInactive, true).frame < 2,
    "message browsing suppresses autonomous walking and stretching");
  Check(oa::SamplePetMotion(0).x == 0 && oa::SamplePetMotion(43000).x == 0,
    "idle cycle repeats at its anchor without moving the desktop window");
}
