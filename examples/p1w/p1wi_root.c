/*
  (C) Nguyen Ba Ngoc 2021
  Minh họa sử dụng hàm cập nhật
*/
#include "cgen.h"
#include <stdio.h>

void print_p1wi(p1w_t q) {
  long sz = p1w_size(q);
  gtype *a = P1WARR(q);
  for (long i = 0; i < sz; ++i) {
    printf(" %ld", a[i].i);
  }
  printf("\n");
}

int main() {
  p1w_t q = p1w_create(PRIORITY_MAX, gtype_cmp_i);
  p1w_enqueue(q, gtype_i(3));
  p1w_enqueue(q, gtype_i(5));
  p1w_enqueue(q, gtype_i(9));
  p1w_enqueue(q, gtype_i(11));
  p1w_enqueue(q, gtype_i(8));
  print_p1wi(q);
  printf("Update Root = 20: ");
  p1w_root(q, gtype_i(20));
  print_p1wi(q);
  printf("Update Root = 6: ");
  p1w_root(q, gtype_i(6));
  print_p1wi(q);
  printf("Update Root = 1: ");
  p1w_root(q, gtype_i(1));
  print_p1wi(q);
  p1w_free(q);
  return 0;
}