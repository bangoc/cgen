/* (C) Nguyễn Bá Ngọc 2023 */
#include "tests/mylib/lib.h"
#include "tests/utils.h"

int rcmpi(const void *p1, const void *p2) {
  return *(const int*)p2 - *(const int *)p1;
}

int main() {
  VCONSTRUCT(vectint, v, 0);
  int elem;
  while (scanf("%d", &elem) == 1) {
    VAPPEND(v, elem);
  }
  printf("%ld %ld\n", VSIZE(v), VCAP(v));
  VSORT(v, rcmpi);
  VFOR(i, v) {
    printf(" %d", VELEM(v, i));
  }
  printf("\n");
  VFREE(v);
  TEST_OK();
}