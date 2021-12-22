#ifndef TESTS_BASE_HELPERS_H_
#define TESTS_BASE_HELPERS_H_

#include "tests/bn/bn_helper.h"
#include "tests/rb/rb_helper.h"
#include "tests/rb/rbi_helper.h"

#include <string.h>

int gtype_seqi(gtype *g, int *a, int n) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != g[i].l) {
      return 0;
    }
  }
  return 1;
}

int gtype_seqs(gtype *g, char *a[], int n) {
  for (int i = 0; i < n; ++i) {
    if (strcmp(a[i], g[i].s) != 0) {
      return 0;
    }
  }
  return 1;
}

#endif  // TESTS_BASE_HELPERS_H_