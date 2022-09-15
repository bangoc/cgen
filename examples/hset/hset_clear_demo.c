/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa hàm làm rỗng tập (hợp dựa trên hàm) băm.
 */

#include "all.h"
#include "tests/base/rands.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_hset(struct hset *tab) {
  printf("size: %d  capacity: %d  noccupied: %d\n", tab->size, tab->capacity, tab->noccupied);
  hset_traverse(cur, tab) {
    printf("%s ", cur->s);
  }
  printf("\n");
}

int main() {
  srand(time(NULL));
  struct hset *tab = hset_create(gtype_hash_s, gtype_cmp_s, gtype_free_s);
  for (int i = 0; i < 10; ++i) {
    hset_insert(tab, gtype_s(strdup(rands(10))));
  }
  printf("Trạng thái sau khi thêm 10 khóa ngẫu nhiên: \n");
  print_hset(tab);
  hset_clear(tab);
  printf("Trạng thái sau khi làm rỗng: \n");
  print_hset(tab);
  printf("Trạng thái sau khi thêm từng phần tử: \n");
  for (int i = 0; i < 10; ++i) {
    hset_insert(tab, gtype_s(strdup(rands(10))));
    print_hset(tab);
  }
  hset_free(tab);
  return 0;
}