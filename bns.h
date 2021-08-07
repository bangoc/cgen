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

// ========== Macro viết nhanh ===========

#define bns_child(n, order) (order < 0? n->left: n->right)
#define bns_child_ref(n, order) (order < 0? &n->left: &n->right)
#define bns_set_child(n, order, child) \
    if (order < 0) n->left = child; else n->right = child

// ========== Định nghĩa hàm =============

#define bns_find_insert_location(loc, root, data, cmp, same, parent) \
  do { \
    bn_node_t x = root; \
    int order; \
    while (x) { \
      parent = x; \
      order = cmp(data, x); \
      if (!order) { \
        same = x; \
      } \
      x = bns_child(x, order); \
    } \
    loc = parent? bns_child_ref(parent, order): &root; \
  } while (0)

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

#endif  // BSNT_H_
