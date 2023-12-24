/* (C) Nguyen Ba Ngoc 2021 */

#include "list/spec/isl.h"

struct slnode *isl_create_node(long value) {
  struct islnode *nn = malloc(sizeof(struct islnode));
  nn->base.next = NULL;
  nn->value = value;
  return (struct slnode *)nn;
}

void isl_stack_push(struct sllist *list, long value) {
  struct slnode *nn = isl_create_node(value);
  return sll_push_front(list, nn);
}

long isl_stack_pop(struct sllist *list) {
  long value = isl_stack_top(list);
  sll_pop_front(list);
  return value;
}

long isl_stack_top(struct sllist *list) {
  struct slnode *tmp = sll_front(list);
  return isl_node_value(tmp);
}

void isn_pprint(struct slnode *node) {
  printf("[%ld]", isl_node_value(node));
}


void isl_pprint(struct sllist *list) {
  sll_pprint(list, isn_pprint);
}

/* Triển khai giao diện queue số nguyên */
void isl_fifo_enq(struct sllist *list, long value) {
  struct slnode *nn = isl_create_node(value);
  return sll_push_back(list, nn);
}

long isl_fifo_deq(struct sllist *list) {
  long value = isl_fifo_peek(list);
  sll_pop_front(list);
  return value;
}

long isl_fifo_peek(struct sllist *list) {
  struct slnode *tmp = sll_front(list);
  return isl_node_value(tmp);
}