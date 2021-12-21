#ifndef BASE_ARR_H_
#define BASE_ARR_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include <stdlib.h>

#define ARR(pa) (*(pa))
#define arr_t(etyp) etyp **
#define elem(a, i) (ARR(a)[i])
#define elem_ref(a, i) (ARR(a) + i)

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

#define ARR_BEG(a) (((long*)ARR(a)) - ARR_ATT_MAX)
#define arr_size(a) (ARR_BEG(a)[ARR_SZ])
#define arr_capacity(a) (ARR_BEG(a)[ARR_CAP])
#define arr_elem_sz(a) (ARR_BEG(a)[ARR_ELEM_SZ])
#define arr_inc(a) (ARR_BEG(a)[ARR_INC])

#define arr_free(a) \
  do { \
    free(ARR_BEG(a)); \
    *a = NULL; \
    free(a); \
    a = NULL; \
  } while (0)

#define arr_set_capacity(a, newcap) \
  do { \
    long *_tmp = ARR_BEG(a); \
    long _elem_sz = _tmp[ARR_ELEM_SZ]; \
    _tmp = realloc(_tmp, ARR_ATT_MAX * sizeof(long) + newcap * _elem_sz); \
    if (_tmp) { \
      if (_tmp[ARR_SZ] > newcap) { \
        _tmp[ARR_SZ] = newcap; \
      } \
      _tmp[ARR_CAP] = newcap; \
      (*((void**)a)) = (void*)(_tmp + ARR_ATT_MAX); \
    } \
  } while (0)

#define arr_set_size(a, newsize) \
  do { \
    long _c = arr_capacity(a); \
    if (newsize > _c) {  \
      arr_set_capacity(a, newsize); \
    } \
    if (newsize <= arr_capacity(a)) { \
      arr_size(a) = newsize; \
    } \
  } while (0)

#define arr_create(cap, etyp) \
   (arr_t(etyp))arr_create_internal(cap, sizeof(etyp))

#define arr_decl(name, cap, etyp) \
   arr_t(etyp) name = arr_create(cap, etyp)

#define arr_append(a, elem) \
   do { \
     long *_tmp = ARR_BEG(a); \
     if (_tmp[ARR_SZ] >= _tmp[ARR_CAP]) { \
       long _c = _tmp[ARR_CAP]; \
       long _inc = _tmp[ARR_INC]; \
       long _newcap = _c > 100? _c + _c * _inc / 100: _c + _inc; \
       arr_set_capacity(a, _newcap); \
       _tmp = ARR_BEG(a); \
     } \
     if (_tmp[ARR_SZ] < _tmp[ARR_CAP]) { \
       (*a)[_tmp[ARR_SZ]] = elem; \
       ++(_tmp[ARR_SZ]); \
     } \
   } while (0)

#endif  // BASE_ARR_H_
