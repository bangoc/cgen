#include "tests/base/utils.h"

#include "tree/spec/gbs.h"
#include "tree/spec/grb.h"

int main() {
  struct grbtree *t = grb_create_tree(NULL, gtype_cmp_l, NULL);
  grb_insert(t, gtype_l(1));
  grb_insert(t, gtype_l(3));
  grb_insert(t, gtype_l(5));
  grb_insert(t, gtype_l(7));
  grb_insert(t, gtype_l(9));
  CHECK_MSG(grb_search_gte(t, gtype_l(10)) == NULL, "Tìm >= 10");
  CHECK_MSG(grb_search_gte(t, gtype_l(2))->key.l == 3, "Tìm >= 2");
  CHECK_MSG(grb_search_gte(t, gtype_l(5))->key.l == 5, "Tìm >= 5");
  grb_free_tree(t);
  TEST_OK();
  return 0;
}
