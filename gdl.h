#ifndef GDL_H_
#define GDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype double linked list
*/

#include "base/dll.h"
#include "gtype.h"

typedef struct gdn_s {
  struct dln_s base;
  gtype value;
} *gdn_t;

typedef struct gdl_s {
  struct dll_s base;
  gtype_free_t free_value;
} *gdl_t;

#define to_gdn(n)((gdn_t)n)
#define gdn_value(n) (to_gdn(n)->value)
#define gdn_next(n) (to_gdn(to_dln(n)->next))
#define gdn_prev(n) (to_gdn(to_dln(n)->next))

#define gdl_traverse(cur, list) \
  for (gdn_t cur = gdl_front_node(list); cur; cur = gdn_next(cur))

gdn_t gdn_create(gtype value);
gdl_t gdl_create(gtype_free_t free_value);
void gdl_push_back(gdl_t list, gtype value);
void gdl_push_front(gdl_t list, gtype value);
void gdl_pop_front(gdl_t list);
void gdl_pop_back(gdl_t list);
gtype gdl_front(gdl_t list);
gtype gdl_back(gdl_t list);
gdn_t gdl_front_node(gdl_t list);
gdn_t gdl_back_node(gdl_t list);
gdn_t gdl_inserta(gdl_t list, gdn_t pos, gtype value);
gdn_t gdl_insertb(gdl_t list, gdn_t pos, gtype value);
void gdl_clear(gdl_t list);
int gdl_is_empty(gdl_t list);
void gdl_free(gdl_t list);

#endif  // GDL_H_