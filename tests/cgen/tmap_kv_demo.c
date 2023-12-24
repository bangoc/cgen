#include "cgen.h"

#include <stdio.h>

TDECL_IMPL(simap, char*, int, si);
int main() {
  struct simap *si = simap(cmps);
  siput(si, "aaa", 5);
  siput(si, "bbb", 10);
  siput(si, "ccc", 15);
  siput(si, "ddd", 20);
  siput(si, "eee", 30);
  char *a[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff"};
  int n = sizeof(a)/sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    int *v = siget(si, a[i]);
    if (v) {
      printf("%s: %d\n", sipval_node(v)->key, *v);
    } else {
      printf("Not found %s\n", a[i]);
    }
  }
  sifree(si);
}