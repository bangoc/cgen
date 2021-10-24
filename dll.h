#ifndef DLL_H_
#define DLL_H_

/*
  (c) Nguyen Ba Ngoc, 2021
  Double Linked List (DLL/dll) and its derived types
*/

typedef struct dll_node_s {
  struct dll_node_s *next;
  struct dll_node_s *prev;
} *dll_node_t;

typedef struct dll_s {
  dll_node_t front;
  dll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
  long size;
} *dll_t;

#define to_dll(n) ((dll_node_t)n)

#define dll_traverse(cur, list) \
  for (dll_node_t cur = list->front; cur != NULL; cur = cur->next)

#define dll_rtraverse(cur, list) \
  for (dll_node_t cur = list->back; cur != NULL; cur = cur->prev)

/* Giao diện khái quát */

dll_node_t dll_create_node();
void dll_free_node(dll_node_t node);
dll_t dll_create_list();
void dll_free_list(dll_t list);

void dll_push_back(dll_t list, dll_node_t nn);
void dll_push_front(dll_t list, dll_node_t nn);
void dll_pop_front(dll_t list);
void dll_pop_back(dll_t list);
dll_node_t dll_front(dll_t list);
dll_node_t dll_back(dll_t list);
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn);
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn);
int dll_is_empty(dll_t list);
void dll_erase(dll_t list, dll_node_t pos);
void dll_clear(dll_t list);

void dll_pprint_node(dll_node_t);
void dll_pprint_list(dll_t);

/* Giao diện cho gtype */

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

/* Giao diện cho kiểu int */

typedef struct dll_node_i_s {
  struct dll_node_s base;
  int value;
} *dll_node_i_t;

#define to_dll_node_i(n) ((dll_node_i_t)n)
#define dll_node_i_value(n) (to_dll_node_i(n)->value)

dll_node_t dll_create_node_i(int value);

void dll_push_back_i(dll_t list, int value);
void dll_push_front_i(dll_t list, int value);
int dll_pop_back_i(dll_t list);
int dll_pop_front_i(dll_t list);
int dll_front_i(dll_t list);
int dll_back_i(dll_t list);
dll_node_t dll_inserta_i(dll_t list, dll_node_t pos, int value);
dll_node_t dll_insertb_i(dll_t list, dll_node_t pos, int value);

void dll_pprint_node_i(dll_node_t);
void dll_pprint_list_i(dll_t);

#endif  // DLL_H_
