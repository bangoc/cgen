/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

int main() {
  amake(int, a, 0);
  apush(a, 3);
  apush(a, 2);
  apush(a, 6);
  while (asize(a) > 0) {
    printf("%d\n", atop(a));
    apop(a);
  }
  afree(a);
  TEST_OK();
}