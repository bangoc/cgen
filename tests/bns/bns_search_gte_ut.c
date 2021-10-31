#include "tests/base/utils.h"

#include "tests/rb/rbi.h"

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_insert(t, 1);
  rbi_insert(t, 3);
  rbi_insert(t, 5);
  rbi_insert(t, 7);
  rbi_insert(t, 9);
  rbi_node_t n = to_rbi(rbi_create_node(10));
  bns_search_gte_inline(out, t, to_bn(n), rbi_compare,
      CHECK_MSG(out == NULL_PTR, "Tìm >= 10"));
  n->value = 2;
  bns_search_gte_inline(out, t, to_bn(n), rbi_compare,
    CHECK_MSG(to_rbi(out)->value == 3, "Tìm >= 2"));
  n->value = 5;
  bns_search_gte_inline(out, t, to_bn(n), rbi_compare,
    CHECK_MSG(to_rbi(out)->value == 5, "Tìm >= 5"));
  return 0;
}
