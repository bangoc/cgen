#ifndef ARR_H_
#define ARR_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include <stdlib.h>

#define ARR(pa) (*(pa))
#define arr_t(etyp) etyp **
#define ELEM(a, i) (ARR(a)[i])

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
    long *tmp = ARR_BEG(a); \
    long elem_sz = tmp[ARR_ELEM_SZ]; \
    tmp = realloc(tmp, ARR_ATT_MAX * sizeof(long) + newcap * elem_sz); \
    if (tmp) { \
      if (tmp[ARR_SZ] > newcap) { \
        tmp[ARR_SZ] = newcap; \
      } \
      tmp[ARR_CAP] = newcap; \
      (*((void**)a)) = (void*)(tmp + ARR_ATT_MAX); \
    } \
  } while (0)

#define arr_set_size(a, newsize) \
  do { \
    long c = arr_capacity(a); \
    if (newsize > c) {  \
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
     long *tmp = ARR_BEG(a); \
     if (tmp[ARR_SZ] >= tmp[ARR_CAP]) { \
       long c = tmp[ARR_CAP]; \
       long inc = tmp[ARR_INC]; \
       long newcap = c > 100? c + c * inc / 100: c + inc; \
       arr_set_capacity(a, newcap); \
       tmp = ARR_BEG(a); \
     } \
     if (tmp[ARR_SZ] < tmp[ARR_CAP]) { \
       (*a)[tmp[ARR_SZ]] = elem; \
       ++(tmp[ARR_SZ]); \
     } \
   } while (0)

#endif  // ARR_H_
