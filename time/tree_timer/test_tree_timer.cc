#include "tree_timer.h"
#include <thread>
#include <chrono>
void funB() {
  auto tm = TreeTimer::Create("funB");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}


void funD() {
  auto tm = TreeTimer::Create("funD");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void funC() {
  auto tm = TreeTimer::Create("funC");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  funD();
}

void funA() {
  auto tm = TreeTimer::Create("funA");
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  for (int i = 0; i < 10; ++i) {
    funB();
  }
  funC();
}

int main() {
  auto tm = TreeTimer::Create("main");
  funA();
}
