/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "dab/gvec.h"

gvec_t gvec_create(int cap, gtype_free_t free_value) {
  gvec_t v = malloc(sizeof(struct gtype_vector));
  if (!v) {
    return NULL;
  }
  v->arr = arr_create(cap, gtype);
  if (!v->arr) {
    free(v);
    return NULL;
  }
  v->free_value = free_value;
  return v;
}

void gtype_free_gvec(gtype value) {
  gvec_free(value.gvec);
}