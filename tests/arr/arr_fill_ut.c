#include "all.h"

#include "tests/base/utils.h"

int t1() {
  arr_make(a, 10, int);
  arr_fill(a, 9);
  CHECK_MSG(arr_size(a) == 10, "size = 10");
  arr_traverse(cur, a) {
    CHECK_MSG(*cur == 9, "element == 9");
  }
  arr_free(a);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}