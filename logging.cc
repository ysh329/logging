/*
 * This file implements an lightweight alternative for glog, which is more
 * friendly for mobile.
 */

#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// NOLINTFILE()

// LOG()
#define LOG(status) LOG_##status.stream()
#define LOG_ERROR LOG_INFO
#define LOG_INFO LogMessage(__FILE__, __FUNCTION__, __LINE__, "I")
#define LOG_WARNING \
  LogMessage(__FILE__, __FUNCTION__, __LINE__, "W")
#define LOG_FATAL \
  LogMessageFatal(__FILE__, __FUNCTION__, __LINE__)
#define VLOG(level) VLogMessage(__FILE__, __FUNCTION__, __LINE__, level).stream()

// CHECK()
// clang-format off
#define CHECK(x) if (!(x)) LogMessageFatal(__FILE__, __FUNCTION__, __LINE__).stream() << "Check failed: " #x << ": " // NOLINT(*)
// clang-format on
#define CHECK_EQ(x, y) _CHECK_BINARY(x, ==, y)
#define CHECK_NE(x, y) _CHECK_BINARY(x, !=, y)
#define CHECK_LT(x, y) _CHECK_BINARY(x, <, y)
#define CHECK_LE(x, y) _CHECK_BINARY(x, <=, y)
#define CHECK_GT(x, y) _CHECK_BINARY(x, >, y)
#define CHECK_GE(x, y) _CHECK_BINARY(x, >=, y)
#define _CHECK_BINARY(x, cmp, y) CHECK(x cmp y) << x << "!" #cmp << y << " "

using namespace std;

void gen_log(std::ostream& log_stream_, const char* file, const char* func, int lineno, const char* level, const int kMaxLen=20) {
  const int len = strlen(file);
  std::string time_str;
  struct tm tm_time;  // Time of creation of LogMessage
  time_t timestamp = time(NULL);
  localtime_r(&timestamp, &tm_time);
  struct timeval tv;
  gettimeofday(&tv, NULL);

  // print date / time
  log_stream_ << '[' << level << ' ' << std::setw(2) << 1 + tm_time.tm_mon
              << '/' << std::setw(2) << tm_time.tm_mday << ' ' << std::setw(2)
              << tm_time.tm_hour << ':' << std::setw(2) << tm_time.tm_min
              << ':' << std::setw(2) << tm_time.tm_sec << '.' << std::setw(3)
              << tv.tv_usec / 1000 << " ";

  if (len > kMaxLen) {
    log_stream_ << "..." << file + len - kMaxLen << " " << func << ":"
                << lineno << "] ";
  } else {
    log_stream_ << file << " " << func << ":" << lineno << "] ";
  }
}


// LogMessage
class LogMessage {
 public:
  LogMessage(const char* file, const char* func,
             int lineno, const char* level="I")  {
    gen_log(log_stream_, file, func, lineno, level);
  }

  ~LogMessage() {
    log_stream_ << '\n';
    fprintf(stderr, "%s", log_stream_.str().c_str());
  }

  std::ostream& stream() { return log_stream_; }

 protected:
  std::stringstream log_stream_;
  LogMessage(const LogMessage&) = delete;
  void operator=(const LogMessage&) = delete;
};


// LogMessageFatal
class LogMessageFatal : public LogMessage {
 public:
  LogMessageFatal(const char* file, const char* func,
                  int lineno, const char* level="F") 
      : LogMessage(file, func, lineno, level) {}

  ~LogMessageFatal() {
    log_stream_ << '\n';
    fprintf(stderr, "%s", log_stream_.str().c_str());
    abort();
  }
};


// VLOG
class VLogMessage {
 public:
  VLogMessage(const char* file, const char* func,
                  int lineno, const int32_t level_int=0) {
    const char* GLOG_v = std::getenv("GLOG_v");
    GLOG_v_int = (GLOG_v && atoi(GLOG_v) > 0) ? atoi(GLOG_v) : 0;
    this->level_int = level_int;
    if (GLOG_v_int < level_int) {
      return;
    }
    const char* level = to_string(level_int).c_str();
    gen_log(log_stream_, file, func, lineno, level);
  }

  ~VLogMessage() {
    if (GLOG_v_int < this->level_int) {
      return;
    }
    log_stream_ << '\n';
    fprintf(stderr, "%s", log_stream_.str().c_str());
  }
  std::ostream& stream() { return log_stream_; }

 protected:
  std::stringstream log_stream_;
  int32_t GLOG_v_int;
  int32_t level_int;

  VLogMessage(const VLogMessage&) = delete;
  void operator=(const VLogMessage&) = delete;

};


int main() {

  LOG(INFO) << "this is a LOG(INFO) message";
  VLOG(3) << "this is a VLOG(3) message";

  cout << "hello" << endl;
  int a = 1;
  LOG(INFO) << "a";
  //LOG(FATAL) << "ccc";
  float *b = nullptr;
  //CHECK(b) << 123;
  CHECK_EQ(1, 1);
  CHECK_GT(2, 1);
  CHECK_GT(2, 2);
}
