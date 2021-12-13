#include "hmap.h"
#include "tests/base/utils.h"

#include <stdlib.h>
#include <time.h>

int t(int n) {
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
    hmap_insert(map, gtype_i(keys[i]), gtype_i(values[i]));
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hmap_value(map, gtype_i(keys[i]))->i == values[i], "value i");
  }
  CHECK_MSG(hmap_nnodes(map) == n, "nnodes");
  free(keys);
  free(values);
  hmap_free(map);
  return 0;
}

int main() {
  srand(time(NULL));
  CHECK_MSG(t(100000) == 0, "t 100000");
  TEST_OK();
}