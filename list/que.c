/* (C) Nguyen Ba Ngoc 2022 */

#include "que.h"

gsl_t que_enq(gsl_t q, gtype value) {
  gsl_push_back(q, value);
  return q;
}

gsl_t que_deq(gsl_t q) {
  gsl_pop_front(q);
}

gtype que_peek(gsl_t q) {
  return gsl_node_value(gsl_front(q));
}