#include "all.h"

#include "tests/base/utils.h"

int t1() {
  struct gsllist *q = gsl_create_list(NULL);
  for (int i = 1; i <= 1000; ++i) {
    que_enq(q, gtype_l(i));
  }
  CHECK_MSG(que_size(q) == 1000, "size 1000");
  for (int i = 1; i <= 1000; ++i) {
    CHECK_MSG(que_peek(q).l == i, "Fifo i");
    que_deq(q);
  }
  gsl_free(q);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}