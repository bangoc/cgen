/* (C) Nguyen Ba Ngoc 2022 */

#include "stk.h"

struct gsl *stk_push(struct gsl *stk, gtype value) {
  gsl_push_front(stk, value);
  return stk;
}

struct gsl *stk_pop(struct gsl *stk) {
  gsl_pop_front(stk);
  return stk;
}

gtype stk_top(struct gsl *stk) {
  return gsl_node_value(gsl_front(stk));
}