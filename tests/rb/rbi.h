/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#ifndef TESTS_RB_RBI_H_
#define TESTS_RB_RBI_H_

#include "tree/spec/grb.h"

// ========== Khai báo hàm ===============
static struct grbnode *rbi_create_node(int value);
static struct grbnode *rbi_create_color_node(int value, enum rbnode_color color);

static struct grbnode *__rbi_insert(struct bntree *t, int value);
#define rbi_insert(t, value) __rbi_insert(bn_tree(t), value)

static struct grbnode *__rbi_search(struct bntree *t, int value);
#define rbi_search(t, value) __rbi_search(bn_tree(t), value)

static struct grbtree *__rbi_create_tree(struct bnnode *root);
#define rbi_create_tree(root) __rbi_create_tree(bn_node(root))

static int __rbi_delete(struct bntree *t, int value);
#define rbi_delete(t, value) __rbi_delete(bn_tree(t), value)

static void rbi_print_node(struct bnnode *n);
static int rbi_similar_node(struct bnnode *n1, struct bnnode *n2);

// ========== Macro viết nhanh ===========

#define rbi_value(x) grb_node(x)->key.l

// ========== Định nghĩa hàm =============

static struct grbnode *rbi_create_node(int value) {
  return grb_create_node(gtype_l(value));
}

static struct grbnode *rbi_create_color_node(int value, enum rbnode_color color) {
  struct grbnode *n = rbi_create_node(value);
  rb_set_color(n, color);
  return n;
}

static struct grbnode *__rbi_insert(struct bntree *t, int value) {
  struct bs_ires ires = grb_insert(t, gtype_l(value));
  return grb_node(ires.nn);
}

static struct grbnode *__rbi_search(struct bntree *t, int value) {
  return grb_node(grb_search(t, gtype_l(value)));
}

static struct grbtree *__rbi_create_tree(struct bnnode *root) {
  struct grbtree *t = grb_create_tree(root, gtype_cmp_l, NULL);
  return t;
}

#define rbi_free_tree(t) grb_free_tree(grb_tree(t))

static int __rbi_delete(struct bntree *t, int value) {
  struct grbnode *n = rbi_search(t, value);
  if (n) {
    grb_delete(t, bn_node(n));
    return 1;
  }
  return 0;
}

static void rbi_print_node(struct bnnode *n) {
  printf("(%ld, %s)\n", grb_node(n)->key.l, rb_color_str(n));
}

static int rbi_similar_node(struct bnnode *n1, struct bnnode *n2) {
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
