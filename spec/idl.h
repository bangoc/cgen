#ifndef SPEC_IDL_H_
#define SPEC_IDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Int Double Linked List
*/

#include "base/dll.h"

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

#endif // SPEC_IDL_H_