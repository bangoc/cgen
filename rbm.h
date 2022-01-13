/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef RBM_H_
#define RBM_H_

#include "base/rb.h"
#include "base/gtype.h"

typedef struct rbm_node {
  struct rb_node_s rb_node;
  gtype key, value;
} *rbm_node_t;

typedef struct rbm_s {
  struct bn_tree t;
  gtype_cmp_t cmp;
  gtype_free_t free_key, free_value;
} *rbm_t;

typedef struct rbm_insert_result {
  gtype *value;
  int inserted;
} rbm_ires;

#define to_rbm(n) ((rbm_node_t)(n))
#define rbm_node_key(n) (to_rbm(n)->key)
#define rbm_node_value(n) (to_rbm(n)->value)

rbm_node_t rbm_create_node(gtype key, gtype value);
rbm_t rbm_create(gtype_cmp_t cmp,
  gtype_free_t free_key, gtype_free_t free_value);

rbm_ires rbm_insert(rbm_t t, gtype key, gtype value);
gtype *rbm_vref(rbm_t t, gtype key);
rbm_node_t rbm_search(rbm_t t, gtype key);
int rbm_remove(rbm_t t, gtype key);

#define rbm_free(m) \
  do { \
    if ((m)->free_key || (m)->free_value) { \
      rbm_traverse(_k, _v, (m)) { \
        if ((m)->free_key) { \
          (m)->free_key(*_k); \
        } \
        if ((m)->free_value) { \
          (m)->free_value(*_v); \
        } \
      } \
    } \
    bn_free_tree((bn_tree_t)(m)); \
  } while (0)

static inline void _rbm_move_next(gtype **k, gtype **v) {
  rbm_node_t nd = container_of(*k, struct rbm_node, key);
  bn_node_t tmp = bn_next_inorder(to_bn(nd));
  if (!tmp) {
    *k = NULL_PTR;
    *v = NULL_PTR;
    return;
  }
  *k = &(rbm_node_key(tmp));
  *v = &(rbm_node_value(tmp));
}

#define rbm_traverse(k, v, m) \
  for (gtype *k = &(rbm_node_key(bn_left_most((m)->t.root))), \
             *v = &(rbm_node_value(bn_left_most((m)->t.root))); \
       k != NULL_PTR && v != NULL_PTR; _rbm_move_next(&k, &v)) \

#endif  // RBM_H_
