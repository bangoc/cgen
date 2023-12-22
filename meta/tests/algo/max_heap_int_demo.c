#include "algo/algo.h"
#include <stdio.h>

int main() {
  int a[] = {3, 1, 2, 9, 20, 18, 29, 22, 11, 15, 21};
  int n = sizeof(a)/sizeof(a[0]);
  heap_make(a, n, sizeof(a[0]), cmpi);
  printf("Nhập k = ");
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; ++i) {
    printf("%d\n", a[0]);
    vswap(&a[0], &a[n - i - 1], sizeof(a[0]));
    heap_shift_down(a, n - i - 1, sizeof(a[0]), 0, cmpi);
  }
}