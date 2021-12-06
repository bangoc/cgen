#include "bns.h"

#include "tests/base/utils.h"
#include "tests/bns/bns_gtype_helper.h"

int t1() {
  bn_tree_t t = bns_create_tree_g(NULL_PTR, gtype_cmp_i);
  bns_insert_g(t, gtype_i(30));
  bns_insert_g(t, gtype_i(20));
  bns_insert_g(t, gtype_i(10));
  bns_insert_g(t, gtype_i(50));
  bns_insert_g(t, gtype_i(60));
  bns_insert_g(t, gtype_i(80));
  bns_insert_g(t, gtype_i(23));
  /*
            30
        20      50
      10  23      60
                    80
  */
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_i(10), gtype_i(20), gtype_i(23), gtype_i(30),
            gtype_i(50), gtype_i(60), gtype_i(80)}, 7), "bns 7 nodes");
  CHECK_MSG(bns_node_g_key(bns_search_g(t, gtype_i(60))).i == 60, "Search 60");
  CHECK_MSG(bns_search_g(t, gtype_i(68)) == NULL_PTR, "Search 68");

  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_i(15))).i == 20, "Search gte 15");
  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_i(0))).i == 10, "Search gte 0");
  CHECK_MSG(bns_node_g_key(bns_search_gte_g(t, gtype_i(80))).i == 80, "Search gte 80");
  CHECK_MSG(bns_search_gte_g(t, gtype_i(90)) == NULL_PTR, "Search gte 90");

  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_i(15))).i == 10, "Search lte 15");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_i(31))).i == 30, "Search lte 31");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_i(50))).i == 50, "Search lte 50");
  CHECK_MSG(bns_node_g_key(bns_search_lte_g(t, gtype_i(99))).i == 80, "Search lte 99");
  CHECK_MSG(bns_search_lte_g(t, gtype_i(8)) == NULL_PTR, "Search lte 8");
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  return 0;
}