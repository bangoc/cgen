#include "all.h"

#include "tests/base/utils.h"

#include <stdlib.h>

int t1(int n) {
  struct gvector *v = gvec_create(n, NULL);
  for (int i = 0; i < n; ++i) {
    gvec_elem(v, i).l = rand();
  }
  q2m3sort(n, gvec_arr(v), gtype_cmp_l);
  for (int i = 0; i < n - 1; ++i) {
    CHECK_MSG(gtype_cmp_l(gvec_elem(v, i), gvec_elem(v, i + 1)) <= 0, "Increment sort");
  }
  gvec_free(v);
  return 0;
}

int t2(int n) {
  gtype *a = malloc(sizeof(gtype) * n);
  for (int i = 0; i < n; ++i) {
    a[i].l = i;
  }
  q2m3sort(n, a, gtype_cmp_l);
  for (int i = 0; i < n - 1; ++i) {
    CHECK_MSG(gtype_cmp_l(a[i], a[i + 1]) <= 0, "Increment sort");
  }
  free(a);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000\n");
    return 1;
  }
  int n;
  srand(time(NULL));
  sscanf(argv[1], "%d", &n);
  CHECK_MSG(t1(n) == 0, "t1");
  CHECK_MSG(t2(n) == 0, "t2");
  TEST_OK();
  return 0;
}