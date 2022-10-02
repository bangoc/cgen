#ifndef TESTS_BN_BN_HELPER_H_
#define TESTS_BN_BN_HELPER_H_

#include "tree/bn.h"

typedef int (*bn_similar_node_t)();

static int bn_similar_tree_internal(struct bnnode *n1, struct bnnode *n2, bn_similar_node_t cmp) {
  if (n1 == NULL && n2 == NULL) {
    return 1;
  }

  if ((n1 == NULL && n2 != NULL) || (n1 != NULL && n2 == NULL)) {
    return 0;
  }

  return cmp(n1, n2) &&
         bn_similar_tree_internal(n1->left, n2->left, cmp) &&
         bn_similar_tree_internal(n1->right, n2->right, cmp);
}

static int __bn_similar_tree(struct bntree *t1,
    struct bntree *t2, bn_similar_node_t cmp) {
  return bn_similar_tree_internal(t1->root, t2->root, cmp);
}

#define bn_similar_tree(t1, t2, cmp) __bn_similar_tree(bn_tree(t1), bn_tree(t2), cmp)

#endif  // TESTS_BN_BN_HELPER_H_