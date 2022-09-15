/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gsl.h"

struct gsn *gsl_create_node(gtype value) {
  struct sln *tmp = sll_create_node();
  struct gsn *nn = realloc(tmp, sizeof(struct gsn));
  nn->value = value;
  return nn;
}

struct gsl *gsl_create_list(gtype_free_t free_value) {
  struct sll *tmp = sll_create_list();
  struct gsl *l = realloc(tmp, sizeof(struct gsl));
  l->free_value = free_value;
  return l;
}

void gtype_free_gsl(gtype value) {
  gsl_free(value.gsl);
}

void gsl_pprint(struct gsl *l, gtype_print_t pp) {
  gsl_traverse(cur, l) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}