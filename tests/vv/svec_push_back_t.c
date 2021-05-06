#include "svec.h"
#include "tests/base/utils.h"

#include <string.h>

int t1() {
  vector_t v = vv_create();
  char *s1 = "Nguyen Van A";
  char *s2 = "Tran Van B";
  char *s3 = "Nguyen Thi C";
  svec_push_back(&v, s1);
  svec_push_back(&v, s2);
  svec_push_back(&v, s3);
  CHECK_MSG(vv_size(v) == 3, "Failed size");
  CHECK_MSG(strcmp((char*)v[0], s1) == 0, "Failed value 1");
  CHECK_MSG(strcmp((char*)v[1], s2) == 0, "Failed value 2");
  CHECK_MSG(strcmp((char*)v[2], s3) == 0, "Failed value 3");
  svec_free(&v);
  return 0;
}

int main() {
  CHECK(t1() == 0);
  return 0;
}