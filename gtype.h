/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GTYPE_H_
#define GTYPE_H_

#include <stdio.h>
#include <string.h>

typedef union {
  long i;
  double d;
  char *s;
  void *v;
} gtype;

#define INVALID_VALUE ((gtype){.i = -1})
#define gtype_value(type, val) ((gtype){.type = val})
#define gtype_i(value) gtype_value(i, value)
#define gtype_d(value) gtype_value(d, value)
#define gtype_s(value) gtype_value(s, value)
#define gtype_v(value) gtype_value(v, value)

typedef int (*gtype_cmp_t)(gtype, gtype);

static int gtype_cmp_i(gtype v1, gtype v2) {
  return v1.i - v2.i;
}

static int gtype_cmp_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return -1;
  } else if (v1.d > v2.d) {
    return 1;
  }
  return 0;
}

static int gtype_cmd_s(gtype v1, gtype v2) {
  return strcmp(v1.s, v2.s);
}

typedef void (*gtype_print_t)(gtype);

static void gtype_print_i(gtype value) {
  printf("%ld\n", value.i);
}

static void gtype_print_d(gtype value) {
  printf("%f\n", value.d);
}

static void gtype_print_s(gtype value) {
  printf("%s\n", value.s);
}

#endif  // GTYPE_H_