#include "hmap.h"
#include <stdio.h>

int main() {
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_insert(map, gtype_s("aaa"), gtype_i(100));
  hmap_insert(map, gtype_s("bbb"), gtype_i(200));
  hmap_insert(map, gtype_s("ccc"), gtype_i(300));
  hmap_insert(map, gtype_s("ddd"), gtype_i(400));
  hmap_insert(map, gtype_s("eee"), gtype_i(500));
  hmap_insert(map, gtype_s("fff"), gtype_i(600));
  gtype *value;
  if (value = hmap_value(map, gtype_s("ccc"))) {
    printf("Value of ccc = %ld\n", value->i);
  } else {
    printf("Surprised\n");
  }
  hmap_traverse(key, value, map) {
    printf("%s:%ld\n", key->s, value->i);
  }
  hmap_free(map);
  return 0;
}