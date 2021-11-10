#include "s2i.h"

void s2i_custom_node_print(bn_node_t n) {
  printf("%s:%s\n", to_s2i(n)->key, rb_color_str(n));
}

int main() {
  s2i_t si = s2i_create();
  s2i_insert(si, "Một", 1);
  s2i_insert(si, "Hai", 2);
  s2i_insert(si, "Ba", 3);
  s2i_insert(si, "Bốn", 4);
  s2i_insert(si, "Năm", 5);
  s2i_insert(si, "Sáu", 6);
  s2i_insert(si, "Bẩy", 7);
  s2i_insert(si, "Tám", 8);
  s2i_insert(si, "Chín", 9);
  s2i_insert(si, "Mười", 10);
  bn_pprint(si, s2i_custom_node_print);
  s2i_free(si);
  return 0;
}