/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Cấu trúc map dựa trên cây đỏ đen (rb)
*/

#include "tree/rbm.h"

#define tm_cmp_conv(u, x) cmp(u, rbm_node_key(x))

struct rbmn *rbm_create_node(gtype key, gtype value) {
  struct rbn *tmp = rb_create_node();
  struct rbmn *n = realloc(tmp, sizeof(struct rbmn));
  rbm_node_key(n) = key;
  rbm_node_value(n) = value;
  return n;
}

int rbm_cmp_node(struct bnn *n1, struct bnn *n2, struct bnt *t) {
  return rbm_tree(t)->cmp(rbm_node(n1)->key, rbm_node(n2)->key);
}

struct rbm *rbm_create(gtype_cmp_t cmp, gtype_free_t fk, gtype_free_t fv) {
  struct bnt *tmp = bn_create_tree(NULL);
  struct rbm *m = realloc(tmp, sizeof(struct rbm));
  m->cmp = cmp;
  m->fk = fk;
  m->fv = fv;
  m->size = 0;
  return m;
}

struct rbm_ires rbm_insert(struct rbm *t, gtype key, gtype value) {
  struct rbmn *nn = rbm_create_node(key, value);
  struct bs_ires ires = rb_insert_unique(bn_tree(t), nn, rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return (struct rbm_ires){&rbm_node_value(ires.nn), 0};
  }
  ++t->size;
  return (struct rbm_ires){&rbm_node_value(ires.nn), 1};
}

gtype *rbm_put(struct rbm *t, gtype key, gtype value) {
  struct rbmn *nn = rbm_create_node(key, value);
  struct bs_ires ires = rb_insert_unique(bn_tree(t), bn_node(nn), rbm_cmp_node);
  if (!ires.inserted) {
    free(nn);
    return &rbm_node_value(ires.nn);
  }
  ++t->size;
  return NULL;
}

struct rbmn *rbm_search(struct rbm *t, gtype key) {
  struct rbmn sn = {.key = key};
  return rbm_node(bs_search(bn_tree(t), bn_node(&sn), rbm_cmp_node));
}

gtype *rbm_value(struct rbm *t, gtype key) {
  struct rbmn *n = rbm_search(t, key);
  if (n) {
    return &rbm_node_value(n);
  }
  return NULL;
}

int rbm_remove(struct rbm *t, gtype key) {
  struct rbmn *n = rbm_search(t, key);
  if (!n) {
    return 0;
  }
  if (t->fk) {
    t->fk(n->key);
  }
  if (t->fv) {
    t->fv(n->value);
  }
  rb_delete((struct bnt *)t, bn_node(n));
  --(t->size);
  return 1;
}

void gtype_free_rbm(gtype value) {
  rbm_free(value.rbm);
}
