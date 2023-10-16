#include "cgen.h"

#include <stdio.h>

int main() {
  struct queue *q = qcreate(5);
  for (int i = 0; i < 10; ++i) {
    qenque(q, GDOUBLE(i * 1.5));
  }
  gtype val;
  while (!qempty(q)) {
    printf(" %f", qpeek(q)->d);
    qdeque(q);
  }
  printf("\n");
  qfree(q);
}