/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "tree/spec/grb.h"

// ========== Khai báo hàm ===============
static grb_node_t rbi_create_node(int value);
static grb_node_t rbi_create_color_node(int value, rb_node_color_t color);
static grb_node_t rbi_insert(bn_tree_t t, int value);
static grb_node_t rbi_search(bn_tree_t t, int value);
static grb_tree_t rbi_create_tree(bn_node_t root);
static int rbi_delete(bn_tree_t t, int value);
static void rbi_print_node(bn_node_t n);
static int rbi_similar_node(bn_node_t n1, bn_node_t n2);

// ========== Macro viết nhanh ===========

#define rbi_value(x) grb_node(x)->key.l

// ========== Định nghĩa hàm =============

static grb_node_t rbi_create_node(int value) {
  return grb_create_node(gtype_l(value));
}

static grb_node_t rbi_create_color_node(int value, rb_node_color_t color) {
  grb_node_t n = rbi_create_node(value);
  rb_set_color(n, color);
  return n;
}

static grb_node_t rbi_insert(bn_tree_t t, int value) {
  bs_ires ires = grb_insert(t, gtype_l(value));
  return grb_node(ires.nn);
}

static grb_node_t rbi_search(bn_tree_t t, int value) {
  return grb_node(grb_search(t, gtype_l(value)));
}

static grb_tree_t rbi_create_tree(bn_node_t root) {
  grb_tree_t t = grb_create_tree(root, gtype_cmp_l, NULL);
  return t;
}

#define rbi_free_tree(t) grb_free_tree(grb_tree(t))

static int rbi_delete(bn_tree_t t, int value) {
  grb_node_t n = rbi_search(t, value);
  if (n) {
    grb_delete(t, bn_node(n));
    return 1;
  }
  return 0;
}

static void rbi_print_node(bn_node_t n) {
  printf("(%ld, %s)\n", grb_node(n)->key.l, rb_color_str(n));
}

static int rbi_similar_node(bn_node_t n1, bn_node_t n2) {
  if (n1 == NULL && n2 == NULL) {
    return 0;
  }
  if ((n1 != NULL && n2 == NULL) ||
      (n1 == NULL && n2 != NULL)) {
    return 1;
  }
  return grb_node(n1)->key.l == grb_node(n2)->key.l &&
         rb_color(n1) == rb_color(n2);
}

#endif  // TESTS_RB_RBI_H_
