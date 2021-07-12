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

#define to_tm(n) ((treemap_node_t)n)
#define tm_key_from_bn_node(n) to_tm(n)->key
#define tm_value_from_bn_node(n) to_tm(n)->value
#define tm_postorder_foreach_inline(cur, t) \
  for (void *cur = bn_first_postorder(t); cur != NULL_PTR; cur = bn_next_postorder(cur))

// ========== Định nghĩa hàm =============

static treemap_node_t tm_create_node(gtype key, gtype value) {
  treemap_node_t n = malloc(sizeof(struct treemap_node));
  rb_node_init_null((&n->rb_node));
  n->key = key;
  n->value = value;
  return n;
}

static treemap_node_t tm_insert(bn_tree_t t,
                      gtype key, gtype value,
                      bn_compare_t cmp) {
  treemap_node_t n = tm_create_node(key, value);
  rb_insert(t, to_bn(n), cmp);
  return n;
}

static treemap_node_t tm_search(bn_tree_t t, gtype key, bn_compare_t cmp) {
  static struct treemap_node query;
  query.key = key;
  bn_node_t n = bns_search(t->root, to_bn(&query), cmp);
  return to_tm(n);
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
    rb_delete(t, to_bn(n));
    if (cb) {
      cb(n);
    }
    return 1;
  }
  return 0;
}

#endif  // TREEMAP_H_