#include "algo.h"

#include <stdio.h>

int icmp(const void *o1, const void *o2) {
  const int *v1 = o1, *v2 = o2;
  return *v1 - *v2;
}

int icmpr(const void *o1, const void *o2) {
  const int *v1 = o1, *v2 = o2;
  return *v2 - *v1;
}

int main() {
  int a[] = {3, 1, 2, 9, 3, 2, 7, 10, 21, 22, 35, 21, 1, 3, 2};
  int n = sizeof(a) / sizeof(a[0]);
  q2insort(a, n, sizeof(int), icmp);
  for (int i = 0; i < n; ++i) {
    if (i > 0 && icmp(a + (i - 1), a + i) > 0) {
      return 1;
    }
    printf("%d ", a[i]);
  }
  printf("\n");
  q2insort(a, n, sizeof(int), icmpr);
  for (int i = 0; i < n; ++i) {
    if (i > 0 && icmpr(a + (i - 1), a + i) > 0) {
      return 1;
    }
    printf("%d ", a[i]);
  }
  printf("\n");
  int b[10] = {0};
  int bn = sizeof(b) / sizeof(b[0]);
  q2insort(b, bn, sizeof(int), icmp);
  q2insort(b, bn, sizeof(int), icmpr);
  for (int i = 0; i < bn; ++i) {
    printf("%d ", b[i]);
  }
  printf("\n");
}