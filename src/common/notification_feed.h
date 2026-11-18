#pragma once

#include <cstdint>
#include <chrono>
#include <deque>
#include <string>
#include <utility>
#include <vector>

namespace oa {

struct OrderNotification {
  int64_t id = 0;
  std::string action;
  std::string order;
};

//2026.11.17 by codex, retain session-only messages for reopening and bounded keyboard navigation.
class NotificationHistory {
 public:
  void Clear() { entries_.clear(); selected_ = 0; visible_ = false; }
  void Add(OrderNotification event) {
    entries_.push_back(std::move(event));
    if (entries_.size() > 500) {
      entries_.pop_front();
      if (selected_ > 0) --selected_;
    }
    if (!visible_) selected_ = entries_.size() - 1;
  }
  void Show() { visible_ = true; }
  void Hide() { visible_ = false; }
  bool visible() const { return visible_; }
  size_t size() const { return entries_.size(); }
  size_t position() const { return entries_.empty() ? 0 : selected_ + 1; }
  const OrderNotification* current() const { return entries_.empty() ? nullptr : &entries_[selected_]; }
  void Move(int direction) {
    if (entries_.empty()) return;
    if (direction < 0 && selected_ > 0) --selected_;
    else if (direction > 0 && selected_ + 1 < entries_.size()) ++selected_;
  }
 private:
  std::deque<OrderNotification> entries_;
  size_t selected_ = 0;
  bool visible_ = false;
};

//2026.11.17 by codex, retain the server date and cursor across transient failures without replaying a new login baseline.
class NotificationFeed {
 public:
  std::string date;
  int64_t cursor = 0;
  std::string scope;

  static bool ValidDate(const std::string& value) {
    if (value.size() != 8) return false;
    for (char c : value) if (c < '0' || c > '9') return false;
    const int year = std::stoi(value.substr(0, 4)), month = std::stoi(value.substr(4, 2)), day = std::stoi(value.substr(6, 2));
    return year > 0 && std::chrono::year_month_day{std::chrono::year{year},
      std::chrono::month{static_cast<unsigned>(month)}, std::chrono::day{static_cast<unsigned>(day)}}.ok();
  }

  void Connect(const std::string& binding, const std::string& server_date, int64_t baseline) {
    if (scope != binding || date.empty()) {
      date = server_date;
      cursor = baseline;
    }
    scope = binding;
  }

  bool Apply(const std::string& server_date, int64_t next, bool gap,
      const std::vector<OrderNotification>& events, std::vector<OrderNotification>& fresh) {
    fresh.clear();
    if (!ValidDate(server_date) || next < 0) return false;
    const bool reset = date != server_date || (gap && next < cursor);
    int64_t previous = reset ? 0 : cursor;
    for (const auto& event : events) {
      if (event.id <= 0 || event.id > next || event.order.empty() || event.order.size() > 128 ||
          (event.action != "add" && event.action != "mod")) return false;
      if (event.id > previous) {
        fresh.push_back(event);
        previous = event.id;
      }
    }
    if (!reset && next < cursor) return false;
    date = server_date;
    cursor = next;
    return true;
  }
};

}
