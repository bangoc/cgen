#ifndef TREE_BS_H_
#define TREE_BS_H_

/* (C) 2022 Nguyen Ba Ngoc (bangoc) */

#include "tree/bn.h"

#define bs_child(n, rl) ((rl) < 0? bn_node(n)->left: bn_node(n)->right)
#define bs_child_ref(n, rl) ((rl) < 0? &(bn_node(n)->left): &(bn_node(n)->right))

struct bs_ires {
  struct bnnode *nn;
  int inserted;
};

struct bs_ires __bs_insert(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
#define bs_insert(t, nn, cmp) __bs_insert(bn_tree(t), bn_node(nn), cmp)

struct bs_ires __bs_insert_unique(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
#define bs_insert_unique(t, nn, cmp) __bs_insert_unique(bn_tree(t), bn_node(nn), cmp)

struct bnnode *__bs_search(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
#define bs_search(t, nn, cmp) __bs_search(bn_tree(t), bn_node(nn), cmp)

struct bnnode *__bs_search_gte(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
#define bs_search_gte(t, nn, cmp) __bs_search_gte(bn_tree(t), bn_node(nn), cmp)

struct bnnode *__bs_search_lte(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
#define bs_search_lte(t, nn, cmp) __bs_search_lte(bn_tree(t), bn_node(nn), cmp)

int __bs_delete(struct bntree *t, struct bnnode *dn);
#define bs_delete(t, dn) __bs_delete(bn_tree(t), bn_node(dn))

#endif  // TREE_BS_H_
