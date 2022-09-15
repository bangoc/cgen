#ifndef VEC_P1W_H_
#define VEC_P1W_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include "base/gtype.h"
#include "vec/arr.h"

enum p1w_types {
  PRIORITY_MIN = 0,
  PRIORITY_MAX,
  PRIORITY_TYPES_COUNT
};

struct p1way {
  arr_t(gtype) data;
  enum p1w_types typ;
  gtype_cmp_t cmp;
};

struct p1way *p1w_create(enum p1w_types typ, gtype_cmp_t cmp);
gtype p1w_peek(struct p1way *h);
gtype p1w_dequeue(struct p1way *h);
int p1w_enqueue(struct p1way *h, gtype value);
void p1w_root(struct p1way *h, gtype value);
long p1w_size(struct p1way *h);

#define p1w_is_empty(h) \
  (p1w_size(h) == 0)

#define p1w_free(h) \
  do { \
    arr_free((h)->data); \
    free(h); \
  } while (0)

#define p1w_clear(h) \
  do { \
    arr_set_size((h)->data, 0); \
    arr_set_capacity((h)->data, 0); \
  } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng p1w
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng p1w.
 * Con trỏ value.p1w (kiểu ::struct p1way *) được truyền cho p1w_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_p1w(gtype value);

#define P1WARR(h) (arr((h)->data))

#endif  // VEC_P1W_H_
