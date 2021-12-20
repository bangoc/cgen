#ifndef GDL_H_
#define GDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype double linked list
*/

#include "base/dll.h"
#include "base/gtype.h"

typedef struct gdn_s {
  struct dln_s base;
  gtype value;
} *gdn_t;

typedef struct gdl_s {
  struct dll_s base;
  gtype_free_t free_value;
} *gdl_t;

#define to_gdn(n)((gdn_t)(n))
#define gdn_value(n) (to_gdn(n)->value)
#define gdn_next(n) (to_gdn(to_dln(n)->next))
#define gdn_prev(n) (to_gdn(to_dln(n)->next))

#define gdl_front(list) (to_gdn((list)->base.front))
#define gdl_back(list) (to_gdn((list)->base.back))
#define gdl_front_value(list) (gdl_front(list)->value)
#define gdl_back_value(list) (gdl_back(list)->value)
#define gdl_is_empty(list) (dll_is_empty(to_dll(list)))
#define gdl_push_front(list, value) \
  dll_push_front(to_dll(list), to_dln(gdn_create(value)))
#define gdl_push_back(list, value) \
  dll_push_back(to_dll(list), to_dln(gdn_create(value)))

#define gdl_pop_front(list) \
  do { \
    if (list->free_value) { \
      list->free_value(gdl_front_value(list)); \
    } \
    dll_pop_front(to_dll(list)); \
  } while (0)

#define gdl_pop_back(list) \
  do { \
    if (list->free_value) { \
      list->free_value(gdl_back_value(list)); \
    } \
    dll_pop_back(to_dll(list)); \
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

#define gdl_traverse(cur, list) \
  for (gdn_t cur = gdl_front(list); cur; cur = gdn_next(cur))

#define gdl_pprint(list, gdn_pprint) \
  dll_pprint(list, gdn_pprint)

gdn_t gdn_create(gtype value);
void gdn_pprint_i(dln_t);
gdl_t gdl_create(gtype_free_t free_value);
gdn_t gdl_inserta(gdl_t list, gdn_t pos, gtype value);
gdn_t gdl_insertb(gdl_t list, gdn_t pos, gtype value);

#endif  // GDL_H_