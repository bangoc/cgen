/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa sử dụng hset
 */

#include "all.h"

int main() {
  struct hset *s = hset_create(gtype_hash_s, gtype_cmp_s, NULL);
  hset_insert(s, gtype_s("aaaaa"));
  hset_insert(s, gtype_s("bbbbb"));
  hset_insert(s, gtype_s("ccccc"));
  hset_insert(s, gtype_s("aaaaa"));
  hset_insert(s, gtype_s("ccccc"));
  hset_insert(s, gtype_s("bbbbb"));
  printf("Số lượng giá trị duy nhất = %d\n", hset_size(s));
  hset_traverse(key, s) {
    printf("%s\n", key->s);
  }
  hset_free(s);
  return 0;
}