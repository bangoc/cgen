/*
  (C) Nguyen Ba Ngoc 2021
  Cấu trúc map dựa trên cây đỏ đen (rb)
*/

#include "rbm.h"

#define tm_cmp_conv(u, x) cmp(u, rbm_node_key(x))

rbm_node_t rbm_create_node(gtype key, gtype value) {
  rbm_node_t n = calloc(1, sizeof(struct rbm_node));
  n->key = key;
  n->value = value;
  return n;
}

rbm_node_t rbm_insert(rbm_t t, gtype key, gtype value) {
  bn_node_t same = NULL_PTR, parent = NULL_PTR;
  bn_node_t *loc;
  bn_compare_t cmp = t->cmp;
  bns_insert_setup(loc, t->t.root, key, tm_cmp_conv, same, parent);
  if (same) {
    return to_rbm(same);
  }
  rbm_node_t n = rbm_create_node(key, value);
  rb_insert((bn_tree_t)t, to_bn(n), loc, parent);
  return n;
}

rbm_t rbm_create(bn_compare_t cmp) {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbm_t m = realloc(t, sizeof(struct rbm_s));
  m->cmp = cmp;
  return m;
}

rbm_node_t rbm_search(rbm_t t, gtype key) {
  bn_compare_t cmp = t->cmp;
  bns_search_inline(n, ((bn_tree_t)t), key, tm_cmp_conv, return to_rbm(n));
}

gtype *rbm_vref(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (n) {
    return &n->value;
  }
  return NULL;
}

rbm_node_t rbm_delete(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (n) {
    rb_delete((bn_tree_t)t, to_bn(n));
  }
  return n;
}