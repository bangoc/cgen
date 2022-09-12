/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gdl.h"

gdn_t gdl_create_node(gtype value) {
  dln_t tmp = dll_create_node();
  gdn_t nn = realloc(tmp, sizeof(struct gtype_double_linked_node));
  nn->value = value;
  return nn;
}

gdl_t gdl_create_list(gtype_free_t free_value) {
  dll_t tmp = dll_create_list();
  gdl_t list = realloc(tmp, sizeof(struct gtype_double_linked));
  list->free_value = free_value;
  return list;
}

long gdl_size(gdl_t list) {
  long cc = 0;
  gdl_traverse(cur, list) {
    ++cc;
  }
  return cc;
}

void gtype_free_gdl(gtype value) {
  gdl_free(value.gdl);
}

void gdl_pprint(gdl_t list, gtype_print_t pp) {
  gdl_traverse(cur, list) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}