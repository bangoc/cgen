#include "algo/algo.h"
#include <stdio.h>
void aprint(int n, double *a) {
  printf("%d: ", n);
  for (int i = 0; i < n; ++i) {
    printf(" %f", a[i]);
  }
  printf("\n");
}
int icmp(const void *p1, const void *p2) {
  return *(const int*)p2 - *(const int *)p1;
}
int dcmp(const void *p1, const void *p2) {
  double v1 = *(const double*)p1,
         v2 = *(const double*)p2;
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
int main() {
  double a[] = {6, 2.15, 1, 6, 8, 9, 10, 9.5, 6.9, 9.9};
  int n = sizeof(a)/sizeof(a[0]);
  q2sort(a, n, sizeof(a[0]), dcmp);
  aprint(n, a);
}