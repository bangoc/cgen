#include "tree/spec/grb.h"
#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  struct bnnode *n1 = bn_create_node();
  struct bnnode *n2 = bn_create_node();
  struct bnnode *n3 = bn_create_node();
  struct bnnode *n4 = bn_create_node();
  struct bnnode *n5 = bn_create_node();
  struct bntree *t = bn_create_tree(n4);
  /*
         4
    2          5
  1   3
  */
  bn_connect2(n2, left, n1, top);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n4, left, n2, top);
  bn_connect2(n4, right, n5, top);
  t->root = n4;

  bn_rotate(t, n4, right, left);
  /*
            5
        4
    2
 1     3
  */
  CHECK_MSG(t->root == n5, "root 5");
  CHECK_MSG(t->root->right == NULL, "right null");
  CHECK_MSG(t->root->left == n4, "left n4");
  CHECK_MSG(t->root->left->right == NULL, "left->right null");
  CHECK_MSG(t->root->left->left == n2, "left left n2");
  CHECK_MSG(t->root->left->left->left == n1, " left left left n1");
  CHECK_MSG(t->root->left->left->right == n3, "left left right n3");

  bn_rotate(t, n5, left, right);
  /*
           4
    2          5
  1   3
  */
  CHECK_MSG(t->root == n4, "root n4");
  CHECK_MSG(t->root->right == n5, "root right n5");
  CHECK_MSG(t->root->left == n2, "root left n2");
  CHECK_MSG(t->root->left->left == n1, "left left n1");
  CHECK_MSG(t->root->left->right == n3, "left right n3");
  CHECK_MSG(t->root->right->right == NULL, "right right null");

  bn_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}