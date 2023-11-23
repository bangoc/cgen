#include <stdio.h>
int icmp(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int *)p2;
}
typedef int (*cmp_t)(const void *p1, const void *p2);
int my_bsearch(const void *a, int n, int sz, const void *v, cmp_t cmp) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    int x = cmp(a + m * sz, v);
    if (x == 0) {
      return m;
    }
    if (x < 0) {
      l = m + 1;
    } else if (x > 0) {
      r = m - 1;
    }
  }
  return -1;
}
int main(int argc, char *argv[]) {
  int a[] = {1, 3, 5, 7, 9, 11, 20, 22, 24, 26, 28, 30};
  int n = sizeof(a)/sizeof(a[0]);
  int v;
  sscanf(argv[1], "%d", &v);
  printf("%d\n", my_bsearch(a, n, sizeof(int), &v, icmp));
}