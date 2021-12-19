/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gsl.h"

sll_node_t gsl_create_node(gtype value) {
  gsn_t nn = malloc(sizeof(struct gsn_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void gsl_push_back(sll_t list, gtype value) {
  sll_node_t node = gsl_create_node(value);
  sll_push_back(list, node);
}

void gsl_push_front(sll_t list, gtype value) {
  sll_node_t node = gsl_create_node(value);
  sll_push_front(list, node);
}

gtype gsl_pop_front(sll_t list) {
  gtype value = gsl_front(list);
  sll_pop_front(list);
  return value;
}

gtype gsl_front(sll_t list) {
  sll_node_t front = sll_front(list);
  return gsn_value(front);
}
