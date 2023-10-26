/* (C) Nguyễn Bá Ngọc */
/* Thử append trực tiếp số nguyên vào vec-tơ */
#include "all.h"
int main() {
  struct vector *v = vcreate(0);
  vappend(v, 10);
  vappend(v, 15);
  vappend(v, 20);
  vappend(v, 30);
  vappend(v, 90);
  VTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  vfree(v);
}