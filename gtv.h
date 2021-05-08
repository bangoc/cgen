/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef VV_H_
#define VV_H_

#include "gtype.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef gtype *vector_t;

static vector_t gtv_create() {
  return (vector_t)&((size_t*)calloc(2, sizeof(size_t)))[2];
}

static size_t gtv_capacity(vector_t const v) {
  return ((v) ? ((size_t *)(v))[-1] : (size_t)0);
}

static size_t gtv_size(vector_t const v) {
  return ((v) ? ((size_t *)(v))[-2] : (size_t)0);
}

static int gtv_grow(vector_t *v, size_t newcapacity) {
  size_t capacity = gtv_capacity(*v);
  if (capacity < newcapacity) {
    const size_t __sz = newcapacity * sizeof(gtype) + 2 * sizeof(size_t);
    size_t *__p1 = &((size_t *)(*v))[-2];
    size_t *__p2 = (size_t *)realloc(__p1, (__sz));
    assert(__p2);
    if (!__p2) {
      return 1;
    }
    (*v) = (vector_t)(&__p2[2]);
    __p2[1] = newcapacity;
  }
  return 0;
}

static int gtv_push_back(vector_t *v, gtype value) {
  size_t __cap = gtv_capacity(*v);
  if (__cap <= gtv_size(*v)) {
    gtv_grow(v, !__cap ? __cap + 1 : __cap * 2);
  }
  vector_t vec = *v;
  vec[gtv_size(vec)] = value;
  ((size_t*)vec)[-2] += 1;
  return 0;
}

static void gtv_free(vector_t *v) {
  void *p = &(((size_t*)(*v))[-2]);
  free(p);
}

#endif  // VV_H_