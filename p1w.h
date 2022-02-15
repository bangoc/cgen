#ifndef P1W_H_
#define P1W_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "base/arr.h"
#include "base/gtype.h"

typedef enum {
  PRIORITY_MIN = 0,
  PRIORITY_MAX,
  PRIORITY_TYPES_COUNT
} p1w_types;

typedef struct priority_one_way {
  arr_t(gtype) data;
  p1w_types typ;
  gtype_cmp_t cmp;
} *p1w_t;

p1w_t p1w_create(p1w_types typ, gtype_cmp_t cmp);
gtype p1w_peek(p1w_t h);
gtype p1w_dequeue(p1w_t h);
int p1w_enqueue(p1w_t h, gtype value);
void p1w_root(p1w_t h, gtype value);
long p1w_size(p1w_t h);

#define p1w_is_empty(h) \
  (p1w_size(h) == 0)

#define p1w_free(h) \
  do { \
    arr_free((h)->data); \
    free(h); \
  } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng p1w
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng p1w.
 * Con trỏ value.p1w (kiểu ::p1w_t) được truyền cho p1w_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_p1w(gtype value);

#define P1WARR(h) (ARR((h)->data))

#endif  // P1W_H_
