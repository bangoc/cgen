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
  int n;
  sscanf(argv[1], "%d", &n);
  struct rbmtree *map = rbm_create(gtype_cmp_s, gtype_free_s, gtype_free_s);
  srand(time(NULL));
  char **keys = malloc(n * sizeof(char *)),
       **values = malloc(n * sizeof(char *));
  long cc = 0;
  for (int i = 0; i < n; ++i) {
    gen_buff();
    char *tmp = strdup(buff);
    struct rbm_ires ires = rbm_insert(map, gtype_s(tmp), gtype_s(NULL));
    if (!ires.inserted) {
      CHECK_MSG(rbm_size(map) == bn_size((struct bntree *)map), "Size equal bn_size");
      CHECK_MSG(rbm_size(map) == cc, "size == cc");
      free(tmp);
      continue;
    }
    keys[cc] = tmp;
    gen_buff();
    values[cc] = strdup(buff);
    ires.value->s = values[cc];
    ++cc;
    CHECK_MSG(rbm_size(map) == bn_size((struct bntree *)map), "Size equal bn_size");
    CHECK_MSG(rbm_size(map) == cc, "size == cc");
  }
  int sz = cc;
  for (int i = 0; i < sz; ++i) {
    CHECK_MSG(rbm_value(map, gtype_s(keys[i]))->s == values[i], "Point to the same place");
    CHECK_MSG(rbm_remove(map, gtype_s(keys[i])) == 1, "Remove key i");
    --cc;
    CHECK_MSG(rbm_size(map) == bn_size((struct bntree *)map), "Size equal bn_size");
    CHECK_MSG(rbm_size(map) == cc, "size == cc");
  }
  rbm_free(map);
  free(keys);
  free(values);
  TEST_OK();
  return 0;
}