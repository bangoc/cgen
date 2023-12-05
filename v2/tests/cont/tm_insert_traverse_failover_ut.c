/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct tmap *tm = tcreate(cmpl);
  tput(tm, GLONG(1), GDOUBLE(1.11));
  tput(tm, GLONG(2), GDOUBLE(1.12));
  tput(tm, GLONG(3), GDOUBLE(1.13));
  tput(tm, GLONG(4), GDOUBLE(1.14));
  tput(tm, GLONG(5), GDOUBLE(1.15));
  tput(tm, GLONG(6), GDOUBLE(1.16));
  TTRAVERSE(k, v, tm) {
    printf("%ld:%f\n", k->l, v->d);
  }
  TRTRAVERSE(k, v, tm) {
    printf("%ld:%f\n", k->l, v->d);
  }
  tfree(tm);
  return 0;
}