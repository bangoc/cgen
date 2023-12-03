#ifndef CONT_ARR_H_
#define CONT_ARR_H_

/* (C) Nguyen Ba Ngoc 2021-2023 */

#include <stdlib.h>

struct ainfo {
  long size;
  long cap;
  long esz;
  double rio;
};

static inline void *acreate_internal(long size, long esz, double rio) {
  long cap = size > 0? size: 8;
  struct ainfo *info = malloc(sizeof(struct ainfo) + cap * esz);
  info->size = size;
  info->cap = cap;
  info->esz = esz;
  info->rio = rio;
  void **p = malloc(sizeof(void*));
  *p = info + 1;
  return p;
}

#define ainfo(a) ((struct ainfo *)((void*)(*(a)) - sizeof(struct ainfo)))
#define asize(a) (ainfo(a)->size)
#define acap(a) (ainfo(a)->cap)
#define aesz(a) (ainfo(a)->esz)
#define ario(a) (ainfo(a)->rio)

/* Mặc định rio = 2 */
#define acreate(elemtype, size) \
   acreate_internal(size, sizeof(elemtype), 2.0)

#define aelem(a, i) (*(a))[i]

#define areserve(a, newcap) \
  do { \
    if ((newcap) < asize(a)) { \
      break; \
    } \
    struct ainfo *_info = ainfo(a); \
    _info = realloc(_info, sizeof(struct ainfo) + (newcap) * _info->esz); \
    _info->cap = (newcap); \
    *(a) = (void*)(_info + 1); \
  } while (0)

#define aresize(a, newsize) \
  do { \
    if (newsize > acap(a)) {  \
      printf("newsize: %ld\n"); \
      areserve((a), newsize); \
    } \
    asize(a) = (newsize); \
  } while (0)

#define afree(a) \
    free(ainfo(a)); \
    free(a)

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

#define aqsort(a, cmp) \
   qsort(*(a), asize(a), aesz(a), cmp)

/**
 * Duyệt tuần tự từng phần tử của mảng a,
 * typeof ban đầu là 1 từ khóa trong mở rộng của GNU,
 * và đến nay đã chính thức trở thành 1 từ khóa của ISO C kể từ C23
 */
#define atraverse(iter_decl, cur, a) \
  for (iter_decl cur = *(a), *_end = cur + asize(a); \
       cur < _end; ++cur)

#define aremove(a, idx) \
    do { \
      for (long _i = (idx); _i < asize(a) - 1; ++_i) { \
        aelem(a, _i) = aelem(a, _i + 1); \
      } \
    } while (0)
#define apush(a, elem) aappend(a, elem)
#define atop(a) aelem(a, asize(a) - 1)
#define apop(a) aremove(a, asize(a) - 1)

#endif  // CONT_ARR_H_
