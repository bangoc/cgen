#include "all.h"

#include "tests/base/utils.h"

#include <stdlib.h>

int t1(int n) {
  struct gvector *v = gvec_rand_l(n);
  heapsort(n, gvec_arr(v), gtype_cmp_l);
  for (int i = 0; i < n - 1; ++i) {
    CHECK_MSG(gtype_cmp_l(gvec_elem(v, i), gvec_elem(v, i + 1)) <= 0, "Increment sort");
  }
  gvec_free(v);
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
  TEST_OK();
  return 0;
}