// setprecision example
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include "boost/filesystem.hpp"
#define MST (-7)
#define UTC (0)
#define CCT (+8)

using path = boost::filesystem::path;

std::string GetTimeFormat(std::time_t timestamp) {
  std::tm * local_time = std::localtime(&timestamp);
  char time_format[80];
  snprintf(time_format, sizeof(time_format), "%d-%d-%d_%d:%d:%d", local_time->tm_year+1900, local_time->tm_mon+1,
           local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
  return time_format;
}


int main (int argc, char**argv) {
  std::string fp(argv[1]);
  std::time_t file_timestamp = boost::filesystem::last_write_time(path(fp));
  std::cout << file_timestamp << std::endl;

  std::cout << GetTimeFormat(file_timestamp);
  return 0;
}
