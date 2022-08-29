/* (C) Nguyen Ba Ngoc 2021 */

#include "base/bs.h"

#include "tests/base/utils.h"
#include "tests/bs/bs_gtype_helper.h"

int t1() {
  bs_tree_t t = bs_create_tree(NULL, gtype_cmp_l, NULL);
  bs_insert(t, gtype_l(30));
  bs_insert(t, gtype_l(20));
  bs_insert(t, gtype_l(10));
  bs_insert(t, gtype_l(50));
  bs_insert(t, gtype_l(60));
  bs_insert(t, gtype_l(80));
  bs_insert(t, gtype_l(23));
  bs_pprint(t, gtype_print_l);
  /*
            30
        20      50
      10  23      60
                    80
  */
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(10), gtype_l(20), gtype_l(23), gtype_l(30),
            gtype_l(50), gtype_l(60), gtype_l(80)}, 7), "bs 7 nodes");
  CHECK_MSG(bs_search(t, gtype_l(60))->key.l == 60, "Search 60");
  CHECK_MSG(bs_search(t, gtype_l(68)) == NULL, "Search 68");

  CHECK_MSG(bs_search_gte(t, gtype_l(15))->key.l == 20, "Search gte 15");
  CHECK_MSG(bs_search_gte(t, gtype_l(0))->key.l == 10, "Search gte 0");
  CHECK_MSG(bs_search_gte(t, gtype_l(80))->key.l == 80, "Search gte 80");
  CHECK_MSG(bs_search_gte(t, gtype_l(90)) == NULL, "Search gte 90");

  CHECK_MSG(bs_search_lte(t, gtype_l(15))->key.l == 10, "Search lte 15");
  CHECK_MSG(bs_search_lte(t, gtype_l(31))->key.l == 30, "Search lte 31");
  CHECK_MSG(bs_search_lte(t, gtype_l(50))->key.l == 50, "Search lte 50");
  CHECK_MSG(bs_search_lte(t, gtype_l(99))->key.l == 80, "Search lte 99");
  CHECK_MSG(bs_search_lte(t, gtype_l(8)) == NULL, "Search lte 8");

  bs_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok!");
  return 0;
}