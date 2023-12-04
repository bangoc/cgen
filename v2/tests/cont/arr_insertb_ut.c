/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>
int main() {
  amake(int, a, 0);
  ainsertb(a, 1, 0);
  aappend(a, 3);
  ainsertb(a, 2, 1);
  aappend(a, 4);
  aappend(a, 5);
  aappend(a, 6);
  aappend(a, 7);
  aappend(a, 8);
  aappend(a, 9);
  aappend(a, 10);
  ainsertb(a, 20, asize(a) - 1);
  afor(i, a) {
    printf(" %d", aelem(a, i));
  }
  printf("\n");
  afree(a);
}