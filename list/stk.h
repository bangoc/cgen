#ifndef LIST_STK_H_
#define LIST_STK_H_

/* (C)  Nguyễn Bá Ngọc 2022 */

/* Triển khai khái quát ngăn xếp dựa trên danh sách móc nối đơn
   với gtype */

#include "list/gsl.h"

struct gsl *stk_push(struct gsl *stk, gtype value);
struct gsl *stk_pop(struct gsl *stk);
gtype stk_top(struct gsl *stk);

#define stk_is_empty(stk) (gsl_is_empty(stk))
#define stk_size(stk) (gsl_length(stk))

#endif  // LIST_STK_H_