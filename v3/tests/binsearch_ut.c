#include "algo.h"

#include <stdio.h>

int icmp(const void *o1, const void *o2) {
  const int *v1 = o1, *v2 = o2;
  return *v1 - *v2;
}

int main() {
  int a[] = {1, 2, 3, 5, 6, 8, 9, 10};
  int n = sizeof(a) / sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    if (binsearch(&a[i], a, n, sizeof(int), icmp) != a + i) {
      return 1;
    }
  }
  if (binsearch((int[]){100}, a, n, sizeof(int), icmp) != 0 ||
      binsearch((int[]){-10}, a, n, sizeof(int), icmp) != 0) {
    return 1;
  }
}