/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa tạo tập hợp với rbstree
 */

#include "all.h"

int main() {
  struct rbstree *s = rbs_create(gtype_cmp_s, NULL);
  rbs_insert(s, gtype_s("aaaaa"));
  rbs_insert(s, gtype_s("bbbbb"));
  rbs_insert(s, gtype_s("ccccc"));
  rbs_insert(s, gtype_s("aaaaa"));
  rbs_insert(s, gtype_s("ccccc"));
  rbs_insert(s, gtype_s("bbbbb"));
  printf("Số lượng giá trị duy nhất = %ld\n", rbs_size(s));
  rbs_traverse(key, s) {
    printf("%s\n", key->s);
  }
  rbs_free(s);
  return 0;
}