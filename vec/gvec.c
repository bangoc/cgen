/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/gvec.h"

struct gvector *gvec_create(long n, gtype_free_t free_value) {
  struct gvector *v = malloc(sizeof(struct gvector));
  if (!v) {
    return NULL;
  }
  if (n == 0) {
    v->elems = NULL;
  } else {
    v->elems = malloc(n * sizeof(gtype));
    if (!v->elems) {
      free(v);
      return NULL;
    }
  }
  v->free_value = free_value;
  v->sz = n;
  v->cap = n;
  return v;
}

void gtype_free_gvec(gtype value) {
  gvec_free(value.gvec);
}

void gvec_pprint(struct gvector *v, gtype_print_t pp) {
  gvec_traverse(cur, v) {
    pp(*cur);
  }
}