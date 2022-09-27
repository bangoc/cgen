/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa sử dụng hàm append
 */

#include "all.h"

#include <stdio.h>

long sum(atype(int) *a) {
  long s = 0;
  for (int i = 0; i < arr_size(a); ++i) {
    s += a[i];
  }
  return s;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  arr_make(a, 0, int);
  printf("Nhập vào 1 dãy số bất kỳ, nhập 0 để kết thúc nhập\n:");
  for(;;) {
    int v;
    scanf("%d", &v);
    if (v == 0) {
      break;
    }
    arr_append(a, v);
  }
  printf("Tổng các số đã nhập: %ld\n", sum(a));
  printf("Danh sách các số theo chiều ngược lại: ");
  for (long i = arr_size(a) - 1; i >= 0; --i) {
    printf(" %d", a[i]);
  }
  printf("\n");
  arr_free(a);
  return 0;
}