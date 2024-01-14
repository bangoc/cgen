#include "cgen.h"
#include <stdio.h>
int icmp(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int *)p2;
}
int main(int argc, char *argv[]) {
  int a[] = {1, 3, 5, 7, 9, 11, 20, 22, 24, 26, 28, 30};
  int n = sizeof(a)/sizeof(a[0]);
  int k;
  if (argc == 1) {
    printf("Usage: binsearch xyz\n");
    return 0;
  }
  for (int i = 1; i < argc; ++i) {
    sscanf(argv[i], "%d", &k);
    int *pos = bnear_search(&k, a, n, sizeof(int), icmp);
    if (*pos == k) {
      printf("Found %d at position %ld\n", k, pos - a);
    } else {
      printf("Not found %d.", k);
      printf(" Near %ld - %d\n", pos - a, *pos);
    }
  }
}