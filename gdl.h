#ifndef GDL_H_
#define GDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Gtype Double linked list
*/

#include "base/dll.h"
#include "gtype.h"

typedef struct dll_node_g_s {
  struct dll_node_s base;
  gtype value;
} *dll_node_g_t;

#define to_dll_node_g(n)((dll_node_g_t)n)
#define dll_node_g_value(n) (to_dll_node_g(n)->value)

dll_node_t dll_create_node_g(gtype value);
void dll_push_back_g(dll_t list, gtype value);
void dll_push_front_g(dll_t list, gtype value);
gtype dll_pop_front_g(dll_t list);
gtype dll_pop_back_g(dll_t list);
gtype dll_front_g(dll_t list);
gtype dll_back_g(dll_t list);
dll_node_t dll_inserta_g(dll_t list, dll_node_t pos, gtype value);
dll_node_t dll_insertb_g(dll_t list, dll_node_t pos, gtype value);

#endif  // GDL_H_