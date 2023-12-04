#ifndef CONT_ARR_H_
#define CONT_ARR_H_

/* (C) Nguyen Ba Ngoc 2021-2023 */

#include <stdlib.h>

struct ainfo {
  void *elems;
  long size;
  long cap;
  long esz;
  double rio;
};

static inline void *acreate_internal(long size, long esz, double rio) {
  long cap = size > 0? size: 8;
  struct ainfo *info = malloc(sizeof(struct ainfo));
  info->elems = malloc(cap * esz);
  info->size = size;
  info->cap = cap;
  info->esz = esz;
  info->rio = rio;
  return &info->elems;
}

/* Mặc định rio = 2 */
#define acreate(elemtype, size) \
   acreate_internal(size, sizeof(elemtype), 2.0)

#define adecl(elemtype, name) elemtype **name
#define amake(elemtype, name, size) \
   adecl(elemtype, name) = acreate(elemtype, size)

#define ainfo(a) ((struct ainfo *)(a))
#define asize(a) (ainfo(a)->size)
#define acap(a) (ainfo(a)->cap)
#define aesz(a) (ainfo(a)->esz)
#define ario(a) (ainfo(a)->rio)
#define aarr(a) (*(a))
#define aelem(a, i) aarr(a)[i]

#define areserve(a, newcap) \
  do { \
    if ((newcap) < asize(a)) { \
      break; \
    } \
    struct ainfo *_info = ainfo(a); \
    _info->elems = realloc(_info->elems, (newcap) * _info->esz); \
    _info->cap = (newcap); \
    *(a) = _info->elems; \
  } while (0)

#define aresize(a, newsize) \
  do { \
    if (newsize > acap(a)) {  \
      areserve((a), newsize); \
    } \
    asize(a) = (newsize); \
  } while (0)

#define afree(a) \
    free(*(a)); \
    free(ainfo(a))

#define aclear(a) \
  do { \
    aresize(a, 0); \
    areserve(a, 8); \
  } while (0)

#define aappend(a, elem) \
   do { \
     struct ainfo *_info = ainfo(a); \
     if (_info->size >= _info->cap) { \
       long _newcap = _info->cap * _info->rio; \
       areserve((a), _newcap); \
       _info = ainfo(a); \
     } \
     (*(a))[_info->size++] = (elem); \
   } while (0)

#define ainsertb(a, elem, pos) \
   do { \
     long _pos = (pos); \
     struct ainfo *_info = ainfo(a); \
     aresize(a, _info->size + 1); \
     _info = ainfo(a); \
     for (long _i = _info->size - 1; _i > _pos; --_i) { \
        aelem(a, _i) = aelem(a, _i - 1); \
     } \
     aelem(a, _pos) = elem; \
     printf("pos: %ld\n", _pos); \
   } while (0)

#define aqsort(a, cmp) \
   qsort(*(a), asize(a), aesz(a), cmp)

/**
 * Duyệt tuần tự từng phần tử của mảng a,
 * typeof ban đầu là 1 từ khóa trong mở rộng của GNU,
 * và đến nay đã chính thức trở thành 1 từ khóa của ISO C kể từ C23
 */
#define afor(i, a) \
  for (long i = 0; i < asize(a); ++i)

#define aremove(a, idx) \
    do { \
      if (asize(a) == 0) { \
        break; \
      } \
      for (long _i = (idx); _i < asize(a) - 1; ++_i) { \
        aelem(a, _i) = aelem(a, _i + 1); \
      } \
      --asize(a); \
    } while (0)
#define apush(a, elem) aappend(a, elem)
#define atop(a) aelem(a, asize(a) - 1)
#define apop(a) \
  do { \
    struct ainfo *_info = ainfo(a); \
    aremove(a, _info->size - 1); \
    if (_info->cap / (_info->size + 1) > 8) { \
      areserve(a, _info->size + 8); \
    } \
  } while (0)
#define aenque(a, elem) aappend(a, elem)
#define apeek(a, head) aelem(a, head)
#define adeque(a, head) \
    do { \
      struct ainfo *_info = ainfo(a); \
      if (head >= _info->size) { \
        break; \
      } \
      ++head; \
      if (head / (_info->cap - head + 1) > 8) { \
        for (long _i = head; _i < _info->size; ++_i) { \
          aelem(a, _i - head) = aelem(a, _i); \
        } \
        aresize(a, _info->size - head); \
        areserve(a, _info->size + 8); \
        head = 0; \
      } \
    } while (0)

#endif  // CONT_ARR_H_
