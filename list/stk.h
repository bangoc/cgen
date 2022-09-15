#ifndef LIST_STK_H_
#define LIST_STK_H_

/* (C)  Nguyễn Bá Ngọc 2022 */

/* Triển khai khái quát ngăn xếp dựa trên danh sách móc nối đơn
   với gtype */

#include "list/gsl.h"

struct gsllist *stk_push(struct gsllist *stk, gtype value);
struct gsllist *stk_pop(struct gsllist *stk);
gtype stk_top(struct gsllist *stk);

#define stk_is_empty(stk) (gsl_is_empty(stk))
#define stk_size(stk) (gsl_length(stk))

#endif  // LIST_STK_H_