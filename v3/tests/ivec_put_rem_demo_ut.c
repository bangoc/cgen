#include "vec.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

VEC_DECL_IMPL(i, int)

void ivec_print(struct ivector *v) {
  printf("sz: %d\ncap: %d\n", v->size, v->cap);
  for (int i = 0; i < v->size; ++i) {
    printf("%d\n", v->elems[i]);
  }
}

int main() {
  srand(time(NULL));
  struct ivector *v = ivector(0);
  ivec_put(v, 1, 0);
  ivec_put(v, 2, 0);
  ivec_put(v, 3, 1);
  ivec_put(v, 5, 3);
  ivec_put(v, 6, 3);
  ivec_append(v, 10);
  ivec_print(v);
  ivec_rem(v, 2);
  ivec_rem(v, 3);
  ivec_print(v);
  for (int i = 0; i <= 100; ++i) {
    ivec_put(v, rand(), i);
  }
  for (int i = 100; i >= 0; --i) {
    ivec_rem(v, i);
  }
  ivec_print(v);
  ivec_del(v);
}