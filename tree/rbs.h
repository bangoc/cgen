#ifndef TREE_RBS_H_
#define TREE_RBS_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include "tree/spec/grb.h"

/**
 * Cấu trúc điều khiển của tập hợp với kiểu gtype dựa trên
 * cây đỏ đen
 * rbstree = red black set tree
 */
struct rbstree {
  struct grbtree base;
  long size;
};

#define rbs_tree(t) ((struct rbstree *)(t))

#define rbs_node_key(n) (grb_node(n)->key)
#define rbs_contains(s, v) (rbs_search(s, v) != NULL)

struct rbstree *rbs_create(gtype_cmp_t cmp, gtype_free_t fk);
int rbs_insert(struct rbstree *s, gtype elem);
struct grbnode *rbs_search(struct rbstree *s, gtype elem);
int rbs_remove(struct rbstree *s, gtype elem);

static inline void _rbs_move_next(gtype **cur) {
  struct grbnode *nd = container_of(*cur, struct grbnode, key);
  struct bnnode *tmp = bn_next_inorder(bn_node(nd));
  if (!tmp) {
    *cur = NULL;
    return;
  }
  *cur = &(rbs_node_key(tmp));
}

#define rbs_size(s) ((s)->size)

#define rbs_traverse(cur, s) \
  for (gtype *cur = (rbs_size(s))? &(rbs_node_key(bn_left_most(bn_tree(s)->root))): NULL; \
        cur != NULL; _rbs_move_next(&cur))

#define rbs_free(s) \
    do {  \
      if (grb_tree(s)->fk) { \
        rbs_traverse(_k, (s)) { \
          grb_tree(s)->fk(*_k); \
        } \
      } \
      bn_free_tree(bn_tree(s)); \
    } while (0)

#define rbs_clear(s) \
    do {  \
      if (grb_tree(s)->fk) { \
        rbs_traverse(_k, (s)) { \
          grb_tree(s)->fk(*_k); \
        } \
      } \
      bn_clear_tree(bn_tree(s)); \
      rbs_tree(s)->size = 0; \
    } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng rbstree
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng rbstree.
 * Con trỏ value.rbs (kiểu ::struct rbstree * được truyền cho rbs_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_rbs(gtype value);

#endif  // TREE_RBS_H_
