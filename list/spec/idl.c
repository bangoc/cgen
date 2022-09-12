/* (C) Nguyen Ba Ngoc 2021 */

#include "list/spec/idl.h"

idn_t idn_create(int value) {
  idn_t n = malloc(sizeof(struct idn_s));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return n;
}

void idl_push_back(dll_t list, int value) {
  idn_t nn = idn_create(value);
  dll_push_back(list, dl_node(nn));
}

void idl_push_front(dll_t list, int value) {
  idn_t nn = idn_create(value);
  dll_push_front(list, dl_node(nn));
}

int idl_pop_back(dll_t list) {
  int value = idl_back_value(list);
  dll_pop_back(list);
  return value;
}

int idl_pop_front(dll_t list) {
  int value = idl_front_value(list);
  dll_pop_front(list);
  return value;
}

idn_t idl_insert_a(dll_t list, idn_t pos, int value) {
  return to_idn(dll_inserta(list, dl_node(pos),
      dl_node(idn_create(value))));
}

idn_t idl_insertb(dll_t list, idn_t pos, int value) {
  return to_idn(dll_insertb(list, dl_node(pos),
      dl_node(idn_create(value))));
}

void idn_pprint(idn_t node) {
  printf("[%d]", idn_value(node));
}

void idl_pprint(dll_t list) {
  dll_pprint(list, idn_pprint);
}
