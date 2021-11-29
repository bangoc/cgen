#ifndef HEAP_H_
#define HEAP_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gtype.h"

#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)

static void heapify_g(gtype *a, long i, const long sz, gtype_cmp_t cmp) {
  for (;;) {
    long l = HLEFT(i),
         r = HRIGHT(i),
         largest = i;
    if (l < sz && cmp(a[l], a[i]) > 0) {
      largest = l;
    }
    if (r < sz && cmp(a[r], a[largest]) > 0) {
      largest = r;
    }
    if (largest == i) {
      break;
    }
    gtype_swap(a[i], a[largest]);
    i = largest;
  }
}

static void make_heap_g(gtype *a, const long sz, gtype_cmp_t cmp) {
  for (long i = sz / 2; i >= 0; --i) {
    heapify_g(a, i, sz, cmp);
  }
}

#endif  // HEAP_H_