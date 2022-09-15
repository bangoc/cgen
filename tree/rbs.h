#ifndef TREE_RBS_H_
#define TREE_RBS_H_

/* (C) Nguyen Ba Ngoc 2021 */

#include "tree/spec/grb.h"

struct rbs {
  struct grbt base;
  long size;
};

#define rbs_tree(t) ((struct rbs *)(t))

#define rbs_node_key(n) (grb_node(n)->key)
#define rbs_contains(s, v) (rbs_search(s, v) != NULL)

struct rbs *rbs_create(gtype_cmp_t cmp, gtype_free_t fk);
int rbs_insert(struct rbs *s, gtype elem);
struct grbn *rbs_search(struct rbs *s, gtype elem);
int rbs_remove(struct rbs *s, gtype elem);

static inline void _rbs_move_next(gtype **cur) {
  struct grbn *nd = container_of(*cur, struct grbn, key);
  struct bnn *tmp = bn_next_inorder(bn_node(nd));
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
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng rbs
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng rbs.
 * Con trỏ value.rbs (kiểu ::struct rbs * được truyền cho rbs_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_rbs(gtype value);

#endif  // TREE_RBS_H_
