/*
  (C) Nguyen Ba Ngoc 2021
  Triển khai hàng đợi ưu tiên
*/

#include "heap.h"
#include "p1w.h"

#include <stdlib.h>

p1w_t create_p1w(gtype_cmp_t cmp) {
  p1w_t h = malloc(sizeof(struct p1w_s));
  h->data = arr_create(0, gtype);
  h->cmp = cmp;
  return h;
}

gtype p1w_peek(p1w_t h) {
  return ARR(h->data)[0];
}

gtype p1w_dequeue(p1w_t h) {
  long sz = arr_size(h->data);
  gtype *a = P1WARR(h);
  gtype_swap(a[0], a[sz - 1]);
  arr_set_size(h->data, sz - 1);
  heapify_g(a, 0, sz - 1, h->cmp);
  return a[sz - 1];
}

int p1w_enqueue(p1w_t h, gtype value) {
  arr_append(h->data, value);
  long j = p1w_size(h) - 1;
  gtype *a = P1WARR(h);
  while (j > 0) {
    long i = HTOP(j);
    if (h->cmp(a[j], a[i]) <= 0) {
      break;
    }
    gtype_swap(a[j], a[i]);
    j = i;
  }
  return 0;
}

long p1w_size(p1w_t h) {
  return arr_size(h->data);
}
