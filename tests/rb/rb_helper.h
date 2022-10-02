#ifndef TESTS_RB_RB_HELPER_H_
#define TESTS_RB_RB_HELPER_H_

#include "tree/spec/grb.h"

static long rb_is_valid_black_height = -1;
static int rb_is_valid_internal_stop = 0;

#define END_INTERNAL() rb_is_valid_internal_stop = 1; \
  return 0

static int rb_is_valid_internal(struct bnnode *n, long blacks) {
  if (rb_is_valid_internal_stop) {
    return 0;
  }
  if (n == NULL) {
    if (rb_is_valid_black_height < 0) {
      rb_is_valid_black_height = blacks;
      return 1;  // Ok
    } else if (rb_is_valid_black_height != blacks) {
      printf("Tính chất 5.\n");
      END_INTERNAL();
    }
    return 1;  // Ok
  }
  if (rb_is_red(n)) {
    if (rb_is_red(n->left) || rb_is_red(n->right)) {
      printf("Tính chất 4.\n");
      END_INTERNAL();
    }
    return rb_is_valid_internal(n->left, blacks) &&
        rb_is_valid_internal(n->right, blacks);
  } else if (rb_is_black(n)) {
    return rb_is_valid_internal(n->left, blacks + 1) &&
        rb_is_valid_internal(n->right, blacks + 1);
  }
  printf("Tính chất 1.\n");
  END_INTERNAL();
}

static int __rb_is_valid(struct bntree *t) {
  if (t->root == NULL) {
    return 1;
  }
  if (rb_is_red(t->root)) {
    printf("Tính chất 2.\n");
    return 0;
  }
  rb_is_valid_black_height = -1;
  rb_is_valid_internal_stop = 0;
  return rb_is_valid_internal(t->root, 0);
}

#define rb_is_valid(t) __rb_is_valid(bn_tree(t))

#endif  // TESTS_RB_RB_HELPER_H_