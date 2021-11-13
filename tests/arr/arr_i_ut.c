/*
  (C) Nguyen Ba Ngoc 2021
  Minh họa mảng giá trị int cấp phát động.
*/

#include "arr.h"

#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  int **a = (int**)arr_create(10, int);
  ASSERT(arr_size(a) == 0, "init size = 0");
  ASSERT(arr_capacity(a) == 10, "init cap = 0");
  ASSERT(arr_elem_sz(a) == sizeof(int), "elem sz");
  const int n = 100;
  for (int i = 0; i < n; ++i) {
    arr_append(a, i);
  }
  ASSERT(arr_size(a) == n, "append n elements");
  ASSERT(arr_capacity(a) >= n, "capacity changed");
  for (long i = 0; i < arr_size(a); ++i) {
    ASSERT((*a)[i] == i, "Value");
  }
  arr_free(a);
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}