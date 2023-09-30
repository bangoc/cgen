/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

void empty_free(gtype v) {}

int main() {
  struct gvector *v0 = gvec_create();
  CHECK_MSG(gvec_size(v0) == 0, "Empty size 0");
  CHECK_MSG(gvec_capacity(v0) >= gvec_size(v0), "Capacity >= size");
  CHECK_MSG(gvec_free_value(v0) == NULL, "Null pointer");
  CHECK_MSG((long)(gvec_capacity(v0) * gvec_scale(v0)) > gvec_capacity(v0), "grow up" );

  TEST_OK();
}