/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Triển khai các hàm vun đống
 */

#include "vec/heap.h"

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

void heap_shift_up(long i, gtype *a, gtype_cmp_t cmp) {
  long j = HTOP(i);
  while (i > 0 && cmp(a[j], a[i]) < 0) {
    gtype_swap(a[i], a[j]);
    i = j;
    j = HTOP(i);
  }
}

void heap_make(long n, gtype *a, gtype_cmp_t cmp) {
  for (long i = n / 2; i >= 0; --i) {
    heap_shift_down(i, n, a, cmp);
  }
}
