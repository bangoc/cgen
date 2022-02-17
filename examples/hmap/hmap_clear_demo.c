/*
  (C) Nguyen Ba Ngoc 2022
  Minh họa hàm làm rỗng bảng băm.
*/

#include "cgen.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *rands(int n) {
  static char buff[21];
  if (n > 20) {
    n = 20;
  }
  for (int i = 0; i < n; ++i) {
    buff[i] = rand() % ('z' - 'a') + 'a';
  }
  buff[n] = '\0';
  return buff;
}

void print_hmap(hmap_t tab) {
  printf("size: %d  capacity: %d  noccupied: %d\n", tab->size, tab->capacity, tab->noccupied);
  hmap_traverse(k, v, tab) {
    printf("%s:\t %ld\n", k->s, v->l);
  }
}

int main() {
  srand(time(NULL));
  hmap_t tab = hmap_create(gtype_hash_s, gtype_cmp_s, gtype_free_s, NULL);
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