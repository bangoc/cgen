/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/** @file
 * @brief Định nghĩa kiểu ::gtype và các thành phần bổ trợ.
 */

#ifndef MYLIB_GTYPE_H_
#define MYLIB_GTYPE_H_

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

static inline gtype gtype_from_long(long value) {
  return (gtype){.l = value};
}

static inline gtype gtype_from_double(double value) {
  return (gtype){.d = value};
}

static inline gtype gtype_from_str(char *value) {
  return (gtype){.s = value};
}

static inline gtype gtype_from_void(void *value) {
  return (gtype){.v = value};
}

static inline gtype gtype_from_gtype(gtype value) {
  return value;
}

#define GTYPE(value) \
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

#define GZERO (GTYPE(0l))

#define GSWAP(v1, v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)

#endif  // MYLIB_GTYPE_H_
