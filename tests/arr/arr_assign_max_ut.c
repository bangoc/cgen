#include "all.h"

#include "tests/base/utils.h"

int t1() {
  arr_make(a, 3, int);
  int cases[][4] = {{3, 1, 2, 3},
                    {5, 1, 5, 3},
                    {7, 7, 3, 6}};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a[j] = cases[i][j];
    }
    int max;
    arr_assign_max(max, a);
    CHECK_MSG(max == cases[i][0], "Max value");
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