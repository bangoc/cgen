#include "all.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1() {
  struct gvector *v = gvec_create(0, NULL);
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
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}