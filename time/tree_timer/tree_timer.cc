#include "tree_timer.h"

std::stack<std::weak_ptr<TreeTimer>> TreeTimer::calling_stack;

std::shared_ptr<TreeTimer> TreeTimer::Create(std::string name) {
  std::shared_ptr<TreeTimer> father = nullptr;
  if (!calling_stack.empty()) {
    father = calling_stack.top().lock();
    assert(father != nullptr);
  }
  std::shared_ptr<TreeTimer> p(new TreeTimer(name, father));
  calling_stack.push(p);
  return p;
}

TreeTimer::TreeTimer(std::string name, std::shared_ptr<TreeTimer> father)
    : running_(true), name_(name), father_(father) {
  start_ = std::chrono::steady_clock::now();
}

TreeTimer::~TreeTimer() {
  Pause();
  assert(!calling_stack.empty());
  calling_stack.pop();
  std::shared_ptr<TimeRecord> record(
      new TimeRecord(name_, elaps_, std::move(subs_)));
  if (father_) {
    father_->RecordSubTime(record);
  } else {
    record->print("", true);
  }
}

void TreeTimer::RecordSubTime(std::shared_ptr<TimeRecord> sub) {
  if (subs_.find(sub->GetName()) != subs_.end()) {
    subs_[sub->GetName()]->Merge(sub);
  } else {
    subs_.insert({sub->GetName(), sub});
  }
}

