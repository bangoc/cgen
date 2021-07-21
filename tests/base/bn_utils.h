#ifndef TESTS_BASE_BN_UTILS_H_
#define TESTS_BASE_BN_UTILS_H_

#include "bn.h"

typedef int (*bn_similar_node_t)();

static int bn_similar_tree_internal(bn_node_t n1, bn_node_t n2, bn_similar_node_t cmp) {
  if (n1 == NULL_PTR && n2 == NULL_PTR) {
    return 1;
  }

  if ((n1 == NULL_PTR && n2 != NULL_PTR) || (n1 != NULL_PTR && n2 == NULL_PTR)) {
    return 0;
  }

  return cmp(n1, n2) &&
         bn_similar_tree_internal(n1->left, n2->left, cmp) &&
         bn_similar_tree_internal(n1->right, n2->right, cmp);
}

static int bn_similar_tree(bn_tree_t t1,
    bn_tree_t t2, bn_similar_node_t cmp) {
  return bn_similar_tree_internal(t1->root, t2->root, cmp);
}

#endif  // TESTS_BASE_BN_UTILS_H_