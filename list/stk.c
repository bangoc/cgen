/* (C) Nguyen Ba Ngoc 2022 */

#include "stk.h"

gsl_t stk_push(gsl_t stk, gtype value) {
  gsl_push_front(stk, value);
  return stk;
}

gsl_t stk_pop(gsl_t stk) {
  gsl_pop_front(stk);
  return stk;
}

gtype stk_top(gsl_t stk) {
  return gsl_node_value(gsl_front(stk));
}