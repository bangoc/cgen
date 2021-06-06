#include "rb.h"
#include "tests/base/utils.h"

typedef struct my_rb_node {
  struct rb_node rb_node;
  int key;
  int value;
} *my_rb_node_t;

int node_values(bn_node_t bn_node,
    int key,
    int value,
    rb_node_color_t color,
    bn_node_t left,
    bn_node_t right,
    bn_node_t top) {
  my_rb_node_t nd = container_of(container_of(bn_node, struct rb_node, bn_node),
          struct my_rb_node, rb_node);
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
  my_rb_node_t nd = container_of(container_of(bn_node, struct rb_node, bn_node),
          struct my_rb_node, rb_node);
  return nd->key;
}

int compare(bn_node_t x, bn_node_t y) {
  return node_key(x) - node_key(y);
}

#define my_rb_bn_node(n) rb_bn_node(((rb_node_t)&n.rb_node))

int t1() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  struct my_rb_node n1 = {{{NULL_PTR, NULL_PTR, NULL_PTR}, RB_BLACK}, 1, 1};
  rb_insert(t, my_rb_bn_node(n1), compare);
  CHECK(node_values(t->root, 1, 1, RB_BLACK, NULL_PTR, NULL_PTR, NULL_PTR) == 0);

  struct my_rb_node n2 = {{{NULL_PTR, NULL_PTR, NULL_PTR}, RB_BLACK}, 2, 2};
  rb_insert(t, my_rb_bn_node(n2), compare);
  CHECK(node_values(t->root, 1, 1, RB_BLACK, NULL_PTR, my_rb_bn_node(n2), NULL_PTR) == 0);
  CHECK(node_values(t->root->right, 2, 2, RB_RED, NULL_PTR, NULL_PTR, my_rb_bn_node(n1)) == 0);

  struct my_rb_node n3 = {{{NULL_PTR, NULL_PTR, NULL_PTR}, RB_BLACK}, 3, 3};
  rb_insert(t, my_rb_bn_node(n3), compare);
  CHECK(node_values(t->root, 2, 2, RB_BLACK, my_rb_bn_node(n1), my_rb_bn_node(n3), NULL_PTR) == 0);
  CHECK(node_values(t->root->left, 1, 1, RB_RED, NULL_PTR, NULL_PTR, my_rb_bn_node(n2)) == 0);
  CHECK(node_values(t->root->right, 3, 3, RB_RED, NULL_PTR, NULL_PTR, my_rb_bn_node(n2)) == 0);

  rb_delete(t, my_rb_bn_node(n1));
  CHECK(node_values(t->root, 2, 2, RB_BLACK, NULL_PTR, my_rb_bn_node(n3), NULL_PTR) == 0);
  CHECK(node_values(t->root->right, 3, 3, RB_RED, NULL_PTR, NULL_PTR, my_rb_bn_node(n2)) == 0);

  rb_delete(t, my_rb_bn_node(n2));
  CHECK(node_values(t->root, 3, 3, RB_BLACK, NULL_PTR, NULL_PTR, NULL_PTR) == 0);

  rb_delete(t, my_rb_bn_node(n3));
  CHECK(t->root == NULL_PTR);
  return 0;
}

int main() {
  CHECK (t1() == 0);
  return 0;
}