#include "vec.h"

#include <stdio.h>

VEC_DECL_IMPL(ivec, int)

int main() {
  int elem;
  struct ivec *v = ivec(0);
  while (scanf("%d", &elem) == 1) {
    ivec_append(v, elem);
  }
  printf("size = %d, cap = %d\n", v->size, v->cap);
  vrfor(v, i) {
    printf(" %d", v->elems[i]);
  }
  printf("\n");
  ivec_free(v);
}