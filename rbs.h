#ifndef RBS_H_
#define RBS_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/


#include "base/gtype.h"
#include "base/rb.h"

typedef struct red_black_set_node {
  struct rb_node_s rb_node;
  gtype value;
} *rbs_node_t;

typedef struct red_black_set {
  struct bn_tree t;
  gtype_cmp_t cmp;
  gtype_free_t free_key;
  long size;
} rbs_s, *rbs_t;

#define to_rbs(n) ((rbs_node_t)(n))
#define rbs_node_value(n) (to_rbs(n)->value)
#define rbs_contains(s, v) (rbs_search(s, v) != NULL)

rbs_node_t rbs_create_node(gtype elem);
rbs_t rbs_create(gtype_cmp_t cmp, gtype_free_t free_key);
int rbs_insert(rbs_t s, gtype elem);
rbs_node_t rbs_search(rbs_t s, gtype elem);
int rbs_remove(rbs_t s, gtype elem);

static inline void _rbs_move_next(gtype **cur) {
  rbs_node_t nd = container_of(*cur, struct red_black_set_node, value);
  bn_node_t tmp = bn_next_inorder(to_bn(nd));
  if (!tmp) {
    *cur = NULL_PTR;
    return;
  }
  *cur = &(rbs_node_value(tmp));
}

#define rbs_size(s) ((s)->size)

#define rbs_traverse(cur, s) \
  for (gtype *cur = (rbs_size(s))? &(rbs_node_value(bn_left_most((s)->t.root))): NULL_PTR; \
        cur != NULL_PTR; _rbs_move_next(&cur))

#define rbs_free(s) \
    do {  \
      if ((s)->free_key) { \
        rbs_traverse(_k, (s)) { \
          (s)->free_key(*_k); \
        } \
      } \
      bn_free_tree((bn_tree_t)(s)); \
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
