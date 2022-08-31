#include "tests/base/utils.h"
#include "tests/bs/bs_gtype_helper.h"

#include "tree/spec/bsg.h"

int t1() {
  bsg_tree_t t = bsg_create_tree(NULL, gtype_cmp_l, NULL);
  bsg_insert(t, gtype_l(20));
  bsg_insert(t, gtype_l(10));
  bsg_insert(t, gtype_l(30));
  bsg_insert(t, gtype_l(50));
  bsg_insert(t, gtype_l(8));
  /*
        20
      10  30
     8     50
  */
  CHECK_MSG(bn_size(bn_tree(t)) == 5, "size 5");

  bsg_pprint(t, gtype_print_l);
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(10),
    gtype_l(20), gtype_l(30), gtype_l(50)}, 5), "Match sequence 5");

  bsg_node_t tmp = bsg_search(t, gtype_l(10));
  CHECK_MSG(tmp && tmp->key.l == 10, "key 10");
  bsg_delete(t, tmp);

  tmp = bsg_search(t, gtype_l(50));
  CHECK_MSG(tmp && tmp->key.l == 50, "key 50");
  bsg_delete(t, tmp);

  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(20),
      gtype_l(30)}, 3), "Match sequence 3");
  bsg_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}