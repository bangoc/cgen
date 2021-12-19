/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gdl.h"

gdn_t gdn_create(gtype value) {
  gdn_t nn = malloc(sizeof(struct gdn_s));
  nn->base.prev = nn->base.next = NULL;
  nn->value = value;
  return nn;
}

gdl_t gdl_create(gtype_free_t free_value) {
  dll_t tmp = dll_create_list();
  gdl_t list = realloc(tmp, sizeof(struct gdl_s));
  list->free_value = free_value;
  return list;
}

void gdl_push_back(gdl_t list, gtype value) {
  dll_push_back(to_dll_list(list), to_dll_node(gdn_create(value)));
}

void gdl_push_front(gdl_t list, gtype value) {
  dll_push_front(to_dll_list(list), to_dll_node(gdn_create(value)));
}

void gdl_pop_front(gdl_t list) {
  if (list->free_value) {
    list->free_value(gdl_front(list));
  }
  dll_pop_front(list);
}

void gdl_pop_back(gdl_t list) {
  if (list->free_value) {
    list->free_value(gdl_back(list));
  }
  dll_pop_back(list);
}

gtype gdl_front(gdl_t list) {
  return gdl_front_node(list)->value;
}

gtype gdl_back(gdl_t list) {
  return gdl_back_node(list)->value;
}

gdn_t gdl_front_node(gdl_t list) {
  return to_gdn(to_dll_list(list)->front);
}

gdn_t gdl_back_node(gdl_t list) {
  return to_gdn(to_dll_list(list)->back);
}

gdn_t gdl_inserta(gdl_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdn_create(value);
  dll_inserta(to_dll_list(list), to_dll_node(pos), to_dll_node(nn));
  return nn;
}

gdn_t gdl_insertb(gdl_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdn_create(value);
  dll_insertb(to_dll_list(list), to_dll_node(pos), to_dll_node(nn));
  return nn;
}

int gdl_is_empty(gdl_t list) {
  return dll_is_empty(to_dll_list(list));
}

void gdl_free(gdl_t list) {
  while (!gdl_is_empty(list)) {
    gdl_pop_front(list);
  }
  free(list);
}