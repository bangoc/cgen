#ifndef TREE_BS_H_
#define TREE_BS_H_

/* (C) 2022 Nguyen Ba Ngoc (bangoc) */

#include "tree/bn.h"

#define bs_child(n, rl) ((rl) < 0? bn_node(n)->left: bn_node(n)->right)
#define bs_child_ref(n, rl) ((rl) < 0? &(bn_node(n)->left): &(bn_node(n)->right))

typedef struct {
  bn_node_t nn;
  int inserted;
} bs_ires;

bs_ires bs_insert(bn_tree_t t, bn_node_t nn, bn_compare_t cmp);
bs_ires bs_insert_unique(bn_tree_t t, bn_node_t nn, bn_compare_t cmp);
bn_node_t bs_search(bn_tree_t t, bn_node_t nn, bn_compare_t cmp);
bn_node_t bs_search_gte(bn_tree_t t, bn_node_t nn, bn_compare_t cmp);
bn_node_t bs_search_lte(bn_tree_t t, bn_node_t nn, bn_compare_t cmp);
int bs_delete(bn_tree_t t, bn_node_t dn);

#endif  // TREE_BS_H_
