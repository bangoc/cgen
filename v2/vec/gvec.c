/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/gvec.h"

struct gvector *gvec_create1(long n) {
  struct gvector *v = malloc(sizeof(struct gvector));
  v->fv = NULL;
  if (n <= 0) {
    // Lỗi hàm gọi
    v->sz = 0;
    v->cap = 8;
  } else {
    v->sz = n;
    v->cap = n;
  }

  /* Mặc định x 2 dung lượng mỗi lần tăng kích thước*/
  v->k = 2.0;
  v->elems = calloc(v->cap, sizeof(gtype));
  return v;
}

struct gvector *gvec_create2(long n, gtype_free_t fv) {
  struct gvector *base = gvec_create1(n);
  if (base) {
    base->fv = fv;
  }
  return base;
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
