#include "tests/base/utils.h"

#include "tests/rb/rbi.h"

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_insert(t, 1);
  rbi_insert(t, 3);
  rbi_insert(t, 5);
  rbi_insert(t, 7);
  rbi_insert(t, 9);
  rbi_node_t n = to_rbi(rbi_create_node(0));
  CHECK_MSG(bns_search_lte(t->root, n, rbi_compare) == NULL_PTR, "Tìm <= 0");
  n->value = 2;
  CHECK_MSG(to_rbi(bns_search_lte(t->root, n, rbi_compare))->value == 1, "Tìm <= 2");
  n->value = 7;
  CHECK_MSG(to_rbi(bns_search_lte(t->root, n, rbi_compare))->value == 7, "Tìm <= 7");
  return 0;
}