#include "hmap.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int t1(int n) {
  int *keys = malloc(sizeof(int) * n),
      *values = malloc(sizeof(int) * n);

  hmap_t map = hmap_create(gtype_hash_i, gtype_cmp_i,
      NULL, NULL);
  for (int i = 0; i < n; ++i) {
    for (;;) {
      keys[i] = rand();
      if (hmap_value(map, gtype_i(keys[i])) == NULL) {
        break;
      }
    }
    values[i] = rand();
    hmap_ires res = hmap_insert(map, gtype_i(keys[i]), gtype_i(values[i]));
    CHECK_MSG(res.inserted == 1, "insert new");
    CHECK_MSG(hmap_key_at(map, res.idx)->i == keys[i], "Key at i");
    CHECK_MSG(hmap_value_at(map, res.idx)->i == values[i], "Value at i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hmap_value(map, gtype_i(keys[i]))->i == values[i], "value i");
    hmap_ires res = hmap_insert(map, gtype_i(keys[i]), gtype_i(values[i]));
    CHECK_MSG(res.inserted == 0, "Insert existed");
    CHECK_MSG(hmap_key_at(map, res.idx)->i == keys[i], "Key at i");
    CHECK_MSG(hmap_value_at(map, res.idx)->i == values[i], "Value at i");
  }
  CHECK_MSG(hmap_nnodes(map) == n, "nnodes");
  free(keys);
  free(values);
  hmap_free(map);
  return 0;
}

void rands9(char *s) {
  for (int i = 0; i < 9; ++i) {
    s[i] = 'a' + rand() % ('z' - 'a' + 1);
  }
  s[9] = 0;
}

int t2(int n) {
  char **keys = malloc(sizeof(char*) * n),
       **values = malloc(sizeof(char*) * n);
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, gtype_free_s);
  for (int i = 0; i < n; ++i) {
    keys[i] = malloc(10);
    values[i] = malloc(10);
    for (;;) {
      rands9(keys[i]);
      if (hmap_value(map, gtype_s(keys[i])) == NULL) {
        break;
      }
    }
    rands9(values[i]);
    hmap_ires res = hmap_insert(map, gtype_s(keys[i]), gtype_s(values[i]));
    CHECK_MSG(res.inserted == 1, "insert new");
    CHECK_MSG(strcmp(hmap_key_at(map, res.idx)->s, keys[i]) == 0, "Key i");
    CHECK_MSG(strcmp(hmap_value_at(map, res.idx)->s, values[i]) == 0, "Value i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(strcmp(hmap_value(map, gtype_s(keys[i]))->s, values[i]) == 0, "value i");
    hmap_ires res = hmap_insert(map, gtype_s(keys[i]), gtype_s(values[i]));
    CHECK_MSG(res.inserted == 0, "Insert again");
    CHECK_MSG(strcmp(hmap_key_at(map, res.idx)->s, keys[i]) == 0, "Key i");
    CHECK_MSG(strcmp(hmap_value_at(map, res.idx)->s, values[i]) == 0, "Value i");
  }
  hmap_free(map);
  free(keys);
  free(values);
  return 0;
}

int main() {
  srand(time(NULL));
  CHECK_MSG(t1(100000) == 0, "t1 100000");
  CHECK_MSG(t2(100000) == 0, "t2 100000");
  TEST_OK();
}