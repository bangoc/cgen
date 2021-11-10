/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef RBM_H_
#define RBM_H_

#include "rb.h"
#include "gtype.h"

typedef struct rbm_node {
  struct rb_node rb_node;
  gtype key, value;
} *rbm_node_t;

typedef struct rbm_s {
  struct bn_tree t;
  bn_compare_t cmp;
} *rbm_t;

// ========== Khai báo hàm ===============

rbm_node_t rbm_create_node(gtype key, gtype value);
rbm_t rbm_create(bn_compare_t cmp);

// Nếu đã có khóa thì bỏ qua và trả về nút tương ứng với khóa
rbm_node_t rbm_insert(rbm_t t, gtype key, gtype value);
gtype *rbm_vref(rbm_t t, gtype key);
rbm_node_t rbm_search(rbm_t t, gtype key);
rbm_node_t rbm_delete(rbm_t t, gtype key);


// ========== Macro viết nhanh ===========

#define to_rbm(n) ((rbm_node_t)n)
#define rbm_node_key(n) to_rbm(n)->key
#define rbm_node_value(n) to_rbm(n)->value
#define rbm_free(m) \
  do { \
    bn_free_tree((bn_tree_t)m); \
  } while (0)

#define tm_traverse(cur, tm) \
  for (rbm_node_t cur = to_rbm(bn_left_most(tm->t.root)); \
       cur != NULL_PTR; cur = to_rbm(bn_next_inorder(to_bn(cur))))


#endif  // RBM_H_
