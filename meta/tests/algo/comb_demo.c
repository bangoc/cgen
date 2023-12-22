#include "all.h"

#include <stdio.h>

int main() {
  int k = 3, n = 5, *a = first_comb(k, n);
  do {
    for (int i = 0; i < k; ++i) {
      printf(" %d", a[i]);
    }
    printf("\n");
  } while (next_comb(a));
  free_comb(a);
}