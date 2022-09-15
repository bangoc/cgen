#include "tests/base/utils.h"
#include "tests/bs/bs_gtype_helper.h"

#include "tree/spec/gbs.h"

int t1() {
  struct gbstree *t = gbs_create_tree(NULL, gtype_cmp_l, NULL);
  gbs_insert(t, gtype_l(20));
  gbs_insert(t, gtype_l(10));
  gbs_insert(t, gtype_l(30));
  gbs_insert(t, gtype_l(50));
  gbs_insert(t, gtype_l(8));
  /*
        20
      10  30
     8     50
  */
  CHECK_MSG(bn_size(bn_tree(t)) == 5, "size 5");

  gbs_pprint(t, gtype_print_l);
  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(10),
    gtype_l(20), gtype_l(30), gtype_l(50)}, 5), "Match sequence 5");

  struct gbsnode *tmp = gbs_search(t, gtype_l(10));
  CHECK_MSG(tmp && tmp->key.l == 10, "key 10");
  gbs_delete(t, tmp);

  tmp = gbs_search(t, gtype_l(50));
  CHECK_MSG(tmp && tmp->key.l == 50, "key 50");
  gbs_delete(t, tmp);

  CHECK_MSG(lnr_match_g(t, (gtype[]){gtype_l(8), gtype_l(20),
      gtype_l(30)}, 3), "Match sequence 3");
  gbs_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}