/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Giải phóng bộ nhớ hmap rỗng, kiểm tra với valgrind
 */

#include "vec/hmap.h"

int main() {
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, gtype_free_s);
  hmap_free(map);
  return 0;
}