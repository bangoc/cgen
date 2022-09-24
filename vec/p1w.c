/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Triển khai hàng đợi ưu tiên
 */

#include "vec/heap.h"
#include "vec/p1w.h"

#include <stdlib.h>

struct p1way *p1w_create(gtype_cmp_t cmp) {
  struct p1way *h = malloc(sizeof(struct p1way));
  h->elems = arr_create(0, gtype);
  h->cmp = cmp;
  return h;
}

gtype p1w_peek(struct p1way *h) {
  return p1w_arr(h)[0];
}

gtype p1w_dequeue(struct p1way *h) {
  long sz = p1w_size(h);
  gtype *a = p1w_arr(h);
  gtype tmp = a[0];
  gtype_swap(a[0], a[sz - 1]);
  arr_resize(h->elems, sz - 1);
  heap_shift_down(0, sz - 1, a, h->cmp);
  return tmp;
}

void p1w_enqueue(struct p1way *h, gtype value) {
  arr_append(h->elems, value);
  long j = p1w_size(h) - 1;
  gtype *a = p1w_arr(h);
  heap_shift_up(j, a, h->cmp);
}

void p1w_root(struct p1way *h, gtype value) {
  long sz = p1w_size(h);
  gtype *a = p1w_arr(h);
  a[0] = value;
  heap_shift_down(0, sz, a, h->cmp);
}

void gtype_free_p1w(gtype value) {
  p1w_free(value.p1w);
}