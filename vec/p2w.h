/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef VEC_P2W_H_
#define VEC_P2W_H_

#include "base/gtype.h"
#include "vec/arr.h"

#include <stdbool.h>

typedef struct priority_two_ways {
    long size;
    arr_t(gtype) data;
    arr_t(gtype) index;
    arr_t(gtype) index2;
} p2w_s, *p2w_t;

#define PARENT(x)   (((x)+1)/2-1)
#define LEFTCHILD(x)  (((x)+1)*2-1)
#define RIGHTCHILD(x) (((x)+1)*2)

// ========== Khai báo hàm ===============

p2w_t p2w_create();

#define p2w_free(h) \
  do { \
    arr_free(h->data); \
    arr_free(h->index); \
    arr_free(h->index2); \
    free(h); \
  } while (0)

long p2w_size(const p2w_t h);
int p2w_clear(p2w_t h);
bool p2w_empty(const p2w_t h);
int p2w_push_with_index(p2w_t h, long idx, gtype elem, gtype_cmp_t cmp);
gtype p2w_max(const p2w_t h);
long p2w_max_index(const p2w_t h);
gtype p2w_get(const p2w_t h, long idx);
gtype p2w_delete_max(p2w_t h, gtype_cmp_t cmp);
gtype p2w_deactivate_max(p2w_t h, gtype_cmp_t cmp);
gtype p2w_delete_max_index(p2w_t h, long *idx, gtype_cmp_t cmp);
int p2w_modify(p2w_t h, long idx, gtype elem, gtype_cmp_t cmp);
bool p2w_check(p2w_t h, gtype_cmp_t cmp);

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng p2w
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng p2w.
 * Con trỏ value.p2w (kiểu ::p2w_t) được truyền cho p2w_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_p2w(gtype value);

#endif  // VEC_P2W_H_