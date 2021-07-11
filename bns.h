/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef BNS_H_
#define BNS_H_

#include "bn.h"

// ========== Khai báo hàm ===============

static bn_node_t bns_search(bn_node_t root, bn_node_t query,
        bn_compare_t cmp);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

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
