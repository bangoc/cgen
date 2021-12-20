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
