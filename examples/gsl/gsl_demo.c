/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa sử dụng gsllist
 */

#include "all.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  struct gsllist *list = gsl_create_list(gtype_free_s);
  char *line = NULL;
  while (cgetline(&line, 0, stdin)) {
    if (strcmp(line, "STOP\n") == 0) {
      break;
    }
    gsl_push_back(list, gtype_s(strdup(line)));
  }
  printf("Đã nhập %ld dòng:\n", gsl_length(list));
  gsl_traverse(cur, list) {
    printf("%s", cur->s);
  }
  free(line);
  gsl_free(list);
  return 0;
}