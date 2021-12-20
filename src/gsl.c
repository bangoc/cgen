/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "gsl.h"

gsn_t gsn_create(gtype value) {
  sln_t tmp = sln_create();
  gsn_t nn = realloc(tmp, sizeof(struct gsn_s));
  nn->value = value;
  return nn;
}

gsl_t gsl_create(gtype_free_t free_value) {
  sll_t tmp = sll_create();
  gsl_t list = realloc(tmp, sizeof(struct gsl_s));
  list->free_value = free_value;
  return list;
}

void gsl_push_back(gsl_t list, gtype value) {
  gsn_t node = gsn_create(value);
  sll_push_back(to_sll(list), to_sln(node));
}

void gsl_push_front(gsl_t list, gtype value) {
  gsn_t node = gsn_create(value);
  sll_push_front(to_sll(list), to_sln(node));
}

void gsl_pop_front(gsl_t list) {
  if (list->free_value) {
    list->free_value(gsl_front(list));
  }
  sll_pop_front(to_sll(list));
}

gtype gsl_front(gsl_t list) {
  sln_t front = list->base.front;
  return gsn_value(front);
}

gsn_t gsl_front_node(gsl_t list) {
  return to_gsn(list->base.front);
}