/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Kiểm tra hmap_put với khóa là chuỗi và trị là số nguyên.
 */

#include "all.h"
#include "tests/base/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *rands10() {
  static char buff[20];
  int i = 0;
  for (; i < 10; ++i) {
    buff[i] = rand() % ('z' - 'a') + 'a';
  }
  buff[i] = 0;
  return buff;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 1000\n");
    return 1;
  }
  srand(time(NULL));
  int n;
  sscanf(argv[1], "%d", &n);
  char **str = malloc(n * sizeof(char*));
  int *a = malloc(n * sizeof(int));
  struct hmap *tab = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  for (int i = 0; i < n; ++i) {
    str[i] = strdup(rands10());
    a[i] = rand() % 10 + 1;
    for (int j = 0; j < a[i]; ++j) {
      gtype *res = hmap_put(tab, gtype_s(str[i]), gtype_l(1));
      if (res) {
        ++res->l;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    CHECK_MSG(hmap_value(tab, gtype_s(str[i]))->l == a[i], "Wrong value");
  }
  for (int i = 0; i < n; ++i) {
    free(str[i]);
  }
  hmap_free(tab);
  free(a);
  free(str);
  TEST_OK();
  return 0;
}