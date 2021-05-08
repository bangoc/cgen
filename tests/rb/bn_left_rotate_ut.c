#include "rb.h"
#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  bn_node_t n1 = bn_create_node();
  bn_node_t n2 = bn_create_node();
  bn_node_t n3 = bn_create_node();
  bn_node_t n4 = bn_create_node();
  bn_node_t n5 = bn_create_node();
  bn_tree_t t = bn_create_tree(n4);
  /*
         4
    2          5
  1   3
  */
  n2->left = n1;
  n1->top = n2;
  n2->right = n3;
  n3->top = n1;
  n2->top = n4;
  n4->left = n2;
  n4->right = n5;
  n5->top = n4;
  t->root = n4;
  bn_node_t y = bn_left_rotate(t, n4);
  /*
            5
        4
    2
 1     3
  */
  CHECK(t->root == n5);
  CHECK(t->root->right == NULL_PTR);
  CHECK(t->root->left == n4);
  CHECK(t->root->left->right == NULL_PTR);
  CHECK(t->root->left->left == n2);
  CHECK(t->root->left->left->left == n1);
  CHECK(t->root->left->left->right == n3);
  y = bn_right_rotate(t, y);
  /*
           4
    2          5
  1   3
  */
  CHECK(t->root == n4);
  CHECK(t->root->right == n5);
  CHECK(t->root->left == n2);
  CHECK(t->root->left->left == n1);
  CHECK(t->root->left->right == n3);
  CHECK(t->root->right->right == NULL_PTR);
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}