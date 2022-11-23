/* (C) Nguyen Ba Ngoc 2021 */

#include "all.h"
#include "tests/base/utils.h"

int t1() {
  void *p1 = ext_malloc(100);
  void *p2 = ext_malloc(101);
  void *p3 = ext_malloc(105);
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  gvec_append(v, gtype_v(p1));
  gvec_append(v, gtype_v(p2));
  gvec_append(v, gtype_v(p3));
  CHECK_MSG(gvec_arr(v)[0].v == p1, "p1");
  CHECK_MSG(gvec_arr(v)[1].v == p2, "p2");
  CHECK_MSG(gvec_arr(v)[2].v == p3, "p3");
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}