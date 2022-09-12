#ifndef LIST_GDL_H_
#define LIST_GDL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * gtype double linked list
 */

#include "base/core.h"
#include "base/gtype.h"
#include "list/dll.h"

typedef struct gtype_double_linked_node {
  struct double_linked_node base;
  gtype value;
} gdn_s, *gdn_t;

typedef struct gtype_double_linked {
  struct double_linked_list base;
  gtype_free_t free_value;
} gdl_s, *gdl_t;

#define gdl_node(n) ((gdn_t)(n))
#define gdl_list(lst) ((gdl_t)(lst))

#define gdl_node_value(n) (gdl_node(n)->value)
#define gdl_node_next(n) (gdl_node(dl_node(n)->next))
#define gdl_node_prev(n) (gdl_node(dl_node(n)->prev))

#define gdl_front(list) (gdl_node(dll_front(list)))
#define gdl_back(list) (gdl_node(dll_back(list)))
#define gdl_is_empty(list) (gdl_front(list) == NULL && gdl_back(list) == NULL)
#define gdl_push_front(list, value) \
  do { \
    gdn_t _nn = gdl_create_node(value); \
    dll_push_front(dl_list(list), dl_node(_nn)); \
  } while (0)

#define gdl_push_back(list, value) \
  do { \
    gdn_t _nn = gdl_create_node(value); \
    dll_push_back(dl_list(list), dl_node(_nn)); \
  } while (0)

#define gdl_pop_front(list) \
  do { \
    gdn_t _tmp = gdl_front(list); \
    if (!_tmp) { \
      break; \
    } \
    if (list->free_value) { \
      list->free_value(gdl_node_value(_tmp)); \
    } \
    dll_pop_front(list); \
  } while (0)

#define gdl_pop_back(list) \
  do { \
    gdn_t _tmp = gdl_back(list); \
    if (!_tmp) { \
      break; \
    } \
    if (list->free_value) { \
      list->free_value(gdl_node_value(_tmp)); \
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
    gdn_t _nn = gdl_create_node(value); \
    dll_inserta(dl_list(list), dl_node(pos), dl_node(_nn)); \
  } while (0)

#define gdl_insertb(list, pos, value) \
  do { \
    gdn_t _nn = gdl_create_node(value); \
    dll_insertb(dl_list(list), dl_node(pos), dl_node(_nn)); \
  } while (0)

static inline gtype* gdl_first_value(gdl_t lst) {
  gdn_t n = gdl_front(lst);
  return n? &n->value: NULL;
}

static inline gtype* gdl_next_value(gtype *cur) {
  gdn_t nn = gdl_node_next(container_of(cur, struct gtype_double_linked_node, value));
  return nn? &nn->value: NULL;
}

#define gdl_traverse(cur, list) \
  for (gtype *cur = gdl_first_value(list); cur; cur = gdl_next_value(cur))

gdn_t gdl_create_node(gtype value);
gdl_t gdl_create_list(gtype_free_t free_value);
long gdl_size(gdl_t list);
void gtype_free_gdl(gtype value);
void gdl_pprint(gdl_t list, gtype_print_t pp);

#endif  // LIST_GDL_H_