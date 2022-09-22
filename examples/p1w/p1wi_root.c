/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa sử dụng hàm cập nhật
 */
#include "all.h"
#include <stdio.h>

void print_p1wi(struct p1way *q) {
  long sz = p1w_size(q);
  gtype *a = p1w_arr(q);
  for (long i = 0; i < sz; ++i) {
    printf(" %ld", a[i].l);
  }
  printf("\n");
}

int main() {
  struct p1way *q = p1w_create(gtype_cmp_l);
  p1w_enqueue(q, gtype_l(3));
  p1w_enqueue(q, gtype_l(5));
  p1w_enqueue(q, gtype_l(9));
  p1w_enqueue(q, gtype_l(11));
  p1w_enqueue(q, gtype_l(8));
  print_p1wi(q);
  printf("Update Root = 20: ");
  p1w_root(q, gtype_l(20));
  print_p1wi(q);
  printf("Update Root = 6: ");
  p1w_root(q, gtype_l(6));
  print_p1wi(q);
  printf("Update Root = 1: ");
  p1w_root(q, gtype_l(1));
  print_p1wi(q);
  p1w_free(q);
  return 0;
}