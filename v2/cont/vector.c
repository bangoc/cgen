/* (C) Nguyen Ba Ngoc 2021 */

#include "cont/vector.h"

struct vector *vcreate1(long n) {
  struct vector *v = malloc(sizeof(struct vector));
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

struct vector *vcreate2(long n, gtype_free_t fv) {
  struct vector *base = vcreate1(n);
  if (base) {
    base->fv = fv;
  }
  return base;
}

struct vector *vclone(struct vector *v) {
  struct vector *v2 = malloc(sizeof(struct vector));
  memcpy(v2, v, sizeof(struct vector));
  if (v->cap == 0) {
    v2->elems = NULL;
    return v2;
  }
  size_t elems_size = v2->cap * sizeof(gtype);
  v2->elems = malloc(elems_size);
  memcpy(v2->elems, v->elems, elems_size);
  return v2;
}

int vsameas(struct vector *v1, struct vector *v2) {
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

void gfree_vec(gtype *value) {
  vfree(value->vec);
}

void vpprint(struct vector *v, gtype_print_t pp) {
  vtraverse(cur, v) {
    pp(cur);
  }
}
