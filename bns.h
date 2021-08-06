/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BNS_H_
#define BNS_H_

#include "bn.h"

// ========== Khai báo hàm ===============

static bn_node_t bns_search(bn_node_t root, const void *query,
        bn_compare_t cmp);

// gte = greater than or equal, lte = less than or equal
static bn_node_t bns_search_gte(bn_node_t root, const void *query,
        bn_compare_t cmp);
static bn_node_t bns_search_lte(bn_node_t root, const void *query,
        bn_compare_t cmp);

static bn_node_t bns_can_hold(bn_node_t root, const void *data,
        bn_compare_t cmp);

// ========== Macro viết nhanh ===========

#define bns_child(n, order) (order < 0? n->left: n->right)
#define bns_set_child(n, order, child) \
    if (order < 0) n->left = child; else n->right = child

// ========== Định nghĩa hàm =============

static bn_node_t bns_search(bn_node_t root, const void *query,
        bn_compare_t cmp) {
  int order;
  if (root == NULL_PTR || (order = cmp(query, root)) == 0) {
    return root;
  }
  return bns_search(bns_child(root, order), query, cmp);
}

static bn_node_t bns_search_gte(bn_node_t root, const void *query,
        bn_compare_t cmp) {
  if (!root || cmp(query, root) == 0) {
    return root;
  }
  if (cmp(query, root) > 0) {
    return bns_search_gte(root->right, query, cmp);
  }
  bn_node_t res = bns_search_gte(root->left, query, cmp);
  if (res) {
    return res;
  }
  return root;
}

static bn_node_t bns_search_lte(bn_node_t root, const void *query,
                                bn_compare_t cmp) {
  if (!root || cmp(query, root) == 0) {
    return root;
  }
  if (cmp(query, root) < 0) {
    return bns_search_lte(root->left, query, cmp);
  }
  bn_node_t res = bns_search_lte(root->right, query, cmp);
  if (res) {
    return res;
  }
  return root;
}

static bn_node_t bns_can_hold(bn_node_t x, const void *data,
        bn_compare_t cmp) {
  bn_node_t y = NULL_PTR;
  while (x != NULL_PTR) {
    y = x;
    x = bns_child(x, cmp(data, x));
  }
  return y;
}

#endif  // BSNT_H_
