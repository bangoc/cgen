#include "cgen.h"

#include <stdio.h>

int main() {
  struct queue *q = qcreate(5);
  for (int i = 0; i < 10; ++i) {
    qenque(q, gtype_d(i * 1.5));
  }
  gtype val;
  while (!qempty(q)) {
    qdeque(qpeek(q, &val));
    printf(" %f", val.d);
  }
  printf("\n");
  qfree(q);
}