/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct tmap *tm = tcreate(cmpl);
  tput(tm, 1, 1.11);
  tput(tm, 2, 1.12);
  tput(tm, 3, 1.13);
  tput(tm, 4, 1.14);
  tput(tm, 5, 1.15);
  tput(tm, 6, 1.16);
  TTRAVERSE(k, v, tm) {
    printf("%ld:%f\n", k->l, v->d);
  }
  TRTRAVERSE(k, v, tm) {
    printf("%ld:%f\n", k->l, v->d);
  }
  tfree(tm);
  return 0;
}