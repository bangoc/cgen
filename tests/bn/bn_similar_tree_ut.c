#include "tree/bn.h"
#include "tests/base/helpers.h"
#include "tests/base/utils.h"

int bn_similar_null(struct bnn *n1, struct bnn *n2) {
  return (n1 != NULL) == (n2 != NULL);
}

int main() {
  struct bnn *n11 = bn_create_node();
  struct bnn *n12 = bn_create_node();
  struct bnn *n13 = bn_create_node();

  struct bnn *n21 = bn_create_node();
  struct bnn *n22 = bn_create_node();
  struct bnn *n23 = bn_create_node();

  struct bnt *t2 = bn_create_tree(NULL);
  struct bnt *t1 = bn_create_tree(NULL);

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
  bn_free_tree(t1);
  bn_free_tree(t2);
  return 0;
}
