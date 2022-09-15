#ifndef LIST_QUE_H_
#define LIST_QUE_H_

/* (C) Nguyen Ba Ngoc 2022 */

/* Triển khai hàng đợi FIFO dựa trên danh sách móc nối đơn
   cho gtype */

#include "list/gsl.h"

struct gsllist *que_enq(struct gsllist *q, gtype value);
struct gsllist *que_deq(struct gsllist *q);
gtype que_peek(struct gsllist *q);

#define que_size(q) (gsl_length(q))
#define que_is_empty(q) (gsl_is_empty(q))

#endif  // LIST_QUE_H_