#include "all.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1() {
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  gvec_append(v, gtype_l(5));
  gvec_append(v, gtype_l(2));
  gvec_append(v, gtype_l(9));
  gvec_append(v, gtype_l(-1));
  gvec_append(v, gtype_l(10));
  gvec_append(v, gtype_l(6));
  gvec_insort(v, gtype_cmp_l);
  CHECK_MSG(gvec_sequence(v, 6,
         (gtype[]){gtype_l(-1), gtype_l(2), gtype_l(5), gtype_l(6),
                   gtype_l(9), gtype_l(10)}, gtype_cmp_l), "Sequence 6");
#ifndef CGEN_USE_GC
  gvec_free(v);
#endif  // CGEN_USE_GC
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}