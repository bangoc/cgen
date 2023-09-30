#include "tree/bn.h"

#include "tests/base/utils.h"

int t1() {
  struct bnnode *n1 = bn_create_node();
  struct bnnode *n2 = bn_create_node();
  struct bnnode *n3 = bn_create_node();
  struct bnnode *n4 = bn_create_node();
  struct bnnode *n5 = bn_create_node();
  /* bn là cây nhị phân tổng quát, không phải cây tìm kiếm.
            n2
          n1   n3
        n4   n5
  */
  bn_connect2(n1, top, n2, left);
  bn_connect2(n4, top, n1, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n3, left, n5, top);
  struct bntree *t = bn_create_tree(n2);
  CHECK_MSG(bn_edge_height(t) == 2, "Edge height = 2");
  bn_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}