/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
  Cài đặt khái quát của cây đỏ-đen,
  tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef RBI_H_
#define RBI_H_

#include "bn.h"
#include "bns.h"

typedef enum {
  RB_BLACK,
  RB_RED
} rb_node_color_t;

typedef struct rb_node {
  struct bn_node bn_node;
  rb_node_color_t color;
} *rb_node_t;

/*
  Trong triển khai này mình sử dụng NULL thay vì lính canh (một
  rbi_node đặc biệt) để tương thích tốt hơn với các api của cây nhị
  phân tìm kiếm cơ bản.
 */

/* Nút NULL được quy ước là nút đen */
#define rb_color(x) (x? (container_of(x, struct rb_node, bn_node))->color: RB_BLACK)
#define rb_set_color(x, new_color) (container_of(x, struct rb_node, bn_node))->color = new_color
#define rb_bn_node(n) (n? ((bn_node_t)&(n->bn_node)): NULL_PTR)
#define rb_node_init(n, left_value, right_value, top_value, color_value) \
  bn_node_init(rb_bn_node(n), left_value, right_value, top_value); \
  n->color = color_value

static rb_node_t rb_create_node() {
  rb_node_t n = malloc(sizeof(struct rb_node));
  rb_node_init(n, NULL_PTR, NULL_PTR, NULL_PTR, RB_BLACK);
  return n;
}

static bn_tree_t rb_create_tree() {
  return bn_create_tree(NULL_PTR);
}

#define IMPL_ROTATION(t, x, left, right) \
static bn_node_t bn_ ##left ##_rotate(bn_tree_t t, bn_node_t x) { \
  bn_node_t y = x->right; \
  x->right = y->left; \
  if (y->left != NULL_PTR) { \
    y->left->top = x; \
  } \
  y->top = x->top; \
  if (x->top == NULL_PTR) { \
    t->root = y; \
  } else if (x == x->top->left) { \
    x->top->left = y; \
  } else { \
    x->top->right = y; \
  } \
  y->left = x; \
  x->top = y; \
  return y; \
}

IMPL_ROTATION(t, x, left, right)
IMPL_ROTATION(t, x, right, left)
#undef IMPL_ROTATION

static bn_tree_t rb_insert_fixup(bn_tree_t t, bn_node_t z) {
  while (rb_color(z->top) == RB_RED) {
    if (z->top == z->top->top->left) {
#define IMPL_INSERT_FIXUP(left, right) \
      bn_node_t y = z->top->top->right; \
      if (rb_color(y) == RB_RED) { \
        rb_set_color(z->top, RB_BLACK); \
        rb_set_color(y, RB_BLACK); \
        rb_set_color(z->top->top, RB_RED); \
        z = z->top->top; \
      } else { \
        if (z == z->top->right) { \
          z = z->top; \
          bn_ ##left ##_rotate(t, z); \
        } \
        rb_set_color(z->top, RB_BLACK); \
        rb_set_color(z->top->top, RB_RED); \
        bn_ ##right ##_rotate(t, z->top->top); \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
  }
  rb_set_color(t->root, RB_BLACK);
  return t;
}

#undef IMPL_INSERT_FIXUP

static bn_tree_t rb_insert(bn_tree_t t, bn_node_t z, bn_compare_t cmp) {
  bn_node_t y = NULL_PTR;
  bn_node_t x = t->root;
  while (x != NULL_PTR) {
    y = x;
    if (cmp(z, x) < 0) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->top = y;
  if (y == NULL_PTR) {
    t->root = z;
  } else if (cmp(z, y) < 0) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = NULL_PTR;
  z->right = NULL_PTR;
  rb_set_color(z, RB_RED);
  rb_insert_fixup(t, z);
  return t;
}

static bn_tree_t rb_delete_fixup(bn_tree_t t, bn_node_t x) {
  while (x != t->root && rb_color(x) == RB_BLACK) {
    if (x == x->top->left) {
#define IMPL_DELETE_FIXUP(left, right) \
      bn_node_t w = x->top->right; \
      if (rb_color(w) == RB_RED) { \
        rb_set_color(w, RB_BLACK); \
        rb_set_color(x->top, RB_RED); \
        bn_ ##left ##_rotate(t, x->top); \
        w = x->top->right; \
      } \
      if (rb_color(w->left) == RB_BLACK && \
          rb_color(w->right) == RB_BLACK) { \
        rb_set_color(w, RB_RED); \
        x = x->top; \
      } else if (rb_color(w->right) == RB_BLACK) { \
        rb_set_color(w->left, RB_BLACK); \
        rb_set_color(w, RB_RED); \
        bn_ ##right ##_rotate(t, w); \
        w = x->top->right; \
      } \
      rb_set_color(w, rb_color(x->top)); \
      rb_set_color(x->top, RB_BLACK); \
      rb_set_color(w->right, RB_BLACK); \
      bn_left_rotate(t, x->top); \
      x = t->root
      IMPL_DELETE_FIXUP(left, right);
    } else {
      IMPL_DELETE_FIXUP(right, left);
    }
  }
  rb_set_color(x, RB_BLACK);
  return t;
}

#undef IMPL_DELETE_FIXUP

static int rb_delete(bn_tree_t t, bn_node_t z) {
  bn_node_t y = z;
  rb_node_color_t y_original_color = rb_color(y);
  bn_node_t x;
  if (z->left == NULL_PTR) {
    x = z->right;
    bn_transplant(t, z, z->right);
  } else if (z->right == NULL_PTR) {
    x = z->left;
    bn_transplant(t, z, z->left);
  } else {
    y = bns_minimum(z->right);
    y_original_color = rb_color(y);
    x = y->right;
    if (y->top == z) {
      x->top = y;
    } else {
      bn_transplant(t, y, z->right);
      y->right = z->right;
      y->right->top = y;
    }
    bn_transplant(t, z, y);
    y->left = z->left;
    y->left->top = y;
    rb_set_color(y, rb_color(z));
  }
  if (y_original_color == RB_BLACK) {
    rb_delete_fixup(t, x);
  }
  return 1;
}

#endif  // RBI_H_
