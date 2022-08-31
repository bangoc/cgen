/*
  (C) Nguyen Ba Ngoc 2021
  Cấu trúc map dựa trên cây đỏ đen (rb)
*/

#include "tree/rbm.h"

#define tm_cmp_conv(u, x) cmp(u, rbm_node_key(x))

rbm_node_t rbm_create_node(gtype key, gtype value) {
  rbm_node_t n = calloc(1, sizeof(struct red_black_map_node));
  rbm_node_key(n) = key;
  rbm_node_value(n) = value;
  return n;
}

rbm_t rbm_create_map(gtype_cmp_t cmp, gtype_free_t fk, gtype_free_t fv) {
  gbs_tree_t t = gbs_create_tree(NULL, cmp, fk);
  rbm_t m = realloc(t, sizeof(struct red_black_map));
  m->fv = fv;
  m->size = 0;
  return m;
}

rbm_ires rbm_insert(rbm_t t, gtype key, gtype value) {
  bs_ires ires = grb_insert_unique(gbs_tree(t), key);
  if (!ires.inserted) {
    return (rbm_ires){&rbm_node_value(ires.nn), 0};
  }
  rbm_node_t nn = realloc(ires.nn, sizeof(struct red_black_map_node));
  bn_recover(ires.nn, nn, t);
  nn->value = value;
  ++t->size;
  return (rbm_ires){&rbm_node_value(nn), 1};
}

gtype *rbm_put(rbm_t t, gtype key, gtype value) {
  bs_ires ires = grb_insert_unique(gbs_tree(t), key);
  if (!ires.inserted) {
    return &rbm_node_value(ires.nn);
  }
  rbm_node_t nn = realloc(ires.nn, sizeof(struct red_black_map_node));
  bn_recover(ires.nn, nn, t);
  nn->value = value;
  ++t->size;
  return NULL;
}

rbm_node_t rbm_search(rbm_t t, gtype key) {
  return rbm_node(gbs_search(gbs_tree(t), key));
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
  if (t->fv) {
    t->fv(rbm_node_value(n));
  }
  grb_delete((bn_tree_t)t, bn_node(n));
  --(t->size);
  return 1;
}

void gtype_free_rbm(gtype value) {
  rbm_free(value.rbm);
}
