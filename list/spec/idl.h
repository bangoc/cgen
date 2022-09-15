#ifndef LIST_SPEC_IDL_H_
#define LIST_SPEC_IDL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Kế thừa dll cho kiểu int
 * Int Double Linked List
 */

#include "list/dll.h"

typedef struct idn {
  struct dln base;
  int value;
};

#define idl_node(n) ((struct idn *)(n))
#define idl_node_value(n) (idl_node(n)->value)
#define idl_front(list) (idl_node(dll_front(list)))
#define idl_back(list) (idl_node(dll_back(list)))
#define idl_front_value(list) (idl_front(list)->value)
#define idl_back_value(list) (idl_back(list)->value)

struct idn *idl_create_node(int value);

void idl_push_back(struct dll *list, int value);
void idl_push_front(struct dll *list, int value);
int idl_pop_back(struct dll *list);
int idl_pop_front(struct dll *list);
void idl_insert_a(struct dll *list, struct idn *pos, int value);
void idl_insertb(struct dll *list, struct idn *pos, int value);

void idn_pprint(struct idn *);
void idl_pprint(struct dll *);

#endif // LIST_SPEC_IDL_H_