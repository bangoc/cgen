#include "cgen.h"
#include <stdio.h>
#include <stdlib.h>

struct point {
  int r, c;
};

struct point *point_create(int r, int c) {
  struct point *p = malloc(sizeof(struct point));
  p->r = r;
  p->c = c;
}

void point_free(void *v) {
  free(v);
}

int main() {
  struct queue *q = qcreate(10);
  qsetfv(q, point_free);
  int r, c;
  for (;;) {
    scanf("%d", &r);
    if (r < 0) {
      break;
    }
    scanf("%d", &c);
    qenque(q, GVOID(point_create(r, c)));
  }
  printf("size = %ld\n", qsize(q));
  while (!qempty(q)) {
    struct point *p = qpeek(q)->v;
    printf(" (%d, %d)", p->r, p->c);
    qdeque(q);
  }
  qfree(q);
}