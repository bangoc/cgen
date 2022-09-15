/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa tiến trình ngẫu nhiên lấy các viên bi mầu red, green, blue
 * sau đó thống kê xác suất.
 * Tiến trình ngẫu nhiên được mô phỏng bằng hàm rand, kết quả mong đợi là
 * xác suất cho các mầu là tương đương.
*/

#include "all.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum colors {
  RED,
  GREEN,
  BLUE,
  NUM_COLORS
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000");
    return 1;
  }
  const char *colors[] = {[RED] = "red", [GREEN] = "green", [BLUE] = "blue"};
  srand(time(NULL));
  int n = 0;
  sscanf(argv[1], "%d", &n);
  struct rbmtree *tab = rbm_create(gtype_cmp_s, NULL, gtype_free_gvec);
  for (int i = 0; i < n; ++i) {
    int j = rand() % NUM_COLORS;
    gtype* tmp = rbm_value(tab, gtype_s(colors[j]));
    if (tmp) {
      gvec_append(tmp->gvec, gtype_l(i));
    } else {
      struct gvector *vec = gvec_create(10, NULL);
      gvec_append(vec, gtype_l(i));
      rbm_insert(tab, gtype_s(colors[j]), gtype_gvec(vec));
    }
  }
  rbm_traverse(k, v, tab) {
    printf("%s %.2f\n", k->s, gvec_size(v->gvec)/((double)n) * 100);
  }
  rbm_free(tab);
  return 0;
}