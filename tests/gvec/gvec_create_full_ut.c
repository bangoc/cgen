/* (C) Nguyễn Bá Ngọc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create_full(3, 5, gtype_l(101), NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create_full(3, 5, gtype_l(101));
#endif  // CGEN_USE_GC
  CHECK_MSG(gvec_size(v) == 3, "size 3");
  CHECK_MSG(gvec_capacity(v) == 5, "capacity 5");
  gvec_traverse(cur, v) {
    CHECK_MSG(cur->l == 101, "value 101");
  }
#ifndef CGEN_USE_GC
  gvec_free(v);
  CHECK_MSG(gvec_create_full(5, 3, gtype_zero, NULL) == NULL, "size must <= cap");
#else  // CGEN_USE_GC
  CHECK_MSG(gvec_create_full(5, 3, gtype_zero) == NULL, "size must <= cap");
#endif  // CGEN_USE_GC
  TEST_OK();
  return 0;
}