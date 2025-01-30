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
  int *tmp = binsearch_lte((int[]){7}, a, n, sizeof(int), icmp);
  if (*tmp != 6) {
    printf("%d - error\n", *tmp);
    return 1;
  }
  tmp = binsearch_gte((int[]){7}, a, n, sizeof(int), icmp);
  if (*tmp != 8) {
    printf("%d - error\n", *tmp);
    return 1;
  }
  tmp = binsearch_lte((int[]){0}, a, n, sizeof(int), icmp);
  if (tmp) {
    printf("Error lte\n");
    return 1;
  }
  tmp = binsearch_gte((int[]){11}, a, n, sizeof(int), icmp);
  if (tmp) {
    printf("Error gte\n");
    return 1;
  }
  tmp = binsearch_lte((int[]){11}, a, n, sizeof(int), icmp);
  if (*tmp != 10) {
    printf("%d - error\n", *tmp);
    return 1;
  }
  tmp = binsearch_gte((int[]){0}, a, n, sizeof(int), icmp);
  if (*tmp != 1) {
    printf("%d - error\n", *tmp);
    return 1;
  }
}