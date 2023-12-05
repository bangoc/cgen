/* (C) Nguyễn Bá Ngọc */
#include "all.h"
#include "tests/ut/utils.h"

int sort_str() {
  struct vector *v = vcreate(0);
  vappend(v, "aaaaa");
  vappend(v, "cccccc");
  vappend(v, "bbbb");
  VSORT(v, cmps);
  VTRAVERSE(cur, v) {
    printf("%s\n", cur->s);
  }
  vfree(v);
  return 1;
}

int main() {
  struct vector *v = vcreate(0);
  int a[] = {3, 1, 2, 9, 8, 10};
  int n = sizeof(a)/sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    vappend(v, a[i]);
  }
  VSORT(v, cmpl);
  printf("size cap: %ld %ld\n", vsize(v), vcap(v));
  VTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
  vfree(v);
  CHECK_MSG(sort_str(), "sort str");
  TEST_OK();
}