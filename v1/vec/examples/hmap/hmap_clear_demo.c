/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa hàm làm rỗng bảng băm.
 */

#include "all.h"
#include "tests/base/rands.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_hmap(struct hmap *tab) {
  printf("size: %d  capacity: %d  noccupied: %d\n", tab->size, tab->capacity, tab->noccupied);
  hmap_traverse(k, v, tab) {
    printf("%s:\t %ld\n", k->s, v->l);
  }
}

int main() {
  srand(time(NULL));
  struct hmap *tab = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, NULL);
  for (int i = 0; i < 10; ++i) {
    hmap_insert(tab, gtype_s(strdup(rands(10))), gtype_l(rand()));
  }
  printf("Trạng thái hmap sau khi thêm ngẫu nhiên 10 cặp: \n");
  print_hmap(tab);
  hmap_clear(tab);
  printf("Trạng thái hmap sau khi được làm rỗng: \n");
  print_hmap(tab);
  printf("Trạng thái hmap sau khi thêm phần tử mới: \n");
  for (int i = 0; i < 10; ++i) {
    hmap_insert(tab, gtype_s(strdup(rands(10))), gtype_l(rand()));
    print_hmap(tab);
  }
  hmap_free(tab);
  return 0;
}