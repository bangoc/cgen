#include "base/gtype.h"
#include "vec/arr.h"

#include "tests/base/utils.h"

int t1() {
  arr_make(v, 0, gtype);
  CHECK_MSG(arr_capacity(v) == 0, "t1 cap");
  CHECK_MSG(arr_size(v) == 0, "t1 size");
  arr_free(v);
  return 0;
}

int t2() {
  arr_make(v, 0, gtype);
  arr_reserve(v, 100);
  CHECK_MSG(arr_capacity(v) == 100, "t2 cap");
  CHECK_MSG(arr_size(v) == 0, "t2 size");

  arr_reserve(v, 30);
  CHECK_MSG(arr_capacity(v) == 30, "t2 cap 30");
  CHECK_MSG(arr_size(v) == 0, "t2 size 0");

  arr_reserve(v, 200);
  CHECK_MSG(arr_capacity(v) == 200, "t2 cap 200");
  CHECK_MSG(arr_size(v) == 0, "t2 size 0");

  arr_resize(v, 300);
  CHECK_MSG(arr_capacity(v) == 300, "t2 cap 300");
  CHECK_MSG(arr_size(v) == 300, "t2 size 300");

  arr_resize(v, 60);
  CHECK_MSG(arr_capacity(v) == 300, "t2 cap 300");
  CHECK_MSG(arr_size(v) == 60, "t2 size 60");
  arr_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  CHECK_MSG(t2() == 0, "t2()");
  printf("Test Ok\n");
  return 0;
}