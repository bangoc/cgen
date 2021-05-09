#include "gtvector.h"

#include "tests/base/utils.h"

int t1() {
  vector_t v = gtv_create();
  CHECK_MSG(gtv_capacity(v) == 0, "t1 cap");
  CHECK_MSG(gtv_size(v) == 0, "t1 size");
  return 0;
}

int t2() {
  vector_t v = gtv_create();
  gtv_grow(&v, 100);
  CHECK_MSG(gtv_capacity(v) == 100, "t2 cap");
  CHECK_MSG(gtv_size(v) == 0, "t2 size");
  gtv_grow(&v, 30);
  CHECK_MSG(gtv_capacity(v) == 100, "t2 cap 100/30");
  gtv_grow(&v, 200);
  CHECK_MSG(gtv_capacity(v) == 200, "t2 cap 200");
  gtv_grow(&v, 300);
  CHECK_MSG(gtv_capacity(v) == 300, "t2 cap 300");
  return 0;
}

int main() {
  CHECK(t1() == 0);
  CHECK(t2() == 0);
  return 0;
}