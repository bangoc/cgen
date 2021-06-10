/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BN_H_
#define BN_H_

#include "core.h"

#include <stdlib.h>
#include <stddef.h>

#define NULL_PTR 0

// bn = binary tree
typedef struct bn_node {
  struct bn_node *left;
  struct bn_node *right;
  struct bn_node *top;
} *bn_node_t;

typedef struct bn_tree {
  bn_node_t root;
} *bn_tree_t;

typedef int (*bn_callback_t)();
typedef int (*bn_compare_t)();

#define bn_node_init(n, left_value, right_value, top_value) \
  n->left = left_value; n->right = right_value; n->top = top_value

// ========== Khai báo hàm ===============

static bn_node_t bn_create_node();
static bn_tree_t bn_create_tree(bn_node_t node);
static bn_node_t bn_first_postorder(bn_tree_t t);
static bn_node_t bn_next_postorder(bn_node_t node);
static void bn_postorder_foreach(bn_tree_t t, bn_callback_t op, void *u);

// ========== Macro viết nhanh ===========

#define bn_postorder_foreach_inline(cur, tree) \
  for (cur = bn_first_postorder(tree); cur != NULL_PTR; cur = bn_next_postorder(cur))

// ========== Định nghĩa hàm =============

static bn_node_t bn_create_node() {
  bn_node_t n = malloc(sizeof(struct bn_node));
  bn_node_init(n, NULL_PTR, NULL_PTR, NULL_PTR);
  return n;
}

static bn_tree_t bn_create_tree(bn_node_t node) {
  bn_tree_t tree = malloc(sizeof(struct bn_tree));
  tree->root = node;
  return tree;
}

static void bn_free(bn_tree_t t) {
  free(t);
}

static bn_node_t bn_left_most(bn_node_t x) {
  bn_node_t y;
  #define bn_MOST(x, child, out) \
  out = x; \
  do { \
    while (out->child != NULL_PTR) { \
      out = out->child; \
    } \
  } while (0)
  bn_MOST(x, left, y);
  return y;
}

static bn_node_t bn_right_most(bn_node_t x) {
  bn_node_t y;
  bn_MOST(x, right, y);
  return y;
}

static bn_tree_t bn_transplant(bn_tree_t t, bn_node_t u, bn_node_t v) {
  if (u->top == NULL_PTR) {
    t->root = v;
  } else if (u == u->top->left) {
    u->top->left = v;
  } else {
    u->top->right = v;
  }
  if (v != NULL_PTR) {
    v->top = u->top;
  }
  return t;
}

static bn_node_t bn_left_deepest_node(bn_node_t node) {
  for (;;) {
    if (node->left) {
      node = node->left;
    } else if (node->right) {
      node = node->right;
    } else {
      return node;
    }
  }
}

static bn_node_t bn_next_postorder(bn_node_t node) {
  bn_node_t parent;
  if (!node)
    return NULL;
  parent = node->top;

  /* If we're sitting on node, we've already seen our children */
  if (parent && node == parent->left && parent->right) {
    /* If we are the parent's left node, go to the parent's right
     * node then all the way down to the left */
    return bn_left_deepest_node(parent->right);
  } else
    /* Otherwise we are the parent's right node, and the parent
     * should be next */
    return parent;
}

static bn_node_t bn_first_postorder(bn_tree_t t) {
  if (!t->root)
    return NULL;

  return bn_left_deepest_node(t->root);
}

static void bn_postorder_foreach(bn_tree_t t, bn_callback_t op, void *u) {
  bn_node_t n = bn_first_postorder(t);
  for (; n != NULL; n = bn_next_postorder(n)) {
    if (op(n, u)) {
      break;
    }
  }
}

#endif  // BN_H_
