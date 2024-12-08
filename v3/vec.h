#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

/* (C) Nguyễn Bá Ngọc 2024 */
#define VEC_DECL(pre, elem_t) \
\
struct pre##vector; \
struct pre##vector *pre##vector(int n); \
int pre##vec_reserve(struct pre##vector *v, int new_cap); \
void pre##vec_append(struct pre##vector *v, elem_t elem); \
elem_t pre##vec_rem(struct pre##vector *v, int idx); \
void pre##vec_put(struct pre##vector *v, elem_t elem, int idx); \
void pre##vec_resize(struct pre##vector *v, int new_sz); \
void pre##vec_del(struct pre##vector *v);

#define VEC_IMPL(pre, elem_t) \
struct pre##vector { \
  int sz; \
  int cap; \
  elem_t *elems; \
}; \
struct pre##vector *pre##vector(int n) {  \
  struct pre##vector *v = malloc(sizeof(struct pre##vector)); \
  v->sz = n; \
  v->cap = v->sz > 0? v->sz: 8; \
  v->elems = calloc(v->cap, sizeof(elem_t)); \
  return v; \
} \
elem_t pre##vec_rem(struct pre##vector *v, int idx) { \
  elem_t tmp = v->elems[idx]; \
  for (int i = idx; i < v->sz - 1; ++i) { \
    v->elems[i] = v->elems[i + 1]; \
  } \
  --v->sz; \
  if (v->sz > 8 && v->cap > v->sz * 2) { \
    pre##vec_reserve(v, v->sz * 1.33); \
  } \
  return tmp; \
} \
void pre##vec_put(struct pre##vector *v, elem_t elem, int idx) { \
  pre##vec_append(v, elem); \
  for (int i = v->sz; i > idx; --i) { \
    v->elems[i] = v->elems[i - 1]; \
  } \
  v->elems[idx] = elem; \
} \
int pre##vec_reserve(struct pre##vector *v, int newcap) { \
  if (newcap <= v->sz) { \
    return 1; \
  } \
  v->elems = realloc(v->elems, newcap * sizeof(elem_t)); \
  if (v->cap < newcap) { \
    memset(v->elems + v->cap, 0, sizeof(elem_t) * (newcap - v->cap)); \
  } \
  v->cap = newcap; \
  return 0; \
} \
void pre##vec_append(struct pre##vector *v, elem_t value) { \
  if (v->cap == 0) { \
    pre##vec_reserve(v, 16); \
  } else if (v->sz == v->cap) { \
    pre##vec_reserve(v, 2 * v->cap); \
  } \
  v->elems[v->sz] = value; \
  ++v->sz; \
} \
void pre##vec_resize(struct pre##vector *v, int newsize) { \
  if (newsize > v->cap) { \
    pre##vec_reserve(v, newsize); \
  } \
  v->sz = newsize; \
} \
void pre##vec_del(struct pre##vector *v) { \
  if (!v) { \
    return; \
  } \
  free(v->elems); \
  free(v); \
}

#define VEC_DECL_IMPL(pre, elem_t) \
VEC_DECL(pre, elem_t) \
VEC_IMPL(pre, elem_t)

#endif  // VEC_H_