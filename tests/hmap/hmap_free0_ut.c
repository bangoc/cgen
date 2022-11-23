/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Giải phóng bộ nhớ hmap rỗng, kiểm tra với valgrind
 */

#include "tests/base/utils.h"
#include "vec/hmap.h"

int main(int argc, char *argv[]) {
  GC_INIT();
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, gtype_free_s);
  hmap_free(map);
  TEST_OK();
  return 0;
}