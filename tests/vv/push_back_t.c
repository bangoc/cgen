#include "vv.h"
#include "tests/base/utils.h"

int t1() {
  vector_t v = vv_create();
  void *v1 = (void*)1;
  void *v2 = (void*)2;
  void *v3 = (void*)3;
  vv_push_back(&v, v1);
  vv_push_back(&v, v2);
  vv_push_back(&v, v3);
  CHECK_MSG(vv_size(v) == 3, "Vector size");
  CHECK_MSG(v[0] == v1, "Element 1");
  CHECK_MSG(v[1] == v2, "Element 2");
  CHECK_MSG(v[2] == v3, "Element 3");
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}