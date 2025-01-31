#include "vec.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

VECT_DECL_IMPL(ivec, int)

void ivec_print(struct ivec *v) {
  printf("sz: %d\ncap: %d\n", v->size, v->cap);
  for (int i = 0; i < v->size; ++i) {
    printf("%d\n", v->elems[i]);
  }
}

int main() {
  srand(time(NULL));
  struct ivec *v = ivec(0);
  ivec_ins(v, 0, 1);
  ivec_ins(v, 0, 2);
  ivec_ins(v, 1, 3);
  ivec_ins(v, 3, 5);
  ivec_ins(v, 3, 6);
  ivec_append(v, 10);
  ivec_print(v);
  ivec_del(v, 2);
  ivec_del(v, 3);
  ivec_print(v);
  for (int i = 0; i <= 100; ++i) {
    ivec_ins(v, i, rand());
  }
  for (int i = 100; i >= 0; --i) {
    ivec_del(v, i);
  }
  ivec_print(v);
  ivec_free(v);
}