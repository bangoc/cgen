/*
  (C) Nguyen Ba Ngoc 2021
  Triển khai hàng đợi ưu tiên
*/

#include "base/heap.h"
#include "p1w.h"

#include <stdlib.h>

p1w_t p1w_create(p1w_types typ, gtype_cmp_t cmp) {
  p1w_t h = malloc(sizeof(struct priority_one_way));
  h->data = arr_create(0, gtype);
  h->typ = typ;
  h->cmp = cmp;
  return h;
}

gtype p1w_peek(p1w_t h) {
  return ARR(h->data)[0];
}

gtype p1w_dequeue(p1w_t h) {
  long sz = arr_size(h->data);
  gtype *a = P1WARR(h);
  gtype tmp = a[0];
  gtype_swap(a[0], a[sz - 1]);
  arr_set_size(h->data, sz - 1);
  switch (h->typ) {
    case PRIORITY_MIN: min_shift_down_g(a, 0, sz - 1, h->cmp);
      break;
    case PRIORITY_MAX: max_shift_down_g(a, 0, sz - 1, h->cmp);
      break;
    default:
      fprintf(stderr, "Không xác định được kiểu heap (mặc định là max)");
      max_shift_down_g(a, 0, sz - 1, h->cmp);
      break;
  }
  return tmp;
}

int p1w_enqueue(p1w_t h, gtype value) {
  arr_append(h->data, value);
  long j = p1w_size(h) - 1;
  gtype *a = P1WARR(h);
  switch (h->typ) {
    case PRIORITY_MIN: min_shift_up_g(a, j, h->cmp);
      break;
    case PRIORITY_MAX: max_shift_up_g(a, j, h->cmp);
      break;
    default:
      fprintf(stderr, "Không xác định được kiểu heap (mặc định là max)");
      max_shift_up_g(a, j, h->cmp);
      break;
  }
  return 0;
}

long p1w_size(p1w_t h) {
  return arr_size(h->data);
}

void p1w_root(p1w_t h, gtype value) {
  long sz = p1w_size(h);
  gtype *a = P1WARR(h);
  int order = h->cmp(a[0], value);
  a[0] = value;
  if (order <= 0) {
    return;
  }
  switch (h->typ) {
    case PRIORITY_MIN: min_shift_down_g(a, 0, sz, h->cmp);
      break;
    case PRIORITY_MAX: max_shift_down_g(a, 0, sz, h->cmp);
      break;
    default:
      fprintf(stderr, "Không xác định được kiểu heap (mặc định là max)");
      max_shift_down_g(a, 0, sz, h->cmp);
      break;
  }
}