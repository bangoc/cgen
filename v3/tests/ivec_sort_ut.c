#include "algo.h"
#include "vec.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

VEC_DECL_IMPL(i, int)

int lte(const void *o1, const void *o2) {
  return *((const int *)o1) <= *((const int *)o2);
}

int main() {
  srand(time(NULL));
  struct ivector *v = ivector(0);
  for (int i = 0; i < 10; ++i) {
    ivec_append(v, rand());
  }
  VQ2INSORT(v, lte);
  for (int i = 0; i < v->size; ++i) {
    if (i > 0 && !lte(v->elems + i - 1, v->elems + i)) {
      return 1;
    }
  }
  printf("sz: %d\ncap: %d\n", v->size, v->cap);
  for (int i = 0; i < v->size; ++i) {
    printf("%d\n", v->elems[i]);
  }
  ivec_del(v);
}