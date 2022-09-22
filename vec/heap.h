#ifndef VEC_HEAP_H_
#define VEC_HEAP_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include "base/gtype.h"

#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)

void heap_shift_down(long i, long n, gtype *a, gtype_cmp_t cmp);
void heap_shift_up(long i, gtype *a, gtype_cmp_t cmp);

/**
 * Sử dụng hàm so sánh thuận cho kết quả là đống cực đại,
 * Sử dụng hàm so sánh nghịch cho kết quả là đống cực tiểu.
 */
void heap_make(long n, gtype *a, gtype_cmp_t cmp);

#endif  // VEC_HEAP_H_