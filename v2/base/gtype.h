/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/** @file
 * @brief Định nghĩa kiểu ::gtype và các thành phần bổ trợ.
 */

#ifndef BASE_GTYPE_H_
#define BASE_GTYPE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Kiểu dữ liệu cơ bản của các cấu trúc dữ liệu và thuật toán 
 * được triển khai trong thư viện.
 * \ref gtype có thể thay thế cho 1 nhóm kiểu dữ liệu.
 */
typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
} gtype;

#define GZERO (GLONG(0l))

#define GTYPE(type, val) ((gtype){.type = (val)})
#define GLONG(value) GTYPE(l, value)
#define GDOUBLE(value) GTYPE(d, value)
#define GSTR(value) GTYPE(s, value)
#define GVOID(value) GTYPE(v, value)

static inline gtype gtype_from_long(long value) {
  return GLONG(value);
}

static inline gtype gtype_from_double(double value) {
  return GDOUBLE(value);
}

static inline gtype gtype_from_str(char *value) {
  return GSTR(value);
}

static inline gtype gtype_from_void(void *value) {
  return GVOID(value);
}

static inline gtype gtype_from_gtype(gtype value) {
  return value;
}

#define TO_GTYPE(value) \
    _Generic((value), \
        char: gtype_from_long, \
        short: gtype_from_long, \
        int: gtype_from_long, \
        long: gtype_from_long, \
        float: gtype_from_double, \
        double: gtype_from_double, \
        char *: gtype_from_str, \
        gtype: gtype_from_gtype, \
        default: gtype_from_void \
    )(value)

#define VALUE(elem, member) _Generic((elem),\
        gtype: gget_##member,\
        gtype*: pgget_##member)(elem)
#define LONGG(elem) VALUE(elem, l)
#define DOUBLEG(elem) VALUE(elem, d)
#define STRG(elem) VALUE(elem, s)
#define VOIDG(elem) VALUE(elem, v)
static inline long gget_l(gtype g) { return g.l; }
static inline double gget_d(gtype g) { return g.d; }
static inline char *gget_s(gtype g) { return g.s; }
static inline void *gget_v(gtype g) { return g.v; }
static inline long pgget_l(gtype *g) { return g->l; }
static inline double pgget_d(gtype *g) { return g->d; }
static inline char *pgget_s(gtype *g) { return g->s; }
static inline void *pgget_v(gtype *g) { return g->v; }

#define GSWAP(v1, v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)

typedef int (*gprint_fn_t)(const gtype);

static int gtype_print_l(const gtype value) {
  printf("%ld\n", value.l);
  return 0;  // Tương thích với foreach
}

static int gtype_print_d(const gtype value) {
  printf("%f\n", value.d);
  return 0;
}

static int gtype_print_s(const gtype value) {
  printf("%s\n", value.s);
  return 0;
}

#endif  // BASE_GTYPE_H_
