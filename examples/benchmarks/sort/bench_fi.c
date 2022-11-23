#include "all.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  GC_INIT();
  if (argc != 2) {
    printf("Usage: ./prog input.txt\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  if (!f) {
    printf("Lỗi mở tệp!\n");
    return 1;
  }
  int n;
  fscanf(f, "%d", &n);
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(n, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(n);
#endif  // CGEN_USE_GC
  for (int i = 0; i < n; ++i) {
    fscanf(f, "%ld", &(gvec_elem(v, i).l));
  }
  BENCH(argv[0], 1,
    quicksort(gvec_size(v), gvec_arr(v), gtype_cmp_l);
  );
  fclose(f);
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}