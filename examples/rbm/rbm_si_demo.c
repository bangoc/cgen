/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "rbm.h"

int main() {
  rbm_t m = rbm_create(gtype_cmp_s, NULL, NULL);
  rbm_insert(m, gtype_s("Nguyen Van A"), gtype_i(1));
  rbm_insert(m, gtype_s("Tran Van D"), gtype_i(5));
  rbm_insert(m, gtype_s("Nguyen Van B"), gtype_i(3));
  rbm_insert(m, gtype_s("Nguyen Van C"), gtype_i(120));
  rbm_traverse(n, m) {
    printf("%s: %ld\n", n->key.s, n->value.i);
  }
  rbm_free(m);
  return 0;
}