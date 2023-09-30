#ifndef LIST_SPEC_IDL_H_
#define LIST_SPEC_IDL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Kế thừa dllist cho kiểu int
 * Int Double Linked List
 */

#include "list/dll.h"

/**
 * Cấu trúc nút của danh sách móc nối kép
 * với kiểu int.
 * idlnode = int double linked (list) node
 */
struct idlnode {
  struct dlnode base;
  int value;
};

#define idl_node(n) ((struct idlnode *)(n))
#define idl_node_value(n) (idl_node(n)->value)
#define idl_front(list) (idl_node(dll_front(list)))
#define idl_back(list) (idl_node(dll_back(list)))
#define idl_front_value(list) (idl_front(list)->value)
#define idl_back_value(list) (idl_back(list)->value)

struct idlnode *idl_create_node(int value);

void idl_push_back(struct dllist *list, int value);
void idl_push_front(struct dllist *list, int value);
int idl_pop_back(struct dllist *list);
int idl_pop_front(struct dllist *list);
void idl_insert_a(struct dllist *list, struct idlnode *pos, int value);
void idl_insertb(struct dllist *list, struct idlnode *pos, int value);

void idn_pprint(struct dlnode *);
void idl_pprint(struct dllist *);

#endif // LIST_SPEC_IDL_H_