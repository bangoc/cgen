#ifndef VEC_ARR_H_
#define VEC_ARR_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include <stdlib.h>

#define arr_ptr(elemtype) elemtype *

struct arr_info {
  long size;
  long cap;
  long esz;
  double scale;
};

static inline void *arr_create_internal(long n, long elem_size, double scale) {
  struct arr_info *info = malloc(sizeof(struct arr_info) + n * elem_size);
  info->size = n;
  info->cap = n;
  info->esz = elem_size;
  info->scale = scale;
  return (void*)(info + 1);
}

#define arr_info(a) ((struct arr_info *)((void*)(a) - sizeof(struct arr_info)))
#define arr_size(a) (arr_info(a)->size)
#define arr_capacity(a) (arr_info(a)->cap)
#define arr_elemsize(a) (arr_info(a)->esz)
#define arr_scale(a) (arr_info(a)->scale)

/* Mặc định scale = 2 */
#define arr_create(count, elemtype) \
   (arr_ptr(elemtype))arr_create_internal(count, sizeof(elemtype), 2.0)

#define arr_make(name, count, elemtype) \
   arr_ptr(elemtype) name = arr_create(count, elemtype)

#define arr_reserve(a, newcap) \
  do { \
    if ((newcap) < arr_size(a)) { \
      break; \
    } \
    struct arr_info *_info = \
      realloc(arr_info(a), sizeof(struct arr_info) + (newcap) * arr_elemsize(a)); \
    _info->cap = (newcap); \
    (a) = (void*)(_info + 1); \
  } while (0)

#define arr_resize(a, newsize) \
  do { \
    if (newsize > arr_capacity(a)) {  \
      arr_reserve((a), newsize); \
    } \
    arr_size(a) = (newsize); \
  } while (0)

#define arr_free(a) \
    free(arr_info(a)); \

#define arr_clear(a) \
  do { \
    arr_resize(a, 0); \
    arr_reserve(a, 0); \
  } while (0)

#define arr_append(a, elem) \
   do { \
     struct arr_info *_info = arr_info(a); \
     if (_info->size >= _info->cap) { \
       long _newcap = _info->cap < 10? 10: _info->cap * _info->scale; \
       arr_reserve((a), _newcap); \
       _info = arr_info(a); \
     } \
     (a)[_info->size] = (elem); \
     ++(_info->size); \
   } while (0)

#endif  // VEC_ARR_H_
