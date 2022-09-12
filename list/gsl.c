/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gsl.h"

gsn_t gsl_create_node(gtype value) {
  sln_t tmp = sll_create_node();
  gsn_t nn = realloc(tmp, sizeof(struct gtype_single_linked_node));
  nn->value = value;
  return nn;
}

gsl_t gsl_create_list(gtype_free_t free_value) {
  sll_t tmp = sll_create_list();
  gsl_t l = realloc(tmp, sizeof(struct gtype_single_linked_list));
  l->free_value = free_value;
  return l;
}

long gsl_size(gsl_t list) {
  gtype *tmp = gsl_front(list);
  long sz = 0;
  while (tmp) {
    ++sz;
    tmp = gsl_node_next(tmp);
  }
  return sz;
}

void gtype_free_gsl(gtype value) {
  gsl_free(value.gsl);
}

void gsl_pprint(gsl_t l, gtype_print_t pp) {
  gsl_traverse(cur, l) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}