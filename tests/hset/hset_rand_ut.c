/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/hset.h"
#include "tests/base/utils.h"

void rands9(char *s) {
  for (int i = 0; i < 9; ++i) {
    s[i] = 'a' + rand() % ('z' - 'a' + 1);
  }
  s[9] = 0;
}

int t1(int n) {
  char **keys = malloc(n * sizeof(char *));
  struct hset *hs = hset_create(gtype_hash_s, gtype_cmp_s, gtype_free_s);
  for (int i = 0; i < n; ++i) {
    keys[i] = malloc(10);
    for (;;) {
      rands9(keys[i]);
      if (!hset_contains(hs, gtype_s(keys[i]))) {
        break;
      }
    }
    int res = hset_insert(hs, gtype_s(keys[i]));
    CHECK_MSG(res == 1, "Insert new");
    CHECK_MSG(hset_contains(hs, gtype_s(keys[i])), "Contains key i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hset_contains(hs, gtype_s(keys[i])), "Contain key i");
  }
  CHECK_MSG(hset_size(hs) == n, "nnodes == n");
  hset_free(hs);
  free(keys);
  return 0;
}

int main() {
  CHECK_MSG(t1(100000) == 0, "t1() 100000");
  TEST_OK();
  return 0;
}