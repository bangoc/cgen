#ifndef BASE_GTYPE_H_
#define BASE_GTYPE_H_

/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/** @file
 * @brief Định nghĩa kiểu ::gtype và các thành phần bổ trợ.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * \headerfile "all.h"
 * Kiểu dữ liệu cơ bản của các cấu trúc dữ liệu được triển khai.
 * ::gtype có thể thay thế cho 1 nhóm kiểu dữ liệu.
 */
typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
  union generic_type *g;
  struct gdllist *gdl;
  struct gsllist *gsl;
  struct gvector *gvec;
  struct rbmtree *rbm;
  struct rbstree *rbs;
  struct hmap *hmap;
  struct hset *hset;
  struct p1way *p1w;
  struct p2ways *p2w;
} gtype;

#define gtype_zero (gtype_l(0l))

#define gtype_value(type, val) ((gtype){.type = (val)})
#define gtype_l(value) gtype_value(l, value)
#define gtype_d(value) gtype_value(d, value)
#define gtype_s(value) gtype_value(s, (char *)value)
#define gtype_v(value) gtype_value(v, value)
#define gtype_g(value) gtype_value(g, value)
#define gtype_gdl(value) gtype_value(gdl, value)
#define gtype_gsl(value) gtype_value(gsl, value)
#define gtype_gvec(value) gtype_value(gvec, value)
#define gtype_rbm(value) gtype_value(rbm, value)
#define gtype_rbs(value) gtype_value(rbs, value)
#define gtype_hmap(value) gtype_value(hmap, value)
#define gtype_hset(value) gtype_value(hset, value)
#define gtype_p1w(value) gtype_value(p1w, value)
#define gtype_p2w(value) gtype_value(p2w, value)

#define gtype_swap(v1, v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)

typedef int (*gtype_cmp_t)(gtype, gtype);
typedef void (*gtype_free_t)(gtype);
typedef int (*gtype_print_t)(gtype);

static inline int gtype_cmp_l(gtype v1, gtype v2) {
  return v1.l - v2.l;
}

static inline int gtype_rcmp_l(gtype v1, gtype v2) {
  return v2.l - v1.l;
}

static inline int gtype_cmp_d(gtype v1, gtype v2) {
  if (v1.d < v2.d) {
    return -1;
  } else if (v1.d > v2.d) {
    return 1;
  }
  return 0;
}

static inline int gtype_rcmp_d(gtype v1, gtype v2) {
  if (v2.d < v1.d) {
    return -1;
  } else if (v2.d > v1.d) {
    return 1;
  }
  return 0;
}

/**
 * Hàm so sánh các giá trị gtype chứa con trỏ chuỗi ký tự.
 *
 * @param v1 Đối số thứ nhất.
 * @param v2 Đỗ số thứ 2.
 * @return Giá trị trả về theo định dạng strcmp <br>
 *   -1 nếu v1.s < v2.s, <br>
 *    1 nếu ngược lại và v1.s > v2.s, <br>
 *    0 nếu ngược lại (v1.s == v2.s). <br>
 *
 * \memberof generic_type
 */
static inline int gtype_cmp_s(gtype v1, gtype v2) {
  return strcmp(v1.s, v2.s);
}

static inline int gtype_rcmp_s(gtype v1, gtype v2) {
  return strcmp(v2.s, v1.s);
}

static inline int gtype_qsort_l(const void *v1, const void *v2) {
  return ((const gtype*)v1)->l - ((const gtype*)v2)->l;
}

static inline int gtype_qsort_d(const void *v1, const void *v2) {
  if (((const gtype*)v1)->l > ((const gtype*)v2)->l) {
    return 1;
  } else if (((const gtype*)v1)->l < ((const gtype*)v2)->l) {
    return -1;
  }
  return 0;
}

static inline int gtype_qsort_s(const void *v1, const void *v2) {
  return strcmp(((const gtype*)v1)->s, ((const gtype*)v2)->s);
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

/**
 * Giải phóng chuỗi được trỏ đến bởi con trỏ v.s
 *
 * @param v Giá trị gtype chứa con trỏ tới chuỗi.
 * @return Hàm không trả về giá trị.
 */
static void gtype_free_s(gtype v) {
  free(v.s);
}

static void gtype_free_v(gtype v) {
  free(v.v);
}

#endif  // BASE_GTYPE_H_
