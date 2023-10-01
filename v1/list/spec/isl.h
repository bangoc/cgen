#ifndef LIST_SPEC_ISL_H_
#define LIST_SPEC_ISL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * LIFO và FIFO với kiểu long (đóng gói sllist)
 */

#include "list/sll.h"

/**
 * Cấu trúc nút của danh sách móc nối đơn kiêu int
 * islnode = int single linked (list) node
 */
struct islnode {
  struct slnode base;
  long value;
};

void isn_pprint(struct slnode *node);
void isl_pprint(struct sllist *list);

#define isl_node(n) ((struct islnode *)(n))
#define isl_node_value(n) (isl_node(n)->value)

struct slnode *isl_create_node(long value);
void isl_stack_push(struct sllist *list, long value);
long isl_stack_pop(struct sllist *list);
long isl_stack_top(struct sllist *list);

/* Giao diện queue kiểu long dựa trên giao diện sll */
void isl_fifo_enq(struct sllist *list, long value);
long isl_fifo_deq(struct sllist *list);
long isl_fifo_peek(struct sllist *list);

#endif  // LIST_SPEC_ISL_H_