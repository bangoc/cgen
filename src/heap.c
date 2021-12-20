/*
  (C) Nguyen Ba Ngoc 2021
  Triển khai min heap và max heap
*/

#include "base/heap.h"

// Định nghĩa chỉ sử dụng bên trong.
// nprop - nghịch đảo của tính chất heap.
//   <   - max heap
//   >   - min heap
#define heap_shift_down(a, i, sz, nprop, cmp) \
  for (;;) { \
    long l = HLEFT(i), r = HRIGHT(i), root = i; \
    if (l < sz && cmp(a[root], a[l]) nprop 0) { \
      root = l; \
    } \
    if (r < sz && cmp(a[root], a[r]) nprop 0) { \
      root = r; \
    } \
    if (root == i) { \
      break; \
    } \
    gtype_swap(a[i], a[root]); \
    i = root; \
  }

#define heap_shift_up(a, i, nprop, cmp, swap) \
  while (i > 0) { \
    long j = HTOP(i); \
    if (cmp(a[j], a[i]) nprop 0) { \
      swap(a[i], a[j]); \
      i = j; \
    } else {\
      break; \
    }\
  }

#define heap_make(a, sz, nprop, cmp) \
  for (long i = sz / 2; i >= 0; --i) { \
    heap_shift_down(a, i, sz, nprop, cmp); \
  } \

void min_shift_down_g(gtype *a, long i, const long sz, gtype_cmp_t cmp) {
  heap_shift_down(a, i, sz, >, cmp);
}

void min_shift_up_g(gtype *a, long i, gtype_cmp_t cmp) {
  heap_shift_up(a, i, >, cmp, gtype_swap);
}

void min_heap_g(gtype *a, const long sz, gtype_cmp_t cmp) {
  heap_make(a, sz, >, cmp);
}

void max_shift_down_g(gtype *a, long i, const long sz, gtype_cmp_t cmp) {
  heap_shift_down(a, i, sz, <, cmp);
}

void max_shift_up_g(gtype *a, long i, gtype_cmp_t cmp) {
  heap_shift_up(a, i, <, cmp, gtype_swap);
}

void max_heap_g(gtype *a, const long sz, gtype_cmp_t cmp) {
  heap_make(a, sz, <, cmp);
}

#undef heap_shift_down
#undef heap_shift_up
#undef heap_make