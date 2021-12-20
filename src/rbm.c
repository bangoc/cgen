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

rbm_t rbm_create(gtype_cmp_t cmp,
    gtype_free_t free_key, gtype_free_t free_value) {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbm_t m = realloc(t, sizeof(struct rbm_s));
  m->cmp = cmp;
  m->free_key = free_key;
  m->free_value = free_value;
  return m;
}

rbm_ires rbm_insert(rbm_t t, gtype key, gtype value) {
  bn_node_t same = NULL_PTR, parent = NULL_PTR;
  bn_node_t *loc;
  gtype_cmp_t cmp = t->cmp;
  bns_insert_setup(loc, t->t.root, key, tm_cmp_conv, same, parent);
  if (same) {
    return (rbm_ires){to_rbm(same), 0};
  }
  rbm_node_t n = rbm_create_node(key, value);
  rb_insert((bn_tree_t)t, to_bn(n), loc, parent);
  return (rbm_ires){n, 1};
}

rbm_node_t rbm_search(rbm_t t, gtype key) {
  gtype_cmp_t cmp = t->cmp;
  bns_search_inline(n, ((bn_tree_t)t), key, tm_cmp_conv, return to_rbm(n));
}

gtype *rbm_vref(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (n) {
    return &n->value;
  }
  return NULL;
}

int rbm_remove(rbm_t t, gtype key) {
  rbm_node_t n = rbm_search(t, key);
  if (!n) {
    return 0;
  }
  rb_delete((bn_tree_t)t, to_bn(n));
  if (t->free_key) {
    t->free_key(n->key);
  }
  if (t->free_value) {
    t->free_value(n->value);
  }
  free(n);
  return 1;
}
