#include "all.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1() {
#ifndef CGEN_USE_GC
  struct gvector *v = gvec_create(0, NULL);
#else  // CGEN_USE_GC
  struct gvector *v = gvec_create(0);
#endif  // CGEN_USE_GC
  gvec_append(v, gtype_d(1.2));
  gvec_append(v, gtype_d(2.1));
  gvec_append(v, gtype_d(3.3));
  gvec_append(v, gtype_d(3.5));
  gvec_append(v, gtype_d(2.2));
  gvec_append(v, gtype_d(-1.2));
  gvec_append(v, gtype_d(11.2));
  gvec_bubsort(v, gtype_cmp_d);
  CHECK_MSG(gvec_sequence(v, 7,
      (gtype[]){gtype_d(-1.2), gtype_d(1.2), gtype_d(2.1),
          gtype_d(2.2), gtype_d(3.3), gtype_d(3.5), gtype_d(11.2)},
          gtype_cmp_d), "Sequence 7");
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