/* (C) Nguyen Ba Ngoc 2021 */

#include "all.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  struct gvector *v = gvec_create(0, NULL);
  srand(time(NULL));
  for (int i = 0; i < 10; ++i) {
    gvec_append(v, gtype_l(rand() % 100));
  }
  printf("Before sort: ");
  gvec_traverse(g, v) {
    printf(" %ld", g->l);
  }
  printf("\n");
  gvec_qsort(v, gtype_qsort_l);
  printf("After sort: ");
  gvec_traverse(g, v) {
    printf(" %ld", g->l);
  }
  printf("\n");
  gvec_free(v);
  return 0;
}