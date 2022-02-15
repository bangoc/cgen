#ifndef GSL_H_
#define GSL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype single linked list
*/

#include "base/gtype.h"

typedef enum {
  GSN_VALUE,
  GSN_NEXT,
  GSN_ELEMENTS
} gsn_elements;

typedef struct gtype_single_linked {
  gtype *front, *back;
  gtype_free_t free_value;
} *gsl_t;

#define gsn_value(n) (*(n))
#define gsn_next(n) (((gtype*)(n) + GSN_NEXT)->g)
#define gsl_front(list) (list->front)
#define gsl_back(list) (list->back)
#define gsl_push_back(list, value) \
  do { \
    gtype *_node = malloc(GSN_ELEMENTS * sizeof(gtype)); \
    gsn_value(_node) = (value); \
    gsn_next(_node) = NULL; \
    if (gsl_back(list)) { \
      gsn_next(gsl_back(list)) = _node; \
      gsl_back(list) = _node; \
    } else { \
      gsl_back(list) = gsl_front(list) = _node; \
    } \
  } while (0)

#define gsl_push_front(list, value) \
  do { \
    gtype *_node = malloc(GSN_ELEMENTS * sizeof(gtype)); \
    gsn_value(_node) = (value); \
    gsn_next(_node) = gsl_front(list); \
    if (gsl_front(list)) { \
      gsl_front(list) = _node; \
    } else { \
      gsl_front(list) = gsl_back(list) = _node; \
    } \
  } while (0)

#define gsl_pop_front(list) \
  do { \
    gtype *_front = gsl_front(list); \
    gtype *_tmp = gsn_next(_front); \
    if (list->free_value) { \
      list->free_value(_front[GSN_VALUE]); \
    } \
    free(_front); \
    gsl_front(list) = _tmp; \
    if (!_tmp) { \
      gsl_back(list) = NULL; \
    } \
  } while (0)

#define gsl_is_empty(list) (gsl_front(list) == NULL && gsl_back(list) == NULL)
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

#define gsl_traverse(cur, list) \
  for (gtype *cur = gsl_front(list); cur; cur = gsn_next(cur))

gsl_t gsl_create(gtype_free_t free_value);
long gsl_size(gsl_t);

#endif  // GSL_H_
