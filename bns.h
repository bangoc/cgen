#ifndef BNS_H_
#define BNS_H_

/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#include "bn.h"

bn_node_t bns_search(bn_node_t root, const void *query,
        bn_compare_t cmp);

// gte = greater than or equal, lte = less than or equal
bn_node_t bns_search_gte(bn_node_t root, const void *query,
        bn_compare_t cmp);
bn_node_t bns_search_lte(bn_node_t root, const void *query,
        bn_compare_t cmp);

// ========== Macro viết nhanh ===========

#define bns_child(n, order) (order < 0? n->left: n->right)
#define bns_child_ref(n, order) (order < 0? &n->left: &n->right)
#define bns_set_child(n, order, child) \
    if (order < 0) n->left = child; else n->right = child

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

#define bns_search_inline(out, root, query, cmp) \
  do { \
    int order; \
    bn_node_t x = root; \
    out = NULL_PTR; \
    while (x) { \
      order = cmp(query, x); \
      if (!order) { \
        out = x; \
        break; \
      } \
      x = bns_child(x, order); \
    } \
  } while (0)

#define bns_search_gte_inline(out, root, query, cmp) \
  do {\
    int order; \
    bn_node_t x = root; \
    out = NULL_PTR; \
    while (x) { \
      order = cmp(query, x); \
      if (!order) { \
        out = x; \
        break; \
      } \
      if (order < 0) { \
        out = x; \
        x = x->left; \
        continue; \
      } \
      x = x->right; \
    } \
  } while (0)

#define bns_search_lte_inline(out, root, query, cmp) \
  do { \
    int order; \
    bn_node_t x = root; \
    out = NULL_PTR; \
    while (x) { \
      order = cmp(query, x); \
      if (!order) { \
        out = x; \
        break; \
      } \
      if (order > 0) { \
        out = x; \
        x = x->right; \
        continue; \
      } \
      x = x->left; \
    } \
  } while (0)

#endif  // BSNT_H_
