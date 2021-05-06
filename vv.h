/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef VV_H_
#define VV_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *vptr;
typedef vptr *vptr_vec_t;

static vptr_vec_t vv_create() {
  return (vptr_vec_t)&((size_t*)calloc(2, sizeof(size_t)))[2];
}


static size_t vv_capacity(vptr_vec_t const v) {
  return ((v) ? ((size_t *)(v))[-1] : (size_t)0);
}

static size_t vv_size(vptr_vec_t const v) {
  return ((v) ? ((size_t *)(v))[-2] : (size_t)0);
}

static int vv_grow(vptr_vec_t *v, size_t newcapacity) {
  size_t capacity = vv_capacity(*v);
  if (capacity < newcapacity) {
    const size_t __sz = newcapacity * sizeof(vptr) + 2 * sizeof(size_t);
    size_t *__p1 = &((size_t *)(*v))[-2];
    size_t *__p2 = (size_t *)realloc(__p1, (__sz));
    assert(__p2);
    if (!__p2) {
      return 1;
    }
    (*v) = (vptr_vec_t)(&__p2[2]);
    __p2[1] = newcapacity;
  }
  return 0;
}

static int vv_push_back(vptr_vec_t *v, vptr value) {
  size_t __cap = vv_capacity(*v);
  if (__cap <= vv_size(*v)) {
    vv_grow(v, !__cap ? __cap + 1 : __cap * 2);
  }
  vptr_vec_t vec = *v;
  vec[vv_size(vec)] = value;
  ((size_t*)vec)[-2] += 1;
  return 0;
}

#endif  // VV_H_