#ifndef TESTS_GSL_HELPER_H_
#define TESTS_GSL_HELPER_H_

#include "list/gsl.h"

int gsl_sequence_g(struct gsllist *list, gtype *a, int n, gtype_cmp_t cmp) {
  if (gsl_length(list) != n) {
    return 0;
  }
  struct gslnode *node = gsl_front(list);
  for (int i = 0; i < n; ++i) {
    if (cmp(a[i], node->value)) {
      return 0;
    }
    node = gsl_node_next(node);
  }
  return 1;
}

#endif  // TESTS_GSL_HELPER_H_