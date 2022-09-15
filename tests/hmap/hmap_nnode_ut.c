#include "vec/hmap.h"
#include "tests/base/utils.h"

struct hmap_ires hmap_insert_free_key(struct hmap *map, gtype key, gtype value) {
  struct hmap_ires res = hmap_insert(map, key, value);
  if (!res.inserted) {
    if (map->free_key) {
      map->free_key(key);
    }
  }
  return res;
}

int main() {
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s,
        gtype_free_s, NULL);
  hmap_insert(map, gtype_s(strdup("aaa")), gtype_l(100));
  hmap_insert(map, gtype_s(strdup("bbb")), gtype_l(200));
  hmap_insert(map, gtype_s(strdup("ccc")), gtype_l(300));
  hmap_insert(map, gtype_s(strdup("ddd")), gtype_l(400));
  hmap_insert(map, gtype_s(strdup("eee")), gtype_l(500));
  CHECK_MSG(hmap_size(map) == 5, "nnodes == 5");
  CHECK_MSG(map->noccupied == 5, "noccupied == 5");
  hmap_remove(map, gtype_s("aaa"));
  hmap_remove(map, gtype_s("bbb"));
  CHECK_MSG(hmap_size(map) == 3, "nnodes == 3");
  CHECK_MSG(map->noccupied == 5, "noccupied == 5");
  gtype *value = hmap_insert_free_key(map, gtype_s(strdup("eee")), gtype_l(600)).value;
  CHECK_MSG(value->l == 500, "value eee == 500");
  hmap_insert(map, gtype_s(strdup("fff")), gtype_l(700));
  hmap_insert(map, gtype_s(strdup("ggg")), gtype_l(800));
  hmap_insert(map, gtype_s(strdup("hhh")), gtype_l(900));
  hmap_insert(map, gtype_s(strdup("iii")), gtype_l(1000));
  hmap_insert(map, gtype_s(strdup("jjj")), gtype_l(1100));
  CHECK_MSG(hmap_size(map) == 8, "nnodes == 8");
  CHECK_MSG(map->noccupied == 8, "noccupied (sau resize) == 8");
  hmap_remove(map, gtype_s("eee"));
  value = hmap_insert_free_key(map, gtype_s(strdup("eee")), gtype_l(600)).value;
  CHECK_MSG(value->l == 600, "value eee == 600");
  CHECK_MSG(hmap_value(map, gtype_s("eee"))->l == 600, "value eee == 600");
  hmap_free(map);
  TEST_OK();
  return 0;
}
