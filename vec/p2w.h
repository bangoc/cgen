/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef VEC_P2W_H_
#define VEC_P2W_H_

#include "base/gtype.h"
#include "vec/arr.h"

struct p2ways {
  atype(gtype) *data;
  atype(long) *index;
  atype(long) *index2;
  gtype_cmp_t cmp;
};

struct p2ways *p2w_create(gtype_cmp_t cmp);

#define p2w_free(h) \
  do { \
    arr_free((h)->data); \
    arr_free((h)->index); \
    arr_free((h)->index2); \
    free(h); \
  } while (0)

#define p2w_size(h) arr_size((h)->data)

#define p2w_clear(h) \
  do { \
    arr_clear((h)->data); \
    arr_clear((h)->index); \
    arr_clear((h)->index2); \
  } while (0)

#define p2w_is_empty(h) (p2w_size(h) == 0)

int p2w_push_with_index(struct p2ways *h, long idx, gtype elem);
gtype p2w_max(const struct p2ways *h);
long p2w_max_index(const struct p2ways *h);
gtype p2w_get(const struct p2ways *h, long idx);
gtype p2w_delete_max(struct p2ways *h);
gtype p2w_deactivate_max(struct p2ways *h);
gtype p2w_delete_max_index(struct p2ways *h, long *idx);
int p2w_modify(struct p2ways *h, long idx, gtype elem);
int p2w_check(struct p2ways *h);

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng p2w
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng p2w.
 * Con trỏ value.p2w (kiểu ::struct p2ways *) được truyền cho p2w_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_p2w(gtype value);

#endif  // VEC_P2W_H_
