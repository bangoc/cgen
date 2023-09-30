#include "tests/base/utils.h"
#include "tree/spec/gbs.h"

int main() {
  struct gbsnode n1 = {.key = gtype_l(1)};
  struct gbsnode n2 = {.key = gtype_l(2)};
  struct gbsnode n3 = {.key = gtype_l(3)};
  struct gbsnode n4 = {.key = gtype_l(4)};
  struct gbsnode n5 = {.key = gtype_l(5)};
  struct gbsnode n6 = {.key = gtype_l(6)};
  struct gbsnode n_1 = {.key = gtype_l(-1)};

  n2.base.left = bn_node(&n1);
  n1.base.top = bn_node(&n2);
  n2.base.right = bn_node(&n3);
  n3.base.top = bn_node(&n2);
  n3.base.right = bn_node(&n5);
  n5.base.top = bn_node(&n3);
  n5.base.left = bn_node(&n4);
  n4.base.top = bn_node(&n5);
  struct gbstree *t = gbs_create_tree(&n2, gtype_cmp_l, NULL);
  /*
          2
        1   3
              5
            4
  */
  CHECK_MSG(gbs_search(t, n1.key) == &n1, "Failed search 1");
  CHECK_MSG(gbs_search(t, n2.key) == &n2, "Failed search 2");
  CHECK_MSG(gbs_search(t, n3.key) == &n3, "Failed search 3");
  CHECK_MSG(gbs_search(t, n4.key) == &n4, "Failed search 4");
  CHECK_MSG(gbs_search(t, n5.key) == &n5, "Failed search 5");
  CHECK_MSG(gbs_search(t, n6.key) == NULL, "Failed search 6");
  CHECK_MSG(gbs_search(t, n_1.key) == NULL, "Failed search -1");
  free(t);
  TEST_OK();
  return 0;
}
