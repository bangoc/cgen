/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa mảng giá trị int cấp phát động.
 */

#include "vec/arr.h"

#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  arr_make(a, 0, int);
  CHECK_MSG(arr_size(a) == 0, "init size = 0");
  CHECK_MSG(arr_capacity(a) == 0, "init cap = 0");
  CHECK_MSG(arr_elemsize(a) == sizeof(int), "elem sz");
  const int n = 100;
  for (int i = 0; i < n; ++i) {
    arr_append(a, i);
  }
  CHECK_MSG(arr_size(a) == n, "append n elements");
  CHECK_MSG(arr_capacity(a) >= n, "capacity changed");
  for (long i = 0; i < arr_size(a); ++i) {
    CHECK_MSG(a[i] == i, "Value");
  }
  arr_free(a);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}