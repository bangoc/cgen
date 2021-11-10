#ifndef TESTS_RBS
#define TESTS_RBS

#include "rbs.h"

static int rbs_traverse_match(rbs_t s, gtype *a, int n) {
  bn_compare_t cmp = s->cmp;
  int i = 0;
  rbs_traverse(cur, s) {
    if (i >= n || cmp(a[i], cur->value) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_RBS