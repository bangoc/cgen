#include "all.h"
#include "vec/b02_solve.h"
#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1() {
  struct gvector *v = gvec_create(0, NULL);
  long a[] = {1, 2, 3, 4, 5};
  gtype b[] = {gtype_l(5), gtype_l(4), gtype_l(3),
               gtype_l(2), gtype_l(1)};
  int n = sizeof(a)/sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    gvec_append(v, gtype_l(a[i]));
  }
  gvec_revert(v);
  CHECK_MSG(gvec_sequence(v, n, b, gtype_cmp_l),
      "Reverted sequence");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}