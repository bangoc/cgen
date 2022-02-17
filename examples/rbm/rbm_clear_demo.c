/*
  (C) Nguyen Ba Ngoc 2022
  Minh họa sử dụng hàm làm rỗng bảng cây.
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

void print_rbm(rbm_t tab) {
  printf("size: %ld \n", tab->size);
  rbm_traverse(k, v, tab) {
    printf("%s:\t %ld\n", k->s, v->l);
  }
}

int main() {
  srand(time(NULL));
  rbm_t tab = rbm_create(gtype_cmp_s, gtype_free_s, NULL);
  for (int i = 0; i < 10; ++i) {
    rbm_insert(tab, gtype_s(strdup(rands(10))), gtype_l(rand()));
  }
  printf("Trạng thái rbm sau khi thêm ngẫu nhiên 10 cặp: \n");
  print_rbm(tab);
  rbm_clear(tab);
  printf("Trạng thái rbm sau khi được làm rỗng: \n");
  print_rbm(tab);
  printf("Trạng thái rbm sau khi thêm phần tử mới: \n");
  for (int i = 0; i < 10; ++i) {
    rbm_insert(tab, gtype_s(strdup(rands(10))), gtype_l(rand()));
    print_rbm(tab);
  }
  rbm_free(tab);
  return 0;
}