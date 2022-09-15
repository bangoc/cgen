/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Cấu trúc map dựa trên cây đỏ đen (rb)
*/

#include "tree/rbm.h"

#define tm_cmp_conv(u, x) cmp(u, rbm_node_key(x))

struct rbmnode *rbm_create_node(gtype key, gtype value) {
  struct rbnode *tmp = rb_create_node();
  struct rbmnode *n = realloc(tmp, sizeof(struct rbmnode));
  rbm_node_key(n) = key;
  rbm_node_value(n) = value;
  return n;
}

int rbm_cmp_node(struct bnnode *n1, struct bnnode *n2, struct bntree *t) {
  return rbm_tree(t)->cmp(rbm_node(n1)->key, rbm_node(n2)->key);
}

struct rbmtree *rbm_create(gtype_cmp_t cmp, gtype_free_t fk, gtype_free_t fv) {
  struct bntree *tmp = bn_create_tree(NULL);
  struct rbmtree *m = realloc(tmp, sizeof(struct rbmtree));
  m->cmp = cmp;
  m->fk = fk;
  m->fv = fv;
  m->size = 0;
  return m;
}

struct rbm_ires rbm_insert(struct rbmtree *t, gtype key, gtype value) {
  struct rbmnode *nn = rbm_create_node(key, value);
  struct bs_ires ires = rb_insert_unique(bn_tree(t), nn, rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return (struct rbm_ires){&rbm_node_value(ires.nn), 0};
  }
  ++t->size;
  return (struct rbm_ires){&rbm_node_value(ires.nn), 1};
}

gtype *rbm_put(struct rbmtree *t, gtype key, gtype value) {
  struct rbmnode *nn = rbm_create_node(key, value);
  struct bs_ires ires = rb_insert_unique(bn_tree(t), bn_node(nn), rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return &rbm_node_value(ires.nn);
  }
  ++t->size;
  return NULL;
}

struct rbmnode *rbm_search(struct rbmtree *t, gtype key) {
  struct rbmnode sn = {.key = key};
  return rbm_node(bs_search(bn_tree(t), bn_node(&sn), rbm_cmp_node));
}

gtype *rbm_value(struct rbmtree *t, gtype key) {
  struct rbmnode *n = rbm_search(t, key);
  if (n) {
    return &rbm_node_value(n);
  }
  return NULL;
}

int rbm_remove(struct rbmtree *t, gtype key) {
  struct rbmnode *n = rbm_search(t, key);
  if (!n) {
    return 0;
  }
  if (t->fk) {
    t->fk(n->key);
  }
  if (t->fv) {
    t->fv(n->value);
  }
  rb_delete((struct bntree *)t, bn_node(n));
  --(t->size);
  return 1;
}

void gtype_free_rbm(gtype value) {
  rbm_free(value.rbm);
}
