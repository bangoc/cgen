/* (C) 2021 Nguyen Ba Ngoc (bangoc) */


/**
 * Cài đặt khái quát của cây đỏ-đen,
 * tương thích với các hàm cho cây nhị phân và cây nhị phân tìm kiếm
*/

#ifndef TREE_SPEC_GRB_H_
#define TREE_SPEC_GRB_H_

#include "base/gtype.h"
#include "tree/rb.h"

#include <stdbool.h>

/**
 * Cấu trúc nút đỏ đen với kiểu gtype, kế thừa ::struct rbnode
 * grbnode = gtype red black node
 */
struct grbnode {
  struct rbnode base;
  gtype key;
};

/**
 * Cấu trúc điều khiển của cây đỏ đen với kiểu gtype
 * grbtree = gtype red black tree
 */
struct grbtree {
  struct bntree base;
  gtype_cmp_t cmp;
  gtype_free_t fk;
};

#define grb_node(n) ((struct grbnode *)(n))
#define grb_tree(t) ((struct grbtree *)(t))

struct grbnode *grb_create_node(gtype key);
#define grb_free_node(n, t) gbs_free_node(n, gbs_tree(t)->fk)
int grb_cmp_node(struct bnnode *, struct bnnode *, struct bntree *);

struct grbtree *grb_create_tree(struct grbnode *root, gtype_cmp_t cmp, gtype_free_t fk);

#define grb_free_tree(t) \
  do { \
    if (grb_tree(t)->fk) { \
      bn_traverse_lnr(_cur, bn_tree(t)) { \
        grb_tree(t)->fk(grb_node(_cur)->key); \
      }  \
    } \
    bn_free_tree(bn_tree(t)); \
  } while (0)

struct bs_ires grb_insert(struct grbtree *t, gtype key);
struct bs_ires grb_insert_unique(struct grbtree *t, gtype key);
struct grbnode *grb_search(struct grbtree *t, gtype key);
struct grbnode *grb_search_gte(struct grbtree *t, gtype key);
struct grbnode *grb_search_lte(struct grbtree *t, gtype key);
int grb_delete(struct grbtree *t, struct grbnode *dn);


#endif  // TREE_SPEC_GRB_H_
