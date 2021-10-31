#ifndef BNS_H_
#define BNS_H_

/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#include "bn.h"

#define bns_child(n, order) (order < 0? n->left: n->right)
#define bns_child_ref(n, order) (order < 0? &n->left: &n->right)

#define bns_insert_setup(loc, root, data, cmp, same, parent) \
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

#define bns_search_inline(o, t, u, cmp, ...) \
  do { \
    int order; \
    bn_node_t x = t->root; \
    bn_node_t o = NULL_PTR; \
    while (x) { \
      order = cmp(u, x); \
      if (!order) { \
        o = x; \
        break; \
      } \
      x = bns_child(x, order); \
    } \
    __VA_ARGS__; \
  } while (0)

// gte = greater than or equal
#define bns_search_gte_inline(o, t, u, cmp, ...) \
  do {\
    int order; \
    bn_node_t x = t->root; \
    bn_node_t o = NULL_PTR; \
    while (x) { \
      order = cmp(u, x); \
      if (!order) { \
        o = x; \
        break; \
      } \
      if (order < 0) { \
        o = x; \
        x = x->left; \
        continue; \
      } \
      x = x->right; \
    } \
    __VA_ARGS__;\
  } while (0)

// lte = less than or equal
#define bns_search_lte_inline(o, t, u, cmp, ...) \
  do { \
    int order; \
    bn_node_t x = t->root; \
    bn_node_t o = NULL_PTR; \
    while (x) { \
      order = cmp(u, x); \
      if (!order) { \
        o = x; \
        break; \
      } \
      if (order > 0) { \
        o = x; \
        x = x->right; \
        continue; \
      } \
      x = x->left; \
    } \
    __VA_ARGS__; \
  } while (0)


/* Giao diện hỗ trợ gtype */

#include "gtype.h"

typedef struct bns_node_g {
  struct bn_node base;
  gtype key;
} *bns_node_g_t;

#define to_bns_node_g(n) ((bns_node_g_t)n)
#define bns_node_g_key(n) (to_bns_node_g(n)->key)

typedef struct bns_tree_g {
  struct bn_tree base;
  bn_compare_t cmp;
} *bns_tree_g_t;

#define to_bns_tree_g(t) ((bns_tree_g_t)t)

bn_node_t bns_create_node_g(gtype key);
bn_tree_t bns_create_tree_g(bn_node_t root, bn_compare_t cmp);

bn_node_t bns_insert_g(bn_tree_t t, gtype key);
bn_node_t bns_search_g(bn_tree_t t, gtype key);
void bns_delete_g(bn_tree_t t, bn_node_t n);

void bns_pprint_i(bn_node_t n);

int bns_gcmp_i(gtype u, bn_node_t n);

#endif  // BSNT_H_
