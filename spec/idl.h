#ifndef SPEC_IDL_H_
#define SPEC_IDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Int Double Linked List
*/

#include "base/dll.h"

typedef struct idn_s {
  struct dll_node_s base;
  int value;
} *idn_t;

#define to_idn(n) ((idn_t)n)
#define idn_value(n) (to_idn(n)->value)

idn_t idn_create(int value);

void idl_push_back(dll_t list, int value);
void idl_push_front(dll_t list, int value);
int idl_pop_back(dll_t list);
int idl_pop_front(dll_t list);
int idl_front(dll_t list);
int idl_back(dll_t list);
idn_t idl_insert_a(dll_t list, idn_t pos, int value);
idn_t idl_insertb(dll_t list, idn_t pos, int value);

void idn_pprint(idn_t);
void idl_pprint(dll_t);

#endif // SPEC_IDL_H_