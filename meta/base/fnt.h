/* (C) Nguyễn Bá Ngọc 2023 */
#ifndef BASE_FNT_H_
#define BASE_FNT_H_

#include <stdlib.h>
#include <string.h>

typedef int (*compare_fnt)(const void *p1, const void *p2);
typedef void (*destructor_fnt)(void *p);

/* Mong đợi p1 và p2 trỏ tới các đối tượng int */
static inline int cmpi(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int*)p2;
}

static inline int rcmpi(const void *p1, const void *p2) {
  return *(const int*)p2 - *(const int*)p1;
}

/* Mong đợi p1 và p2 trỏ tới các đối tượng double */
static inline int cmpd(const void *p1, const void *p2) {
  double v1 = *(const double *)p1, v2 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}

static inline int rcmpd(const void *p1, const void *p2) {
  double v2 = *(const double *)p1, v1 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}

/* Mong đợi p1 và p2 trỏ tới các đối tượng char * */
static inline int cmps(const void *p1, const void *p2) {
  char *const *s1 = p1, *const *s2 = p2;
  return strcmp(*s1, *s2);
}

static inline int rcmps(const void *p1, const void *p2) {
  char *const *s2 = p1, *const *s1 = p2;
  return strcmp(*s1, *s2);
}

static inline void frees(void *p) {
  free(*(char**)p);
}

#endif  // BASE_FNT_H_