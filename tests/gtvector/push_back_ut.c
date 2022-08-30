#include "base/gtype.h"
#include "dab/arr.h"
#include "tests/base/utils.h"

int t1() {
  arr_decl(v, 0, gtype);
  gtype v1 = {.l = 1},
        v2 = {.l = 2},
        v3 = {.l = 3};
  arr_append(v, v1);
  arr_append(v, v2);
  arr_append(v, v3);
  CHECK_MSG(arr_size(v) == 3, "Vector size");
  CHECK_MSG(ARR(v)[0].l == 1, "Element 1");
  CHECK_MSG(ARR(v)[1].l == 2, "Element 2");
  CHECK_MSG(ARR(v)[2].l == 3, "Element 3");
  arr_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1");
  printf("Test ok!\n");
  return 0;
}