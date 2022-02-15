/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gvec.h"

gvec_t gvec_create(int cap, gtype_free_t free_value) {
  gvec_t v = malloc(sizeof(struct gvec_s));
  if (!v) {
    return NULL_PTR;
  }
  v->arr = arr_create(cap, gtype);
  if (!v->arr) {
    free(v);
    return NULL_PTR;
  }
  v->free_value = free_value;
  return v;
}

void gtype_free_gvec(gtype value) {
  gvec_free(value.gvec);
}