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
  printf("%ld\n", LONGG(varr(v)[0]));
  printf("%f\n", DOUBLEG(vref(v, 1)));
  printf("%s\n", STRG(vref(v, 2)));
  struct point *tmp = VOIDG(vref(v, 3));
  printf("(%d, %d)\n", tmp->x, tmp->y);
  vfree(v);
}