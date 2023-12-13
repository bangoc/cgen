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
    destructor_fnt fv; \
  }

#define VARR(v) ((v)->elems)
#define VELEM(v, i) (VARR(v)[(i)])
#define VIDXOF(pe, v) ((pe) - VARR(v))
#define VRIO(v) ((v)->rio)
#define VFV(v) ((v)->fv)
#define VSIZE(v) ((const long)((v)->size))
#define VCAP(v) ((const long)(v)->cap)
#define VLASTIDX(v) (VSIZE(v) - 1)
#define VEMPTY(v) (VSIZE(v) == 0)
#define VSORT(v, cmp) qsort(v->elems, v->size, sizeof(v->elems[0]), cmp)
#define VCONSTRUCT(vecname, objname, size) \
  struct vecname *objname = VMATCH((struct vecname *)NULL, create)(size)
#define VRESERVE(v, ...) VMATCH(v, reserve)(v, __VA_ARGS__)
#define VRESIZE(v, ...) VMATCH(v, resize)(v, __VA_ARGS__)
#define VAPPEND(v, ...) VMATCH(v, append)(v, __VA_ARGS__)
#define VREMOVE(v, ...) VMATCH(v, remove)(v, __VA_ARGS__)
#define VINSERTB(v, ...) VMATCH(v, insertb)(v, __VA_ARGS__)
#define VCLEAR(v) VMATCH(v, clear)(v)
#define VFREE(v) VMATCH(v, free)(v)
#define VFILL(v, ...) VMATCH(v, fill)(v, __VA_ARGS__)
#define VPUSH(v, ...) VMATCH(v, push)(v, __VA_ARGS__)
#define VPOP(v) VMATCH(v, pop)(v)
#define VTOP(v) VMATCH(v, top)(v)
#define VENQUE(v, ...) VMATCH(v, enque)(v, __VA_ARGS__)
#define VPEEK(v) VMATCH(v, peek)(v)
#define VDEQUE(v, ...) VMATCH(v, deque)(v, __VA_ARGS__)

#define VFOR(i, v) \
  for (long i = 0; i < VSIZE(v); ++i)

#define VRFOR(i, v) \
  for (long i = VLASTIDX(v); i >= 0; --i)

#define VDECL(vecname, elemtype, prefix) \
VDEFN(vecname, elemtype); \
struct vecname *prefix##create(long sz); \
struct vecname *prefix##reserve(struct vecname *v, long newcap); \
struct vecname *prefix##resize(struct vecname *v, long newsz); \
struct vecname *prefix##append(struct vecname *v, elemtype val); \
struct vecname *prefix##remove(struct vecname *v, long idx); \
struct vecname *prefix##insertb(struct vecname *v, elemtype elem, long pos); \
struct vecname *prefix##clear(struct vecname *v); \
void prefix##free(void *po); \
struct vecname *prefix##fill(struct vecname *v, elemtype value); \
struct vecname *prefix##push(struct vecname *v, elemtype elem); \
struct vecname *prefix##pop(struct vecname *v); \
elemtype *prefix##top(struct vecname *v); \
struct vecname *prefix##enque(struct vecname *v, elemtype elem); \
elemtype *prefix##peek(struct vecname *v, long *head); \
struct vecname *prefix##deque(struct vecname *v, long *head)

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
      v->fv(v->elems + j_); \
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
 for (long i = VLASTIDX(v); i > pos; --i) { \
   arr[i] = arr[i - 1]; \
 } \
 arr[pos] = elem; \
 return v; \
} \
struct vecname *prefix##clear(struct vecname *v) { \
  return prefix##resize(v, 0); \
} \
void prefix##free(void *po) { \
  struct vecname *v = po; \
  prefix##resize(v, 0); \
  free(v->elems); \
  free(v); \
} \
struct vecname *prefix##fill(struct vecname *v, elemtype value) { \
  VFOR(i, v) {\
    v->elems[i] = value; \
  } \
  return v; \
} \
struct vecname *prefix##push(struct vecname *v, elemtype elem) { \
  return prefix##append(v, elem); \
}\
struct vecname *prefix##pop(struct vecname *v) { \
  return prefix##remove(v, VLASTIDX(v)); \
} \
elemtype *prefix##top(struct vecname *v) { \
  return v->elems + (VLASTIDX(v)); \
} \
struct vecname *prefix##enque(struct vecname *v, elemtype elem) { \
  return prefix##append(v, elem); \
} \
elemtype *prefix##peek(struct vecname *v, long *head) { \
  return v->elems + *head; \
} \
struct vecname *prefix##deque(struct vecname *v, long *head) {\
  long h = *head; \
  if (h >= v->size) { \
    return NULL; \
  } \
  if (v->fv) {\
    v->fv(v->elems + h); \
  } \
  ++h; \
  if (h / (v->cap - h + 1) > 8) { \
    elemtype *a = v->elems; \
    for (long i = h; i < v->size; ++i) { \
      a[i - h] = a[i]; \
    } \
    v->size -= h; \
    prefix##reserve(v, v->size + 8); \
    h = 0; \
  } \
  *head = h; \
  return v; \
}

#endif  // CONT_VECTOR_H_