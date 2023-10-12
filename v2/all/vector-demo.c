#include "cgen.h"

#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  struct vector *v = vcreate(n);
  vtraverse(cur, v) {
    scanf("%ld", (long*)cur);
  }
  vrtraverse(cur, v) {
    printf("%ld ", cur->l);
  }
  printf("\n");
  vfree(v);
}