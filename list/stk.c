/* (C) Nguyen Ba Ngoc 2022 */

#include "stk.h"

struct gsllist *stk_push(struct gsllist *stk, gtype value) {
  gsl_push_front(stk, value);
  return stk;
}

struct gsllist *stk_pop(struct gsllist *stk) {
  gsl_pop_front(stk);
  return stk;
}

gtype stk_top(struct gsllist *stk) {
  return gsl_node_value(gsl_front(stk));
}