/* (C) Nguyễn Bá Ngọc 2022 */

#include "all.h"

#include "tests/base/utils.h"

int main() {
  struct gvector *v = gvec_create_full(3, 5, gtype_l(101), NULL);
  CHECK_MSG(gvec_size(v) == 3, "size 3");
  CHECK_MSG(gvec_capacity(v) == 5, "capacity 5");
  gvec_traverse(cur, v) {
    CHECK_MSG(cur->l == 101, "value 101");
  }
  gvec_free(v);
  CHECK_MSG(gvec_create_full(5, 3, gtype_zero, NULL) == NULL, "size must <= cap");
  TEST_OK();
  return 0;
}