#include "all.h"
#include <stdio.h>

int main() {
  struct hmap *map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_insert(map, gtype_s("aaa"), gtype_l(100));
  hmap_insert(map, gtype_s("bbb"), gtype_l(200));
  hmap_insert(map, gtype_s("ccc"), gtype_l(300));
  hmap_insert(map, gtype_s("ddd"), gtype_l(400));
  hmap_insert(map, gtype_s("eee"), gtype_l(500));
  hmap_insert(map, gtype_s("fff"), gtype_l(600));
  gtype *value = hmap_value(map, gtype_s("ccc"));
  if (value) {
    printf("Value of ccc = %ld\n", value->l);
  } else {
    printf("Surprised\n");
  }
  hmap_traverse(key, value, map) {
    printf("%s:%ld\n", key->s, value->l);
  }
  hmap_free(map);
  return 0;
}