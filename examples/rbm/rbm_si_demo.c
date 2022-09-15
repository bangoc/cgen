/* (C) Nguyen Ba Ngoc 2021 */

#include "all.h"

int main() {
  struct rbmtree *m = rbm_create(gtype_cmp_s, NULL, NULL);
  rbm_insert(m, gtype_s("Nguyen Van A"), gtype_l(1));
  rbm_insert(m, gtype_s("Tran Van D"), gtype_l(5));
  rbm_insert(m, gtype_s("Nguyen Van B"), gtype_l(3));
  rbm_insert(m, gtype_s("Nguyen Van C"), gtype_l(120));
  rbm_traverse(k, v, m) {
    printf("%s: %ld\n", k->s, v->l);
  }
  rbm_free(m);
  return 0;
}