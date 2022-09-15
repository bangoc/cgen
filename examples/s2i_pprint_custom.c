#include "all.h"

void s2i_custom_node_print(struct bnnode *n) {
  printf("%s:%ld:%s\n", rbm_node_key(n).s,
         rbm_node_value(n).l, rb_color_str(n));
}

int main() {
  struct rbmtree *si = s2i_create();
  s2i_put(si, "Một", 1);
  s2i_put(si, "Hai", 2);
  s2i_put(si, "Ba", 3);
  s2i_put(si, "Bốn", 4);
  s2i_put(si, "Năm", 5);
  s2i_put(si, "Sáu", 6);
  s2i_put(si, "Bẩy", 7);
  s2i_put(si, "Tám", 8);
  s2i_put(si, "Chín", 9);
  s2i_put(si, "Mười", 10);
  bn_pprint((struct bntree *)si, s2i_custom_node_print);
  s2i_free(si);
  return 0;
}