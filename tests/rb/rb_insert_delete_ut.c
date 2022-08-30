#include "tree/rb.h"
#include "tests/base/utils.h"

int node_values(bn_node_t nd,
    int key,
    rb_node_color_t color,
    bn_node_t left,
    bn_node_t right,
    bn_node_t top) {
  CHECK_MSG(nd, "Node not NULL");
  CHECK_MSG(bs_node(nd)->key.l == key, "Different key");
  CHECK_MSG(rb_node(nd)->color == color, "Different color");
  CHECK_MSG(nd->left == left, "Different left child");
  CHECK_MSG(nd->right == right, "Different right child");
  CHECK_MSG(nd->top == top, "Different top link");
  return 1;
}

int node_key(bn_node_t nd) {
  return bs_node(nd)->key.l;
}

int compare(bn_node_t x, bn_node_t y) {
  return node_key(x) - node_key(y);
}

int t1() {
  bn_tree_t t = bs_create_tree(NULL, gtype_cmp_l, NULL);
  rb_insert(t, gtype_l(1));
  CHECK_MSG(node_values(t->root, 1, RB_BLACK, NULL, NULL, NULL), "root values");

  rb_insert(t, gtype_l(2));
  CHECK_MSG(node_values(t->root, 1, RB_BLACK, NULL, t->root->right, NULL), "root values 1");
  CHECK_MSG(node_values(t->root->right, 2, RB_RED, NULL, NULL, t->root), "root right child");

  rb_insert(t, gtype_l(3));
  CHECK_MSG(node_values(t->root, 2, RB_BLACK, t->root->left, t->root->right, NULL), "root values 3");
  CHECK_MSG(node_values(t->root->left, 1, RB_RED, NULL, NULL, t->root), "root left child");
  CHECK_MSG(node_values(t->root->right, 3, RB_RED, NULL, NULL, t->root), "root right child");

  bs_free_tree(bs_tree(t));
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  return 0;
}
