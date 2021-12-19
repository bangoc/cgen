#ifndef TESTS_BNS_BNS_GTYPE_HELPER_H_
#define TESTS_BNS_BNS_GTYPE_HELPER_H_

#include "base/bns.h"

static int lnr_match_g(bn_tree_t t, gtype *a, int n) {
  bn_compare_t cmp = to_bns_tree_g(t)->cmp;
  int i = 0;
  bn_traverse_lnr(cur, t) {
    if (i >= n || bns_cmp_conv(a[i], cur) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_BNS_BNS_GTYPE_HELPER_H_