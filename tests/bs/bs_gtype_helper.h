#ifndef TESTS_BS_BS_GTYPE_HELPER_H_
#define TESTS_BS_BS_GTYPE_HELPER_H_

#include "base/bs.h"

static int lnr_match_g(bs_tree_t t, gtype *a, int n) {
  int i = 0;
  bn_traverse_lnr(cur, bn_tree(t)) {
    if (i >= n || t->cmp(a[i], bs_node(cur)->key) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_BS_BS_GTYPE_HELPER_H_