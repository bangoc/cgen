#include "tests/base/utils.h"
#include "tests/bns/bns_gtype_helper.h"

#include "base/bns.h"

int t1() {
  bn_tree_t t = bns_create_tree_g(NULL_PTR, gtype_cmp_l);
  bns_insert_g(t, gtype_l(20));
  bns_insert_g(t, gtype_l(10));
  bns_insert_g(t, gtype_l(30));
  bns_insert_g(t, gtype_l(50));
  bns_insert_g(t, gtype_l(8));
  /*
        20
      10  30
     8     50
  */
  CHECK_MSG(bn_size(t) == 5, "size 5");

  bns_pprint(t, gtype_print_l);
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(10),
    gtype_l(20), gtype_l(30), gtype_l(50)}, 5), "Match sequence 5");

  bn_node_t tmp = bns_search_g(t, gtype_l(10));
  CHECK_MSG(tmp && bns_node_g_key(tmp).l == 10, "key 10");
  bns_delete_g(t, tmp);
  free(tmp);

  tmp = bns_search_g(t, gtype_l(50));
  CHECK_MSG(tmp && bns_node_g_key(tmp).l == 50, "key 50");
  bns_delete_g(t, tmp);
  free(tmp);

  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(20),
      gtype_l(30)}, 3), "Match sequence 3");

  bn_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}