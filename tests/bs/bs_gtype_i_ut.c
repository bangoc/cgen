#include "tests/base/utils.h"
#include "tests/bs/bs_gtype_helper.h"

#include "tree/bs.h"

int t1() {
  bs_tree_t t = bs_create_tree(NULL, gtype_cmp_l, NULL);
  bs_insert(t, gtype_l(20));
  bs_insert(t, gtype_l(10));
  bs_insert(t, gtype_l(30));
  bs_insert(t, gtype_l(50));
  bs_insert(t, gtype_l(8));
  /*
        20
      10  30
     8     50
  */
  CHECK_MSG(bn_size(bn_tree(t)) == 5, "size 5");

  bs_pprint(t, gtype_print_l);
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(10),
    gtype_l(20), gtype_l(30), gtype_l(50)}, 5), "Match sequence 5");

  bs_node_t tmp = bs_search(t, gtype_l(10));
  CHECK_MSG(tmp && tmp->key.l == 10, "key 10");
  bs_delete(t, tmp);

  tmp = bs_search(t, gtype_l(50));
  CHECK_MSG(tmp && tmp->key.l == 50, "key 50");
  bs_delete(t, tmp);

  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(20),
      gtype_l(30)}, 3), "Match sequence 3");
  bs_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}