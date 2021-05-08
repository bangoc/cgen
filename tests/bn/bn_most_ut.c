#include "tests/base/utils.h"
#include "bns.h"

int t1() {
  bn_node_t n1 = bn_create_node();
  bn_node_t n2 = bn_create_node();
  bn_node_t n3 = bn_create_node();
  bn_node_t n4 = bn_create_node();
  bn_node_t n5 = bn_create_node();
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
  CHECK(bn_left_most(n3) == n1);
  CHECK(bn_right_most(n3) == n5);
  CHECK(bn_left_most(n2) == n1);
  CHECK(bn_right_most(n2) == n2);
  CHECK(bn_left_most(n4) == n4);
  CHECK(bn_right_most(n4) == n5);
  CHECK(bn_left_most(n1) == n1);
  CHECK(bn_right_most(n1) == n1);
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}