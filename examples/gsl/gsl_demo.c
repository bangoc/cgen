/*
  (C) Nguyen Ba Ngoc 2021
  Minh họa sử dụng gsl
*/

#include "ext/io.h"
#include "gsl.h"

#include <stdio.h>
#include <string.h>

int main() {
  gsl_t list = gsl_create(gtype_free_s);
  char *line = NULL;
  while (cgetline(&line, 0, stdin)) {
    if (strcmp(line, "STOP\n") == 0) {
      break;
    }
    gsl_push_back(list, gtype_s(strdup(line)));
  }
  printf("Đã nhập %d dòng:\n", gsl_size(list));
  gsl_traverse(cur, list) {
    printf("%s", cur->s);
  }
  free(line);
  gsl_free(list);
  return 0;
}