#include "ivector.h"

#include "tests/base/utils.h"

int main() {
  vector_t v = gtv_create();
  ivec_push_back(&v, 1);
  ivec_push_back(&v, 2);
  ivec_push_back(&v, 3);
  CHECK_MSG(gtv_size(v) == 3, "Vector size");
  CHECK_MSG(gtv_capacity(v) >= 3, "Vector capacity");
  CHECK_MSG(v[0].i == 1, "V0 value");
  CHECK_MSG(v[1].i == 2, "V1 value");
  CHECK_MSG(v[2].i == 3, "V2 value");
  return 0;
}