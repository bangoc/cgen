#ifndef VEC_P1W_H_
#define VEC_P1W_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * @file
 * @brief Triển khai hàng đợi ưu tiên 1 chiều dựa trên cấu trúc đống.
 */

#include "base/gtype.h"
#include "vec/arr.h"

struct p1way {
  atype(gtype) *elems;
  gtype_cmp_t cmp;
};

/**
 * Hàm tạo hàng đợi ưu tiên, sử dụng hàm so sánh thuận cho kết quả
 * là hàng đợi ưu tiên giá trị cực đại (đống cực đại),
 * sử dụng hàm so sánh nghịch cho kết quả là hàng đợi ưu tiên
 * giá trị cực tiểu
 *
 * @param cmp Hàm so sánh
 * @return Con trỏ hàng đợi ưu tiên, có kiểu struct p1way*
 */
struct p1way *p1w_create(gtype_cmp_t cmp);
gtype p1w_peek(struct p1way *h);
gtype p1w_dequeue(struct p1way *h);
void p1w_enqueue(struct p1way *h, gtype value);
void p1w_root(struct p1way *h, gtype value);

#define p1w_size(h) \
  (arr_size((h)->elems))

#define p1w_is_empty(h) \
  (p1w_size(h) == 0)

#define p1w_free(h) \
  do { \
    arr_free((h)->elems); \
    free(h); \
  } while (0)

#define p1w_clear(h) \
  arr_clear((h)->elems)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng p1w
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng p1w.
 * Con trỏ value.p1w (kiểu ::struct p1way *) được truyền cho p1w_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_p1w(gtype value);

#define p1w_arr(h) ((h)->elems)

#endif  // VEC_P1W_H_
