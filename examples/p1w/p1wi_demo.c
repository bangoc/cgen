#include "all.h"

int main() {
  // max heap
  struct p1way *h = p1w_create(gtype_cmp_l);
  p1w_enqueue(h, gtype_l(10));
  p1w_enqueue(h, gtype_l(30));
  p1w_enqueue(h, gtype_l(20));
  p1w_enqueue(h, gtype_l(20));
  p1w_enqueue(h, gtype_l(8));
  while (!p1w_is_empty(h)) {
    printf("deque: %ld\n", p1w_dequeue(h).l);
  }
  p1w_free(h);

  // min heap
  h = p1w_create(gtype_rcmp_l);
  p1w_enqueue(h, gtype_l(10));
  p1w_enqueue(h, gtype_l(30));
  p1w_enqueue(h, gtype_l(20));
  p1w_enqueue(h, gtype_l(20));
  p1w_enqueue(h, gtype_l(8));
  while (!p1w_is_empty(h)) {
    printf("deque: %ld\n", p1w_dequeue(h).l);
  }
  p1w_free(h);
  return 0;
}