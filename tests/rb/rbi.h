/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "tree/rb.h"

// ========== Khai báo hàm ===============
static rb_node_t rbi_create_node(int value);
static rb_node_t rbi_create_color_node(int value, rb_node_color_t color);
static rb_node_t rbi_insert(bn_tree_t t, int value);
static rb_node_t rbi_search(bn_tree_t t, int value);
static gbs_tree_t rbi_create_tree(bn_node_t root);
static int rbi_delete(bn_tree_t t, int value);
static void rbi_print_node(bn_node_t n);
static int rbi_similar_node(bn_node_t n1, bn_node_t n2);

// ========== Macro viết nhanh ===========

#define rbi_value(x) gbs_node(x)->key.l

// ========== Định nghĩa hàm =============

static rb_node_t rbi_create_node(int value) {
  return rb_create_node(gtype_l(value));
}

static rb_node_t rbi_create_color_node(int value, rb_node_color_t color) {
  rb_node_t n = rbi_create_node(value);
  rb_set_color(n, color);
  return n;
}

static rb_node_t rbi_insert(bn_tree_t t, int value) {
  bs_ires ires = rb_insert(t, gtype_l(value));
  return rb_node(ires.nn);
}

static rb_node_t rbi_search(bn_tree_t t, int value) {
  return rb_node(gbs_search(t, gtype_l(value)));
}

static gbs_tree_t rbi_create_tree(bn_node_t root) {
  gbs_tree_t t = gbs_create_tree(root, gtype_cmp_l, NULL);
}

#define rbi_free_tree(t) gbs_free_tree(gbs_tree(t))

static int rbi_delete(bn_tree_t t, int value) {
  rb_node_t n = rbi_search(t, value);
  if (n) {
    rb_delete(t, bn_node(n));
    return 1;
  }
  return 0;
}

static void rbi_print_node(bn_node_t n) {
  printf("(%ld, %s)\n", gbs_node(n)->key.l, rb_color_str(n));
}

static int rbi_similar_node(bn_node_t n1, bn_node_t n2) {
  if (n1 == NULL && n2 == NULL) {
    return 0;
  }
  if ((n1 != NULL && n2 == NULL) ||
      (n1 == NULL && n2 != NULL)) {
    return 1;
  }
  return gbs_node(n1)->key.l == gbs_node(n2)->key.l &&
         rb_color(n1) == rb_color(n2);
}

#endif  // TESTS_RB_RBI_H_
