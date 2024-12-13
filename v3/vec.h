#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

/* (C) Nguyễn Bá Ngọc 2024 */
#define VECT_DECL(vname, elem_t) \
\
struct vname; \
struct vname *vname(int n); \
int vname##_reserve(struct vname *v, int new_cap); \
void vname##_append(struct vname *v, elem_t elem); \
elem_t vname##_rem(struct vname *v, int idx); \
void vname##_put(struct vname *v, elem_t elem, int idx); \
void vname##_resize(struct vname *v, int new_sz); \
void vname##_del(struct vname *v);

#define VECT_IMPL(vname, elem_t) \
struct vname { \
  int size; \
  int cap; \
  elem_t *elems; \
}; \
struct vname *vname(int n) {  \
  struct vname *v = malloc(sizeof(struct vname)); \
  v->size = n; \
  v->cap = v->size > 0? v->size: 8; \
  v->elems = calloc(v->cap, sizeof(elem_t)); \
  return v; \
} \
elem_t vname##_rem(struct vname *v, int idx) { \
  elem_t tmp = v->elems[idx]; \
  for (int i = idx; i < v->size - 1; ++i) { \
    v->elems[i] = v->elems[i + 1]; \
  } \
  --v->size; \
  if (v->size > 8 && v->cap > v->size * 2) { \
    vname##_reserve(v, v->size * 1.33); \
  } \
  return tmp; \
} \
void vname##_put(struct vname *v, elem_t elem, int idx) { \
  vname##_append(v, elem); \
  for (int i = v->size; i > idx; --i) { \
    v->elems[i] = v->elems[i - 1]; \
  } \
  v->elems[idx] = elem; \
} \
int vname##_reserve(struct vname *v, int newcap) { \
  if (newcap <= v->size) { \
    return 1; \
  } \
  v->elems = realloc(v->elems, newcap * sizeof(elem_t)); \
  if (v->cap < newcap) { \
    memset(v->elems + v->cap, 0, sizeof(elem_t) * (newcap - v->cap)); \
  } \
  v->cap = newcap; \
  return 0; \
} \
void vname##_append(struct vname *v, elem_t value) { \
  if (v->cap == 0) { \
    vname##_reserve(v, 16); \
  } else if (v->size == v->cap) { \
    vname##_reserve(v, 2 * v->cap); \
  } \
  v->elems[v->size] = value; \
  ++v->size; \
} \
void vname##_resize(struct vname *v, int newsize) { \
  if (newsize > v->cap) { \
    vname##_reserve(v, newsize); \
  } \
  v->size = newsize; \
} \
void vname##_del(struct vname *v) { \
  if (!v) { \
    return; \
  } \
  free(v->elems); \
  free(v); \
}

#define VECT_DECL_IMPL(pre, elem_t) \
VECT_DECL(pre, elem_t) \
VECT_IMPL(pre, elem_t)

#endif  // VEC_H_