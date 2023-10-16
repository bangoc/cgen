/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct vector *v = vcreate(10);
  for (int i = 0; i < 10; ++i) {
    vref(v, i)->l = i;
  }
  VTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  VRTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  vfree(v);
  TEST_OK();
}