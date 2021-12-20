/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "hset.h"
#include "tests/base/utils.h"

void rands9(char *s) {
  for (int i = 0; i < 9; ++i) {
    s[i] = 'a' + rand() % ('z' - 'a' + 1);
  }
  s[9] = 0;
}

int t1(int n) {
  char **keys = malloc(n * sizeof(char *));
  hset_t hs = hset_create(gtype_hash_s, gtype_cmp_s, gtype_free_s);
  for (int i = 0; i < n; ++i) {
    keys[i] = malloc(10);
    for (;;) {
      rands9(keys[i]);
      if (!hset_contains(hs, gtype_s(keys[i]))) {
        break;
      }
    }
    hset_ires res = hset_insert(hs, gtype_s(keys[i]));
    CHECK_MSG(res.inserted == 1, "Insert new");
    CHECK_MSG(strcmp(hset_key_at(hs, res.idx)->s, keys[i]) == 0, "Key i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hset_contains(hs, gtype_s(keys[i])), "Contain key i");
  }
  CHECK_MSG(hset_nnodes(hs) == n, "nnodes == n");
  hset_free(hs);
  free(keys);
  return 0;
}

int main() {
  CHECK_MSG(t1(100000) == 0, "t1() 100000");
  TEST_OK();
}