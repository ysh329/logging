#include "logging.h"

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
