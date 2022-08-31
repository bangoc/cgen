#ifndef SPEC_TREE_BS_H_
#define SPEC_TREE_BS_H_

/*
  (C) 2022 Nguyen Ba Ngoc (bangoc)
*/

#include "base/gtype.h"
#include "tree/bs.h"

typedef struct _bsg_node {
  struct _bn_node base;
  gtype key;
} bsg_node_s, *bsg_node_t;

#define bsg_node(n) ((bsg_node_t)(n))

typedef struct _bsg_tree {
  struct _bn_tree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
} bsg_tree_s, *bsg_tree_t;

#define bsg_tree(t) ((bsg_tree_t)(t))

bsg_node_t bsg_create_node(gtype key);
int bsg_node_cmp(bn_node_t n1, bn_node_t n2, bn_tree_t t);
bsg_tree_t bsg_create_tree(bsg_node_t root, gtype_cmp_t cmp, gtype_free_t fk);

bs_ires bsg_insert(bsg_tree_t t, gtype key);
bs_ires bsg_insert_unique(bsg_tree_t t, gtype key);
bsg_node_t bsg_search(bsg_tree_t t, gtype key);
bsg_node_t bsg_search_gte(bsg_tree_t t, gtype key);
bsg_node_t bsg_search_lte(bsg_tree_t t, gtype key);
int bsg_delete(bsg_tree_t t, bsg_node_t n);

#define bsg_free_node(n, fk) \
  do { \
    if (fk) { \
      (fk)(bsg_node(n)->key); \
    } \
    bn_free_node(n); \
  } while (0)

#define bsg_free_tree(t) \
  do { \
    if (bsg_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        bsg_tree(t)->fk(bsg_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

void bsg_pprint(bsg_tree_t, gtype_print_t gpp);

#endif  // SPEC_TREE_BS_H_
