#ifndef GSL_H_
#define GSL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype single linked list
*/

#include "base/sll.h"
#include "base/gtype.h"

typedef struct gsn_s {
  struct sln_s base;
  gtype value;
} *gsn_t;

typedef struct gsl_s {
  struct sll_s base;
  gtype_free_t free_value;
} *gsl_t;

#define to_gsn(n) ((gsn_t)(n))
#define gsn_value(n) (to_gsn(n)->value)
#define gsn_next(n) (to_gsn(to_sln(n)->next))

#define gsl_front(list) (to_gsn((list)->base.front))
#define gsl_front_value(list) (gsl_front(list)->value)
#define gsl_push_back(list, value) \
  sll_push_back(to_sll(list), to_sln(gsn_create(value)))

#define gsl_push_front(list, value) \
  sll_push_front(to_sll(list), to_sln(gsn_create(value)))

#define gsl_pop_front(list) \
  do { \
    if (list->free_value) { \
      list->free_value(gsl_front_value(list)); \
    } \
    sll_pop_front(to_sll(list)); \
  } while (0)
#define gsl_length(list) sll_length(to_sll(list))
#define gsl_is_empty(list) sll_is_empty(to_sll(list))
#define gsl_clear(list) \
  do {\
    while (!gsl_is_empty(list)) { \
      gsl_pop_front(list); \
    } \
  } while (0)
#define gsl_free(list) \
  do {\
      gsl_clear(list); \
      free(list); \
  } while (0)
gsn_t gsn_create(gtype value);
gsl_t gsl_create(gtype_free_t free_value);

#define gsl_traverse(cur, list) \
  for (gsn_t cur = gsl_front(list); cur; cur = gsn_next(cur))

#endif  // GSL_H_
