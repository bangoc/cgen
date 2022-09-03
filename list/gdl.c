/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gdl.h"

gdl_t gdl_create(gtype_free_t free_value) {
  gdl_t list = malloc(sizeof(struct gtype_double_linked));
  list->front = list->back = NULL;
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