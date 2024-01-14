#include "cgen.h"

#include <stdio.h>
VDECL_IMPL(dvect, double, dv)
int main() {
  int k, n;
  scanf("%d%d", &k, &n);
  struct dvect *v = dvect(0);
  double tmp;
  for (int i = 0; i < n; ++i) {
    scanf("%lf", &tmp);
    if (i < k) {
      dvappend(v, tmp);
      heap_shift_up(v->elems, v->size, sizeof(v->elems[0]), v->size - 1, cmpd);
    } else if (tmp < v->elems[0]) {
      v->elems[0] = tmp;
      heap_shift_down(v->elems, v->size, sizeof(v->elems[0]), 0, cmpd);
    }
  }
  qsort(v->elems, v->size, sizeof(v->elems[0]), cmpd);
  for (int i = 0; i < v->size; ++i) {
    printf("%.2f\n", v->elems[i]);
  }
}