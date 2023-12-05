/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

void printd(const gtype g) {
  printf("%f\n", g.d);
}

void printl(const gtype g) {
  printf("%ld\n", g.l);
}

#define call(func, param) func(TO_GTYPE(param))

int main() {
  call(printd, 1.101);
  call(printl, 100);
  TEST_OK();
}