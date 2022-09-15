/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/hset.h"
#include "tests/base/utils.h"

int t1() {
  struct hset *hs = hset_create(gtype_hash_s, gtype_cmp_s, gtype_free_s);
  CHECK_MSG(hset_insert(hs, gtype_s(strdup("ABC"))) == 1, "Insert ABC");
  CHECK_MSG(hset_insert(hs, gtype_s(strdup("DEF"))) == 1, "Insert DEF");
  CHECK_MSG(hset_insert(hs, gtype_s("ABC")) == 0, "Duplicate ABC");
  CHECK_MSG(hset_insert(hs, gtype_s(strdup("DHF"))) == 1, "Inserted DHF");
  CHECK_MSG(hset_index_of(hs, gtype_s("ABC")) != INDEX_NOT_FOUND, "Found ABC");
  CHECK_MSG(hset_remove(hs, gtype_s("ABC")) == 1, "Removed ABC");
  CHECK_MSG(hset_index_of(hs, gtype_s("ABC")) == INDEX_NOT_FOUND, "Not found ABC");
  hset_free(hs);
  return 0;
}

int t2() {
  struct hset *hs = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = sizeof(a)/sizeof(a[0]);
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hset_insert(hs, gtype_l(a[i])) == 1, "Insert a[i]");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hset_contains(hs, gtype_l(a[i])), "Contains a[i]");
    hset_remove(hs, gtype_l(a[i]));
    CHECK_MSG(hset_contains(hs, gtype_l(a[i])) == 0, "Not contain a[i]");
  }
  hset_free(hs);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  CHECK_MSG(t2() == 0, "t2()");
  TEST_OK();
  return 0;
}