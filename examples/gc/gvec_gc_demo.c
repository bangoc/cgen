/* (C) Nguyen Ba Ngoc 2021 */

#include "all.h"

#include <gc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  cgen_boehm_gc_init();
  struct gvector *v = gvec_create_simple(0);
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
  return 0;
}