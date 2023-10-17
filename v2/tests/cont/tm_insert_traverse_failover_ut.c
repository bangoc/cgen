/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct tmap *tm = tcreate(glong_cmp);
  tinsert(tm, GLONG(1), GDOUBLE(1.11));
  tinsert(tm, GLONG(2), GDOUBLE(1.12));
  tinsert(tm, GLONG(3), GDOUBLE(1.13));
  tinsert(tm, GLONG(4), GDOUBLE(1.14));
  tinsert(tm, GLONG(5), GDOUBLE(1.15));
  tinsert(tm, GLONG(6), GDOUBLE(1.16));
  TTRAVERSE(k, v, tm) {
    printf("%ld:%f\n", k->l, v->d);
  }
  TEST_OK();
}