#include "tests/base/utils.h"
#include "base/bns.h"

bn_tree_t bn_transplant(bn_tree_t t, bn_node_t u, bn_node_t v) {
  if (u->top == NULL_PTR) {
    t->root = v;
  } else if (u == u->top->left) {
    u->top->left = v;
  } else {
    u->top->right = v;
  }
  if (v != NULL_PTR) {
    v->top = u->top;
  }
  return t;
}

int t1() {
  bn_node_t n1 = bn_create_node();
  bn_node_t n2 = bn_create_node();
  bn_node_t n3 = bn_create_node();
  bn_node_t n4 = bn_create_node();
  bn_node_t n5 = bn_create_node();
  bn_connect2(n3, left, n2, top);
  bn_connect2(n3, right, n4, top);
  bn_connect2(n2, left, n1, top);
  bn_connect2(n4, right, n5, top);
  bn_tree_t t= bn_create_tree(n3);
  /*
        n3
      n2  n4
    n1      n5
  */
  bn_transplant(t, n2, n1);
  CHECK_MSG(t->root == n3, "Failed root");
  CHECK_MSG(t->root->left == n1, "Failed root left");
  CHECK_MSG(t->root->right == n4, "Failed root right");
  bn_free_node(n2);

  bn_transplant(t, n4, n5);
  CHECK_MSG(t->root->right == n5, "Failed root right n5");
  bn_free_node(n4);
  bn_free_tree(t);
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}