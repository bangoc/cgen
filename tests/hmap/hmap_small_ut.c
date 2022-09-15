#include "vec/hmap.h"
#include "tests/base/utils.h"

int main() {
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_insert(map, gtype_s("aa"), gtype_l(1));
  hmap_insert(map, gtype_s("bb"), gtype_l(2));
  hmap_insert(map, gtype_s("cc"), gtype_l(3));
  hmap_insert(map, gtype_s("dd"), gtype_l(4));
  hmap_insert(map, gtype_s("ee"), gtype_l(5));
  hmap_insert(map, gtype_s("ff"), gtype_l(6));
  hmap_insert(map, gtype_s("gg"), gtype_l(7));
  hmap_insert(map, gtype_s("hh"), gtype_l(8));
  hmap_insert(map, gtype_s("ii"), gtype_l(9));
  hmap_insert(map, gtype_s("jj"), gtype_l(10));
  hmap_insert(map, gtype_s("kk"), gtype_l(11));
  hmap_insert(map, gtype_s("ll"), gtype_l(12));
  CHECK_MSG(hmap_value(map, gtype_s("aa"))->l == 1, "value aa == 1");
  CHECK_MSG(hmap_value(map, gtype_s("hh"))->l == 8, "value hh == 8");
  CHECK_MSG(hmap_value(map, gtype_s("ll"))->l == 12, "value ii == 12");
  CHECK_MSG(hmap_remove(map, gtype_s("aa")) == 1, "remove aa");
  CHECK_MSG(hmap_remove(map, gtype_s("bb")) == 1, "remove bb");
  CHECK_MSG(hmap_remove(map, gtype_s("hh")) == 1, "remove kk");
  CHECK_MSG(hmap_remove(map, gtype_s("aa")) == 0, "remove aa");
  CHECK_MSG(hmap_remove(map, gtype_s("bb")) == 0, "remove bb");
  CHECK_MSG(hmap_remove(map, gtype_s("hh")) == 0, "remove kk");
  CHECK_MSG(hmap_value(map, gtype_s("aa")) == NULL, "value aa == NULL");
  CHECK_MSG(hmap_value(map, gtype_s("hh")) == NULL, "value hh == 8");
  CHECK_MSG(hmap_value(map, gtype_s("ll"))->l == 12, "value bb == 12");
  hmap_insert(map, gtype_s("aaa"), gtype_l(13));
  hmap_insert(map, gtype_s("bbb"), gtype_l(14));
  hmap_insert(map, gtype_s("ccc"), gtype_l(15));
  hmap_insert(map, gtype_s("ddd"), gtype_l(16));
  hmap_insert(map, gtype_s("eee"), gtype_l(17));
  hmap_insert(map, gtype_s("fff"), gtype_l(18));
  hmap_insert(map, gtype_s("ggg"), gtype_l(19));
  hmap_insert(map, gtype_s("hhh"), gtype_l(20));
  CHECK_MSG(hmap_value(map, gtype_s("aaa"))->l == 13, "value aaa == 13");
  gtype *value = hmap_insert(map, gtype_s("aaa"), gtype_l(130)).value;
  CHECK_MSG(value->l == 13, "value aaa == 13");
  value->l = 130;
  CHECK_MSG(hmap_value(map, gtype_s("aaa"))->l == 130, "value aaa == 130");
  hmap_free(map);
  TEST_OK();
  return 0;
}