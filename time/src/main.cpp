#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "tree_timer.h"

using namespace std;
using namespace std::chrono;

int main(int argc, const char ** argv){

  auto tm = TreeTimer::Create("test");
  std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
  this_thread::sleep_for(chrono::milliseconds(200));
  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - start;
  std::cout << " ints : " << diff.count() << " s\n";
  return 0;
}
