#include "base/bns.h"

#include "tests/base/utils.h"
#include "tests/bns/bns_gtype_helper.h"

int t1() {
  bn_tree_t t = bns_create_tree_g(NULL_PTR, gtype_cmp_l);
  bns_insert_g(t, gtype_l(30));
  bns_insert_g(t, gtype_l(20));
  bns_insert_g(t, gtype_l(10));
  bns_insert_g(t, gtype_l(50));
  bns_insert_g(t, gtype_l(60));
  bns_insert_g(t, gtype_l(80));
  bns_insert_g(t, gtype_l(23));
  /*
            30
        20      50
      10  23      60
                    80
  */
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(10), gtype_l(20), gtype_l(23), gtype_l(30),
            gtype_l(50), gtype_l(60), gtype_l(80)}, 7), "bns 7 nodes");
  CHECK_MSG(bns_node_g_key(bns_search_g(t, gtype_l(60))).l == 60, "Search 60");
  CHECK_MSG(bns_search_g(t, gtype_l(68)) == NULL_PTR, "Search 68");

  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_l(15))).l == 20, "Search gte 15");
  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_l(0))).l == 10, "Search gte 0");
  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_l(80))).l == 80, "Search gte 80");
  CHECK_MSG(bns_search_gte_g(t, gtype_l(90)) == NULL_PTR, "Search gte 90");

  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_l(15))).l == 10, "Search lte 15");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_l(31))).l == 30, "Search lte 31");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_l(50))).l == 50, "Search lte 50");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_l(99))).l == 80, "Search lte 99");
  CHECK_MSG(bns_search_lte_g(t, gtype_l(8)) == NULL_PTR, "Search lte 8");
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  return 0;
}