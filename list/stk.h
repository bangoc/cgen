#ifndef LIST_STK_H_
#define LIST_STK_H_

/* (C)  Nguyễn Bá Ngọc 2022 */

/* Triển khai khái quát ngăn xếp dựa trên danh sách móc nối đơn
   với gtype */

#include "list/gsl.h"

gsl_t stk_push(gsl_t stk, gtype value);
gsl_t stk_pop(gsl_t stk);
gtype stk_top(gsl_t stk);

#define stk_is_empty(stk) (gsl_is_empty(stk))
#define stk_size(stk) (gsl_length(stk))

#endif  // LIST_STK_H_