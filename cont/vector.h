/* (C) Nguyễn Bá Ngọc 2023 */
#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_

#include "base/core.h"

#define VDEFN(vecname, elemtype) \
  struct vecname { \
    elemtype *elems; \
    long size; \
    long cap; \
    double rio; \
    void (*fv)(elemtype); \
  }

#define VDECL(vecname, elemtype, prefix) \
VDEFN(vecname, elemtype); \
struct vecname *prefix##create(long sz); \
struct vecname *vecname(long sz); \
struct vecname *prefix##clear(struct vecname *v); \
void prefix##free(struct vecname *po); \
int prefix##empty(struct vecname *v); \
struct vecname *prefix##reserve(struct vecname *v, long newcap); \
struct vecname *prefix##resize(struct vecname *v, long newsz); \
struct vecname *prefix##append(struct vecname *v, elemtype val); \
struct vecname *prefix##remove(struct vecname *v, long idx); \
struct vecname *prefix##insertb(struct vecname *v, elemtype elem, long pos); \
struct vecname *prefix##fill(struct vecname *v, elemtype value); \
struct vecname *prefix##push(struct vecname *v, elemtype elem); \
struct vecname *prefix##pop(struct vecname *v); \
elemtype *prefix##top(struct vecname *v)

#define VIMPL(vecname, elemtype, prefix) \
struct vecname *prefix##create(long sz) { \
  if (sz < 0) { \
    FLOG("Tạo vec-tơ với kích thước không hợp lệ, sz = %ld", sz); \
    return NULL; \
  } \
  struct vecname *v = malloc(sizeof(struct vecname)); \
  v->fv = NULL; \
  v->size = sz; \
  v->cap = sz > 0? sz: 8; \
  v->rio = 2.0; \
  v->elems = calloc(v->cap, sizeof(elemtype)); \
  return v; \
} \
struct vecname *vecname(long sz) { \
  return prefix##create(sz); \
} \
struct vecname *prefix##clear(struct vecname *v) { \
  return prefix##resize(v, 0); \
} \
void prefix##free(struct vecname *v) { \
  prefix##clear(v); \
  free(v->elems); \
  free(v); \
} \
int prefix##empty(struct vecname *v) { \
  return v->size == 0; \
} \
struct vecname *prefix##reserve(struct vecname *v, long newcap) {\
  if (newcap < v->size) { \
    FLOG("Dự trữ với dung lượng (%ld) < kích thước (%ld)", newcap, v->size); \
    return NULL; \
  } \
  v->elems = realloc(v->elems, newcap * sizeof(elemtype)); \
  v->cap = newcap; \
  return v; \
} \
struct vecname *prefix##resize(struct vecname *v, long newsize) {\
  if (newsize > v->cap) { \
    prefix##reserve(v, newsize); \
  } else if (newsize < v->size && v->fv) { \
    for (long j_ = newsize; j_ < v->size; ++j_) { \
      v->fv(v->elems[j_]); \
    } \
  } \
  v->size = newsize; \
  return v; \
} \
struct vecname *prefix##append(struct vecname *v, elemtype val) {\
  if (v->size == v->cap) { \
    prefix##reserve(v, v->rio * v->size); \
  } \
  v->elems[v->size] = val; \
  ++v->size; \
  return v; \
} \
struct vecname *prefix##remove(struct vecname *v, long idx) { \
  long sz = v->size; \
  if (idx >= sz || idx < 0) { \
    FLOG("Xóa phần tử với chỉ số không hợp lệ sz = %ld, idx = %ld", sz, idx); \
    return NULL; \
  } \
  elemtype *arr = v->elems; \
  elemtype tmp = arr[idx]; \
  for (long i = idx; i < sz - 1; ++i) { \
    arr[i] = arr[i + 1]; \
  } \
  arr[sz - 1] = tmp; \
  return prefix##resize(v, sz - 1); \
}\
struct vecname *prefix##insertb(struct vecname *v, elemtype elem, long pos) { \
 prefix##resize(v, v->size + 1); \
 elemtype *arr = v->elems; \
 for (long i = v->size - 1; i > pos; --i) { \
   arr[i] = arr[i - 1]; \
 } \
 arr[pos] = elem; \
 return v; \
} \
struct vecname *prefix##fill(struct vecname *v, elemtype value) { \
  for (long i = 0; i < v->size; ++i) {\
    v->elems[i] = value; \
  } \
  return v; \
} \
struct vecname *prefix##push(struct vecname *v, elemtype elem) { \
  return prefix##append(v, elem); \
}\
struct vecname *prefix##pop(struct vecname *v) { \
  return prefix##remove(v, v->size - 1); \
} \
elemtype *prefix##top(struct vecname *v) { \
  return v->elems + (v->size - 1); \
}

#define VDECL_IMPL(vecname, elemtype, prefix) \
VDECL(vecname, elemtype, prefix); \
VIMPL(vecname, elemtype, prefix)

#endif  // CONT_VECTOR_H_
