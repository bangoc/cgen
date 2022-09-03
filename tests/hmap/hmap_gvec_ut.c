/*
  (C) Nguyen Ba Ngoc 2022
  Thử nghiệm lưu gvec trong hmap
*/

#include "all.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  hmap_t map = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, gtype_free_gvec);
  for (int i = 0; i < 100; ++i) {
    gvec_t vec = gvec_create(0, NULL);
    int n = rand() % 100 + 1;
    for (int j = 0; j < n; ++j) {
      gvec_append(vec, gtype_l(rand()));
    }
    CHECK_MSG(hmap_insert(map, gtype_l(i), gtype_v(vec)).inserted, "Insert vector i");
  }
  hmap_traverse(k, v, map) {
    gvec_t vec = v->v;
    printf("%ld: %ld: ", k->l, gvec_size(vec));
    gvec_traverse(value, vec) {
      printf(" %ld", value->l);
    }
    printf("\n");
  }
  hmap_free(map);
  TEST_OK();
  return 0;
}