/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa hàm làm rỗng tập cây (rbs_clear)
 */


#include "all.h"
#include "tests/base/rands.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rbs(struct rbstree *tab) {
  printf("size: %ld \n", tab->size);
  rbs_traverse(cur, tab) {
    printf("%s ", cur->s);
  }
  printf("\n");
}

int main() {
  srand(time(NULL));
  struct rbstree *tab = rbs_create(gtype_cmp_s, gtype_free_s);
  for (int i = 0; i < 10; ++i) {
    rbs_insert(tab, gtype_s(strdup(rands(10))));
  }
  printf("Trạng thái sau khi thêm 10 khóa ngẫu nhiên: \n");
  print_rbs(tab);
  rbs_clear(tab);
  printf("Trạng thái sau khi làm rỗng: \n");
  print_rbs(tab);
  printf("Trạng thái sau khi thêm từng phần tử: \n");
  for (int i = 0; i < 10; ++i) {
    rbs_insert(tab, gtype_s(strdup(rands(10))));
    print_rbs(tab);
  }
  rbs_free(tab);
  return 0;
}