#ifndef RBS_H_
#define RBS_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/


#include "base/gtype.h"
#include "base/rb.h"

typedef struct red_black_set {
  struct _bs_tree t;
  long size;
} rbs_s, *rbs_t;

#define rbs_node_key(n) (bs_node(n)->key)
#define rbs_contains(s, v) (rbs_search(s, v) != NULL)

rbs_t rbs_create(gtype_cmp_t cmp, gtype_free_t free_key);
int rbs_insert(rbs_t s, gtype elem);
bs_node_t rbs_search(rbs_t s, gtype elem);
int rbs_remove(rbs_t s, gtype elem);

static inline void _rbs_move_next(gtype **cur) {
  bs_node_t nd = container_of(*cur, struct _bs_node, key);
  bn_node_t tmp = bn_next_inorder(bn_node(nd));
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
      if (bs_tree(s)->fk) { \
        rbs_traverse(_k, (s)) { \
          bs_tree(s)->fk(*_k); \
        } \
      } \
      bn_free_tree(bn_tree(s)); \
    } while (0)

#define rbs_clear(s) \
    do {  \
      if (bs_tree(s)->fk) { \
        rbs_traverse(_k, (s)) { \
          bs_tree(s)->fk(*_k); \
        } \
      } \
      bn_tree_t _t = (bn_tree_t)(s); \
      bn_clear_tree(_t); \
      (s)->size = 0; \
    } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng rbs
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng rbs.
 * Con trỏ value.rbs (kiểu ::rbs_t) được truyền cho rbs_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_rbs(gtype value);

#endif  // RBS_H_
