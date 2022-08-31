/* (C) Nguyen Ba Ngoc 2022 */

#include "tree/spec/grb.h"

grb_node_t grb_create_node(gtype key) {
  rb_node_t tmp = rb_create_node();
  grb_node_t nn = realloc(tmp, sizeof(struct _grb_node));
  nn->key = key;
  return nn;
}

int grb_cmp_node(bn_node_t n1, bn_node_t n2, bn_tree_t t) {
  return grb_tree(t)->cmp(grb_node(n1)->key, grb_node(n2)->key);
}

grb_tree_t grb_create_tree(grb_node_t root, gtype_cmp_t cmp, gtype_free_t fk) {
  bn_tree_t tmp = bn_create_tree(bn_node(root));
  grb_tree_t t = realloc(tmp, sizeof(struct _grb_tree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

bs_ires grb_insert(grb_tree_t t, gtype key) {
  grb_node_t nn = grb_create_node(key);
  return rb_insert(bn_tree(t), nn, grb_cmp_node);
}

bs_ires grb_insert_unique(grb_tree_t t, gtype key) {
  grb_node_t nn = grb_create_node(key);
  bs_ires r = rb_insert_unique(bn_tree(t), nn, grb_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

grb_node_t grb_search(grb_tree_t t, gtype key) {
  grb_node_s sn = {.key = key};
  return grb_node(bs_search(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

grb_node_t grb_search_gte(grb_tree_t t, gtype key) {
  grb_node_s sn = {.key = key};
  return grb_node(bs_search_gte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

grb_node_t grb_search_lte(grb_tree_t t, gtype key) {
  grb_node_s sn = {.key = key};
  return grb_node(bs_search_lte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}


int grb_delete(grb_tree_t t, grb_node_t dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return rb_delete(bn_tree(t), rb_node(dn));
}
