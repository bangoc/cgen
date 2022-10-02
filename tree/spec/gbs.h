#ifndef SPEC_TREE_GBS_H_
#define SPEC_TREE_GBS_H_

/* (C) 2022 Nguyen Ba Ngoc (bangoc) */

#include "base/gtype.h"
#include "tree/bs.h"

/**
 * Cấu trúc nút của cây nhị phân tìm kiếm với kiểu gtype
 * gbsnode = gtype binary search node
 */
struct gbsnode {
  struct bnnode base;
  gtype key;
};

/**
 * Cấu trúc điều khiển của cây nhị phân tìm kiếm với kiểu gtype
 * gbstree = gtype binary search tree
 */
struct gbstree {
  struct bntree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
};

#define gbs_node(n) ((struct gbsnode *)(n))
#define gbs_tree(t) ((struct gbstree *)(t))

struct gbsnode *gbs_create_node(gtype key);
int gbs_cmp_node(struct bnnode *n1, struct bnnode *n2, struct bntree *t);
struct gbstree *__gbs_create_tree(struct gbsnode *root, gtype_cmp_t cmp, gtype_free_t fk);
#define gbs_create_tree(root, cmp, fk) __gbs_create_tree(gbs_node(root), cmp, fk)

struct bs_ires gbs_insert(struct gbstree *t, gtype key);
struct bs_ires gbs_insert_unique(struct gbstree *t, gtype key);
struct gbsnode *gbs_search(struct gbstree *t, gtype key);
struct gbsnode *gbs_search_gte(struct gbstree *t, gtype key);
struct gbsnode *gbs_search_lte(struct gbstree *t, gtype key);
int gbs_delete(struct gbstree *t, struct gbsnode *n);

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

void gbs_pprint(struct gbstree *, gtype_print_t gpp);

#endif  // SPEC_TREE_GBS_H_
