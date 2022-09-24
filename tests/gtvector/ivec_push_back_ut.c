#include "vec/arr.h"

#include "tests/base/utils.h"

int main() {
  arr_make(v, 0, int);
  arr_append(v, 1);
  arr_append(v, 2);
  arr_append(v, 3);
  CHECK_MSG(arr_size(v) == 3, "Vector size");
  CHECK_MSG(arr_capacity(v) >= 3, "Vector capacity");
  CHECK_MSG(v[0] == 1, "V0 value");
  CHECK_MSG(v[1] == 2, "V1 value");
  CHECK_MSG(v[2] == 3, "V2 value");
  arr_free(v);
  printf("Test Ok!\n");
  return 0;
}