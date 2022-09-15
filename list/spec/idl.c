/* (C) Nguyen Ba Ngoc 2021 */

#include "list/spec/idl.h"

struct idn *idl_create_node(int value) {
  struct idn *n = malloc(sizeof(struct idn));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return n;
}

void idl_push_back(struct dll *list, int value) {
  struct idn *nn = idl_create_node(value);
  dll_push_back(list, dll_node(nn));
}

void idl_push_front(struct dll *list, int value) {
  struct idn *nn = idl_create_node(value);
  dll_push_front(list, dll_node(nn));
}

int idl_pop_back(struct dll *list) {
  int value = idl_back_value(list);
  dll_pop_back(list);
  return value;
}

int idl_pop_front(struct dll *list) {
  int value = idl_front_value(list);
  dll_pop_front(list);
  return value;
}

void idl_insert_a(struct dll *list, struct idn *pos, int value) {
  dll_inserta(list, dll_node(pos), dll_node(idl_create_node(value)));
}

void idl_insertb(struct dll *list, struct idn *pos, int value) {
  dll_insertb(list, dll_node(pos), dll_node(idl_create_node(value)));
}

void idn_pprint(struct idn *node) {
  printf("[%d]", idl_node_value(node));
}

void idl_pprint(struct dll *list) {
  dll_pprint(list, idn_pprint);
}
