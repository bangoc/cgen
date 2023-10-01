/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa sắp xếp vec-tơ chuỗi ký tự với gvec
 */

#include "all.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  printf("Nhập vào các chuỗi ký tự hoặc STOP để kết thúc: \n");
  struct gvector *vec = gvec_create(0, gtype_free_s);
  char *line = NULL;
  for (;;) {
    if (!cgetline(&line, NULL, stdin)) {
      printf("Kết thúc tệp hoặc lỗi nhập.\n");
      break;
    }
    if (strcmp(line, "STOP\n") == 0 || strcmp(line, "STOP") == 0) {
      break;
    }
    gvec_append(vec, gtype_s(strdup(line)));
  }
  printf("Bạn đã nhập: %ld chuỗi ký tự\n", gvec_size(vec));
  gvec_qsort(vec, gtype_qsort_s);
  printf("Các chuỗi đã nhập theo thứ tự tăng dần: ");
  gvec_traverse(value, vec) {
    printf("%s", value->s);
  }
  printf("\n");
  gvec_free(vec);
  free(line);
  return 0;
}