#include "all.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
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
  struct gvector *v = gvec_create(n, NULL);
  for (int i = 0; i < n; ++i) {
    fscanf(f, "%ld", &(gvec_elem(v, i).l));
  }
  BENCH(argv[0], 1,
    quicksort(gvec_size(v), gvec_arr(v), gtype_cmp_l);
  );
  fclose(f);
  gvec_free(v);
  return 0;
}