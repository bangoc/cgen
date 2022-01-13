/*
  (C) Nguyen Ba Ngoc 2022
  Kiểm thử tập chuỗi ký tự.
*/

#include "cgen.h"
#include "tests/base/utils.h"

int main() {
  rbs_t s = rbs_create(gtype_cmp_s, gtype_free_s);
  const char *cases[] = {"aaa", "bbb", "ccc"};
  int n = sizeof(cases)/sizeof(cases[0]);
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(!rbs_contains(s, gtype_s(cases[i])), "Should not contains ");
    rbs_insert(s, gtype_s(strdup(cases[i])));
    CHECK_MSG(rbs_contains(s, gtype_s(cases[i])), "Should contains");
  }
  rbs_free(s);
  TEST_OK();
}