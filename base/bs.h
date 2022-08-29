#ifndef BASE_BS_H_
#define BASE_BS_H_

/*
  (C) 2022 Nguyen Ba Ngoc (bangoc)
*/

#include "base/bn.h"
#include "base/gtype.h"

typedef struct _bs_node {
  struct _bn_node base;
  gtype key;
} bs_node_s, *bs_node_t;

#define bs_node(n) ((bs_node_t)(n))
#define bs_child(n, rl) ((rl) < 0? bn_node(n)->left: bn_node(n)->right)
#define bs_child_ref(n, rl) ((rl) < 0? &(bn_node(n)->left): &(bn_node(n)->right))

typedef struct _bs_tree {
  struct _bn_tree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
} bs_tree_s, *bs_tree_t;

#define bs_tree(t) ((bs_tree_t)(t))

typedef struct {
  bn_node_t nn;
  int inserted;
} bs_ires;

bs_node_t bs_create_node(gtype key);
bs_tree_t bs_create_tree(bs_node_t root, gtype_cmp_t cmp, gtype_free_t fk);

bs_ires bs_insert(bs_tree_t t, gtype key);
bs_ires bs_insert_unique(bs_tree_t t, gtype key);
bs_node_t bs_search(bs_tree_t t, gtype key);
bs_node_t bs_search_gte(bs_tree_t t, gtype key);
bs_node_t bs_search_lte(bs_tree_t t, gtype key);
int bs_delete(bs_tree_t t, bs_node_t n);

#define bs_free_tree(t) \
  do { \
    if (t->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        t->fk(bs_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

#define bs_free_node(n, t) \
  do { \
    if (bs_tree(t)->fk) { \
      bs_tree(t)->fk(bs_node(n)->key); \
    } \
    free(n); \
  } while (0)

void bs_pprint(bs_tree_t, gtype_print_t gpp);

#endif  // BASE_BS_H_
