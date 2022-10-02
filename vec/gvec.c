/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/gvec.h"

struct gvector *gvec_create(long n, gtype_free_t free_value) {
  struct gvector *v = malloc(sizeof(struct gvector));
  v->free_value = free_value;
  v->sz = n;
  v->cap = n;

  /* Mặc định x 2 dung lượng */
  v->scale = 2.0;
  if (n == 0) {
    v->elems = NULL;
    return v;
  }
  v->elems = calloc(n, sizeof(gtype));
  return v;
}

struct gvector *gvec_create_full(long size, long cap, gtype value,
      gtype_free_t free_value) {
  if (size > cap) {
    return NULL;
  }
  struct gvector *v = gvec_create(size, free_value);
  if (cap > size) {
    gvec_reserve(v, cap);
  }
  gvec_fill(v, value);
  return v;
}

struct gvector *gvec_clone(struct gvector *v) {
  struct gvector *v2 = malloc(sizeof(struct gvector));
  memcpy(v2, v, sizeof(struct gvector));
  if (v->cap == 0) {
    v2->elems = NULL;
    return v2;
  }
  size_t elems_size = v2->cap * sizeof(gtype);
  v2->elems = malloc(elems_size);
  memcpy(v2->elems, v->elems, elems_size);
  return v2;
}

int gvec_identical(struct gvector *v1, struct gvector *v2) {
  if (v1->sz != v2->sz || v1->cap != v2->cap) {
    return 0;
  }
  size_t elems_size = v1->cap * sizeof(gtype);
  char *p = (char *)(v1->elems),
       *q = (char *)(v2->elems);
  for (size_t i = 0; i < elems_size; ++i) {
    if (p[i] != q[i]) {
      return 0;
    }
  }
  return 1;
}

void gtype_free_gvec(gtype value) {
  gvec_free(value.gvec);
}

void gvec_pprint(struct gvector *v, gtype_print_t pp) {
  gvec_traverse(cur, v) {
    pp(*cur);
  }
}

struct gvector *gvec_rand_l(long n) {
  struct gvector *v = gvec_create(n, NULL);
  gvec_traverse(cur, v) {
    cur->l = rand();
  }
  return v;
}
