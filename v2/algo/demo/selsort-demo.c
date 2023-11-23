#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void aprint(int n, int *a) {
  printf("%d: ", n);
  for (int i = 0; i < n; ++i) {
    printf(" %d", a[i]);
  }
  printf("\n");
}
int icmp(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int *)p2;
}
typedef int (*cmp_t)(const void *, const void *);
void selsort(void *a, int n, int sz, cmp_t cmp) {
  char *buff = malloc(sz);
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      void *pi = a + i * sz, *pj = a + j * sz;
      if (cmp(pi, pj) > 0) {
        memcpy(buff, pi, sz);
        memcpy(pi, pj, sz);
        memcpy(pj, buff, sz);
      }
    }
  }
  free(buff);
}
int main() {
  int a[] = {3, 2, 1, 6, 8, 9, 10, 5};
  int n = sizeof(a)/sizeof(a[0]);
  selsort(a, n, sizeof(a[0]), icmp);
  aprint(n, a);
}