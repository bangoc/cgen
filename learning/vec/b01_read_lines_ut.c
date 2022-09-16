#include "vec/b01_solve.h"

#include "tests/base/utils.h"
#include "tests/gvec/helper.h"

int t1(const char *fname) {
  struct gvector *v = read_lines(fname);
  CHECK_MSG(v, "return NULL");

  // Đồng bộ với read_lines.txt
  gtype a[] = {gtype_s("Hello world\n"),
               gtype_s("One Love, One Future\n"),
               gtype_s("C Programming is Cool")};
  int n = sizeof(a) / sizeof(a[0]);
  CHECK_MSG(gvec_sequence(v, n, a, gtype_cmp_s), "t1 sequence");
  gvec_free(v);
  return 0;
}

int main(int argc, char *argv[]) {
  CHECK_MSG(t1(argv[1]) == 0, "t1() ");
  TEST_OK();
  return 0;
}