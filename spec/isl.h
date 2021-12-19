#ifndef SPEC_ISL_H_
#define SPEC_ISL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  LIFO và FIFO với kiểu long (đóng gói sll)
*/


typedef struct sll_node_l_s {
  struct sll_node_s base;
  long value;
} *sll_node_l_t;

void sll_pprint_node_l(sll_node_t node);
void sll_pprint_list_l(sll_t list);

#define to_sll_node_l(n) ((sll_node_l_t)n)
#define sll_node_l_value(n) (to_sll_node_l(n)->value)

sll_node_t sll_create_node_l(long value);
void sll_stack_push_l(sll_t list, long value);
long sll_stack_pop_l(sll_t list);
long sll_stack_top_l(sll_t list);

/* Giao diện queue kiểu long dựa trên giao diện sll */
void sll_fifo_enqueue_l(sll_t list, long value);
long sll_fifo_dequeue_l(sll_t list);
long sll_fifo_peek_l(sll_t list);

#endif  // SPEC_ISL_H_