/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gdl.h"

gdl_t gdl_create(gtype_free_t free_value) {
  gdl_t list = malloc(sizeof(struct gdl_s));
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