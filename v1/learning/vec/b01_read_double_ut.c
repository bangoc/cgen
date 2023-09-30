#include "vec/b01_solve.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1(const char *fname) {
  struct gvector *v = read_double(fname);
  CHECK_MSG(v, "return NULL");

  // Đồng bộ với read_double.txt
  gtype a[] = {gtype_d(1.5), gtype_d(3.2), gtype_d(2.01),
    gtype_d(8.901), gtype_d(9.22), gtype_d(7.77), gtype_d(8.013)};
  int n = sizeof(a) / sizeof(a[0]);
  CHECK_MSG(gvec_sequence(v, n, a, gtype_cmp_d), "t1 sequence");
  gvec_free(v);
  return 0;
}

int main(int argc, char *argv[]) {
  CHECK_MSG(t1(argv[1]) == 0, "t1() ");
  TEST_OK();
  return 0;
}