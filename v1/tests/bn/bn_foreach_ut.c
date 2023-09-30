#include "tree/bn.h"

#include "tests/base/utils.h"

struct bnnode *nodes[5];
int idx;
int my_callback(struct bnnode *n, void *u) {
  if (n != nodes[idx]) {
    return 1;
  }
  ++idx;
  return 0;
}

int main() {
  struct bnnode *n1 = bn_create_node();
  struct bnnode *n2 = bn_create_node();
  struct bnnode *n3 = bn_create_node();
  struct bnnode *n4 = bn_create_node();
  struct bnnode *n5 = bn_create_node();
  n3->left = n2;
  n2->top = n3;
  n3->right = n5;
  n5->top = n3;
  n2->left = n1;
  n1->top = n2;
  n5->left = n4;
  n4->top = n5;
  struct bntree *t = bn_create_tree(n3);
  /*
        3
      2    5
    1    4
  */
  nodes[0] = n1;
  nodes[1] = n2;
  nodes[2] = n4;
  nodes[3] = n5;
  nodes[4] = n3;
  idx = 0;
  bn_foreach_lrn(t, my_callback, NULL);
  CHECK_MSG(idx == 5, "Wrong index");
  idx = 0;
  bn_traverse_lrn(cur, t) {
    CHECK_MSG(cur == nodes[idx], "Failed inline");
    ++idx;
  }
  bn_free_tree(t);
  return 0;
}