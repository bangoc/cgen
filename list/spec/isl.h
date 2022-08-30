#ifndef LIST_SPEC_ISL_H_
#define LIST_SPEC_ISL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  LIFO và FIFO với kiểu long (đóng gói sll)
*/

#include "list/sll.h"

typedef struct isn_s {
  struct sln_s base;
  long value;
} *isn_t;

void isn_pprint(sln_t node);
void isl_pprint(sll_t list);

#define to_isn(n) ((isn_t)(n))
#define isn_value(n) (to_isn(n)->value)

sln_t isn_create(long value);
void isl_stack_push(sll_t list, long value);
long isl_stack_pop(sll_t list);
long isl_stack_top(sll_t list);

/* Giao diện queue kiểu long dựa trên giao diện sll */
void isl_fifo_enq(sll_t list, long value);
long isl_fifo_deq(sll_t list);
long isl_fifo_peek(sll_t list);

#endif  // LIST_SPEC_ISL_H_