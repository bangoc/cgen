#ifndef GSL_H_
#define GSL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype single linked list
*/

#include "base/sll.h"
#include "gtype.h"

typedef struct gsn_s {
  struct sll_node_s base;
  gtype value;
} *gsn_t;

sll_node_t gsl_create_node(gtype value);
void gsl_push_back(sll_t list, gtype value);
void gsl_push_front(sll_t list, gtype value);
gtype gsl_pop_front(sll_t list);
gtype gsl_front(sll_t list);

#define to_gsn(n) ((gsn_t)n)
#define gsn_value(n) (to_gsn(n)->value)
#define gsn_next(n) (to_sll_node(n)->next)

#endif  // GSL_H_
