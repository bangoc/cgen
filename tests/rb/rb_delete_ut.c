#include "rbi.h"
#include "tests/base/utils.h"

int test_delete_root() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_node_t root = rbi_create_node(5);
  t->root = &(root->rb_node.bn_node);
  rbi_node_t lc = rbi_create_node(3);
  rb_node_init((&lc->rb_node), NULL_PTR, NULL_PTR, root, RB_RED);
  rbi_node_t rc = rbi_create_node(8);
  rb_node_init((&rc->rb_node), NULL_PTR, NULL_PTR, root, RB_RED);
  /*
  */
  return 1;
}

int main() {
  return 0;
}