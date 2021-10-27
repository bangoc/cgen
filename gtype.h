/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GTYPE_H_
#define GTYPE_H_

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
  return v1.d - v2.d;
}

static int gtype_cmd_s(gtype v1, gtype v2) {
  return strcmp(v1.s, v2.s);
}

#endif  // GTYPE_H_