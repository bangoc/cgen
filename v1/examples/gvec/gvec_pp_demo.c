/* (C) Nguyen Ba Ngoc 2022 */

/**
 * Minh họa sắp xếp mảng cấu trúc point với gvec
 */

#include "all.h"

#include <stdio.h>

struct point {
  double x, y;
};

#define pp(val) ((struct point*)(((gtype*)val)->v))
int gtype_qsort_point(const void *v1, const void *v2) {
  if (pp(v1)->x < pp(v2)->x) {
    return -1;
  } else if (pp(v1)->x > pp(v2)->x) {
    return 1;
  } else if (pp(v1)->y < pp(v2)->y) {
    return -1;
  } else if (pp(v1)->y > pp(v2)->y) {
    return 1;
  }
  return 0;
}
#undef pp

int main(int argc, char *argv[]) {
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  printf("Nhập các các điểm trên mặt phẳng hoặc điểm có tọa độ (0, 0) để kết thúc: \n");
  struct gvector *vec = gvec_create(0, gtype_free_v);
  struct point *p;
  for (;;) {
    p = malloc(sizeof(struct point));
    scanf("%lf%lf", &p->x, &p->y);
    if (p->x == 0 && p->y == 0) {
      free(p);
      break;
    }
    gvec_append(vec, gtype_v(p));
  }
  printf("Bạn đã nhập: %ld điểm\n", gvec_size(vec));
  gvec_qsort(vec, gtype_qsort_point);
  printf("Các điểm theo thứ tự tăng dần (so sánh x sau đó so sánh y): ");
  gvec_traverse(value, vec) {
    struct point *p = value->v;
    printf("\n(%.2lf, %.2lf)", p->x, p->y);
  }
  printf("\n");
  gvec_free(vec);
  return 0;
}