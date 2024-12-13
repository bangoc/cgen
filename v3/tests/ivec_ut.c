#include "vec.h"

#include <stdio.h>

VEC_DECL_IMPL(i, int)

int main() {
  struct ivector *v = ivector(0);
  for (int i = 0; i < 5; ++i) {
    ivec_append(v, i);
  }
  printf("sz = %d\ncap = %d\n", v->size, v->cap);
  for (int i = 0; i < 5; ++i) {
    printf("%d ", v->elems[i]);
  }
  ivec_del(v);
}