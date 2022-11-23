#include "base/gtype.h"
#include "vec/arr.h"
#include "tests/base/utils.h"

int t1() {
  arr_make(v, 0, gtype);
  gtype v1 = {.l = 1},
        v2 = {.l = 2},
        v3 = {.l = 3};
  arr_append(v, v1);
  arr_append(v, v2);
  arr_append(v, v3);
  CHECK_MSG(arr_size(v) == 3, "Vector size");
  CHECK_MSG(v[0].l == 1, "Element 1");
  CHECK_MSG(v[1].l == 2, "Element 2");
  CHECK_MSG(v[2].l == 3, "Element 3");
  arr_free(v);
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  CHECK_MSG(t1() == 0, "t1");
  TEST_OK();
  return 0;
}