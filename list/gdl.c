/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gdl.h"

struct gdn *gdl_create_node(gtype value) {
  struct dln *tmp = dll_create_node();
  struct gdn *nn = realloc(tmp, sizeof(struct gdn));
  nn->value = value;
  return nn;
}

struct gdl *gdl_create_list(gtype_free_t free_value) {
  struct dll *tmp = dll_create_list();
  struct gdl *list = realloc(tmp, sizeof(struct gdl));
  list->free_value = free_value;
  return list;
}

long gdl_size(struct gdl *list) {
  long cc = 0;
  gdl_traverse(cur, list) {
    ++cc;
  }
  return cc;
}

void gtype_free_gdl(gtype value) {
  gdl_free(value.gdl);
}

void gdl_pprint(struct gdl *list, gtype_print_t pp) {
  gdl_traverse(cur, list) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}