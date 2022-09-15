/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa sử dụng setsize
 */

#include "all.h"
#include <stdio.h>

int main() {
  arr_decl(a, 0, int);
  arr_set_size(a, 10);
  printf("size = %zu\n", arr_size(a));
  for (int i = 0; i < arr_size(a); ++i) {
    arr(a)[i] = i;
  }

  //  Thay đổi kích thước mảng
  arr_set_size(a, 20);
  for (int i = 10; i < arr_size(a); ++i) {
    arr(a)[i] = i;
  }
  for (int i = 0; i < arr_size(a); ++i) {
    printf("a[%d] = %d\n", i, arr(a)[i]);
  }
  printf("size = %zu\n", arr_size(a));
  arr_free(a);
  return 0;
}