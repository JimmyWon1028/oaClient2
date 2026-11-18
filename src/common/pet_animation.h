#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <limits>

namespace oa {
//2026.11.17 by codex, sample visible pet motion from elapsed time without moving the desktop window or stealing focus.
enum class PetAction { Breathe, Sway, Wave, Sit, Stretch, Walk, Notify, Click };

struct PetMotion {
  PetAction action = PetAction::Breathe;
  int frame = 0, previous = 0;
  float blend = 1, x = 0, y = 0, scale_x = 1, scale_y = 1, angle = 0, sparkle = 0;
};

constexpr uint64_t kPetInactive = (std::numeric_limits<uint64_t>::max)();
constexpr double kPetPi = 3.14159265358979323846;

struct PetStep { int frame; uint64_t duration; };

inline void PetSequence(PetMotion& motion, uint64_t elapsed, std::initializer_list<PetStep> steps) {
  int previous = 0;
  for (const auto& step : steps) {
    if (elapsed < step.duration) {
      motion.frame = step.frame;
      motion.previous = previous;
      motion.blend = (std::min)(1.0f, static_cast<float>(elapsed) / 130.0f);
      return;
    }
    elapsed -= step.duration;
    previous = step.frame;
  }
}

inline PetMotion SamplePetMotion(uint64_t elapsed, uint64_t notification = kPetInactive,
    uint64_t clicked = kPetInactive, bool paused = false) {
  PetMotion motion;
  const double breath = std::sin(elapsed * 2 * kPetPi / 2800.0);
  motion.scale_x = static_cast<float>(1.0 - 0.012 * breath);
  motion.scale_y = static_cast<float>(1.0 + 0.022 * breath);
  motion.frame = motion.previous = elapsed % 5200 >= 5020 ? 1 : 0;
  if (clicked < 1500) {
    motion.action = PetAction::Click;
    motion.frame = motion.previous = clicked < 650 ? 1 : 0;
    motion.y = clicked < 650 ? static_cast<float>(-14 * std::sin(kPetPi * clicked / 650.0)) : 0;
    motion.angle = static_cast<float>(7 * std::sin(2 * kPetPi * clicked / 1500.0));
    motion.sparkle = static_cast<float>(std::sin(kPetPi * clicked / 1500.0));
    return motion;
  }
  if (notification < 8000) {
    motion.action = PetAction::Notify;
    PetSequence(motion, notification % 1600, {{2, 200}, {3, 200}, {4, 200}, {5, 200},
      {4, 200}, {5, 200}, {6, 200}, {7, 200}});
    if (notification < 650) motion.y = static_cast<float>(-16 * std::sin(kPetPi * notification / 650.0));
    return motion;
  }
  if (paused) return motion;
  const uint64_t phase = elapsed % 43000;
  if (phase >= 4000 && phase < 8000) {
    motion.action = PetAction::Sway;
    motion.angle = static_cast<float>(3.5 * std::sin(2 * kPetPi * (phase - 4000) / 4000.0));
  } else if (phase >= 8000 && phase < 11000) {
    motion.action = PetAction::Wave;
    PetSequence(motion, (phase - 8000) % 1500, {{2, 180}, {3, 180}, {4, 220}, {5, 220},
      {4, 220}, {5, 220}, {6, 130}, {7, 130}});
  } else if (phase >= 13000 && phase < 21000) {
    motion.action = PetAction::Sit;
    PetSequence(motion, phase - 13000, {{8, 200}, {9, 450}, {10, 2400}, {11, 240},
      {10, 1700}, {11, 240}, {10, 1700}, {12, 450}, {8, 300}, {0, 320}});
  } else if (phase >= 23000 && phase < 28500) {
    motion.action = PetAction::Stretch;
    PetSequence(motion, phase - 23000, {{8, 200}, {13, 450}, {14, 1500}, {15, 1600},
      {14, 600}, {16, 550}, {8, 300}, {0, 300}});
  } else if (phase >= 31000 && phase < 39000) {
    motion.action = PetAction::Walk;
    const uint64_t walk = phase - 31000;
    const float amount = static_cast<float>((1 - std::cos(2 * kPetPi * walk / 8000.0)) / 2);
    motion.x = -24 * amount;
    const int left[] = {21, 22, 23, 22}, right[] = {17, 18, 19, 20};
    const auto& frames = walk < 4000 ? left : right;
    const uint64_t step = walk % 800;
    motion.frame = frames[step / 200];
    motion.previous = frames[(step / 200 + 3) % 4];
    motion.blend = (std::min)(1.0f, static_cast<float>(step % 200) / 100.0f);
    motion.y = static_cast<float>(-1.5 * std::sin(kPetPi * (walk % 200) / 200.0));
    if (walk < 160 || walk >= 7840) {
      motion.previous = 0;
      motion.blend = static_cast<float>(walk < 160 ? walk : 8000 - walk) / 160.0f;
    }
  }
  return motion;
}
}
