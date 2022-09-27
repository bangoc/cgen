/** @file
 * @brief Sắp xếp mảng số nguyên kiểu long với arr
 */

#include "all.h"
#include "tests/base/utils.h"

int qsort_cmp_l(const void *v1, const void *v2) {
  return *((const long*)v1) - *((const long*)v2);
}

int t1() {
  atype(long) *a = arr_create(5, long);
  a[0] = 1;
  a[1] = -1;
  a[2] = 3;
  a[3] = 2;
  a[4] = 5;
  arr_qsort(a, qsort_cmp_l);
  long b[] = {-1, 1, 2, 3, 5};
  long n = sizeof(b)/sizeof(b[0]);
  CHECK_MSG(arr_size(a) == n, "size of a");
  for (long i = 0; i < n; ++i) {
    CHECK_MSG(a[i] == b[i], "a[i] == b[i]");
  }
  arr_free(a);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1 ()");
  TEST_OK();
  return 0;
}