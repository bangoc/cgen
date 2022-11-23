/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa hàm làm rỗng vec-tơ.
 */

#include "all.h"

#include <stdio.h>

void print_gvec(struct gvector *v) {
  printf("size = %ld   capacity = %ld\n", gvec_size(v), gvec_capacity(v));
  gvec_traverse(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  GC_INIT();
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 1) {
      gvec_append(v, gtype_l(i));
    }
  }
  printf("Trạng thái sau khi thêm các số lẻ trong khoảng 0..9: \n");
  print_gvec(v);
  gvec_clear(v);
  printf("Trạng thái sau khi làm rỗng: \n");
  print_gvec(v);
  for (int i = 0; i < 20; ++i) {
    if (i % 2 == 0) {
      gvec_append(v, gtype_l(i));
    }
  }
  printf("Trạng thái sau khi thêm các số chẵn trong khoảng 0..19: \n");
  print_gvec(v);
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}