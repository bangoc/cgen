#include "hmap.h"
#include "tests/base/utils.h"

int main() {
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s,
        gtype_free_s, NULL);
  hmap_insert(map, gtype_s(strdup("aaa")), gtype_i(100));
  hmap_insert(map, gtype_s(strdup("bbb")), gtype_i(200));
  hmap_insert(map, gtype_s(strdup("ccc")), gtype_i(300));
  hmap_insert(map, gtype_s(strdup("ddd")), gtype_i(400));
  hmap_insert(map, gtype_s(strdup("eee")), gtype_i(500));
  CHECK_MSG(hmap_nnodes(map) == 5, "nnodes == 5");
  CHECK_MSG(map->noccupied == 5, "noccupied == 5");
  hmap_remove(map, gtype_s("aaa"));
  hmap_remove(map, gtype_s("bbb"));
  CHECK_MSG(hmap_nnodes(map) == 3, "nnodes == 3");
  CHECK_MSG(map->noccupied == 5, "noccupied == 5");
  hmap_insert(map, gtype_s(strdup("eee")), gtype_i(600));
  hmap_insert(map, gtype_s(strdup("fff")), gtype_i(700));
  hmap_insert(map, gtype_s(strdup("ggg")), gtype_i(800));
  hmap_insert(map, gtype_s(strdup("hhh")), gtype_i(900));
  hmap_insert(map, gtype_s(strdup("iii")), gtype_i(1000));
  hmap_insert(map, gtype_s(strdup("jjj")), gtype_i(1100));
  CHECK_MSG(hmap_nnodes(map) == 8, "nnodes == 8");
  CHECK_MSG(map->noccupied == 8, "noccupied (sau resize) == 8");
  CHECK_MSG(hmap_value(map, gtype_s("eee"))->i == 600, "value eee == 600");
  hmap_free(map);
  TEST_OK();
}