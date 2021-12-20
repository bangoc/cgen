#ifndef GSL_H_
#define GSL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype single linked list
*/

#include "base/sll.h"
#include "gtype.h"

typedef struct gsn_s {
  struct sln_s base;
  gtype value;
} *gsn_t;

typedef struct gsl_s {
  struct sll_s base;
  gtype_free_t free_value;
} *gsl_t;

gsn_t gsn_create(gtype value);
gsl_t gsl_create(gtype_free_t free_value);
void gsl_push_back(gsl_t list, gtype value);
void gsl_push_front(gsl_t list, gtype value);
void gsl_pop_front(gsl_t list);
gtype gsl_front(gsl_t list);
gsn_t gsl_front_node(gsl_t list);

#define to_gsn(n) ((gsn_t)n)
#define gsn_value(n) (to_gsn(n)->value)
#define gsn_next(n) (to_sln(n)->next)
#define gsl_traverse(cur, list) \
  for (gsn_t cur = gsl_front_node(list); cur; cur = gsn_next(cur))

#endif  // GSL_H_
