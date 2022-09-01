/*
  (C) Nguyen Ba Ngoc 2021
  Cấu trúc map dựa trên cây đỏ đen (rb)
*/

#include "tree/rbm.h"

#define tm_cmp_conv(u, x) cmp(u, rbm_node_key(x))

rbm_node_t rbm_create_node(gtype key, gtype value) {
  rb_node_t tmp = rb_create_node();
  rbm_node_t n = realloc(tmp, sizeof(struct red_black_map_node));
  rbm_node_key(n) = key;
  rbm_node_value(n) = value;
  return n;
}

int rbm_cmp_node(bn_node_t n1, bn_node_t n2, bn_tree_t t) {
  return rbm_tree(t)->cmp(rbm_node(n1)->key, rbm_node(n2)->key);
}

rbm_t rbm_create(gtype_cmp_t cmp, gtype_free_t fk, gtype_free_t fv) {
  bn_tree_t tmp = bn_create_tree(NULL);
  rbm_t m = realloc(tmp, sizeof(struct red_black_map));
  m->cmp = cmp;
  m->fk = fk;
  m->fv = fv;
  m->size = 0;
  return m;
}

rbm_ires rbm_insert(rbm_t t, gtype key, gtype value) {
  rbm_node_t nn = rbm_create_node(key, value);
  bs_ires ires = rb_insert_unique(bn_tree(t), nn, rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return (rbm_ires){&rbm_node_value(ires.nn), 0};
  }
  ++t->size;
  return (rbm_ires){&rbm_node_value(ires.nn), 1};
}

gtype *rbm_put(rbm_t t, gtype key, gtype value) {
  rbm_node_t nn = rbm_create_node(key, value);
  bs_ires ires = rb_insert_unique(bn_tree(t), bn_node(nn), rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return &rbm_node_value(ires.nn);
  }
  ++t->size;
  return NULL;
}

rbm_node_t rbm_search(rbm_t t, gtype key) {
  rbm_node_s sn = {.key = key};
  return rbm_node(bs_search(bn_tree(t), bn_node(&sn), rbm_cmp_node));
}

gtype *rbm_value(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (n) {
    return &rbm_node_value(n);
  }
  return NULL;
}

int rbm_remove(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (!n) {
    return 0;
  }
  if (t->fk) {
    t->fk(n->key);
  }
  if (t->fv) {
    t->fv(n->value);
  }
  rb_delete((bn_tree_t)t, bn_node(n));
  --(t->size);
  return 1;
}

void gtype_free_rbm(gtype value) {
  rbm_free(value.rbm);
}
