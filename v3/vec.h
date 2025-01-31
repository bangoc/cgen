/* (C) Nguyễn Bá Ngọc 2024 */

#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

#define VECT_DECL(vname, elem_t) \
\
struct vname; \
struct vname *vname(int n); \
struct vname *vname##_reserve(struct vname *v, int newcap); \
struct vname *vname##_resize(struct vname *v, int newsize); \
struct vname *vname##_append(struct vname *v, elem_t elem); \
struct vname *vname##_ins(struct vname *v, int idx, elem_t elem); \
int vname##_del(struct vname *v, int idx); \
elem_t *vname##_at(struct vname *v, int idx); \
void vname##_free(struct vname *v);

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
struct vname *vname##_reserve(struct vname *v, int newcap) { \
  if (newcap <= v->size) { \
    return v; \
  } \
  v->elems = realloc(v->elems, newcap * sizeof(elem_t)); \
  if (v->cap < newcap) { \
    memset(v->elems + v->cap, 0, sizeof(elem_t) * (newcap - v->cap)); \
  } \
  v->cap = newcap; \
  return v; \
} \
struct vname *vname##_resize(struct vname *v, int newsize) { \
  if (newsize > v->cap) { \
    vname##_reserve(v, newsize); \
  } \
  v->size = newsize; \
  return v; \
} \
struct vname *vname##_append(struct vname *v, elem_t value) { \
  if (v->size == v->cap) { \
    vname##_reserve(v, v->cap == 0? 16: 2 * v->cap); \
  } \
  v->elems[v->size] = value; \
  ++v->size; \
  return v; \
} \
struct vname *vname##_ins(struct vname *v, int idx, elem_t elem) { \
  if (idx < 0 || idx > v->size) { \
    return v; \
  } \
  if (idx == v->size) { \
    vname##_append(v, elem); \
    return v; \
  } \
  if (v->size == v->cap) { \
    vname##_reserve(v, v->cap == 0? 16: 2 * v->cap); \
  } \
  for (int i = v->size; i > idx; --i) { \
    v->elems[i] = v->elems[i - 1]; \
  } \
  ++v->size; \
  v->elems[idx] = elem; \
  return v; \
} \
int vname##_del(struct vname *v, int idx) { \
  if (idx < 0 || idx >= v->size) { \
    return 0; \
  } \
  for (int i = idx; i < v->size - 1; ++i) { \
    v->elems[i] = v->elems[i + 1]; \
  } \
  --v->size; \
  if (v->size > 8 && v->cap > v->size * 2) { \
    vname##_reserve(v, v->size * 1.33); \
  } \
  return 1; \
} \
elem_t *vname##_at(struct vname *v, int idx) { \
  if (!v || idx < 0 || idx >= v->size) { \
    return NULL; \
  } \
  return v->elems + idx; \
}\
void vname##_free(struct vname *v) { \
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