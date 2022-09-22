#ifndef VEC_HEAP_H_
#define VEC_HEAP_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include "base/gtype.h"

#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)

void heap_shift_down_min(gtype *a, long i, const long sz, gtype_cmp_t cmp);
void heap_shift_up_min(gtype *a, long idx, gtype_cmp_t cmp);
void heap_make_min(const long sz, gtype *a, gtype_cmp_t cmp);

void heap_shift_down_max(gtype *a, long i, const long sz, gtype_cmp_t cmp);
void heap_shift_up_max(gtype *a, long idx, gtype_cmp_t cmp);
void heap_make_max(const long sz, gtype *a, gtype_cmp_t cmp);

void heap_shift_down(long i, long n, gtype *a, gtype_cmp_t cmp);
void heap_make(long n, gtype *a, gtype_cmp_t cmp);

#endif  // VEC_HEAP_H_