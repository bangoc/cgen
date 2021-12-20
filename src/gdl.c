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

void gdn_pprint_i(dln_t n) {
  printf("%ld", gdn_value(n).i);
}

gdl_t gdl_create(gtype_free_t free_value) {
  dll_t tmp = dll_create();
  gdl_t list = realloc(tmp, sizeof(struct gdl_s));
  list->free_value = free_value;
  return list;
}

gdn_t gdl_inserta(gdl_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdn_create(value);
  dll_inserta(to_dll(list), to_dln(pos), to_dln(nn));
  return nn;
}

gdn_t gdl_insertb(gdl_t list, gdn_t pos, gtype value) {
  gdn_t nn = gdn_create(value);
  dll_insertb(to_dll(list), to_dln(pos), to_dln(nn));
  return nn;
}
