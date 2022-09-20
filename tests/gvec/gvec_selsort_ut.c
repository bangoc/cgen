#include "all.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1() {
  struct gvector *v = gvec_create(0, NULL);
  gvec_append(v, gtype_l(1));
  gvec_append(v, gtype_l(-1));
  gvec_append(v, gtype_l(10));
  gvec_append(v, gtype_l(-20));
  gvec_append(v, gtype_l(9));
  gvec_selsort(v, gtype_cmp_l);
  CHECK_MSG(gvec_sequence(v, 5,
                          (gtype[]){gtype_l(-20), gtype_l(-1), gtype_l(1), gtype_l(9), gtype_l(10)},
                          gtype_cmp_l), "Gvec sequence 5");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}