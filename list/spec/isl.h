#ifndef LIST_SPEC_ISL_H_
#define LIST_SPEC_ISL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * LIFO và FIFO với kiểu long (đóng gói sll)
 */

#include "list/sll.h"

struct isn {
  struct sln base;
  long value;
};

void isn_pprint(struct sln *node);
void isl_pprint(struct sll *list);

#define isl_node(n) ((struct isn *)(n))
#define isl_node_value(n) (isl_node(n)->value)

struct sln *isl_create_node(long value);
void isl_stack_push(struct sll *list, long value);
long isl_stack_pop(struct sll *list);
long isl_stack_top(struct sll *list);

/* Giao diện queue kiểu long dựa trên giao diện sll */
void isl_fifo_enq(struct sll *list, long value);
long isl_fifo_deq(struct sll *list);
long isl_fifo_peek(struct sll *list);

#endif  // LIST_SPEC_ISL_H_