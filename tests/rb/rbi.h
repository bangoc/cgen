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
static rbi_node_t rbi_delete(bn_tree_t t, int value);
static void rbi_node_print(bn_node_t n);

// ========== Macro viết nhanh ===========

#define to_rbi(n) ((rbi_node_t)n)

// ========== Định nghĩa hàm =============

static int rbi_value(bn_node_t x) {
  return to_rbi(x)->value;
}

static int rbi_compare(bn_node_t x, bn_node_t y) {
  return rbi_value(x) - rbi_value(y);
}

static rbi_node_t rbi_create_node(int value) {
  rbi_node_t n = malloc(sizeof(struct rbi_node));
  rb_node_init_null((&n->rb_node));
  n->value = value;
  return n;
}

static rbi_node_t rbi_insert(bn_tree_t t, int value) {
  rbi_node_t n = rbi_create_node(value);
  rb_insert(t, to_bn(n), rbi_compare);
  return n;
}

static rbi_node_t rbi_search(bn_tree_t t, int value) {
  static struct rbi_node query;
  query.value = value;
  bn_node_t r = bns_search(t->root, to_bn(&query), rbi_compare);
  return to_rbi(r);
}

static rbi_node_t rbi_delete(bn_tree_t t, int value) {
  rbi_node_t n = rbi_search(t, value);
  if (n) {
    if (rb_delete(t, to_bn(n)) == 1) {
      return n;
    }
  }
  return NULL_PTR;
}

static void rbi_node_print(bn_node_t n) {
  printf("%d\n", rbi_value(n));
}

#endif  // TESTS_RB_RBI_H_