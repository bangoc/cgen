/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BASE_GTYPE_H_
#define BASE_GTYPE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
  union generic_type *g;
} gtype;

#define gtype_value(type, val) ((gtype){.type = val})
#define gtype_l(value) gtype_value(l, value)
#define gtype_d(value) gtype_value(d, value)
#define gtype_s(value) gtype_value(s, value)
#define gtype_v(value) gtype_value(v, value)

#define gtype_swap(v1, v2) \
  do { \
    gtype _tmp = v1; \
    v1 = v2; \
    v2 = _tmp; \
  } while (0)

typedef int (*gtype_cmp_t)(gtype, gtype);
typedef void (*gtype_free_t)(gtype);
typedef int (*gtype_print_t)(gtype);

static int gtype_cmp_l(gtype v1, gtype v2) {
  return v1.l - v2.l;
}

static int gtype_cmp_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return -1;
  } else if (v1.d > v2.d) {
    return 1;
  }
  return 0;
}

static int gtype_cmp_s(gtype v1, gtype v2) {
  return strcmp(v1.s, v2.s);
}

static int gtype_qsort_l(const void *v1, const void *v2) {
  return gtype_cmp_l(*((gtype*)v1), *((gtype*)v2));
}

static int gtype_qsort_d(const void *v1, const void *v2) {
  return gtype_cmp_d(*((gtype*)v1), *((gtype*)v2));
}

static int gtype_qsort_s(const void *v1, const void *v2) {
  return gtype_cmp_s(*((gtype*)v1), *((gtype*)v2));
}

static int gtype_print_l(gtype value) {
  printf("%ld\n", value.l);
  return 0;  // Tương thích với foreach
}

static int gtype_print_d(gtype value) {
  printf("%f\n", value.d);
  return 0;
}

static int gtype_print_s(gtype value) {
  printf("%s\n", value.s);
  return 0;
}

static void gtype_free_s(gtype v) {
  free(v.s);
}

static void gtype_free_v(gtype v) {
  free(v.v);
}

#endif  // BASE_GTYPE_H_