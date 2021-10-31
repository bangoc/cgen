#ifndef TESTS_BNS_H_
#define TESTS_BNS_H_

#include "bns.h"

int lnr_match_g(bn_tree_t t, gtype *a, int n) {
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  int i = 0;
  bn_traverse_lnr(cur, t) {
    if (i >= n || cmp(a[i], cur) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_BNS_H_