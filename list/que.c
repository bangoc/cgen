/* (C) Nguyen Ba Ngoc 2022 */

#include "que.h"

struct gsl *que_enq(struct gsl *q, gtype value) {
  gsl_push_back(q, value);
  return q;
}

struct gsl *que_deq(struct gsl *q) {
  gsl_pop_front(q);
}

gtype que_peek(struct gsl *q) {
  return gsl_node_value(gsl_front(q));
}