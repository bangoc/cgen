#include "all.h"
#include "vec/b02_solve.h"
#include "tests/base/utils.h"

int t1() {
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(5, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(5);
#endif  // CGEN_USE_GC
  gvec_elem(v, 0).l = 1;
  gvec_elem(v, 1).l = 3;
  gvec_elem(v, 2).l = 10;
  gvec_elem(v, 3).l = -1;
  gvec_elem(v, 4).l = -101;
  CHECK_MSG(gvec_min_l(v).l == -101, "Min -101");
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}