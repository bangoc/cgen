/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gsl.h"

sll_node_t sll_create_node_g(gtype value) {
  sll_node_g_t nn = malloc(sizeof(struct sll_node_g_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void sll_push_back_g(sll_t list, gtype value) {
  sll_node_t node = sll_create_node_g(value);
  sll_push_back(list, node);
}

void sll_push_front_g(sll_t list, gtype value) {
  sll_node_t node = sll_create_node_g(value);
  sll_push_front(list, node);
}

gtype sll_pop_front_g(sll_t list) {
  gtype value = sll_front_g(list);
  sll_pop_front(list);
  return value;
}

gtype sll_front_g(sll_t list) {
  sll_node_t front = sll_front(list);
  return sll_node_g_value(front);
}