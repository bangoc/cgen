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
 * Kiểu dữ liệu cơ bản của các cấu trúc dữ liệu được triển khai.
 * \ref gtype có thể thay thế cho 1 nhóm kiểu dữ liệu.
 */
typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
  struct dlist *dl;
  struct slist *sl;
  struct vector *vec;
  struct tmap *tm;
} gtype;

#define GZERO (GLONG(0l))

#define GTYPE(type, val) ((gtype){.type = (val)})
#define GLONG(value) GTYPE(l, value)
#define GDOUBLE(value) GTYPE(d, value)
#define GSTR(value) GTYPE(s, (char *)value)
#define GVOID(value) GTYPE(v, value)
#define GDLIST(value) GTYPE(dl, value)
#define GSLIST(value) GTYPE(sl, value)
#define GVECTOR(value) GTYPE(vec, value)
#define GTREEMAP(value) GTYPE(tm, value)

#define GSWAP(v1, v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)

typedef int (*gtype_cmp_t)(const gtype*, const gtype*);
typedef void (*gtype_free_t)(gtype*);
typedef int (*gtype_print_t)(const gtype*);

static inline int glong_cmp(const gtype *v1, const gtype *v2) {
  return v1->l - v2->l;
}

static inline int glong_rcmp(const gtype *v1, const gtype *v2) {
  return v2->l - v1->l;
}

static inline int gdouble_cmp(const gtype *v1, const gtype *v2) {
  if (v1->d < v2->d) {
    return -1;
  } else if (v1->d > v2->d) {
    return 1;
  }
  return 0;
}

static inline int gdouble_rcmp(const gtype *v1, const gtype *v2) {
  if (v2->d < v1->d) {
    return -1;
  } else if (v2->d > v1->d) {
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
static inline int gstr_cmp(const gtype *v1, const gtype *v2) {
  return strcmp(v1->s, v2->s);
}

static inline int gstr_rcmp(const gtype *v1, const gtype *v2) {
  return strcmp(v2->s, v1->s);
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

static int gtype_print_l(const gtype *value) {
  printf("%ld\n", value->l);
  return 0;  // Tương thích với foreach
}

static int gtype_print_d(const gtype *value) {
  printf("%f\n", value->d);
  return 0;
}

static int gtype_print_s(const gtype *value) {
  printf("%s\n", value->s);
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
