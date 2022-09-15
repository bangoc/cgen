/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa lưu gvec trong rbmtree
 */

#include "all.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  struct rbmtree *map = rbm_create(gtype_cmp_l, NULL, gtype_free_gvec);
  for (int i = 0; i < 100; ++i) {
    struct gvector *vec = gvec_create(0, NULL);
    int n = rand() % 100 + 1;
    for (int j = 0; j < n; ++j) {
      gvec_append(vec, gtype_l(rand()));
    }
    CHECK_MSG(rbm_insert(map, gtype_l(i), gtype_v(vec)).inserted, "Insert vector i");
  }
  rbm_traverse(k, v, map) {
    struct gvector *vec = v->v;
    printf("%ld: %ld: ", k->l, gvec_size(vec));
    gvec_traverse(value, vec) {
      printf(" %ld", value->l);
    }
    printf("\n");
  }
  rbm_free(map);
  TEST_OK();
  return 0;
}