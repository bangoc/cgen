/* (C) Nguyen Ba Ngoc 2022 */

#include "tree/spec/grb.h"

struct grbnode *grb_create_node(gtype key) {
  struct rbnode *tmp = rb_create_node();
  struct grbnode *nn = realloc(tmp, sizeof(struct grbnode));
  nn->key = key;
  return nn;
}

int grb_cmp_node(struct bnnode *n1, struct bnnode *n2, struct bntree *t) {
  return grb_tree(t)->cmp(grb_node(n1)->key, grb_node(n2)->key);
}

struct grbtree *__grb_create_tree(struct grbnode *root, gtype_cmp_t cmp, gtype_free_t fk) {
  struct bntree *tmp = bn_create_tree(bn_node(root));
  struct grbtree *t = realloc(tmp, sizeof(struct grbtree));
  t->cmp = cmp;
  t->fk = fk;
  return t;
}

struct bs_ires __grb_insert(struct grbtree *t, gtype key) {
  struct grbnode *nn = grb_create_node(key);
  return rb_insert(bn_tree(t), nn, grb_cmp_node);
}

struct bs_ires __grb_insert_unique(struct grbtree *t, gtype key) {
  struct grbnode *nn = grb_create_node(key);
  struct bs_ires r = rb_insert_unique(bn_tree(t), nn, grb_cmp_node);
  if (!r.inserted) {
    free(nn);
  }
  return r;
}

struct grbnode *__grb_search(struct grbtree *t, gtype key) {
  struct grbnode sn = {.key = key};
  return grb_node(bs_search(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

struct grbnode *__grb_search_gte(struct grbtree *t, gtype key) {
  struct grbnode sn = {.key = key};
  return grb_node(bs_search_gte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}

struct grbnode *__grb_search_lte(struct grbtree *t, gtype key) {
  struct grbnode sn = {.key = key};
  return grb_node(bs_search_lte(bn_tree(t), bn_node(&sn), grb_cmp_node));
}


int __grb_delete(struct grbtree *t, struct grbnode *dn) {
  if (t->fk) {
    t->fk(dn->key);
  }
  return rb_delete(bn_tree(t), rb_node(dn));
}
