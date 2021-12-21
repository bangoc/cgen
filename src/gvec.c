/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gvec.h"

gvec_t gvec_create(int cap, gtype_free_t free_value) {
  gvec_t v = malloc(sizeof(struct gvec_s));
  v->arr = arr_create(cap, gtype);
  v->free_value = free_value;
  return v;
}
