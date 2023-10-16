/* (C) Nguyễn Bá Ngọc 2023 */

/* Minh họa hoạt động của ngăn xếp */

#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct vector *v = vcreate(0);
  vpush(v, GLONG(1));
  vpush(v, GLONG(3));
  vpush(v, GLONG(5));
  CHECK_MSG(vtop(v)->l == 5, "Đỉnh = 5");
  CHECK_MSG(vtop(vpop(v))->l == 3, "Đỉnh = 3");
  vpush(vpop(v), GLONG(7));
  CHECK_MSG(vtop(v)->l == 7, "Đỉnh = 7");
  CHECK_MSG(vtop(vpop(v))->l == 1, "Đỉnh = 1");
  vfree(v);
  TEST_OK();
}