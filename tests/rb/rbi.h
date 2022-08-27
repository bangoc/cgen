/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "base/rb.h"

typedef struct rbi_node {
  struct rb_node_s rb_node;
  int value;
} *rbi_node_t;

// ========== Khai báo hàm ===============
static rbi_node_t rbi_create_node(int value);
static rbi_node_t rbi_create_color_node(int value, rb_node_color_t color);
static bn_node_t rbi_insert(bn_tree_t t, int value);
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

static int rbi_compare_data(int value, bn_node_t y) {
  return value - rbi_value(y);
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

static bn_node_t rbi_insert(bn_tree_t t, int value) {
  bn_node_t same = NULL, par = NULL;
  bn_node_t *loc;
  bns_insert_setup(loc, t->root, value, rbi_compare_data, same, par);
  bn_node_t n = bn_node(rbi_create_node(value));
  return rb_insert(t, n, loc, par);
}

static rbi_node_t rbi_search(bn_tree_t t, int value) {
  bns_search_inline(result, t, value, rbi_compare_data, return to_rbi(result));
}

static rbi_node_t rbi_delete(bn_tree_t t, int value) {
  rbi_node_t n = rbi_search(t, value);
  if (n) {
    if (rb_delete(t, bn_node(n)) == 1) {
      return n;
    }
  }
  return NULL;
}

static void rbi_print_node(bn_node_t n) {
  printf("(%d, %s)\n", rbi_value(n), rb_color_str(n));
}

static int rbi_similar_node(bn_node_t n1, bn_node_t n2) {
  if (n1 == NULL && n2 == NULL) {
    return 0;
  }
  if ((n1 != NULL && n2 == NULL) ||
      (n1 == NULL && n2 != NULL)) {
    return 1;
  }
  return rbi_value(n1) == rbi_value(n2) && rb_color(n1) == rb_color(n2);
}

#endif  // TESTS_RB_RBI_H_
