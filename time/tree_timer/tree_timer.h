#pragma once

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>

class TimeRecord {
 public:
  TimeRecord(const std::string name, const double time_used,
             std::map<std::string, std::shared_ptr<TimeRecord>>&& subs)
      : name_(name),
        time_used_(time_used),
        subs_(std::forward<std::map<std::string, std::shared_ptr<TimeRecord>>>(
            subs)) {}

  void print(std::string prefix, bool is_last) {
    //std::cout << name_<< (is_last? " is last": " not last") << std::endl;
    const std::string call_msg =
        count_ > 1 ? " " + std::to_string(count_) + " calls" : "";
    std::cout << prefix << (is_last ? "└──" : "├──") << name_ << ":"
              << 1000 * time_used_ << " ms" << call_msg << std::endl;
    size_t i = 0;
    double sum_sub_time_used = 0;
    std::string sub_prefix = prefix + (is_last ? "   " : "|  ");
    for (auto ptr = subs_.begin(); ptr != subs_.end(); ++ptr, ++i) {
      ptr->second->print(sub_prefix, false);
      sum_sub_time_used += ptr->second->GetTimeUsed();
    }
    if (!subs_.empty()) {

      //std::cout << prefix << (is_last ? "└──" : "├──") << name_ << ":"
                //<< 1000 * time_used_ << " ms" << call_msg << std::endl;
      TimeRecord other("other", time_used_ - sum_sub_time_used,
                       std::map<std::string, std::shared_ptr<TimeRecord>>());
      other.print(sub_prefix, true);
    }
  }
  std::string GetName() { return name_; }
  void Merge(std::shared_ptr<TimeRecord> other) {
    assert(other->name_ == name_);
    ++count_;
    time_used_ += other->time_used_;
    for (auto other_sub : other->subs_) {
      if (subs_.find(other_sub.first) != subs_.end()) {
        subs_[other_sub.first]->Merge(other_sub.second);
      } else {
        subs_.insert(other_sub);
      }
    }
  }
  double GetTimeUsed() { return time_used_; }

 private:
  std::string name_;
  double time_used_;
  std::map<std::string, std::shared_ptr<TimeRecord>> subs_;
  int count_ = 1;
};

class TreeTimer {
 public:
  static std::shared_ptr<TreeTimer> Create(std::string name);
  void Pause() {
    assert(running_);
    running_ = false;
    std::chrono::duration<double> diff =
        std::chrono::steady_clock::now() - start_;
    elaps_ += diff.count();
  }
  void Resume() {
    assert(!running_);
    running_ = true;
    start_ = std::chrono::steady_clock::now();
  }
  ~TreeTimer();

  std::string get_name() const { return name_; }
  void RecordSubTime(std::shared_ptr<TimeRecord> sub);

 private:
  static std::stack<std::weak_ptr<TreeTimer>> calling_stack;
  TreeTimer(std::string name, std::shared_ptr<TreeTimer> father);
  std::chrono::time_point<std::chrono::steady_clock> start_;
  double elaps_ = 0.0;
  bool running_ = true;
  std::string name_;
  std::shared_ptr<TreeTimer> father_;
  std::map<std::string, std::shared_ptr<TimeRecord>> subs_;
};

