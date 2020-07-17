#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, const char ** argv){

  system_clock::time_point clock_end = system_clock::now();
  //cout << clock_end.time_since_epoch() << endl;
  system_clock::duration time_since = clock_end.time_since_epoch();
  double nseconds = double(time_since.count()) * system_clock::period::num / system_clock::period::den;
  printf("%.2f\n", nseconds);
  return 0;
}
