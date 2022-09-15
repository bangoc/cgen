/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "tree/spec/grb.h"

// ========== Khai báo hàm ===============
static struct grbn *rbi_create_node(int value);
static struct grbn *rbi_create_color_node(int value, enum rb_node_color color);
static struct grbn *rbi_insert(struct bnt *t, int value);
static struct grbn *rbi_search(struct bnt *t, int value);
static struct grbt *rbi_create_tree(struct bnn *root);
static int rbi_delete(struct bnt *t, int value);
static void rbi_print_node(struct bnn *n);
static int rbi_similar_node(struct bnn *n1, struct bnn *n2);

// ========== Macro viết nhanh ===========

#define rbi_value(x) grb_node(x)->key.l

// ========== Định nghĩa hàm =============

static struct grbn *rbi_create_node(int value) {
  return grb_create_node(gtype_l(value));
}

static struct grbn *rbi_create_color_node(int value, enum rb_node_color color) {
  struct grbn *n = rbi_create_node(value);
  rb_set_color(n, color);
  return n;
}

static struct grbn *rbi_insert(struct bnt *t, int value) {
  struct bs_ires ires = grb_insert(t, gtype_l(value));
  return grb_node(ires.nn);
}

static struct grbn *rbi_search(struct bnt *t, int value) {
  return grb_node(grb_search(t, gtype_l(value)));
}

static struct grbt *rbi_create_tree(struct bnn *root) {
  struct grbt *t = grb_create_tree(root, gtype_cmp_l, NULL);
  return t;
}

#define rbi_free_tree(t) grb_free_tree(grb_tree(t))

static int rbi_delete(struct bnt *t, int value) {
  struct grbn *n = rbi_search(t, value);
  if (n) {
    grb_delete(t, bn_node(n));
    return 1;
  }
  return 0;
}

static void rbi_print_node(struct bnn *n) {
  printf("(%ld, %s)\n", grb_node(n)->key.l, rb_color_str(n));
}

static int rbi_similar_node(struct bnn *n1, struct bnn *n2) {
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
