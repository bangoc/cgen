#include "tests/base/utils.h"
#include "tests/bns/bns_gtype_helper.h"

#include "bns.h"

int t1() {
  bn_tree_t t = bns_create_tree_g(NULL_PTR, bns_gcmp_i);
  bns_insert_g(t, gtype_i(20));
  bns_insert_g(t, gtype_i(10));
  bns_insert_g(t, gtype_i(30));
  bns_insert_g(t, gtype_i(50));
  bns_insert_g(t, gtype_i(8));
  /*
        20
      10  30
     8     50
  */
  ASSERT(bn_size(t) == 5, "size 5");

  ASSERT(lnr_match_g(t, (gtype[]){gtype_i(8), gtype_i(10),
    gtype_i(20), gtype_i(30), gtype_i(50)}, 5), "Match sequence 5");

  bn_node_t tmp = bns_search_g(t, gtype_i(10));
  ASSERT(tmp && bns_node_g_key(tmp).i == 10, "key 10");
  bns_delete_g(t, tmp);
  free(tmp);

  tmp = bns_search_g(t, gtype_i(50));
  ASSERT(tmp && bns_node_g_key(tmp).i == 50, "key 50");
  bns_delete_g(t, tmp);
  free(tmp);

  ASSERT(lnr_match_g(t, (gtype[]){gtype_i(8), gtype_i(20),
      gtype_i(30)}, 3), "Match sequence 3");

  bn_free_tree(&t);
  return 0;
}

int main() {
  ASSERT(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}