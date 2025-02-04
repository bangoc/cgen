#include "arr.h"

#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  int *a = arr(int, n);
  arr_for(a, i) {
    scanf("%d", &a[i]);
  }
  arr_rfor(a, i) {
    printf(" %d", a[i]);
  }
  printf("\n");
  arr_free(a);
}