#ifndef GDL_H_
#define GDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Gtype Double linked list
*/

#include "base/dll.h"
#include "gtype.h"

typedef struct gdl_node_s {
  struct dll_node_s base;
  gtype value;
} *gdn_t;

#define to_gdn(n)((gdn_t)n)
#define gdn_value(n) (to_gdn(n)->value)
#define gdn_next(n) (to_dll_node(n)->next)
#define gdn_prev(n) (to_dll_node(n)->next)

gdn_t gdl_create_node(gtype value);
void gdl_push_back(dll_t list, gtype value);
void gdl_push_front(dll_t list, gtype value);
gtype gdl_pop_front(dll_t list);
gtype gdl_pop_back(dll_t list);
gtype gdl_front(dll_t list);
gtype gdl_back(dll_t list);
gdn_t gdl_inserta(dll_t list, gdn_t pos, gtype value);
gdn_t gdl_insertb(dll_t list, gdn_t pos, gtype value);

#endif  // GDL_H_