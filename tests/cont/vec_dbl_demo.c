/* (C) Nguyễn Bá Ngọc 2023 */
#include "tests/mylib/lib.h"
#include "tests/utils.h"

int main() {
  VCONSTRUCT(vectdbl, v, 0);
  double elem;
  while (scanf("%lf", &elem) == 1) {
    VAPPEND(v, elem);
  }
  printf("%ld %ld\n", VSIZE(v), VCAP(v));
  VSORT(v, cmpd);
  VFOR(i, v) {
    printf(" %f", VELEM(v, i));
  }
  printf("\n");
  VFREE(v);
  TEST_OK();
}