/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <string.h>
int main() {
  amake(char *, a, 3);
  aelem(a, 0) = strdup("aaaaaaa");
  aelem(a, 1) = strdup("bbbbbbbb");
  aelem(a, 2) = strdup("cccccc");
  afor(i, a) {
    printf("%s\n", aelem(a, i));
  }
  TEST_OK();
}