#include "vec.h"

#include <stdio.h>

VEC_DECL_IMPL(ivec, int)

int main() {
  struct ivec *v = ivec(0);
  for (int i = 0; i < 5; ++i) {
    ivec_append(v, i);
  }
  printf("sz = %d\ncap = %d\n", v->size, v->cap);
  for (int i = 0; i < 5; ++i) {
    printf("%d ", v->elems[i]);
  }
  ivec_free(v);
}