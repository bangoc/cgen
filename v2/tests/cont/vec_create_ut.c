/* (C) Nguyễn Bá Ngọc 2023 */
#define CGEN_DEBUG
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

void empty_free(gtype *v) {}

int main() {
  struct vector *v1 = vcreate(0);
  CHECK_MSG(vsize(v1) == 0, "Empty vector size 0");
  CHECK_MSG(vcap(v1) >= vsize(v1), "Capacity >= size");
  CHECK_MSG(vfreeval(v1) == NULL, "Null pointer");
  CHECK_MSG((long)(vcap(v1) * vratio(v1)) > vcap(v1), 
      "grow up" );

  struct vector *v2 = vcreate(0, empty_free);
  CHECK_MSG(vsize(v2) == 0, "Empty vector size 0");
  CHECK_MSG(vcap(v2) >= vsize(v2), "Capacity >= size");
  CHECK_MSG(vfreeval(v2) == empty_free, "Init fv empty_free");
  CHECK_MSG((long)(vcap(v2) * vratio(v2)) > vcap(v2), 
      "grow up" );

  CHECK_MSG(vcreate(-1) == NULL, "Kích thước không hợp lệ.");
  vfree(v1);
  vfree(v2);
  TEST_OK();
}