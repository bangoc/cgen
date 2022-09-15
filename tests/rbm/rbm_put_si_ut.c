/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Đếm số lần gặp chuỗi với rbmtree
*/

#include "all.h"
#include "tests/base/utils.h"

int main() {
  const char *words[] = {"aaa", "bbb", "ccc", "aaa"};
  int n = sizeof(words)/sizeof(words[0]);
  struct rbmtree *tab = rbm_create(gtype_cmp_s, NULL, NULL);
  for (int i = 0; i < n; ++i) {
    gtype *value = rbm_put(tab, gtype_s(words[i]), gtype_l(1));
    if (value) {
      ++value->l;
    }
  }
  CHECK_MSG(rbm_value(tab, gtype_s("aaa"))->l == 2, "aaa 2");
  CHECK_MSG(rbm_value(tab, gtype_s("bbb"))->l == 1, "bbb 2");
  CHECK_MSG(rbm_value(tab, gtype_s("ccc"))->l == 1, "ccc 2");
  rbm_free(tab);
  TEST_OK();
  return 0;
}