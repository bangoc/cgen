/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Triển khai min heap và max heap
 */

#include "vec/heap.h"

// Định nghĩa chỉ sử dụng bên trong.
// nprop - nghịch đảo của tính chất heap.
//   <   - max heap
//   >   - min heap
#define mheap_shift_down(a, i, sz, nprop, cmp) \
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

#define mheap_make(a, sz, nprop, cmp) \
  for (long _i = (sz) / 2; _i >= 0; --_i) { \
    mheap_shift_down(a, _i, sz, nprop, cmp); \
  } \

void heap_shift_down_min(gtype *a, long i, const long sz, gtype_cmp_t cmp) {
  mheap_shift_down(a, i, sz, >, cmp);
}

void heap_shift_up_min(gtype *a, long i, gtype_cmp_t cmp) {
  heap_shift_up(a, i, >, cmp, gtype_swap);
}

void heap_make_min(const long sz, gtype *a, gtype_cmp_t cmp) {
  mheap_make(a, sz, >, cmp);
}

void heap_shift_down_max(gtype *a, long i, const long sz, gtype_cmp_t cmp) {
  mheap_shift_down(a, i, sz, <, cmp);
}

void heap_shift_up_max(gtype *a, long i, gtype_cmp_t cmp) {
  heap_shift_up(a, i, <, cmp, gtype_swap);
}

void heap_make_max(const long sz, gtype *a, gtype_cmp_t cmp) {
  mheap_make(a, sz, <, cmp);
}

void heap_shift_down(long i, long n, gtype *a, gtype_cmp_t cmp) {
  for (;;) {
    long lc = HLEFT(i), rc = HRIGHT(i), root = i;
    if (lc < n && cmp(a[root], a[lc]) < 0) {
      root = lc;
    }
    if (rc < n && cmp(a[root], a[rc]) < 0) {
      root = rc;
    }
    if (root == i) {
      break;
    }
    gtype_swap(a[i], a[root]);
    i = root;
  }
}

void heap_make(long n, gtype *a, gtype_cmp_t cmp) {
  for (long i = n / 2; i >= 0; --i) {
    heap_shift_down(i, n, a, cmp);
  }
}

#undef mheap_shift_down
#undef heap_shift_up
#undef mheap_make