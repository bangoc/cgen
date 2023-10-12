/* (C) Nguyễn Bá Ngọc 2023 */

/* Minh họa hoạt động của ngăn xếp */

#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct vector *v = vcreate(0);
  vpush(v, gtype_l(1));
  vpush(v, gtype_l(3));
  vpush(v, gtype_l(5));
  gtype val;
  vtop(v, &val);
  CHECK_MSG(val.l == 5, "Đỉnh = 5");
  vpop(v);
  vtop(v, &val);
  CHECK_MSG(val.l == 3, "Đỉnh = 3");
  vpush(v, gtype_l(7));
  vtop(v, &val);
  CHECK_MSG(val.l == 7, "Đỉnh = 7");
  vpop(vpop(v));
  vtop(v, &val);
  CHECK_MSG(val.l == 1, "Đỉnh = 1");
  TEST_OK();
}