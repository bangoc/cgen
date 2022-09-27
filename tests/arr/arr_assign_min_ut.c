#include "all.h"

#include "tests/base/utils.h"

int t1() {
  arr_make(a, 3, int);
  int cases[][4] = {{1, 1, 2, 3},
                    {3, 8, 5, 3},
                    {6, 7, 6, 9}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a[j] = cases[i][j];
    }
    int min;
    arr_assign_min(min, a);
    CHECK_MSG(min == cases[i][0], "Max value");
  }
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  arr_free(a);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}