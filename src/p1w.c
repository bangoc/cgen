/*
  (C) Nguyen Ba Ngoc 2021
  Triển khai hàng đợi ưu tiên
*/

#include "p1w.h"

#include <stdlib.h>

#define p1w_swap(v1, v2) \
  do { \
    gtype tmp = v1; \
    v1 = v2; \
    v2 = tmp; \
  } while (0)

#define P1WP(i) (((i + 1) >> 1) - 1)
#define P1WL(i) (((i) << 1) + 1)
#define P1WR(i) (((i) << 1) + 2)

static void p1w_heapify(p1w_t h, long i) {
  long l = P1WL(i),
       r = P1WR(i),
       sz = p1w_size(h),
       largest = i;
  gtype *a = P1WARR(h);
  if (l < sz && h->cmp(a[l], a[i]) > 0) {
    largest = l;
  }
  if (r < sz && h->cmp(a[r], a[largest]) > 0) {
    largest = r;
  }
  if (largest != i) {
    p1w_swap(a[i], a[largest]);
    p1w_heapify(h, largest);
  }
}

static void p1w_make_heap(p1w_t h) {
  long sz = p1w_size(h);
  for (long i = sz / 2; i >= 0; --i) {
    p1w_heapify(h, i);
  }
}

p1w_t create_p1w(gtype_cmp_t cmp) {
  p1w_t h = malloc(sizeof(struct p1w_s));
  h->data = arr_create(0, gtype);
  h->cmp = cmp;
  return h;
}

p1w_t p1w_from_arr(arr_t(gtype) arr, gtype_cmp_t cmp) {
  p1w_t h = malloc(sizeof(struct p1w_s));
  h->data = arr;
  h->cmp = cmp;
  p1w_make_heap(h);
  return h;
}

p1w_t p1w_from_arr2(gtype* a, long n, gtype_cmp_t cmp) {
  arr_t(gtype) tmp = arr_create(n, gtype);
  arr_set_size(tmp, n);
  for (long i = 0; i < n; ++i) {
    ARR(tmp)[i] = *a++;
  }
  return p1w_from_arr(tmp, cmp);
}

gtype p1w_peek(p1w_t h) {
  return ARR(h->data)[0];
}

gtype p1w_dequeue(p1w_t h) {
  long sz = arr_size(h->data);
  gtype *a = ARR(h->data);
  p1w_swap(a[0], a[sz - 1]);
  arr_set_size(h->data, sz - 1);
  p1w_heapify(h, 0);
  return a[sz - 1];
}

int p1w_enqueue(p1w_t h, gtype value) {
  arr_append(h->data, value);
  long j = p1w_size(h) - 1;
  gtype *a = ARR(h->data);
  while (j > 0) {
    long i = P1WP(j);
    if (h->cmp(a[j], a[i]) <= 0) {
      break;
    }
    p1w_swap(a[j], a[i]);
    j = i;
  }
  return 0;
}

long p1w_size(p1w_t h) {
  return arr_size(h->data);
}
