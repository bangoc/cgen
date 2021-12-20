/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "spec/isl.h"

sll_node_t isn_create(long value) {
  isn_t nn = malloc(sizeof(struct isn_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void isl_stack_push(sll_t list, long value) {
  sll_node_t nn = isn_create(value);
  return sll_push_front(list, nn);
}

long isl_stack_pop(sll_t list) {
  long value = isl_stack_top(list);
  sll_pop_front(list);
  return value;
}

long isl_stack_top(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return isn_value(tmp);
}

void isn_pprint(sll_node_t node) {
  printf("[%ld]", isn_value(node));
}


void isl_pprint(sll_t list) {
  _sll_pprint_list(list, isn_pprint);
}

/* Triển khai giao diện queue số nguyên */
void isl_fifo_enq(sll_t list, long value) {
  sll_node_t nn = isn_create(value);
  return sll_push_back(list, nn);
}

long isl_fifo_deq(sll_t list) {
  long value = isl_fifo_peek(list);
  sll_pop_front(list);
  return value;
}

long isl_fifo_peek(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return isn_value(tmp);
}