#ifndef TESTS_GVEC_HELPER_H_
#define TESTS_GVEC_HELPER_H_

#include "all.h"

static inline int gvec_sequence(struct gvector *v,
    long n, gtype *a, gtype_cmp_t cmp) {
  if (!v) {
    return 0;
  }
  if (gvec_size(v) != n) {
    return 0;
  }
  int i = 0;
  gvec_traverse(cur, v) {
    if (cmp(*cur, a[i++])) {
      return 0;
    }
  }
  return 1;
}

#endif  // TESTS_GVEC_HELPER_H_