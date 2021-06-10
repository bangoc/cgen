/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BNS_H_
#define BNS_H_

#include "bn.h"

// ========== Khai báo hàm ===============

static bn_node_t bns_minimum(bn_node_t x);
static bn_node_t bns_maximum(bn_node_t x);
static bn_node_t bns_successor(bn_node_t x);
static bn_node_t bns_predecessor(bn_node_t x);
static bn_node_t bns_search(bn_node_t root, bn_node_t query,
        bn_compare_t cmp);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static bn_node_t bns_minimum(bn_node_t x) {
  return bn_left_most(x);
}

static bn_node_t bns_maximum(bn_node_t x) {
  return bn_right_most(x);
}

static bn_node_t bns_successor(bn_node_t x)  {
  bn_node_t y;
#define BNS_NEAREST(x, left, right, out) \
  do { \
    if (x->right != NULL_PTR) { \
      out = bn_ ##left ##_most(x->right); \
    } else { \
      out = x->top; \
      while (out != NULL_PTR && x == out->right) {\
        x = out; \
        out = out->top; \
      } \
    } \
  } while (0)
  BNS_NEAREST(x, left, right, y);
  return y;
}

static bn_node_t bns_predecessor(bn_node_t x) {
  bn_node_t y;
  BNS_NEAREST(x, right, left, y);
  return y;
}

static bn_node_t bns_search(bn_node_t root, bn_node_t query,
        bn_compare_t cmp) {
  int tmp = -1;
  if (root == NULL_PTR || (tmp = cmp(root, query)) == 0) {
    return root;
  }
  if (tmp > 0) {
    return bns_search(root->left, query, cmp);
  }
  return bns_search(root->right, query, cmp);
}

#endif  // BSNT_H_
