#include "algo/algo.h"
#include <stdio.h>
int main() {
  int n = 5, *a = first_perm(n);
  do {
    for (int i = 0; i < n; ++i) {
      printf(" %d", a[i]);
    }
    printf("\n");
  } while (next_perm(a));
  free_perm(a);
}