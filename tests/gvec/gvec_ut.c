#include "gvec.h"
#include "tests/base/utils.h"
#include "tests/base/helpers.h"

#include <stdlib.h>
#include <string.h>

int gtype_inc_cmp_i(const void *v1, const void *v2) {
  return ((const gtype*)v1)->i - ((const gtype*)v2)->i;
}

int gtype_inc_cmp_s(const void *v1, const void *v2) {
  return strcmp(((const gtype*)v1)->s, ((const gtype*)v2)->s);
}

int t1() {
  gvec_t v = gvec_create(3, NULL);
  int a[] = {3, 1, 5, 6, 8, 9, 10, 2};
  int n = sizeof(a)/ sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    gvec_append(v, gtype_i(a[i]));
  }
  CHECK_MSG(gtype_seqi(gvec_arr(v), a, n), "vec sequence");
  gvec_qsort(v, gtype_inc_cmp_i);
  CHECK_MSG(gtype_seqi(gvec_arr(v), (int[]){1, 2, 3, 5, 6, 8, 9, 10}, n), "sorted vec seq");
  gvec_free(v);
  return 0;
}

int t2() {
  gvec_t v = gvec_create(3, gtype_free_s);
  gvec_append(v, gtype_s(strdup("AAA")));
  gvec_append(v, gtype_s(strdup("CCC")));
  gvec_append(v, gtype_s(strdup("BBB")));
  gvec_qsort(v, gtype_inc_cmp_s);
  CHECK_MSG(gtype_seqs(gvec_arr(v), (char*[]){"AAA", "BBB", "CCC"}, 3), "sorted strings");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  CHECK_MSG(t2() == 0, "t2()");
  TEST_OK();
}