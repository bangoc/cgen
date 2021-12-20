#ifndef RBS_H_
#define RBS_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/


#include "base/gtype.h"
#include "base/rb.h"

typedef struct rbs_node {
  struct rb_node_s rb_node;
  gtype value;
} *rbs_node_t;

typedef struct rbs {
  struct bn_tree t;
  gtype_cmp_t cmp;
  gtype_free_t free_value;
} *rbs_t;

// ========== Khai báo hàm ===============
rbs_node_t rbs_create_node(gtype elem);
rbs_t rbs_create(gtype_cmp_t cmp, gtype_free_t free_value);
rbs_node_t rbs_insert(rbs_t s, gtype elem);
rbs_node_t rbs_search(rbs_t s, gtype elem);
int rbs_remove(rbs_t s, gtype elem);
long rbs_size(rbs_t s);
void rbs_free(rbs_t s);

// ========== Macro viết nhanh ===========

#define to_rbs(n) ((rbs_node_t)n)
#define rbs_node_value(n) (to_rbs(n)->value)
#define rbs_traverse(cur, s) \
  for (rbs_node_t cur = to_rbs(bn_left_most(s->t.root)); \
       cur != NULL_PTR; cur = to_rbs(bn_next_inorder(to_bn(cur))))

#define rbs_free(s) \
    do {  \
      bn_free_tree((bn_tree_t)s); \
    } while (0)
#endif  // RBS_H_
