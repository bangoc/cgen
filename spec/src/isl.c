/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "spec/isl.h"

sll_node_t sll_create_node_l(long value) {
  sll_node_l_t nn = malloc(sizeof(struct sll_node_l_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void sll_stack_push_l(sll_t list, long value) {
  sll_node_t nn = sll_create_node_l(value);
  return sll_push_front(list, nn);
}

long sll_stack_pop_l(sll_t list) {
  long value = sll_stack_top_l(list);
  sll_pop_front(list);
  return value;
}

long sll_stack_top_l(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return sll_node_l_value(tmp);
}

void sll_pprint_node_l(sll_node_t node) {
  printf("[%ld]", sll_node_l_value(node));
}


void sll_pprint_list_l(sll_t list) {
  _sll_pprint_list(list, sll_pprint_node_l);
}

/* Triển khai giao diện queue số nguyên */
void sll_fifo_enqueue_l(sll_t list, long value) {
  sll_node_t nn = sll_create_node_l(value);
  return sll_push_back(list, nn);
}

long sll_fifo_dequeue_l(sll_t list) {
  long value = sll_fifo_peek_l(list);
  sll_pop_front(list);
  return value;
}

long sll_fifo_peek_l(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return sll_node_l_value(tmp);
}