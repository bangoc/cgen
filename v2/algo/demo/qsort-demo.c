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
typedef int (*cmp_t)(const void *, const void *);
void vswap(char *p, char *q, int sz) {
  char tmp;
  for (int i = 0; i < sz; ++i) {
    tmp = *p;
    *p = *q;
    *q = tmp;
    ++p;
    ++q;
  }
}
void q2sort(void *a, int n, int sz, cmp_t cmp) {
  if (n <= 1) {
    return;
  }
  void *left = a, *right = a + (n - 2) * sz;
  void *v = a + (n - 1) * sz;
  for (;;) {
    while (cmp(v, left) > 0) {
      left += sz;
    }
    while (cmp(right, v) > 0) {
      if (right == a) {
        break;
      }
      right -= sz;
    }
    if (left >= right) {
      break;
    }
    vswap(left, right, sz);
    left += sz;
    right -= sz;
  }
  vswap(left, v, sz);
  right = left + sz;
  left = left - sz;
  q2sort(a, (left - a)/sz + 1, sz, cmp);
  q2sort(right, (a - right)/sz + n, sz, cmp);
}
int main() {
  double a[] = {6, 2.15, 1, 6, 8, 9, 10, 9.5, 6.9, 9.9};
  int n = sizeof(a)/sizeof(a[0]);
  q2sort(a, n, sizeof(a[0]), dcmp);
  aprint(n, a);
}