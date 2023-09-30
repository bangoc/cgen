/* (C) Nguyen Ba Ngoc 2021 */

#include "all.h"
#include "tests/base/utils.h"

int t1() {
  void *p1 = malloc(100);
  void *p2 = malloc(101);
  void *p3 = malloc(105);
  struct gvector *v = gvec_create(0, gtype_free_v);
  gvec_append(v, gtype_v(p1));
  gvec_append(v, gtype_v(p2));
  gvec_append(v, gtype_v(p3));
  CHECK_MSG(gvec_arr(v)[0].v == p1, "p1");
  CHECK_MSG(gvec_arr(v)[1].v == p2, "p2");
  CHECK_MSG(gvec_arr(v)[2].v == p3, "p3");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}