/* (C) Nguyen Ba Ngoc 2022 */

/** @file
 * @brief Thử nghiệm macro khái quát duyệt phần tử của arr
 */

#include "all.h"

#include "tests/base/utils.h"

int t1() {
  arr_make(a, 10, long);
  long b[10];
  for (long i = 0; i < 10; ++i) {
    a[i] = i;
    b[i] = i;
  }
  long *p = b;
  arr_traverse(cur, a) {
    printf("%ld ", *cur);
    CHECK_MSG(*cur == *p, "long element");
    ++p;
  }
  printf("\n");
  return 0;
}

int t2() {
  arr_make(a, 10, double);
  double b[10];
  for (long i = 0; i < 10; ++i) {
    a[i] = i * 1.01;
    b[i] = i * 1.01;
  }
  double *p = b;
  arr_traverse(cur, a) {
    printf("%f ", *cur);
    CHECK_MSG(*cur == *p, "double element");
    ++p;
  }
  printf("\n");
  return 0;
}

int t3() {
  arr_make(a, 10, int);
  int b[10];
  for (long i = 0; i < 10; ++i) {
    a[i] = i * 1.01;
    b[i] = i * 1.01;
  }
  int *p = b;
  arr_traverse(cur, a) {
    printf("%d ", *cur);
    CHECK_MSG(*cur == *p, "int element");
    ++p;
  }
  printf("\n");
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1() - long");
  CHECK_MSG(t2() == 0, "t2() - double");
  CHECK_MSG(t3() == 0, "t3() - int");
  TEST_OK();
  return 0;
}