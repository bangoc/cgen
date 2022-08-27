#include "base/rb.h"
#include "tests/base/utils.h"

typedef struct my_rb_node {
  struct rb_node_s rb_node;
  int key;
  int value;
} *my_rb_node_t;

#define to_myrb(n) ((my_rb_node_t)n)

int node_values(bn_node_t bn_node,
    int key,
    int value,
    rb_node_color_t color,
    bn_node_t left,
    bn_node_t right,
    bn_node_t top) {
  my_rb_node_t nd = to_myrb(bn_node);
  CHECK_MSG(nd, "Node NULL");
  CHECK_MSG(nd->key == key, "Different key");
  CHECK_MSG(nd->value == value, "Different value");
  CHECK_MSG(nd->rb_node.color == color, "Different color");
  CHECK_MSG(nd->rb_node.bn_node.left == left, "Different left child");
  CHECK_MSG(nd->rb_node.bn_node.right == right, "Different right child");
  CHECK_MSG(nd->rb_node.bn_node.top == top, "Different top child");
  return 0;
}

int node_key(bn_node_t bn_node) {
  my_rb_node_t nd = to_myrb(bn_node);
  return nd->key;
}

int compare(bn_node_t x, bn_node_t y) {
  return node_key(x) - node_key(y);
}

void my_rb_insert(bn_tree_t t, bn_node_t n) {
  bn_node_t same = NULL,
            par = NULL;
  bn_node_t *loc;
  bns_insert_setup(loc, t->root, n, compare, same, par);
  rb_insert(t, n, loc, par);
}

int t1() {
  bn_tree_t t = bn_create_tree(NULL);
  struct my_rb_node n1 = {{{NULL, NULL, NULL}, RB_RED}, 1, 1};
  my_rb_insert(t, bn_node(&n1));
  CHECK(node_values(t->root, 1, 1, RB_BLACK, NULL, NULL, NULL) == 0);

  struct my_rb_node n2 = {{{NULL, NULL, NULL}, RB_RED}, 2, 2};
  my_rb_insert(t, bn_node(&n2));
  CHECK(node_values(t->root, 1, 1, RB_BLACK, NULL, bn_node(&n2), NULL) == 0);
  CHECK(node_values(t->root->right, 2, 2, RB_RED, NULL, NULL, bn_node(&n1)) == 0);

  struct my_rb_node n3 = {{{NULL, NULL, NULL}, RB_RED}, 3, 3};
  my_rb_insert(t, bn_node(&n3));
  CHECK(node_values(t->root, 2, 2, RB_BLACK, bn_node(&n1), bn_node(&n3), NULL) == 0);
  CHECK(node_values(t->root->left, 1, 1, RB_RED, NULL, NULL, bn_node(&n2)) == 0);
  CHECK(node_values(t->root->right, 3, 3, RB_RED, NULL, NULL, bn_node(&n2)) == 0);

  rb_delete(t, bn_node(&n1));
  CHECK(node_values(t->root, 2, 2, RB_BLACK, NULL, bn_node(&n3), NULL) == 0);
  CHECK(node_values(t->root->right, 3, 3, RB_RED, NULL, NULL, bn_node(&n2)) == 0);

  rb_delete(t, bn_node(&n2));
  CHECK(node_values(t->root, 3, 3, RB_BLACK, NULL, NULL, NULL) == 0);

  rb_delete(t, bn_node(&n3));
  CHECK(t->root == NULL);
  return 0;
}

int main() {
  CHECK (t1() == 0);
  return 0;
}
