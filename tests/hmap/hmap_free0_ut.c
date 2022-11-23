/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Giải phóng bộ nhớ hmap rỗng, kiểm tra với valgrind
 */

#include "tests/base/utils.h"
#include "vec/hmap.h"

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, gtype_free_s);
  hmap_free(map);
  TEST_OK();
  return 0;
}