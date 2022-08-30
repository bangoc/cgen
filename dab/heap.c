/*
  (C) Nguyen Ba Ngoc 2021
  Triển khai min heap và max heap
*/

#include "dab/heap.h"

// Định nghĩa chỉ sử dụng bên trong.
// nprop - nghịch đảo của tính chất heap.
//   <   - max heap
//   >   - min heap
#define heap_shift_down(a, i, sz, nprop, cmp) \
  for (;;) { \
    long _lc = HLEFT(i), _rc = HRIGHT(i), _root = (i); \
    if (_lc < (sz) && cmp((a)[_root], (a)[_lc]) nprop 0) { \
      _root = _lc; \
    } \
    if (_rc < sz && cmp((a)[_root], (a)[_rc]) nprop 0) { \
      _root = _rc; \
    } \
    if (_root == (i)) { \
      break; \
    } \
    gtype_swap((a)[(i)], (a)[_root]); \
    (i) = _root; \
  }

#define heap_shift_up(a, i, nprop, cmp, swap) \
  while ((i) > 0) { \
    long _j = HTOP(i); \
    if (cmp((a)[_j], (a)[(i)]) nprop 0) { \
      swap((a)[(i)], (a)[_j]); \
      (i) = _j; \
    } else {\
      break; \
    }\
  }

#define heap_make(a, sz, nprop, cmp) \
  for (long _i = (sz) / 2; _i >= 0; --_i) { \
    heap_shift_down(a, _i, sz, nprop, cmp); \
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