/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

#include "tree/bn.h"

struct bnnode *bn_create_node() {
  return calloc(1, sizeof(struct bnnode));
}

struct bntree *bn_create_tree(struct bnnode *root) {
  struct bntree *tree = malloc(sizeof(struct bntree));
  tree->root = root;
  return tree;
}

void __bn_free_tree(struct bntree *t) {
  struct bnnode *tmp = NULL;
  bn_traverse_lrn(cur, t) {
    bn_free_node(tmp);
    tmp = cur;
  }
  bn_free_node(tmp);
  free(t);
}

struct bnnode *bn_left_deepest_node(struct bnnode *node) {
  if (!node) {
    return NULL;
  }
  for (;;) {
    if (node->left) {
      node = node->left;
    } else if (node->right) {
      node = node->right;
    } else {
      return node;
    }
  }
}

struct bnnode *bn_next_postorder(struct bnnode *node) {
  if (!node) {
    return NULL;
  }
  struct bnnode *top = node->top;

  /* If we're sitting on node, we've already seen our children */
  if (top && node == top->left && top->right) {
    /* If we are the top's left node, go to the top's right
     * node then all the way down to the left */
    return bn_left_deepest_node(top->right);
  } else
    /* Otherwise we are the top's right node, and the parent
     * should be next */
    return top;
}

struct bnnode *bn_first_postorder(struct bnnode *n) {
  return bn_left_deepest_node(n);
}

void bn_foreach_lrn(struct bntree *t, bn_callback_t op, void *u) {
  struct bnnode *n = bn_first_postorder(t->root);
  for (; n != NULL; n = bn_next_postorder(n)) {
    if (op(n, u)) {
      break;
    }
  }
}

struct bnnode *bn_left_most(struct bnnode *x) {
  if (!x) {
    return NULL;
  }
  struct bnnode *y;
  #define bn_MOST(x, child, out) \
  (out) = (x); \
  do { \
    while ((out)->child != NULL) { \
      (out) = (out)->child; \
    } \
  } while (0)
  bn_MOST(x, left, y);
  return y;
}

struct bnnode *bn_right_most(struct bnnode *x) {
  if (!x) {
    return NULL;
  }
  struct bnnode *y;
  bn_MOST(x, right, y);
  return y;
}

struct bnnode *bn_next_inorder(struct bnnode *x)  {
  if (!x) {
    return NULL;
  }
  struct bnnode *y;
#define BS_NEAREST(x, left, right, out) \
  do { \
    if ((x)->right != NULL) { \
      (out) = bn_ ##left ##_most((x)->right); \
    } else { \
      (out) = (x)->top; \
      while ((out) != NULL && (x) == (out)->right) {\
        (x) = (out); \
        (out) = (out)->top; \
      } \
    } \
  } while (0)
  BS_NEAREST(x, left, right, y);
  return y;
}

struct bnnode *bn_prev_inorder(struct bnnode *x) {
  if (!x) {
    return NULL;
  }
  struct bnnode *y;
  BS_NEAREST(x, right, left, y);
  return y;
}

void bn_foreach_lnr(struct bntree *t, bn_callback_t op, void *u) {
  if (!t->root) {
    return;
  }
  struct bnnode *n = bn_left_most(t->root);
  for (; n != NULL; n = bn_next_inorder(n)) {
    if (op(n, u)) {
      break;
    }
  }
}

void bn_foreach_rnl(struct bntree *t, bn_callback_t op, void *u) {
  if (!t->root) {
    return;
  }
  struct bnnode *nd = bn_right_most(t->root);
  for (; nd != NULL; nd = bn_prev_inorder(nd)) {
    if (op(nd, u)) {
      break;
    }
  }
}

void bn_pprint_internal(struct bnnode *root, bn_node_print_t nprt,
      int spaces, int step) {
  if (!root) {
    return;
  }
  if (root->right) {
    bn_pprint_internal(root->right, nprt, spaces + step, step);
  }
  for (int i = 0; i < spaces; ++i) {
    printf(" ");
  }
  nprt(root);
  if (root->left) {
    bn_pprint_internal(root->left, nprt, spaces + step, step);
  }
}

int g_bn_pprint_spaces_at_begin = 0;
int g_bn_pprint_step = 3;

void bn_pprint(struct bntree *t, bn_node_print_t p) {
  bn_pprint_internal(t->root, p,
    g_bn_pprint_spaces_at_begin, g_bn_pprint_step);
}

long __bn_size(struct bntree *t) {
  long cc = 0;
  bn_traverse_lrn(cur, t)  {
    ++cc;
  }
  return cc;
}

long bn_distance(struct bnnode *n) {
  long cc = -1;
  while (n != NULL) {
    n = n->top;
    ++cc;
  }
  return cc;
}

long bn_edge_height(struct bntree *t) {
  long max = 0;
  bn_traverse_lnr(n, t) {
    if (n && !n->left && !n->right) {
      long tmp = bn_distance(n);
      if (tmp > max) {
        max = tmp;
      }
    }
  }
  return max;
}
