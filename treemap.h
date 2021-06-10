/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef TREEMAP_H_
#define TREEMAP_H_

#include "rb.h"
#include "gtype.h"

typedef struct treemap_node {
  struct rb_node rb_node;
  gtype key, value;
} *treemap_node_t;

static gtype k_tm_invalid = (gtype){.i = -1};

// ========== Khai báo hàm ===============

static bn_tree_t tm_create();
static treemap_node_t tm_create_node(gtype key, gtype value);
static treemap_node_t tm_insert(bn_tree_t t, gtype key, gtype value,
                      bn_compare_t cmp);
static int tm_value_ref(bn_tree_t t, gtype key, gtype **value,
                          bn_compare_t cmp);
static gtype tm_value(bn_tree_t t, gtype key,
                      bn_compare_t cmp);
static treemap_node_t tm_search(bn_tree_t t, gtype key, bn_compare_t cmp);
static int tm_delete(bn_tree_t t, gtype key,
                      bn_compare_t cmp,
                      bn_callback_t cb);


// ========== Macro viết nhanh ===========

#define tm_container_of(x) container_of(\
      container_of(x, struct rb_node, bn_node), \
      struct treemap_node, rb_node)
#define tm_bn_node(x) &(x->rb_node.bn_node)
#define tm_key_from_bn_node(n) ((treemap_node_t)tm_container_of(n))->key
#define tm_value_from_bn_node(n) ((treemap_node_t)tm_container_of(n))->value
#define tm_postorder_foreach_inline(cur, t) \
  for (bn_node_t tmp = bn_first_postorder(t), cur = tm_container_of(tmp); tmp != NULL_PTR; tmp = bn_next_postorder(tmp), cur = tm_container_of(tmp))

// ========== Định nghĩa hàm =============

static bn_tree_t tm_create() {
  return bn_create_tree(NULL_PTR);
}

static treemap_node_t tm_create_node(gtype key, gtype value) {
  treemap_node_t n = malloc(sizeof(struct treemap_node));
  rb_node_init((&n->rb_node), NULL_PTR, NULL_PTR, NULL_PTR, RB_BLACK);
  n->key = key;
  n->value = value;
  return n;
}

static treemap_node_t tm_insert(bn_tree_t t,
                      gtype key, gtype value,
                      bn_compare_t cmp) {
  treemap_node_t n = tm_create_node(key, value);
  rb_insert(t, tm_bn_node(n), cmp);
  return n;
}

static treemap_node_t tm_search(bn_tree_t t, gtype key, bn_compare_t cmp) {
  static struct treemap_node query;
  query.key = key;
  bn_node_t n = bns_search(t->root, tm_bn_node((&query)), cmp);
  return tm_container_of(n);
}

static int tm_value_ref(bn_tree_t t, gtype key, gtype **value,
                          bn_compare_t cmp) {
  treemap_node_t n = tm_search(t, key, cmp);
  if (n) {
    *value = &(n->value);
    return 0;
  }
  *value = NULL_PTR;
  return 1;
}

static gtype tm_value(bn_tree_t t, gtype key, bn_compare_t cmp) {
  gtype *value = NULL_PTR;
  tm_value_ref(t, key, &value, cmp);
  if (value) {
    return *value;
  }
  return k_tm_invalid;
}

static int tm_delete(bn_tree_t t, gtype key, bn_compare_t cmp, bn_callback_t cb) {
  treemap_node_t n = tm_search(t, key, cmp);
  if (n) {
    rb_delete(t, tm_bn_node(n));
    if (cb) {
      cb(n);
    }
    return 1;
  }
  return 0;
}

#endif  // TREEMAP_H_