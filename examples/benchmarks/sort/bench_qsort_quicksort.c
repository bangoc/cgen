#include "all.h"

#include <stdio.h>
#include <stdlib.h>

void t1(int n) {
  printf("Kịch bản sinh số ngẫu nhiên.\n");
  struct gvector *v = gvec_create(n, NULL);
  gvec_traverse(cur, v) {
    cur->l = rand();
  }
  struct gvector *v1 = gvec_clone(v);
  struct gvector *v2 = gvec_clone(v);
  struct gvector *v3 = gvec_clone(v);
  BENCH("qsort (stdlib.h)", 1,
    gvec_qsort(v1, gtype_qsort_l);
  );
  BENCH("q2m3sort(tự cài dựa trên Sedgwick...)", 1,
    q2m3sort(gvec_size(v2), gvec_arr(v2), gtype_cmp_l);
  );
  BENCH("quicksort (tự cài theo glibc...)", 1,
    gvec_quicksort(v3, gtype_cmp_l);
  );
  if (!gvec_identical(v1, v2)) {
    printf("Kết quả khác nhau!!\n");
  }
  if (!gvec_identical(v1, v3)) {
    printf("Kết quả khác nhau!!\n");
  }
  gvec_free(v);
  gvec_free(v1);
  gvec_free(v2);
  gvec_free(v3);
}

void t2(int n) {
  printf("Kịch bản sinh số ngẫu nhiên nhiều trùng lặp.\n");
  int m = n / 3;
  struct gvector *v = gvec_create(n, NULL);
  gvec_traverse(cur, v) {
    cur->l = rand() % m;
  }
  struct gvector *v1 = gvec_clone(v);
  struct gvector *v2 = gvec_clone(v);
  struct gvector *v3 = gvec_clone(v);
  BENCH("qsort (stdlib.h)", 1,
    gvec_qsort(v1, gtype_qsort_l);
  );
  BENCH("q2m3sort(tự cài dựa trên Sedgwick...)", 1,
    q2m3sort(gvec_size(v2), gvec_arr(v2), gtype_cmp_l);
  );
  BENCH("quicksort (tự cài theo glibc...)", 1,
    gvec_quicksort(v3, gtype_cmp_l);
  );
  if (!gvec_identical(v1, v2)) {
    printf("Kết quả khác nhau!!\n");
  }
  if (!gvec_identical(v1, v3)) {
    printf("Kết quả khác nhau!!\n");
  }
  gvec_free(v);
  gvec_free(v1);
  gvec_free(v2);
  gvec_free(v3);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000\n");
    return 1;
  }
  int n;
  sscanf(argv[1], "%d", &n);
  srand(time(NULL));
  if (n < 10) {
    printf("n quá nhỏ, nên sử dụng n > 1000000 \n");
    return 1;
  }
  t1(n);
  t2(n);
  return 0;
}