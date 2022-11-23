#include "vec/hmap.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int t1(int n) {
  int *keys = ext_malloc(sizeof(int) * n),
      *values = ext_malloc(sizeof(int) * n);

  struct hmap *map = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, NULL);
  for (int i = 0; i < n; ++i) {
    for (;;) {
      keys[i] = rand();
      if (hmap_value(map, gtype_l(keys[i])) == NULL) {
        break;
      }
    }
    values[i] = rand();
    struct hmap_ires res = hmap_insert(map, gtype_l(keys[i]), gtype_l(values[i]));
    CHECK_MSG(res.inserted == 1, "inserted");
    CHECK_MSG(res.value->l == values[i], "Value at i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hmap_value(map, gtype_l(keys[i]))->l == values[i], "value i");
    struct hmap_ires res = hmap_insert(map, gtype_l(keys[i]), gtype_l(values[i]));
    CHECK_MSG(res.inserted == 0, "Insert existed");
    CHECK_MSG(res.value->l == values[i], "Value at i");
  }
  CHECK_MSG(hmap_size(map) == n, "nnodes");
#ifndef CGEN_USE_GC
  ext_free(keys);
  ext_free(values);
  hmap_free(map);
#endif  // CGEN_USE_GC
  return 0;
}

void rands9(char *s) {
  for (int i = 0; i < 9; ++i) {
    s[i] = 'a' + rand() % ('z' - 'a' + 1);
  }
  s[9] = 0;
}

int t2(int n) {
  char **keys = ext_malloc(sizeof(char*) * n),
       **values = ext_malloc(sizeof(char*) * n);
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  for (int i = 0; i < n; ++i) {
    keys[i] = ext_malloc(10);
    values[i] = ext_malloc(10);
    for (;;) {
      rands9(keys[i]);
      if (hmap_value(map, gtype_s(keys[i])) == NULL) {
        break;
      }
    }
    rands9(values[i]);
    struct hmap_ires res = hmap_insert(map, gtype_s(keys[i]), gtype_s(values[i]));
    CHECK_MSG(res.inserted == 1, "insert new");
    CHECK_MSG(strcmp(res.value->s, values[i]) == 0, "Value i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(strcmp(hmap_value(map, gtype_s(keys[i]))->s, values[i]) == 0, "value i");
    struct hmap_ires res = hmap_insert(map, gtype_s(keys[i]), gtype_s(values[i]));
    CHECK_MSG(res.inserted == 0, "Insert again");
    CHECK_MSG(strcmp(res.value->s, values[i]) == 0, "Value i");
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hmap_remove(map, gtype_s(keys[i])) == 1, "Remove keys");
  }
#ifndef CGEN_USE_GC
  hmap_free(map);
  ext_free(keys);
  ext_free(values);
#endif  // CGEN_USE_GC
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  srand(time(NULL));
  CHECK_MSG(t1(100000) == 0, "t1 100000");
  CHECK_MSG(t2(100000) == 0, "t2 100000");
  TEST_OK();
  return 0;
}
