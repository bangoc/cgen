#ifndef VEC_ARR_H_
#define VEC_ARR_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include <stdlib.h>

#define arr(pa) (*(pa))
#define arr_t(etyp) etyp **
#define elem(a, i) (arr(a)[(i)])
#define elem_ref(a, i) (arr(a) + (i))

enum arr_attrib {
  ARR_SZ = 0,
  ARR_CAP,
  ARR_ELEM_SZ,
  ARR_INC,
  ARR_ATT_MAX
};

static inline void **arr_create_internal(long cap, long elem_sz) {
  long* a = malloc(ARR_ATT_MAX * sizeof(long) + cap * elem_sz);
  if (a) {
    a[ARR_SZ] = 0;
    a[ARR_CAP] = cap;
    a[ARR_ELEM_SZ] = elem_sz;
    a[ARR_INC] = 30;  // %
    void **tmp = malloc(sizeof(void*));
    *tmp = a + ARR_ATT_MAX;
    return tmp;
  }
  return NULL;
}

#define arr_beg(a) (((long*)arr(a)) - ARR_ATT_MAX)
#define arr_size(a) (arr_beg(a)[ARR_SZ])
#define arr_capacity(a) (arr_beg(a)[ARR_CAP])
#define arr_elem_sz(a) (arr_beg(a)[ARR_ELEM_SZ])
#define arr_inc(a) (arr_beg(a)[ARR_INC])

#define arr_free(a) \
  do { \
    free(arr_beg(a)); \
    *(a) = NULL; \
    free(a); \
    (a) = NULL; \
  } while (0)

#define arr_set_capacity(a, newcap) \
  do { \
    long *_tmp = arr_beg(a); \
    long _elem_sz = _tmp[ARR_ELEM_SZ]; \
    _tmp = realloc(_tmp, ARR_ATT_MAX * sizeof(long) + (newcap) * _elem_sz); \
    if (_tmp) { \
      if (_tmp[ARR_SZ] > (newcap)) { \
        _tmp[ARR_SZ] = (newcap); \
      } \
      _tmp[ARR_CAP] = (newcap); \
      (*((void**)(a))) = (void*)(_tmp + ARR_ATT_MAX); \
    } \
  } while (0)

#define arr_set_size(a, newsize) \
  do { \
    long _c = arr_capacity(a); \
    if ((newsize) > _c) {  \
      arr_set_capacity(a, newsize); \
    } \
    arr_size(a) = (newsize); \
  } while (0)

#define arr_create(cap, etyp) \
   (arr_t(etyp))arr_create_internal(cap, sizeof(etyp))

#define arr_decl(name, cap, etyp) \
   arr_t(etyp) name = arr_create(cap, etyp)

#define arr_append(a, elem) \
   do { \
     long *_tmp = arr_beg(a); \
     if (_tmp[ARR_SZ] >= _tmp[ARR_CAP]) { \
       long _c = _tmp[ARR_CAP]; \
       long _inc = _tmp[ARR_INC]; \
       long _newcap = _c > 100? _c + _c * _inc / 100: _c + _inc; \
       arr_set_capacity(a, _newcap); \
       _tmp = arr_beg(a); \
     } \
     if (_tmp[ARR_SZ] < _tmp[ARR_CAP]) { \
       arr(a)[_tmp[ARR_SZ]] = (elem); \
       ++(_tmp[ARR_SZ]); \
     } \
   } while (0)

#endif  // VEC_ARR_H_
