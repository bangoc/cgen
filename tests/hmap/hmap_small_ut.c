#include "hmap.h"
#include "tests/base/utils.h"

int main() {
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_insert(map, gtype_s("aa"), gtype_i(1));
  hmap_insert(map, gtype_s("bb"), gtype_i(2));
  hmap_insert(map, gtype_s("cc"), gtype_i(3));
  hmap_insert(map, gtype_s("dd"), gtype_i(4));
  hmap_insert(map, gtype_s("ee"), gtype_i(5));
  hmap_insert(map, gtype_s("ff"), gtype_i(6));
  hmap_insert(map, gtype_s("gg"), gtype_i(7));
  hmap_insert(map, gtype_s("hh"), gtype_i(8));
  hmap_insert(map, gtype_s("ii"), gtype_i(9));
  hmap_insert(map, gtype_s("jj"), gtype_i(10));
  hmap_insert(map, gtype_s("kk"), gtype_i(11));
  hmap_insert(map, gtype_s("ll"), gtype_i(12));
  CHECK_MSG(hmap_value(map, gtype_s("aa"))->i == 1, "value aa == 1");
  CHECK_MSG(hmap_value(map, gtype_s("hh"))->i == 8, "value hh == 8");
  CHECK_MSG(hmap_value(map, gtype_s("ll"))->i == 12, "value ii == 12");
  CHECK_MSG(hmap_remove(map, gtype_s("aa")) == 1, "remove aa");
  CHECK_MSG(hmap_remove(map, gtype_s("bb")) == 1, "remove bb");
  CHECK_MSG(hmap_remove(map, gtype_s("hh")) == 1, "remove kk");
  CHECK_MSG(hmap_remove(map, gtype_s("aa")) == 0, "remove aa");
  CHECK_MSG(hmap_remove(map, gtype_s("bb")) == 0, "remove bb");
  CHECK_MSG(hmap_remove(map, gtype_s("hh")) == 0, "remove kk");
  CHECK_MSG(hmap_value(map, gtype_s("aa")) == NULL, "value aa == NULL");
  CHECK_MSG(hmap_value(map, gtype_s("hh")) == NULL, "value hh == 8");
  CHECK_MSG(hmap_value(map, gtype_s("ll"))->i == 12, "value bb == 12");
  hmap_insert(map, gtype_s("aaa"), gtype_i(13));
  hmap_insert(map, gtype_s("bbb"), gtype_i(14));
  hmap_insert(map, gtype_s("ccc"), gtype_i(15));
  hmap_insert(map, gtype_s("ddd"), gtype_i(16));
  hmap_insert(map, gtype_s("eee"), gtype_i(17));
  hmap_insert(map, gtype_s("fff"), gtype_i(18));
  hmap_insert(map, gtype_s("ggg"), gtype_i(19));
  hmap_insert(map, gtype_s("hhh"), gtype_i(20));
  CHECK_MSG(hmap_value(map, gtype_s("aaa"))->i == 13, "value aaa == 13");
  int idx = hmap_insert(map, gtype_s("aaa"), gtype_i(130)).idx;
  CHECK_MSG(hmap_value_at(map, idx)->i == 13, "value aaa == 13");
  hmap_value_at(map, idx)->i = 130;
  CHECK_MSG(hmap_value_at(map, idx)->i == 130, "value aaa == 130");
  hmap_free(map);
  TEST_OK();
}