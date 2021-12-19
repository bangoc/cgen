/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gdl.h"

dll_node_t dll_create_node_g(gtype value) {
  dll_node_g_t nn = malloc(sizeof(struct dll_node_g_s));
  nn->base.prev = nn->base.next = NULL;
  nn->value = value;
  return to_dll(nn);
}

void dll_push_back_g(dll_t list, gtype value) {
  dll_push_back(list, dll_create_node_g(value));
}

void dll_push_front_g(dll_t list, gtype value) {
  dll_push_front(list, dll_create_node_g(value));
}

gtype dll_pop_front_g(dll_t list) {
  gtype tmp = dll_front_g(list);
  dll_pop_front(list);
  return tmp;
}

gtype dll_pop_back_g(dll_t list) {
  gtype tmp = dll_back_g(list);
  dll_pop_back(list);
  return tmp;
}

gtype dll_front_g(dll_t list) {
  return dll_node_g_value(list->front);
}

gtype dll_back_g(dll_t list) {
  return dll_node_g_value(list->back);
}

dll_node_t dll_inserta_g(dll_t list, dll_node_t pos, gtype value) {
  dll_node_t nn = dll_create_node_g(value);
  dll_inserta(list, pos, nn);
  return nn;
}

dll_node_t dll_insertb_g(dll_t list, dll_node_t pos, gtype value) {
  dll_node_t nn = dll_create_node_g(value);
  dll_insertb(list, pos, nn);
  return nn;
}