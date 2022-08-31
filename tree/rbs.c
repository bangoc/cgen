/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "tree/rbs.h"

#include <stdlib.h>

rbs_t rbs_create(gtype_cmp_t cmp, gtype_free_t fk) {
  bsg_tree_t t = bsg_create_tree(NULL, cmp, fk);
  rbs_t s = realloc(t, sizeof(struct red_black_set));
  s->size = 0;
  return s;
}

int rbs_insert(rbs_t s, gtype elem) {
  bs_ires ires = rb_insert_unique(bsg_tree(s), elem);
  if (ires.inserted) {
    ++(s->size);
  }
  return ires.inserted;
}

bsg_node_t rbs_search(rbs_t s, gtype elem) {
  return bsg_search(bsg_tree(s), elem);
}

int rbs_remove(rbs_t s, gtype elem) {
  bsg_node_t n = rbs_search(s, elem);
  if (!n) {
    return 0;
  }
  rb_delete(bsg_tree(s), n);
  --s->size;
  return 1;
}

void rbs_gtype_free(gtype value) {
  rbs_free(value.rbs);
}
