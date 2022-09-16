#include "vec/b01_solve.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1(const char *fname) {
  struct gvector *v = read_long(fname);
  CHECK_MSG(v, "return NULL");

  // Đồng bộ với read_long.txt
  gtype a[] = {gtype_l(1), gtype_l(3), gtype_l(2), gtype_l(8), gtype_l(9)};
  int n = sizeof(a) / sizeof(a[0]);
  CHECK_MSG(gvec_sequence(v, n, a, gtype_cmp_l), "t1 sequence");
  gvec_free(v);
  return 0;
}

int main(int argc, char *argv[]) {
  CHECK_MSG(t1(argv[1]) == 0, "t1() ");
  TEST_OK();
  return 0;
}