/* (C) Nguyen Ba Ngoc 2022 */

#include "que.h"

struct gsllist *que_enq(struct gsllist *q, gtype value) {
  gsl_push_back(q, value);
  return q;
}

struct gsllist *que_deq(struct gsllist *q) {
  gsl_pop_front(q);
  return q;
}

gtype que_peek(struct gsllist *q) {
  return gsl_node_value(gsl_front(q));
}