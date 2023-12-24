#include "tests/base/utils.h"
#include "tree/bn.h"

int t1() {
  struct bnnode *n1 = bn_create_node();
  struct bnnode *n2 = bn_create_node();
  struct bnnode *n3 = bn_create_node();
  struct bnnode *n4 = bn_create_node();
  struct bnnode *n5 = bn_create_node();
  n3->left = n2;
  n3->right = n4;
  n2->left = n1;
  n2->top = n3;
  n1->top = n2;
  n4->top = n3;
  n4->right = n5;
  n5->top = n4;
  /*
        n3
      n2  n4
    n1      n5
  */
  CHECK_MSG(bn_left_most(n3) == n1, "left_most = n1");
  CHECK_MSG(bn_right_most(n3) == n5, "right most = n5");
  CHECK_MSG(bn_left_most(n2) == n1, "left most = n1");
  CHECK_MSG(bn_right_most(n2) == n2, "right most = n2");
  CHECK_MSG(bn_left_most(n4) == n4, "left most = n4");
  CHECK_MSG(bn_right_most(n4) == n5, "right most = n5");
  CHECK_MSG(bn_left_most(n1) == n1, "left most = n1");
  CHECK_MSG(bn_right_most(n1) == n1, "right most = n1");
  bn_free_node(n1);
  bn_free_node(n2);
  bn_free_node(n3);
  bn_free_node(n4);
  bn_free_node(n5);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  return 0;
}