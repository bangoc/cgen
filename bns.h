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

#define bns_child(n, order) (order < 0? to_bn(n)->left: \
                                        to_bn(n)->right)
#define bns_set_child(n, order, z) if (order < 0) \
        to_bn(n)->left = to_bn(z); else to_bn(n)->right = to_bn(z)

// ========== Định nghĩa hàm =============

static bn_node_t bns_search(bn_node_t root, bn_node_t query,
        bn_compare_t cmp) {
  int order;
  if (root == NULL_PTR || (order = cmp(query, root)) == 0) {
    return root;
  }
  return bns_search(bns_child(root, order), query, cmp);
}

#endif  // BSNT_H_
