/* (C) Nguyen Ba Ngoc 2020 */

/**
 * Tính cf dựa trên danh sách các giá trị tf(t, d)
 */

#include "all.h"

#include <stdio.h>

struct term_freq {
  char term[100];
  int doc;
  int freq;
};

int main() {
  struct term_freq a[] = {
    {"aaa", 1, 10},
    {"bbb", 1, 15},
    {"ccc", 1, 5},
    {"aaa", 2, 15},
    {"ccc", 2, 5},
    {"eee", 2, 8},
    {"bbb", 3, 5},
    {"fff", 3, 2}
  };
  int n = sizeof(a)/sizeof(struct term_freq);
  struct rbmtree *cf = rbm_create(gtype_cmp_s, NULL, NULL);
  for (int i = 0; i < n; ++i) {
    gtype *tmp = rbm_put(cf, gtype_s(a[i].term), gtype_l(a[i].freq));
    if (tmp) {
      tmp->l += a[i].freq;
    }
  }
  rbm_traverse(k, v, cf) {
    printf("%s: %ld\n", k->s, v->l);
  }
  rbm_free(cf);
  return 0;
}