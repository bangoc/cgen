/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"
int main() {
  struct tmap *t = tcreate(cmps);
  tput(t, "aaa", 111);
  tput(t, "ccc", 333);
  tput(t, "bbb", 222);
  long *value;
  tbind(t, "ccc", value);
  printf("%ld\n", *value);
  tfree(t);
  TEST_OK();
}