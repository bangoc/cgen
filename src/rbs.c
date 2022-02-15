/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "rbs.h"

#include <stdlib.h>

#define rbs_cmp_conv(u, x) cmp(u, rbs_node_value(x))

rbs_node_t rbs_create_node(gtype elem) {
  rb_node_t n = rb_create_node();
  rbs_node_t nn = realloc(n, sizeof(struct red_black_set_node));
  nn->value = elem;
  return nn;
}

rbs_t rbs_create(gtype_cmp_t cmp, gtype_free_t free_key) {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbs_t s = realloc(t, sizeof(struct red_black_set));
  s->cmp = cmp;
  s->free_key = free_key;
  s->size = 0;
  return s;
}

int rbs_insert(rbs_t s, gtype elem) {
  bn_node_t same = NULL, par = NULL;
  bn_node_t *loc;
  gtype_cmp_t cmp = s->cmp;
  bns_insert_setup(loc, s->t.root, elem, rbs_cmp_conv, same, par);
  if (same) {
    return 0;
  }
  rbs_node_t n = rbs_create_node(elem);
  rb_insert((bn_tree_t)s, to_bn(n), loc, par);
  ++(s->size);
  return 1;
}

rbs_node_t rbs_search(rbs_t s, gtype elem) {
  gtype_cmp_t cmp = s->cmp;
  bns_search_inline(n, ((bn_tree_t)s), elem, rbs_cmp_conv, return to_rbs(n));
}

int rbs_remove(rbs_t s, gtype elem) {
  rbs_node_t n = rbs_search(s, elem);
  if (!n) {
    return 0;
  }
  rb_delete((bn_tree_t)s, to_bn(n));
  if (s->free_key) {
    s->free_key(rbs_node_value(n));
  }
  free(n);
  --(s->size);
  return 1;
}

void rbs_gtype_free(gtype value) {
  rbs_free(value.rbs);
}