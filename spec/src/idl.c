/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "spec/idl.h"

idn_t idn_create(int value) {
  idn_t n = malloc(sizeof(struct idn_s));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return n;
}

void idl_push_back(dll_t list, int value) {
  idn_t nn = idn_create(value);
  dll_push_back(list, to_dln(nn));
}

void idl_push_front(dll_t list, int value) {
  idn_t nn = idn_create(value);
  dll_push_front(list, to_dln(nn));
}

int idl_pop_back(dll_t list) {
  int value = idl_back(list);
  dll_pop_back(list);
  return value;
}

int idl_pop_front(dll_t list) {
  int value = idl_front(list);
  dll_pop_front(list);
  return value;
}

int idl_front(dll_t list) {
  return idn_value(dll_front(list));
}

int idl_back(dll_t list) {
  return idn_value(dll_back(list));
}

idn_t idl_insert_a(dll_t list, idn_t pos, int value) {
  return to_idn(dll_inserta(list, to_dln(pos),
      to_dln(idn_create(value))));
}

idn_t idl_insertb(dll_t list, idn_t pos, int value) {
  return to_idn(dll_insertb(list, to_dln(pos),
      to_dln(idn_create(value))));
}

void idn_pprint(idn_t node) {
  printf("[%d]", idn_value(node));
}

void idl_pprint(dll_t list) {
  _dll_pprint(list, idn_pprint);
}
