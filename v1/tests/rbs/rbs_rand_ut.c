/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Kiểm tra kịch bản ánh xạ chuỗi -> chuỗi
 */

#include "all.h"
#include "tests/base/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE 32
char buff[BUFF_SIZE] = {0};

void gen_buff() {
  for (int i = 0; i < BUFF_SIZE - 1; ++i) {
    buff[i] = 'a' + rand() % ('z' - 'a' + 1);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage example: ./prog 1000\n");
    return 1;
  }
  int n;
  sscanf(argv[1], "%d", &n);
  struct rbstree *s = rbs_create(gtype_cmp_s, gtype_free_s);
  srand(time(NULL));
  char **keys = malloc(n * sizeof(char *));
  long cc = 0;
  for (int i = 0; i < n; ++i) {
    gen_buff();
    char *tmp = strdup(buff);
    if (!rbs_insert(s, gtype_s(tmp))) {
      CHECK_MSG(rbs_size(s) == bn_size((struct bntree *)s), "Size equal bn_size");
      CHECK_MSG(rbs_size(s) == cc, "size == cc");
      free(tmp);
      continue;
    }
    keys[cc] = tmp;
    ++cc;
    CHECK_MSG(rbs_size(s) == bn_size((struct bntree *)s), "Size equal bn_size");
    CHECK_MSG(rbs_size(s) == cc, "size == cc");
  }
  int sz = cc;
  for (int i = 0; i < sz; ++i) {
    CHECK_MSG(rbs_remove(s, gtype_s(keys[i])) == 1, "Remove key i");
    --cc;
    CHECK_MSG(rbs_size(s) == bn_size((struct bntree *)s), "Size equal bn_size");
    CHECK_MSG(rbs_size(s) == cc, "size == cc");
  }
  rbs_free(s);
  free(keys);
  TEST_OK();
  return 0;
}