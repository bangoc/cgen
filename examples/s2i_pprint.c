#include "s2i.h"

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  s2i_insert(t, "Một", 1);
  s2i_insert(t, "Hai", 2);
  s2i_insert(t, "Ba", 3);
  s2i_insert(t, "Bốn", 4);
  s2i_insert(t, "Năm", 5);
  s2i_insert(t, "Sáu", 6);
  s2i_insert(t, "Bẩy", 7);
  s2i_insert(t, "Tám", 8);
  s2i_insert(t, "Chín", 9);
  s2i_insert(t, "Mười", 10);
  bn_pprint(t->root, s2i_node_print, 0, 3);
  s2i_free(&t);
  return 0;
}