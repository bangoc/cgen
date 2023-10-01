/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

void empty_free(gtype v) {}

int main() {
  struct gvector *v1 = gvec_create(0);
  CHECK_MSG(gvec_size(v1) == 0, "Empty vector size 0");
  CHECK_MSG(gvec_capacity(v1) >= gvec_size(v1), "Capacity >= size");
  CHECK_MSG(gvec_free_value(v1) == NULL, "Null pointer");
  CHECK_MSG((long)(gvec_capacity(v1) * gvec_ratio(v1)) > gvec_capacity(v1), 
      "grow up" );

  struct gvector *v2 = gvec_create(0, empty_free);
  CHECK_MSG(gvec_size(v2) == 0, "Empty vector size 0");
  CHECK_MSG(gvec_capacity(v2) >= gvec_size(v2), "Capacity >= size");
  CHECK_MSG(gvec_free_value(v2) == empty_free, "Init fv empty_free");
  CHECK_MSG((long)(gvec_capacity(v2) * gvec_ratio(v2)) > gvec_capacity(v2), 
      "grow up" );

  gvec_free(v1);
  gvec_free(v2);
  TEST_OK();
}