#include "vv.h"

#include "tests/base/utils.h"

int t1() {
  vptr_vec_t v = vv_create();
  CHECK_MSG(vv_capacity(v) == 0, "t1 cap");
  CHECK_MSG(vv_size(v) == 0, "t1 size");
  return 0;
}

int t2() {
  vptr_vec_t v = vv_create();
  vv_grow(&v, 100);
  CHECK_MSG(vv_capacity(v) == 100, "t2 cap");
  CHECK_MSG(vv_size(v) == 0, "t2 size");
  return 0;
}

int main() {
  CHECK(t1() == 0);
  CHECK(t2() == 0);
  return 0;
}