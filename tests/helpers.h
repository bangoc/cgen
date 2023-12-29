#ifndef TESTS_UT_HELPERS_H_
#define TESTS_UT_HELPERS_H_

#include "all.h"

#include <string.h>

static long rb_back_height = -1;
static int rb_is_invalid = 0;

#define RB_DECL_IMPL(ttree_name, tnode_name) \
static int rb_is_valid_internal(struct tnode_name *n, long blacks) { \
  if (rb_is_invalid) { \
    return 0; \
  } \
  if (n == NULL) { \
    if (rb_back_height < 0) { \
      rb_back_height = blacks; \
      return 1;  /* Ok */ \
    } else if (rb_back_height != blacks) { \
      printf("Tính chất 5.\n"); \
      rb_is_invalid = 1; \
      return 0; \
    } \
    return 1; /* Ok */ \
  } \
  if (TIS_RED(n)) { \
    if (TIS_RED(n->left) || TIS_RED(n->right)) { \
      printf("Tính chất 4.\n"); \
      rb_is_invalid = 1; \
      return 0; \
    } \
    return rb_is_valid_internal(n->left, blacks) && \
        rb_is_valid_internal(n->right, blacks); \
  } else if (TIS_BLACK(n)) { \
    return rb_is_valid_internal(n->left, blacks + 1) && \
        rb_is_valid_internal(n->right, blacks + 1); \
  } \
  printf("Tính chất 1.\n"); \
  rb_is_invalid = 1; \
  return 0; \
} \
\
static int rb_is_valid(struct ttree_name *t) { \
  if (t->root == NULL) { \
    return 1; \
  } \
  if (TIS_RED(t->root)) { \
    printf("Tính chất 2.\n"); \
    return 0; \
  } \
  rb_back_height = -1; \
  rb_is_invalid = 0; \
  return rb_is_valid_internal(t->root, 0); \
}

#endif  // TESTS_UT_HELPERS_H_