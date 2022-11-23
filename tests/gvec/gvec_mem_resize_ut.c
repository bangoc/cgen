/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main(int argc, char *argv[]) {
  GC_INIT();
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, gtype_free_s);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  gvec_append(v, gtype_s(ext_strdup("aaaaa")));
  gvec_append(v, gtype_s(ext_strdup("bbbbb")));
  gvec_append(v, gtype_s(ext_strdup("ccccc")));
  CHECK_MSG(gvec_size(v) == 3, "Vec size == 3");
  gvec_resize(v, 2);
  CHECK_MSG(gvec_size(v) == 2, "Vec size == 2");
#ifndef  CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  TEST_OK();
  return 0;
}