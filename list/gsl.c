/* (C) Nguyen Ba Ngoc 2021 */

#include "list/gsl.h"

struct gslnode *gsl_create_node(gtype value) {
  struct slnode *tmp = sll_create_node();
  struct gslnode *nn = realloc(tmp, sizeof(struct gslnode));
  nn->value = value;
  return nn;
}

struct gsllist *gsl_create_list(gtype_free_t free_value) {
  struct sllist *tmp = sll_create_list();
  struct gsllist *l = realloc(tmp, sizeof(struct gsllist));
  l->free_value = free_value;
  return l;
}

void gtype_free_gsl(gtype value) {
  gsl_free(value.gsl);
}

void gsl_pprint(struct gsllist *l, gtype_print_t pp) {
  gsl_traverse(cur, l) {
    pp(*cur);
    printf(" ");
  }
  printf("\n");
}