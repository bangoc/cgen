/*
  (C) Nguyen Ba Ngoc 2021
  Minh họa sử dụng hàm append
*/

#include "base/arr.h"

#include <stdio.h>

long sum(arr_t(int) a) {
  long s = 0;
  for (int i = 0; i < arr_size(a); ++i) {
    s += ARR(a)[i];
  }
  return s;
}

int main() {
  arr_decl(a, 0, int);
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
    printf(" %d", ARR(a)[i]);
  }
  printf("\n");
  arr_free(a);
  return 0;
}