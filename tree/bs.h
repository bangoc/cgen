#ifndef TREE_BS_H_
#define TREE_BS_H_

/* (C) 2022 Nguyen Ba Ngoc (bangoc) */

#include "tree/bn.h"

#define bs_child(n, rl) ((rl) < 0? bn_node(n)->left: bn_node(n)->right)
#define bs_child_ref(n, rl) ((rl) < 0? &(bn_node(n)->left): &(bn_node(n)->right))

struct bs_ires {
  struct bnn *nn;
  int inserted;
};

struct bs_ires bs_insert(struct bnt *t, struct bnn *nn, bn_compare_t cmp);
struct bs_ires bs_insert_unique(struct bnt *t, struct bnn *nn, bn_compare_t cmp);
struct bnn *bs_search(struct bnt *t, struct bnn *nn, bn_compare_t cmp);
struct bnn *bs_search_gte(struct bnt *t, struct bnn *nn, bn_compare_t cmp);
struct bnn *bs_search_lte(struct bnt *t, struct bnn *nn, bn_compare_t cmp);
int bs_delete(struct bnt *t, struct bnn *dn);

#endif  // TREE_BS_H_
