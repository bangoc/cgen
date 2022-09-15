#ifndef LIST_GSL_H_
#define LIST_GSL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * gtype single linked list
 */

#include "base/core.h"
#include "base/gtype.h"
#include "list/sll.h"

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Triển khai danh sách móc nối đơn cho gtype
 * Kế thừa ::struct sllist
 */

/**
 * Cấu trúc nút của danh sách móc nối đơn với kiểu gtype
 * gslnode = gtype single linked (list) node
 */
struct gslnode {
  struct slnode base;
  gtype value;
};

/**
 * Cấu trúc điều khiển của danh sách móc nối kép của kiểu gtype
 * gsllist = gtype single linked list
 */
struct gsllist {
  struct sllist base;
  gtype_free_t free_value;
};

#define gsl_node(n) ((struct gslnode *)(n))
#define gsl_list(l) ((struct gsllist *)(l))

#define gsl_node_value(n) (gsl_node(n)->value)
#define gsl_node_next(n) (gsl_node(sll_node(n)->next))
#define gsl_front(list) (gsl_node(sll_front(list)))
#define gsl_back(list) (gsl_node(sll_back(list)))
#define gsl_length(list) (sll_length(list))
#define gsl_push_back(list, value) \
  do { \
    struct gslnode *_nn = gsl_create_node(value); \
    sll_push_back(sll_list(list), sll_node(_nn)); \
  } while (0)

#define gsl_push_front(list, value) \
  do { \
    struct gslnode *_nn = gsl_create_node(value); \
    sll_push_front(sll_list(list), sll_node(_nn)); \
  } while (0)

#define gsl_pop_front(list) \
  do { \
    struct gslnode *_nn = gsl_front(list); \
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
    struct gslnode *_nn = gsl_create_node(value); \
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

static inline gtype *gsl_front_value(struct gsllist *l) {
  struct gslnode *tmp = gsl_front(l);
  return tmp? &tmp->value: NULL;
}

static inline gtype *gsl_next_value(gtype *cur) {
  struct gslnode *nn = gsl_node_next(container_of(cur, struct gslnode, value));
  return nn? &nn->value: NULL;
}

#define gsl_traverse(cur, list) \
  for (gtype *cur = gsl_front_value(list); cur; cur = gsl_next_value(cur))

struct gslnode *gsl_create_node(gtype value);
struct gsllist *gsl_create_list(gtype_free_t free_value);
void gtype_free_gsl(gtype value);
void gsl_pprint(struct gsllist *l, gtype_print_t pp);

#endif  // LIST_GSL_H_
