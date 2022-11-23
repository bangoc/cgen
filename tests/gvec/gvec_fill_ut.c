/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main(int argc, char *argv[]) {
  GC_INIT();
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(10, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(10);
#endif  // CGEN_USE_GC
  gvec_fill(v, gtype_l(100));
  gvec_traverse(cur, v) {
    CHECK_MSG(cur->l == 100, "Fill 100");
  }
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  TEST_OK();
  return 0;
}