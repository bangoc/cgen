#ifndef SPEC_TREE_GBS_H_
#define SPEC_TREE_GBS_H_

/*
  (C) 2022 Nguyen Ba Ngoc (bangoc)
*/

#include "base/gtype.h"
#include "tree/bs.h"

typedef struct _gbs_node {
  struct _bn_node base;
  gtype key;
} gbs_node_s, *gbs_node_t;

#define gbs_node(n) ((gbs_node_t)(n))

typedef struct _gbs_tree {
  struct _bn_tree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
} gbs_tree_s, *gbs_tree_t;

#define gbs_tree(t) ((gbs_tree_t)(t))

gbs_node_t gbs_create_node(gtype key);
int gbs_node_cmp(bn_node_t n1, bn_node_t n2, bn_tree_t t);
gbs_tree_t gbs_create_tree(gbs_node_t root, gtype_cmp_t cmp, gtype_free_t fk);

bs_ires gbs_insert(gbs_tree_t t, gtype key);
bs_ires gbs_insert_unique(gbs_tree_t t, gtype key);
gbs_node_t gbs_search(gbs_tree_t t, gtype key);
gbs_node_t gbs_search_gte(gbs_tree_t t, gtype key);
gbs_node_t gbs_search_lte(gbs_tree_t t, gtype key);
int gbs_delete(gbs_tree_t t, gbs_node_t n);

#define gbs_free_node(n, fk) \
  do { \
    if (fk) { \
      (fk)(gbs_node(n)->key); \
    } \
    bn_free_node(n); \
  } while (0)

#define gbs_free_tree(t) \
  do { \
    if (gbs_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        gbs_tree(t)->fk(gbs_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

void gbs_pprint(gbs_tree_t, gtype_print_t gpp);

#endif  // SPEC_TREE_GBS_H_
