/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gdl.h"

struct gdlnode *gdl_create_node(gtype value) {
  struct dlnode *tmp = dll_create_node();
  struct gdlnode *nn = realloc(tmp, sizeof(struct gdlnode));
  nn->value = value;
  return nn;
}

struct gdllist *gdl_create_list(gtype_free_t free_value) {
  struct dllist *tmp = dll_create_list();
  struct gdllist *list = realloc(tmp, sizeof(struct gdllist));
  list->free_value = free_value;
  return list;
}

long gdl_size(struct gdllist *list) {
  long cc = 0;
  gdl_traverse(cur, list) {
    ++cc;
  }
  return cc;
}

void gtype_free_gdl(gtype value) {
  gdl_free(value.gdl);
}

void gdl_pprint(struct gdllist *list, gtype_print_t pp) {
  gdl_traverse(cur, list) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}