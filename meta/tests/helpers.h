#ifndef TESTS_UT_HELPERS_H_
#define TESTS_UT_HELPERS_H_

#include "all.h"

#include <string.h>

int GSTReqi(gtype *g, int *a, int n) {
  for (int i = 0; i < n; ++i) {
    if (a[i] != g[i].l) {
      return 0;
    }
  }
  return 1;
}

int GSTReqs(gtype *g, char *a[], int n) {
  for (int i = 0; i < n; ++i) {
    if (strcmp(a[i], g[i].s) != 0) {
      return 0;
    }
  }
  return 1;
}

static long rb_is_valid_black_height = -1;
static int rb_is_valid_internal_stop = 0;

#define END_INTERNAL() rb_is_valid_internal_stop = 1; \
  return 0

static int rb_is_valid_internal(struct tnode *n, long blacks) {
  if (rb_is_valid_internal_stop) {
    return 0;
  }
  if (n == NULL) {
    if (rb_is_valid_black_height < 0) {
      rb_is_valid_black_height = blacks;
      return 1;  // Ok
    } else if (rb_is_valid_black_height != blacks) {
      printf("Tính chất 5.\n");
      END_INTERNAL();
    }
    return 1;  // Ok
  }
  if (tis_red(n)) {
    if (tis_red(tleft_of(n)) || tis_red(tright_of(n))) {
      printf("Tính chất 4.\n");
      END_INTERNAL();
    }
    return rb_is_valid_internal(tleft_of(n), blacks) &&
        rb_is_valid_internal(tright_of(n), blacks);
  } else if (tis_black(n)) {
    return rb_is_valid_internal(tleft_of(n), blacks + 1) &&
        rb_is_valid_internal(tright_of(n), blacks + 1);
  }
  printf("Tính chất 1.\n");
  END_INTERNAL();
}

static int rb_is_valid(struct tmap *t) {
  if (troot(t) == NULL) {
    return 1;
  }
  if (tis_red(troot(t))) {
    printf("Tính chất 2.\n");
    return 0;
  }
  rb_is_valid_black_height = -1;
  rb_is_valid_internal_stop = 0;
  return rb_is_valid_internal(troot(t), 0);
}

#endif  // TESTS_UT_HELPERS_H_