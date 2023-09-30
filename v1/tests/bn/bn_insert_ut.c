#include "tests/base/utils.h"

#include "tree/bn.h"

int t1() {
  struct bnnode *n1 = bn_create_node();
  struct bnnode *n2 = bn_create_node();
  struct bnnode *n3 = bn_create_node();
  struct bnnode *n4 = bn_create_node();
  struct bnnode *n5 = bn_create_node();
  /*
         n3
    n1       n5
      n2   n4
  */
  struct bntree *t = bn_create_tree(NULL);
  bn_insert(n3, (&(t->root)), NULL);
  bn_insert(n1, (&(n3->left)), n3);
  bn_insert(n2, (&(n1->right)), n1);
  bn_insert(n5, (&(n3->right)), n3);
  bn_insert(n4, (&(n5->left)), n5);

  CHECK_MSG(t->root == n3, "root n3");
  CHECK_MSG(t->root->left == n1, "root left n1");
  CHECK_MSG(t->root->right == n5, "root right n5");
  CHECK_MSG(t->root->left->right == n2, "root left right n2");
  CHECK_MSG(t->root->right->left == n4, "root right left n4");
  bn_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}