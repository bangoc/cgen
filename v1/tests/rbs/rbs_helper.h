#ifndef TESTS_RBS_RBS_HELPER_H_
#define TESTS_RBS_RBS_HELPER_H_

#include "tree/rbs.h"

static int rbs_traverse_match(struct rbstree *s, gtype *a, int n) {
  int i = 0;
  rbs_traverse(cur, s) {
    if (i >= n || grb_tree(s)->cmp(a[i], *cur) != 0) {
      return 0;
    }
    ++i;
  }
  return i == n;
}

#endif  // TESTS_RBS_RBS_HELPER_H_