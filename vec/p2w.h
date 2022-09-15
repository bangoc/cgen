/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef VEC_P2W_H_
#define VEC_P2W_H_

#include "base/gtype.h"
#include "vec/arr.h"

#include <stdbool.h>

struct p2ways {
  long size;
  arr_t(gtype) data;
  arr_t(gtype) index;
  arr_t(gtype) index2;
};

#define PARENT(x)   (((x)+1)/2-1)
#define LEFTCHILD(x)  (((x)+1)*2-1)
#define RIGHTCHILD(x) (((x)+1)*2)

// ========== Khai báo hàm ===============

struct p2ways *p2w_create();

#define p2w_free(h) \
  do { \
    arr_free(h->data); \
    arr_free(h->index); \
    arr_free(h->index2); \
    free(h); \
  } while (0)

long p2w_size(const struct p2ways *h);
int p2w_clear(struct p2ways *h);
bool p2w_empty(const struct p2ways *h);
int p2w_push_with_index(struct p2ways *h, long idx, gtype elem, gtype_cmp_t cmp);
gtype p2w_max(const struct p2ways *h);
long p2w_max_index(const struct p2ways *h);
gtype p2w_get(const struct p2ways *h, long idx);
gtype p2w_delete_max(struct p2ways *h, gtype_cmp_t cmp);
gtype p2w_deactivate_max(struct p2ways *h, gtype_cmp_t cmp);
gtype p2w_delete_max_index(struct p2ways *h, long *idx, gtype_cmp_t cmp);
int p2w_modify(struct p2ways *h, long idx, gtype elem, gtype_cmp_t cmp);
bool p2w_check(struct p2ways *h, gtype_cmp_t cmp);

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