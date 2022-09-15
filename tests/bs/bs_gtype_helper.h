#ifndef TESTS_BS_BS_GTYPE_HELPER_H_
#define TESTS_BS_BS_GTYPE_HELPER_H_

#include "tree/spec/gbs.h"

static int lnr_match_g(struct gbstree *t, gtype *a, int n) {
  int i = 0;
  bn_traverse_lnr(cur, bn_tree(t)) {
    if (i >= n || t->cmp(a[i], gbs_node(cur)->key) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_BS_BS_GTYPE_HELPER_H_