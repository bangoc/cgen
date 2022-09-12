#ifndef LIST_GSL_H_
#define LIST_GSL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * gtype single linked list
 */

#include "base/core.h"
#include "base/gtype.h"
#include "list/sll.h"

typedef struct gtype_single_linked_node {
  struct single_linked_node base;
  gtype value;
} gsn_s, *gsn_t;

typedef struct gtype_single_linked_list {
  struct single_linked_list base;
  gtype_free_t free_value;
} gsl_s, *gsl_t;

#define gsl_node(n) ((gsn_t)(n))

#define gsl_node_value(n) (gsl_node(n)->value)
#define gsl_node_next(n) (gsl_node(sll_node(n)->next))
#define gsl_front(list) (gsl_node(sll_front(list)))
#define gsl_back(list) (gsl_node(sll_back(list)))
#define gsl_length(list) (sll_length(list))
#define gsl_push_back(list, value) \
  do { \
    gsn_t _nn = gsl_create_node(value); \
    sll_push_back(sll_list(list), sll_node(_nn)); \
  } while (0)

#define gsl_push_front(list, value) \
  do { \
    gsn_t _nn = gsl_create_node(value); \
    sll_push_front(sll_list(list), sll_node(_nn)); \
  } while (0)

#define gsl_pop_front(list) \
  do { \
    gsn_t _nn = gsl_front(list); \
    if (!_nn) { \
      break; \
    } \
    if ((list)->free_value) { \
      (list)->free_value(_nn->value); \
    } \
    sll_pop_front(list); \
  } while (0)

#define gsl_inserta(list, pos, value) \
  do { \
    gsn_t _nn = gsl_create_node(value); \
    sll_inserta(sll_list(list), sll_node(pos), sll_node(_nn)); \
  } while (0)

#define gsl_is_empty(list) (sll_is_empty(sll_list(list)))
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

static inline gtype *gsl_front_value(gsl_t l) {
  gsn_t tmp = gsl_front(l);
  return tmp? &tmp->value: NULL;
}

static inline gtype *gsl_next_value(gtype *cur) {
  gsn_t nn = gsl_node_next(container_of(cur, struct gtype_single_linked_node, value));
  return nn? &nn->value: NULL;
}

#define gsl_traverse(cur, list) \
  for (gtype *cur = gsl_front_value(list); cur; cur = gsl_next_value(cur))

gsn_t gsl_create_node(gtype value);
gsl_t gsl_create_list(gtype_free_t free_value);
void gtype_free_gsl(gtype value);
void gsl_pprint(gsl_t l, gtype_print_t pp);

#endif  // LIST_GSL_H_
