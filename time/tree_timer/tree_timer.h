#pragma once


#include <cassert>
#include <chrono>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

class TimeRecord {
 public:
  TimeRecord(const std::string name, const double time_used,
             std::vector<std::shared_ptr<TimeRecord>>&& subs)
      : name_(name),
        time_used_(time_used),
        subs_(std::forward<std::vector<std::shared_ptr<TimeRecord>>>(subs)) {}

  void print(std::string prefix, bool is_last) {
    std::cout << prefix << (is_last ? "└──" : "├──") << name_ << ":"
              << 1000 * time_used_ << std::endl;
    for (size_t i = 0; i < subs_.size(); ++i) {
      std::string sub_prefix = prefix + (is_last ? "   " : "|  ");
      subs_[i]->print(sub_prefix, i == subs_.size() - 1);
    }
  }

 private:
  std::string name_;
  double time_used_;
  std::vector<std::shared_ptr<TimeRecord>> subs_;
};

class TreeTimer {
 public:
  static std::shared_ptr<TreeTimer> Create(std::string name);
  void Pause() {
    assert(running_);
    running_ = false;
    std::chrono::duration<double> diff  = std::chrono::steady_clock::now() - start_;
    elaps_ += diff.count();
  }
  void Resume() {
    assert(!running_);
    running_ = true;
    start_ = std::chrono::steady_clock::now();
  }
  ~TreeTimer();

  std::string get_name() const { return name_; }
  void RecordSubTime(std::shared_ptr<TimeRecord> sub) { subs_.push_back(sub); }

 private:
  static std::stack<std::weak_ptr<TreeTimer>> calling_stack;
  TreeTimer(std::string name, std::shared_ptr<TreeTimer> father);
  std::chrono::time_point<std::chrono::steady_clock> start_;
  double elaps_ = 0.0;
  bool running_ = true;
  std::string name_;
  std::shared_ptr<TreeTimer> father_;
  std::vector<std::shared_ptr<TimeRecord>> subs_;
};



