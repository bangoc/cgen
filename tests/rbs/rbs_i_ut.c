/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "rbs.h"

#include "tests/base/utils.h"
#include "tests/rbs/rbs_helper.h"

int t1() {
  rbs_t s = rbs_create(gtype_cmp_i);
  rbs_insert(s, gtype_i(1));
  rbs_insert(s, gtype_i(2));
  rbs_insert(s, gtype_i(3));
  rbs_insert(s, gtype_i(3));
  rbs_insert(s, gtype_i(3));
  ASSERT(rbs_size(s) == 3, "size == 3");
  ASSERT(rbs_traverse_match(s, (gtype[]){gtype_i(1), gtype_i(2), gtype_i(3)}, 3), "match 3");
  free(rbs_delete(s, gtype_i(2)));
  ASSERT(rbs_size(s) == 2, "size == 2");
  ASSERT(rbs_traverse_match(s, (gtype[]){gtype_i(1), gtype_i(3)}, 2), "match 2");
  ASSERT(rbs_search(s, gtype_i(1))->value.i == 1, "search 1");
  ASSERT(rbs_search(s, gtype_i(3))->value.i == 3, "search 3");
  ASSERT(rbs_search(s, gtype_i(2)) == NULL, "search 2");
  ASSERT(rbs_search(s, gtype_i(100)) == NULL, "search 100");
  rbs_free(s);
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1 == 0");
  TEST_OK();
}