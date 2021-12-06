#ifndef HEAP_H_
#define HEAP_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gtype.h"

#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)

void min_shift_down_g(gtype *a, long i, const long sz, gtype_cmp_t cmp);
void min_shift_up_g(gtype *a, long idx, gtype_cmp_t cmp);
void min_heap_g(gtype *a, const long sz, gtype_cmp_t cmp);

void max_shift_down_g(gtype *a, long i, const long sz, gtype_cmp_t cmp);
void max_shift_up_g(gtype *a, long idx, gtype_cmp_t cmp);
void max_heap_g(gtype *a, const long sz, gtype_cmp_t cmp);

#endif  // HEAP_H_