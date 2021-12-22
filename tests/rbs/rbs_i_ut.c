/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "rbs.h"

#include "tests/base/utils.h"
#include "tests/rbs/rbs_helper.h"

int t1() {
  rbs_t s = rbs_create(gtype_cmp_l, NULL);
  rbs_insert(s, gtype_l(1));
  rbs_insert(s, gtype_l(2));
  rbs_insert(s, gtype_l(3));
  rbs_insert(s, gtype_l(3));
  rbs_insert(s, gtype_l(3));
  CHECK_MSG(rbs_size(s) == 3, "size == 3");
  CHECK_MSG(rbs_traverse_match(s, (gtype[]){gtype_l(1), gtype_l(2), gtype_l(3)}, 3), "match 3");
  CHECK_MSG(rbs_remove(s, gtype_l(2)) == 1, "remove 1");
  CHECK_MSG(rbs_remove(s, gtype_l(6)) == 0, "remove 0");
  CHECK_MSG(rbs_size(s) == 2, "size == 2");
  CHECK_MSG(rbs_traverse_match(s, (gtype[]){gtype_l(1), gtype_l(3)}, 2), "match 2");
  CHECK_MSG(rbs_search(s, gtype_l(1))->value.l == 1, "search 1");
  CHECK_MSG(rbs_search(s, gtype_l(3))->value.l == 3, "search 3");
  CHECK_MSG(rbs_search(s, gtype_l(2)) == NULL, "search 2");
  CHECK_MSG(rbs_search(s, gtype_l(100)) == NULL, "search 100");
  rbs_free(s);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1 == 0");
  TEST_OK();
}
