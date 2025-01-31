#include "arr.h"

#include <stdio.h>

int main() {
  int *a = arr(int, 10);
  arr_for(a, i) {
    a[i] = i;
  }
  printf("cap = %d\n", arr_cap(a));
  arr_for(a, i) {
    printf(" %d", a[i]);
  }
  arr_reserve(a, 20);
  printf("cap = %d\n", arr_cap(a));
  arr_reserve(a, 5);
  if (arr_cap(a) != 5) {
    printf("Cap = %d -- Error\n", arr_cap(a));
    return 1;
  }
  arr_free(a);
  printf("Test Ok!\n");
}