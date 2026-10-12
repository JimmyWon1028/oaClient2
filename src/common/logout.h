#pragma once

#include <chrono>

namespace oa {

// One 500 ms login-state check, then at most twenty 500 ms logout polls.
class LogoutFlow {
 public:
  //2026.10.12 modify by codex, share an opt-in hidden shutdown with an acknowledgement or three-second deadline.
  using Clock = std::chrono::steady_clock;
  enum class Mode { PollForState, BackgroundGrace };
  enum class Action { Probe, Logout, Wait, Close };
  Action Begin(bool ready, Mode mode = Mode::PollForState, Clock::time_point now = Clock::now()) {
    if (started_) return complete_ ? Action::Close : Action::Wait;
    started_ = true;
    mode_ = mode;
    if (mode_ == Mode::BackgroundGrace) {
      state_ = -1;
      logout_sent_ = true;
      deadline_ = now + std::chrono::seconds(3);
      return Action::Logout;
    }
    if (!ready) { complete_ = true; return Action::Close; }
    return Action::Probe;
  }
  void ReceiveState(int state) {
    state_ = state;
    if (started_ && mode_ == Mode::BackgroundGrace && state == 0) complete_ = true;
  }
  Action Tick(Clock::time_point now = Clock::now()) {
    if (complete_) return Action::Close;
    if (mode_ == Mode::BackgroundGrace) {
      if (now >= deadline_) { complete_ = true; timed_out_ = true; return Action::Close; }
      return Action::Probe;
    }
    if (!logout_sent_) {
      if (state_ != 1) { complete_ = true; return Action::Close; }
      logout_sent_ = true;
      return Action::Logout;
    }
    if (state_ == 0) { complete_ = true; return Action::Close; }
    if (++polls_ >= 20) { complete_ = true; timed_out_ = true; return Action::Close; }
    return Action::Probe;
  }
  bool complete() const { return complete_; }
  bool logout_sent() const { return logout_sent_; }
  bool timed_out() const { return timed_out_; }

 private:
  Mode mode_ = Mode::PollForState;
  Clock::time_point deadline_;
  int state_ = -1;
  int polls_ = 0;
  bool started_ = false;
  bool complete_ = false;
  bool logout_sent_ = false;
  bool timed_out_ = false;
};

}  // namespace oa
