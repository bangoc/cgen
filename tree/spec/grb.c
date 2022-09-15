/* (C) Nguyen Ba Ngoc 2022 */

#include "tree/spec/grb.h"

struct grbn *grb_create_node(gtype key) {
  struct rbn *tmp = rb_create_node();
  struct grbn *nn = realloc(tmp, sizeof(struct grbn));
  nn->key = key;
  return nn;
}

int grb_cmp_node(struct bnn *n1, struct bnn *n2, struct bnt *t) {
  return grb_tree(t)->cmp(grb_node(n1)->key, grb_node(n2)->key);
}

struct grbt *grb_create_tree(struct grbn *root, gtype_cmp_t cmp, gtype_free_t fk) {
  struct bnt *tmp = bn_create_tree(bn_node(root));
  struct grbt *t = realloc(tmp, sizeof(struct grbt));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

struct bs_ires grb_insert(struct grbt *t, gtype key) {
  struct grbn *nn = grb_create_node(key);
  return rb_insert(bn_tree(t), nn, grb_cmp_node);
}

struct bs_ires grb_insert_unique(struct grbt *t, gtype key) {
  struct grbn *nn = grb_create_node(key);
  struct bs_ires r = rb_insert_unique(bn_tree(t), nn, grb_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

struct grbn *grb_search(struct grbt *t, gtype key) {
  struct grbn sn = {.key = key};
  return grb_node(bs_search(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

struct grbn *grb_search_gte(struct grbt *t, gtype key) {
  struct grbn sn = {.key = key};
  return grb_node(bs_search_gte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

struct grbn *grb_search_lte(struct grbt *t, gtype key) {
  struct grbn sn = {.key = key};
  return grb_node(bs_search_lte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}


int grb_delete(struct grbt *t, struct grbn *dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return rb_delete(bn_tree(t), rb_node(dn));
}
