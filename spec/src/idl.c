/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "spec/idl.h"

dll_node_t dll_create_node_i(int value) {
  dll_node_i_t n = malloc(sizeof(struct dll_node_i_s));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return (dll_node_t)n;
}

void dll_push_back_i(dll_t list, int value) {
  dll_node_t nn = dll_create_node_i(value);
  dll_push_back(list, nn);
}

void dll_push_front_i(dll_t list, int value) {
  dll_node_t nn = dll_create_node_i(value);
  dll_push_front(list, nn);
}

int dll_pop_back_i(dll_t list) {
  int value = dll_back_i(list);
  dll_pop_back(list);
  return value;
}

int dll_pop_front_i(dll_t list) {
  int value = dll_front_i(list);
  dll_pop_front(list);
  return value;
}

int dll_front_i(dll_t list) {
  return dll_node_i_value(dll_front(list));
}

int dll_back_i(dll_t list) {
  return dll_node_i_value(dll_back(list));
}

dll_node_t dll_inserta_i(dll_t list, dll_node_t pos, int value) {
  return dll_inserta(list, pos, dll_create_node_i(value));
}

dll_node_t dll_insertb_i(dll_t list, dll_node_t pos, int value) {
  return dll_insertb(list, pos, dll_create_node_i(value));
}

void dll_pprint_node_i(dll_node_t node) {
  printf("[%d]", dll_node_i_value(node));
}

void dll_pprint_list_i(dll_t list) {
  _dll_pprint_list(list, dll_pprint_node_i);
}
