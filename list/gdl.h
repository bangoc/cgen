#ifndef LIST_GDL_H_
#define LIST_GDL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Triển khai danh sách móc nối kép cho kiểu gtype
 * Kế thừa ::struct dllist
 */

/**
 * gtype double linked list
 */

#include "base/core.h"
#include "base/gtype.h"
#include "list/dll.h"

/**
 * Cấu trúc nút của danh sách móc nối kép với kiểu gtype.
 * gdlnode = gtype double linked (list) node
 */
struct gdlnode {
  struct dlnode base;
  gtype value;
};

/**
 * Cấu trúc điều khiển của danh sách móc nối kép với kiểu gtype
 * gdllist = gtype double linked list
 */
struct gdllist {
  struct dllist base;
  gtype_free_t free_value;
};

#define gdl_node(n) ((struct gdlnode *)(n))
#define gdl_list(lst) ((struct gdllist *)(lst))

#define gdl_node_value(n) (gdl_node(n)->value)
#define gdl_node_next(n) (gdl_node(dll_node(n)->next))
#define gdl_node_prev(n) (gdl_node(dll_node(n)->prev))

#define gdl_front(list) (gdl_node(dll_front(list)))
#define gdl_back(list) (gdl_node(dll_back(list)))
#define gdl_is_empty(list) (gdl_front(list) == NULL && gdl_back(list) == NULL)
#define gdl_push_front(list, value) \
  do { \
    struct gdlnode *_nn = gdl_create_node(value); \
    dll_push_front(dll_list(list), dll_node(_nn)); \
  } while (0)

#define gdl_push_back(list, value) \
  do { \
    struct gdlnode *_nn = gdl_create_node(value); \
    dll_push_back(dll_list(list), dll_node(_nn)); \
  } while (0)

#define gdl_pop_front(list) \
  do { \
    struct gdlnode *_tmp = gdl_front(list); \
    if (!_tmp) { \
      break; \
    } \
    if ((list)->free_value) { \
      (list)->free_value(gdl_node_value(_tmp)); \
    } \
    dll_pop_front(list); \
  } while (0)

#define gdl_pop_back(list) \
  do { \
    struct gdlnode *_tmp = gdl_back(list); \
    if (!_tmp) { \
      break; \
    } \
    if ((list)->free_value) { \
      (list)->free_value(gdl_node_value(_tmp)); \
    } \
    dll_pop_back(list); \
  } while (0)

#define gdl_clear(list) \
  do { \
    while (!gdl_is_empty(list)) { \
      gdl_pop_front(list); \
    } \
  } while (0)

#define gdl_free(list) \
  do { \
    gdl_clear(list); \
    free(list); \
  } while (0)

#define gdl_inserta(list, pos, value) \
  do { \
    struct gdlnode *_nn = gdl_create_node(value); \
    dll_inserta(dll_list(list), dll_node(pos), dll_node(_nn)); \
  } while (0)

#define gdl_insertb(list, pos, value) \
  do { \
    struct gdlnode *_nn = gdl_create_node(value); \
    dll_insertb(dll_list(list), dll_node(pos), dll_node(_nn)); \
  } while (0)

static inline gtype* gdl_first_value(struct gdllist *lst) {
  struct gdlnode *n = gdl_front(lst);
  return n? &n->value: NULL;
}

static inline gtype* gdl_next_value(gtype *cur) {
  struct gdlnode *nn = gdl_node_next(container_of(cur, struct gdlnode, value));
  return nn? &nn->value: NULL;
}

#define gdl_traverse(cur, list) \
  for (gtype *cur = gdl_first_value(list); cur; cur = gdl_next_value(cur))

struct gdlnode *gdl_create_node(gtype value);
struct gdllist *gdl_create_list(gtype_free_t free_value);
long gdl_size(struct gdllist *list);
void gtype_free_gdl(gtype value);
void gdl_pprint(struct gdllist *list, gtype_print_t pp);

#endif  // LIST_GDL_H_