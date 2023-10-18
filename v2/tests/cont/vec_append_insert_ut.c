/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct vector *v = vcreate(0);
  vappend(v, GLONG(1));
  vappend(v, GLONG(5));
  vappend(v, GLONG(9));
  vinsert_before(v, GLONG(3), 1);  // 1 3 5 9
  vinsert_before(v, GLONG(0), 0);  // 0 1 3 5 9
  vinsert_before(v, GLONG(7), 3);  // 0 1 3 7 5 9
  VTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  CHECK_MSG(vref(v, 0)->l == 0, "elem 0 == 0");
  CHECK_MSG(vref(v, 1)->l == 1, "elem 1 == 1");
  CHECK_MSG(vref(v, 2)->l == 3, "elem 2 == 3");
  CHECK_MSG(vref(v, 3)->l == 7, "elem 2 == 7");
  CHECK_MSG(vref(v, 4)->l == 5, "elem 2 == 5");
  CHECK_MSG(vref(v, 5)->l == 9, "elem 2 == 9");
  vfree(v);
  TEST_OK();
}