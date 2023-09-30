/* (C) Nguyen Ba Ngoc 2022 */

#include "all.h"
#include "tests/base/utils.h"
#include "tests/base/helpers.h"

#include <stdlib.h>
#include <string.h>

int gtype_inc_cmp_i(const void *v1, const void *v2) {
  return ((const gtype*)v1)->l - ((const gtype*)v2)->l;
}

int gtype_inc_cmp_s(const void *v1, const void *v2) {
  return strcmp(((const gtype*)v1)->s, ((const gtype*)v2)->s);
}

int t1() {
  struct gvector *v = gvec_create(0, NULL);
  int a[] = {3, 1, 5, 6, 8, 9, 10, 2};
  int n = sizeof(a)/ sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    gvec_append(v, gtype_l(a[i]));
  }
  CHECK_MSG(gvec_elem(v, 0).l == 3, "elem 0 == 3");
  CHECK_MSG(gtype_seqi(gvec_arr(v), a, n), "vec sequence");
  gvec_qsort(v, gtype_inc_cmp_i);
  CHECK_MSG(gtype_seqi(gvec_arr(v), (int[]){1, 2, 3, 5, 6, 8, 9, 10}, n), "sorted vec seq");
  gvec_free(v);
  return 0;
}

int t2() {
  struct gvector *v = gvec_create(0, gtype_free_s);
  gvec_append(v, gtype_s(strdup("AAA")));
  gvec_append(v, gtype_s(strdup("CCC")));
  gvec_append(v, gtype_s(strdup("BBB")));
  gvec_qsort(v, gtype_inc_cmp_s);
  CHECK_MSG(gtype_seqs(gvec_arr(v), (char*[]){"AAA", "BBB", "CCC"}, 3), "sorted strings");
  gvec_remove(v, 2);
  CHECK_MSG(gtype_seqs(gvec_arr(v), (char*[]){"AAA", "BBB"}, 2), "2 sorted strings");
  CHECK_MSG(gvec_size(v) == 2, "size 2");
  gvec_free(v);
  return 0;
}

int t3() {
  struct gvector *v = gvec_create(0, NULL);
  for (int i = 0; i < 10; ++i) {
    gvec_append(v, gtype_l(i));
  }
  CHECK_MSG(gvec_size(v) == 10, "gvec size 10");
  CHECK_MSG(gtype_seqi(gvec_arr(v), (int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10), "10 seq");
  CHECK_MSG(gvec_arr(v)[0].l == 0, "elem 0");
  CHECK_MSG(gvec_arr(v)[1].l == 1, "elem 1");
  gvec_remove(v, 11);
  gvec_remove(v, 8);
  gvec_remove(v, 4);
  gvec_remove(v, 1);
  CHECK_MSG(gtype_seqi(gvec_arr(v), (int[]){0, 2, 3, 5, 6, 7, 9}, 7), "7 seq");
  CHECK_MSG(gvec_size(v) == 7, "size 7");
  gvec_remove(v, 0);
  gvec_remove(v, 0);
  CHECK_MSG(gvec_size(v) == 5, "size 5");
  CHECK_MSG(gtype_seqi(gvec_arr(v), (int[]){3, 5, 6, 7, 9}, 5), "5 seq");
  gvec_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  CHECK_MSG(t2() == 0, "t2()");
  CHECK_MSG(t3() == 0, "t3()");
  TEST_OK();
  return 0;
}