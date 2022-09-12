#ifndef LIST_SPEC_IDL_H_
#define LIST_SPEC_IDL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Int Double Linked List
 */

#include "list/dll.h"

typedef struct idn_s {
  struct double_linked_node base;
  int value;
} *idn_t;

#define to_idn(n) ((idn_t)(n))
#define idn_value(n) (to_idn(n)->value)
#define idl_front(list) (to_idn(dll_front(list)))
#define idl_back(list) (to_idn(dll_back(list)))
#define idl_front_value(list) (idl_front(list)->value)
#define idl_back_value(list) (idl_back(list)->value)

idn_t idn_create(int value);

void idl_push_back(dll_t list, int value);
void idl_push_front(dll_t list, int value);
int idl_pop_back(dll_t list);
int idl_pop_front(dll_t list);
void idl_insert_a(dll_t list, idn_t pos, int value);
void idl_insertb(dll_t list, idn_t pos, int value);

void idn_pprint(idn_t);
void idl_pprint(dll_t);

#endif // LIST_SPEC_IDL_H_