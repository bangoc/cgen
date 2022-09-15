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

struct bs_ires bs_insert(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
struct bs_ires bs_insert_unique(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
struct bnnode *bs_search(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
struct bnnode *bs_search_gte(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
struct bnnode *bs_search_lte(struct bntree *t, struct bnnode *nn, bn_compare_t cmp);
int bs_delete(struct bntree *t, struct bnnode *dn);

#endif  // TREE_BS_H_
