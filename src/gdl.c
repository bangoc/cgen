/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gdl.h"

gdn_t gdl_create_node(gtype value) {
  gdn_t nn = malloc(sizeof(struct gdl_node_s));
  nn->base.prev = nn->base.next = NULL;
  nn->value = value;
  return nn;
}

void gdl_push_back(dll_t list, gtype value) {
  dll_push_back(list, to_dll_node(gdl_create_node(value)));
}

void gdl_push_front(dll_t list, gtype value) {
  dll_push_front(list, to_dll_node(gdl_create_node(value)));
}

gtype gdl_pop_front(dll_t list) {
  gtype tmp = gdl_front(list);
  dll_pop_front(list);
  return tmp;
}

gtype gdl_pop_back(dll_t list) {
  gtype tmp = gdl_back(list);
  dll_pop_back(list);
  return tmp;
}

gtype gdl_front(dll_t list) {
  return gdn_value(list->front);
}

gtype gdl_back(dll_t list) {
  return gdn_value(list->back);
}

gdn_t gdl_inserta(dll_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdl_create_node(value);
  dll_inserta(list, to_dll_node(pos), to_dll_node(nn));
  return nn;
}

gdn_t gdl_insertb(dll_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdl_create_node(value);
  dll_insertb(list, to_dll_node(pos), to_dll_node(nn));
  return nn;
}
