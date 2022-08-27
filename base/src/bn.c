/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#include "base/bn.h"

bn_node_t bn_create_node() {
  return calloc(1, sizeof(struct _bn_node));
}

void bn_free_node(bn_node_t node) {
  free(node);
}

bn_tree_t bn_create_tree(bn_node_t root) {
  bn_tree_t tree = malloc(sizeof(struct _bn_tree));
  tree->root = root;
  return tree;
}

void bn_free_tree(bn_tree_t t) {
  bn_node_t tmp = NULL;
  bn_traverse_lrn(cur, t) {
    free(tmp);
    tmp = cur;
  }
  free(tmp);
  free(t);
}

bn_node_t bn_left_deepest_node(bn_node_t node) {
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

bn_node_t bn_next_postorder(bn_node_t node) {
  if (!node) {
    return NULL;
  }
  bn_node_t top = node->top;

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

bn_node_t bn_first_postorder(bn_node_t n) {
  return bn_left_deepest_node(n);
}

void bn_foreach_lrn(bn_tree_t t, bn_callback_t op, void *u) {
  bn_node_t n = bn_first_postorder(t->root);
  for (; n != NULL; n = bn_next_postorder(n)) {
    if (op(n, u)) {
      break;
    }
  }
}

bn_node_t bn_left_most(bn_node_t x) {
  if (!x) {
    return NULL;
  }
  bn_node_t y;
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

bn_node_t bn_right_most(bn_node_t x) {
  if (!x) {
    return NULL;
  }
  bn_node_t y;
  bn_MOST(x, right, y);
  return y;
}

bn_node_t bn_next_inorder(bn_node_t x)  {
  if (!x) {
    return NULL;
  }
  bn_node_t y;
#define BNS_NEAREST(x, left, right, out) \
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
  BNS_NEAREST(x, left, right, y);
  return y;
}

bn_node_t bn_prev_inorder(bn_node_t x) {
  if (!x) {
    return NULL;
  }
  bn_node_t y;
  BNS_NEAREST(x, right, left, y);
  return y;
}

void bn_foreach_lnr(bn_tree_t t, bn_callback_t op, void *u) {
  if (!t->root) {
    return;
  }
  bn_node_t n = bn_left_most(t->root);
  for (; n != NULL; n = bn_next_inorder(n)) {
    if (op(n, u)) {
      break;
    }
  }
}

void bn_foreach_rnl(bn_tree_t t, bn_callback_t op, void *u) {
  if (!t->root) {
    return;
  }
  bn_node_t nd = bn_right_most(t->root);
  for (; nd != NULL; nd = bn_prev_inorder(nd)) {
    if (op(nd, u)) {
      break;
    }
  }
}

void bn_pprint_internal(bn_node_t root, bn_node_print_t nprt,
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

void bn_pprint(bn_tree_t t, bn_node_print_t p) {
  bn_pprint_internal(t->root, p,
    g_bn_pprint_spaces_at_begin, g_bn_pprint_step);
}

long bn_size(bn_tree_t t) {
  long cc = 0;
  bn_traverse_lrn(cur, t)  {
    ++cc;
  }
  return cc;
}

long bn_distance(bn_node_t n) {
  long cc = -1;
  while (n != NULL) {
    n = n->top;
    ++cc;
  }
  return cc;
}

long bn_edge_height(bn_tree_t t) {
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
