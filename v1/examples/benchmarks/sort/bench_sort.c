#include "all.h"

#include <stdio.h>
#include <stdlib.h>

void run(struct gvector *v) {
  struct gvector *v1 = gvec_clone(v);
  struct gvector *v2 = gvec_clone(v);
  struct gvector *v3 = gvec_clone(v);
  struct gvector *v4 = gvec_clone(v);
  struct gvector *v5 = gvec_clone(v);
  BENCH("qsort (stdlib.h)", 1,
    gvec_qsort(v1, gtype_qsort_l);
  );
  BENCH("q2m3sort(tự cài dựa trên Sedgwick...)", 1,
    q2m3sort(gvec_size(v2), gvec_arr(v2), gtype_cmp_l);
  );
  BENCH("qinsort(Kết hợp q2m3 với ins...)", 1,
    qinsort(gvec_size(v3), gvec_arr(v3), gtype_cmp_l);
  );
  BENCH("quicksort (tự cài theo glibc...)", 1,
    gvec_quicksort(v4, gtype_cmp_l);
  );
  BENCH("Heapsort", 1,
    heapsort(gvec_size(v5), gvec_arr(v5), gtype_cmp_l);
  );
  if (!gvec_identical(v1, v2)) {
    printf("Kết quả v1 và v2 khác nhau!!\n");
  }
  if (!gvec_identical(v1, v3)) {
    printf("Kết quả v1 và v3 khác nhau!!\n");
  }
  if (!gvec_identical(v1, v4)) {
    printf("Kết quả v1 và v4 khác nhau!!\n");
  }
  if (!gvec_identical(v1, v5)) {
    printf("Kết quả v1 và v5 khác nhau!!\n");
  }
  gvec_free(v1);
  gvec_free(v2);
  gvec_free(v3);
  gvec_free(v4);
  gvec_free(v5);
}

void t1(int n) {
  printf("Kịch bản sinh số ngẫu nhiên.\n");
  struct gvector *v = gvec_create(n, NULL);
  gvec_traverse(cur, v) {
    cur->l = rand();
  }
  run(v);
  gvec_free(v);
}

void t2(int n) {
  printf("Kịch bản sinh số ngẫu nhiên nhiều trùng lặp.\n");
  int m = n / 3;
  struct gvector *v = gvec_create(n, NULL);
  gvec_traverse(cur, v) {
    cur->l = rand() % m;
  }
  run(v);
  gvec_free(v);
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