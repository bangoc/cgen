#include "p1w.h"

int main() {
  // max heap
  p1w_t h = p1w_create(PRIORITY_MAX, gtype_cmp_i);
  p1w_enqueue(h, gtype_i(10));
  p1w_enqueue(h, gtype_i(30));
  p1w_enqueue(h, gtype_i(20));
  p1w_enqueue(h, gtype_i(20));
  p1w_enqueue(h, gtype_i(8));
  while (!p1w_is_empty(h)) {
    printf("deque: %ld\n", p1w_dequeue(h).i);
  }
  p1w_free(h);

  // min heap
  h = p1w_create(PRIORITY_MIN, gtype_cmp_i);
  p1w_enqueue(h, gtype_i(10));
  p1w_enqueue(h, gtype_i(30));
  p1w_enqueue(h, gtype_i(20));
  p1w_enqueue(h, gtype_i(20));
  p1w_enqueue(h, gtype_i(8));
  while (!p1w_is_empty(h)) {
    printf("deque: %ld\n", p1w_dequeue(h).i);
  }
  p1w_free(h);
  return 0;
}