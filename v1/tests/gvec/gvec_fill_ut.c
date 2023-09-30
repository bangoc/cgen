/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main() {
  struct gvector *v = gvec_create(10, NULL);
  gvec_fill(v, gtype_l(100));
  gvec_traverse(cur, v) {
    CHECK_MSG(cur->l == 100, "Fill 100");
  }
  gvec_free(v);
  TEST_OK();
  return 0;
}