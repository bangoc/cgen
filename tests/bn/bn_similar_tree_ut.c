#include "bn.h"
#include "tests/base/bn_utils.h"
#include "tests/base/utils.h"

int bn_similar_null(bn_node_t n1, bn_node_t n2) {
  return (n1 != NULL_PTR) == (n2 != NULL_PTR);
}

int main() {
  bn_node_t n11 = bn_create_node();
  bn_node_t n12 = bn_create_node();
  bn_node_t n13 = bn_create_node();

  bn_node_t n21 = bn_create_node();
  bn_node_t n22 = bn_create_node();
  bn_node_t n23 = bn_create_node();

  bn_tree_t t2 = bn_create_tree(NULL_PTR);
  bn_tree_t t1 = bn_create_tree(NULL_PTR);

  CHECK_MSG(bn_similar_tree(t1, t2, bn_similar_null) == 1, "Hai cây rỗng gốc");
  t1->root = n11;
  CHECK_MSG(bn_similar_tree(t1, t2, bn_similar_null) == 0, "Một cây rỗng gốc");
  t2->root = n21;
  CHECK_MSG(bn_similar_tree(t1, t2, bn_similar_null) == 1, "Hai cây khác rỗng");

  bn_connect2(n11, right, n12, top);
  bn_connect2(n12, right, n13, top);
  bn_connect2(n21, right, n22, top);
  bn_connect2(n22, right, n23, top);

  CHECK_MSG(bn_similar_tree(t1, t2, bn_similar_null) == 1, "Hai cây 1 -> 2 -> 3");
  return 0;
}