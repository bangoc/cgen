/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main() {
  struct gvector *v = gvec_create(0, gtype_free_s);
  gvec_append(v, gtype_s(strdup("aaaaa")));
  gvec_append(v, gtype_s(strdup("bbbbb")));
  gvec_append(v, gtype_s(strdup("ccccc")));
  CHECK_MSG(gvec_size(v) == 3, "Vec size == 3");
  gvec_resize(v, 2);
  CHECK_MSG(gvec_size(v) == 2, "Vec size == 2");
  gvec_free(v);
  TEST_OK();
  return 0;
}