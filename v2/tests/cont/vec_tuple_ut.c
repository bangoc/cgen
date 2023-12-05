/* (C) 2023 Nguyễn Bá Ngọc */
/* Thử nghiệm với các Macro hỗ trợ đọc giá trị gtype */
#include "all.h"
struct point {
  int x, y;
};
int main() {
  struct vector *v = vcreate(0);
  vappend(v, 10);
  vappend(v, 1.15);
  vappend(v, "cccccccccc");
  struct point p = {10, 20};
  vappend(v, &p);
  printf("%ld\n", velem(v, 0).l);
  printf("%f\n", vref(v, 1)->d);
  printf("%s\n", vref(v, 2)->s);
  struct point *tmp = vref(v, 3)->v;
  printf("(%d, %d)\n", tmp->x, tmp->y);
  vfree(v);
}