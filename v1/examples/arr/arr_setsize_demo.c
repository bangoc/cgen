/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa sử dụng setsize
 */

#include "all.h"
#include <stdio.h>

int main() {
  arr_make(a, 0, int);
  arr_resize(a, 10);
  printf("size = %zu\n", arr_size(a));
  for (int i = 0; i < arr_size(a); ++i) {
    a[i] = i;
  }

  //  Thay đổi kích thước mảng
  arr_resize(a, 20);
  for (int i = 10; i < arr_size(a); ++i) {
    a[i] = i;
  }
  for (int i = 0; i < arr_size(a); ++i) {
    printf("a[%d] = %d\n", i, a[i]);
  }
  printf("size = %zu\n", arr_size(a));
  arr_free(a);
  return 0;
}