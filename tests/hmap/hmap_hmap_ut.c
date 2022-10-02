/* (C) Nguyen Ba Ngoc */

/**
 * Thử nghiệm lưu hmap trong hmap
 */

#include "all.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int main() {
  struct hmap *map = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, gtype_free_hmap);
  for (int i = 0; i < 100; ++i) {
    struct hmap *tmp = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, NULL);
    int n = rand() % 1000 + 1;
    for (int j = 0; j < n; ++j) {
      hmap_insert(tmp, gtype_l(rand()), gtype_l(rand()));
    }
    hmap_insert(map, gtype_l(i), gtype_v(tmp));
  }
  hmap_traverse(k, v, map) {
    struct hmap *tmp = v->v;
    printf("%ld: %d: ", k->l, hmap_size(tmp));
    hmap_traverse(k, v, tmp) {
      printf(" (%ld, %ld)", k->l, v->l);
    }
    printf("\n");
  }
  hmap_free(map);
  TEST_OK();
  return 0;
}