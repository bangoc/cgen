#ifndef VEC_SPEC_D2W_H_
#define VEC_SPEC_D2W_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Hàng đợi ưu tiên truy cập 2 chiều với kiểu double
 */

#include "vec/p2w.h"

int d2w_push_with_index(p2w_t h, long idx, double elem);
double d2w_max(const p2w_t h);
double d2w_get(const p2w_t h, long idx);
double d2w_delete_max(p2w_t h);
double d2w_deactivate_max(p2w_t h);
double d2w_delete_max_index(p2w_t h, long *idx);
int d2w_modify(p2w_t h, long idx, double elem);

#endif  // VEC_SPEC_D2W_H_