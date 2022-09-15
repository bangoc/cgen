/* (C) Nguyen Ba Ngoc 2021 */

#include "list/spec/isl.h"

struct sln *isl_create_node(long value) {
  struct isn *nn = malloc(sizeof(struct isn));
  nn->base.next = NULL;
  nn->value = value;
  return (struct sln *)nn;
}

void isl_stack_push(struct sll *list, long value) {
  struct sln *nn = isl_create_node(value);
  return sll_push_front(list, nn);
}

long isl_stack_pop(struct sll *list) {
  long value = isl_stack_top(list);
  sll_pop_front(list);
  return value;
}

long isl_stack_top(struct sll *list) {
  struct sln *tmp = sll_front(list);
  return isl_node_value(tmp);
}

void isn_pprint(struct sln *node) {
  printf("[%ld]", isl_node_value(node));
}


void isl_pprint(struct sll *list) {
  sll_pprint(list, isn_pprint);
}

/* Triển khai giao diện queue số nguyên */
void isl_fifo_enq(struct sll *list, long value) {
  struct sln *nn = isl_create_node(value);
  return sll_push_back(list, nn);
}

long isl_fifo_deq(struct sll *list) {
  long value = isl_fifo_peek(list);
  sll_pop_front(list);
  return value;
}

long isl_fifo_peek(struct sll *list) {
  struct sln *tmp = sll_front(list);
  return isl_node_value(tmp);
}