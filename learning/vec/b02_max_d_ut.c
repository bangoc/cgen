#include "all.h"
#include "vec/b02_solve.h"
#include "tests/base/utils.h"

int t1() {
  struct gvector *v = gvec_create(0, NULL);
  double a[] = {-1.0, 2.22, 9.001, 9.003, 8.5, 6.68};
  int n = sizeof(a)/sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    gvec_append(v, gtype_d(a[i]));
  }
  CHECK_MSG(gvec_max_d(v).d == 9.003, "Max 9.003");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}