#include "gtvector.h"
#include "tests/base/utils.h"

int t1() {
  vector_t v = gtv_create();
  gtype v1 = {.i = 1},
        v2 = {.i = 2},
        v3 = {.i = 3};
  gtv_push_back(&v, v1);
  gtv_push_back(&v, v2);
  gtv_push_back(&v, v3);
  CHECK_MSG(gtv_size(v) == 3, "Vector size");
  CHECK_MSG(v[0].i == 1, "Element 1");
  CHECK_MSG(v[1].i == 2, "Element 2");
  CHECK_MSG(v[2].i == 3, "Element 3");
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}