#ifndef GVEC_H_
#define GVEC_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype vector
*/

#include "base/arr.h"
#include "base/gtype.h"

typedef struct gvec_s {
  arr_t(gtype) arr;
  gtype_free_t free_value;
} *gvec_t;

#define gvec_size(v) (arr_size((v)->arr))
#define gvec_capacity(v) (arr_capacity((v)->arr))
#define gvec_arr(v) (ARR(v->arr))
#define gvec_elem(v, i) ((gvec_arr(v))[i])

#define gvec_append(v, val) \
  do { \
    int old_sz = gvec_size(v); \
    arr_append(v->arr, val); \
  } while (0)

#define gvec_remove(v, idx) \
  do { \
    gtype *arr = ARR(v->arr); \
    int sz = arr_size(v->arr); \
    if (idx >= sz || idx < 0) { \
      break; \
    } \
    if (v->free_value) { \
      v->free_value(arr[idx]); \
    } \
    for (int i = idx; i < sz - 1; ++i) { \
      arr[i] = arr[i + 1]; \
    } \
    arr_set_size(v->arr, sz - 1); \
  } while (0)

#define gvec_set_capacity(v, cap) \
  do { \
    int sz = arr_size(v->arr); \
    if (cap < sz) { \
      break; \
    } \
    arr_set_capacity(v->arr, cap); \
  }

#define gvec_free(v) \
  do{ \
    if (v->free_value) { \
      int sz = arr_size(v->arr); \
      gtype *arr = ARR(v->arr); \
      for (int i = 0; i < sz; ++i) { \
        v->free_value(arr[i]); \
      } \
    } \
    arr_free(v->arr); \
    free(v); \
  } while (0)

#define gvec_qsort(v, cmp) \
  qsort(ARR(v->arr), gvec_size(v), sizeof(gtype), cmp)

gvec_t gvec_create(int cap, gtype_free_t free_value);

#endif  // GVEC_H_