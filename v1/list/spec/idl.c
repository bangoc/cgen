/* (C) Nguyen Ba Ngoc 2021 */

#include "list/spec/idl.h"

struct idlnode *idl_create_node(int value) {
  struct idlnode *n = malloc(sizeof(struct idlnode));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return n;
}

void idl_push_back(struct dllist *list, int value) {
  struct idlnode *nn = idl_create_node(value);
  dll_push_back(list, dll_node(nn));
}

void idl_push_front(struct dllist *list, int value) {
  struct idlnode *nn = idl_create_node(value);
  dll_push_front(list, dll_node(nn));
}

int idl_pop_back(struct dllist *list) {
  int value = idl_back_value(list);
  dll_pop_back(list);
  return value;
}

int idl_pop_front(struct dllist *list) {
  int value = idl_front_value(list);
  dll_pop_front(list);
  return value;
}

void idl_insert_a(struct dllist *list, struct idlnode *pos, int value) {
  dll_inserta(list, dll_node(pos), dll_node(idl_create_node(value)));
}

void idl_insertb(struct dllist *list, struct idlnode *pos, int value) {
  dll_insertb(list, dll_node(pos), dll_node(idl_create_node(value)));
}

void idn_pprint(struct dlnode *node) {
  printf("[%d]", idl_node_value(node));
}

void idl_pprint(struct dllist *list) {
  dll_pprint(list, idn_pprint);
}
