#ifndef ALGO_SORT_H_
#define ALGO_SORT_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "base/gtype.h"

#define swap(a, b) \
  do { \
    gtype _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
  } while (0)

void selsort(long n, gtype *a, gtype_cmp_t cmp);
void insort(long n, gtype *a, gtype_cmp_t cmp);
void bubsort(long n, gtype *a, gtype_cmp_t cmp);
#endif  // ALGO_SORT_H_