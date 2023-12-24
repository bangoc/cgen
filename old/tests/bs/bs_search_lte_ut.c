#include "tests/base/utils.h"

#include "tests/rb/rbi.h"

int main() {
  struct grbtree *t = rbi_create_tree(NULL);
  rbi_insert(t, 1);
  rbi_insert(t, 3);
  rbi_insert(t, 5);
  rbi_insert(t, 7);
  rbi_insert(t, 9);
  CHECK_MSG(grb_search_lte(t, gtype_l(0)) == NULL, "Tìm <= 0");
  CHECK_MSG(grb_search_lte(t, gtype_l(2))->key.l == 1, "Tìm <= 2");
  CHECK_MSG(grb_search_lte(t, gtype_l(7))->key.l == 7, "Tìm <= 7");
  rbi_free_tree(t);
  return 0;
}
