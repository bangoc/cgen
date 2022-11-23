/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa sắp xếp mảng số nguyên với gvec
 */

#include "all.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  GC_INIT();
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  printf("Nhập các số không âm, hoặc nhập -1 để kết thúc: \n");
#ifndef CGEN_USE_GC
  struct gvector *vec = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *vec = gvec_create(0);
#endif  // CGEN_USE_GC
  int x;
  for (;;) {
    scanf("%d", &x);
    if (x < 0) {
      break;
    }
    gvec_append(vec, gtype_l(x));
  }
  printf("Bạn đã nhập %ld giá trị không âm\n", gvec_size(vec));
  gvec_qsort(vec, gtype_qsort_l);
  printf("Các giá trị theo thứ tự tăng dần: ");
  gvec_traverse(value, vec) {
    printf(" %ld", value->l);
  }
  printf("\n");
#ifndef CGEN_USE_GC
  gvec_free(vec);
#endif  // CGEN_USE_GC
  return 0;
}