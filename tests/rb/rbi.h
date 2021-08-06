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
static rbi_node_t rbi_create_color_node(int value, rb_node_color_t color);
static rbi_node_t rbi_insert(bn_tree_t t, int value);
static rbi_node_t rbi_search(bn_tree_t t, int value);
static rbi_node_t rbi_delete(bn_tree_t t, int value);
static void rbi_print_node(bn_node_t n);
static int rbi_similar_node(bn_node_t n1, bn_node_t n2);

// ========== Macro viết nhanh ===========

#define to_rbi(n) ((rbi_node_t)n)
#define rbi_value(x) to_rbi(x)->value

// ========== Định nghĩa hàm =============

static int rbi_compare(bn_node_t x, bn_node_t y) {
  return rbi_value(x) - rbi_value(y);
}

static rbi_node_t rbi_create_node(int value) {
  rbi_node_t n = calloc(1, sizeof(struct rbi_node));
  n->value = value;
  return n;
}

static rbi_node_t rbi_create_color_node(int value, rb_node_color_t color) {
  rbi_node_t n = rbi_create_node(value);
  rb_set_color(n, color);
  return n;
}

static rbi_node_t rbi_insert(bn_tree_t t, int value) {
  rbi_node_t n = rbi_create_node(value);
  bn_node_t y = bns_can_hold(t->root, n, rbi_compare);
  int order;
  if (y) {
    order = rbi_compare(n, y);
  }
  rb_insert_internal(t, n, y, order);
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

static void rbi_print_node(bn_node_t n) {
  printf("(%d, %s)\n", rbi_value(n), rb_color_str(n));
}

static int rbi_similar_node(bn_node_t n1, bn_node_t n2) {
  if (n1 == NULL_PTR && n2 == NULL_PTR) {
    return 0;
  }
  if ((n1 != NULL_PTR && n2 == NULL_PTR) ||
      (n1 == NULL_PTR && n2 != NULL_PTR)) {
    return 1;
  }
  return rbi_value(n1) == rbi_value(n2) && rb_color(n1) == rb_color(n2);
}

#endif  // TESTS_RB_RBI_H_
