#include "s2i.h"

void s2i_custom_node_print(bn_node_t n) {
  printf("%s:%s\n", to_s2i(n)->key, rb_color_str(n));
}

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
  bn_pprint(t, s2i_custom_node_print);
  s2i_free(&t);
  return 0;
}