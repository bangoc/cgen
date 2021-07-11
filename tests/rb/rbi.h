/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "rb.h"

typedef struct rbi_node {
  struct rb_node rb_node;
  int value;
} *rbi_node_t;

// ========== Khai báo hàm ===============
static rbi_node_t rbi_create_node(int value);
static rbi_node_t rbi_insert(bn_tree_t t, int value);
static rbi_node_t rbi_search(bn_tree_t t, int value);

// ========== Macro viết nhanh ===========

#define rbi_container_of(x) container_of(container_of(x, struct rb_node, bn_node), \
                                struct rbi_node, rb_node)
#define rbi_bn_node(x) &((x)->rb_node.bn_node)

// ========== Định nghĩa hàm =============

static int rbi_value(bn_node_t x) {
  rbi_node_t nd = rbi_container_of(x);
  return nd->value;
}

static int rbi_compare(bn_node_t x, bn_node_t y) {
  return rbi_value(x) - rbi_value(y);
}

static rbi_node_t rbi_create_node(int value) {
  rbi_node_t n = malloc(sizeof(struct rbi_node));
  rb_node_init((&n->rb_node), NULL_PTR, NULL_PTR, NULL_PTR, RB_BLACK);
  n->value = value;
  return n;
}

static rbi_node_t rbi_insert(bn_tree_t t, int value) {
  rbi_node_t n = rbi_create_node(value);
  rb_insert(t, rbi_bn_node(n), rbi_compare);
  return n;
}

static rbi_node_t rbi_search(bn_tree_t t, int value) {
  static struct rbi_node query;
  query.value = value;
  bn_node_t r = bns_search(t->root, rbi_bn_node(&query), rbi_compare);
  return r? rbi_container_of(r): NULL_PTR;
}

#endif  // TESTS_RB_RBI_H_