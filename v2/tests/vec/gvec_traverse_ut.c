/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct vector *v = gvec_create(10);
  for (int i = 0; i < 10; ++i) {
    gvec_ref(v, i)->l = i;
  }
  gvec_traverse(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  gvec_rtraverse(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  gvec_free(v);
  TEST_OK();
}