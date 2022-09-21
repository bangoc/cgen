#ifndef ALGO_SORT_H_
#define ALGO_SORT_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "base/gtype.h"

void selsort(long n, gtype *a, gtype_cmp_t cmp);
void insort(long n, gtype *a, gtype_cmp_t cmp);
void bubsort(long n, gtype *a, gtype_cmp_t cmp);
void q2sort(long n, gtype *a, gtype_cmp_t cmp);
void q2m3sort(long n, gtype *a, gtype_cmp_t cmp);
void q3sort(long n, gtype *a, gtype_cmp_t cmp);
void quicksort(long n, gtype *a, gtype_cmp_t cmp);
#endif  // ALGO_SORT_H_