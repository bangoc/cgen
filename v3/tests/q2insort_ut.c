#include "algo.h"

#include <stdio.h>

int lte(const void *o1, const void *o2) {
  const int *v1 = o1, *v2 = o2;
  return *v1 <= *v2;
}

int gte(const void *o1, const void *o2) {
  const int *v1 = o1, *v2 = o2;
  return *v1 >= *v2;
}

int main() {
  int a[] = {3, 1, 2, 9, 3, 2, 7, 10, 21, 22, 35, 21, 1, 3, 2};
  int n = sizeof(a) / sizeof(a[0]);
  q2insort(a, n, sizeof(int), lte);
  for (int i = 0; i < n; ++i) {
    if (i > 0 && !lte(a + (i - 1), a + i)) {
      return 1;
    }
    printf("%d ", a[i]);
  }
  printf("\n");
  q2insort(a, n, sizeof(int), gte);
  for (int i = 0; i < n; ++i) {
    if (i > 0 && !gte(a + (i - 1), a + i)) {
      return 1;
    }
    printf("%d ", a[i]);
  }
  printf("\n");
}