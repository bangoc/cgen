#ifndef BN_H_
#define BN_H_

/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NULL_PTR 0

// bn = binary tree
typedef struct bn_node {
  struct bn_node *left;
  struct bn_node *right;
  struct bn_node *top;
} *bn_node_t;

#define to_bn(n) ((bn_node_t)n)
#define bn_connect1(n1, link, n2) to_bn(n1)->link = to_bn(n2)
#define bn_connect2(n1, link1, n2, link2) bn_connect1(n1, link1, n2); \
    bn_connect1(n2, link2, n1)

typedef struct bn_tree {
  bn_node_t root;
} *bn_tree_t;

typedef int (*bn_callback_t)();
typedef int (*bn_compare_t)();
typedef void (*bn_free_node_t)();
typedef void (*bn_node_print_t)();

bn_node_t bn_create_node();
void bn_free_node(bn_node_t node);
bn_tree_t bn_create_tree(bn_node_t root);
void bn_free_tree(bn_tree_t *t);
void bn_foreach_lrn(bn_tree_t t, bn_callback_t op, void *u);
void bn_foreach_lnr(bn_tree_t t, bn_callback_t op, void *u);
void bn_foreach_rnl(bn_tree_t t, bn_callback_t op, void *u);
void bn_pprint(bn_tree_t t, bn_node_print_t nprt);

bn_node_t bn_left_deepest_node(bn_node_t node);
bn_node_t bn_next_postorder(bn_node_t node);
bn_node_t bn_first_postorder(bn_tree_t t);
bn_node_t bn_left_most(bn_node_t x);
bn_node_t bn_right_most(bn_node_t x);
bn_node_t bn_next_inorder(bn_node_t x);
bn_node_t bn_prev_inorder(bn_node_t x);

#define bn_travese_lrn(cur, tree) \
  for (bn_node_t cur = bn_first_postorder(tree); \
       cur != NULL_PTR; cur = bn_next_postorder(cur))

#define bn_traverse_lnr(cur, tree) \
  for (bn_node_t cur = bn_left_most(t->root); \
       cur != NULL_PTR; cur = bn_next_inorder(cur))

#define bn_traverse_rnl(cur, tree) \
  for (bn_node_t cur = bn_right_most(t->root); \
       cur != NULL_PTR; cur = bn_prev_inorder(cur))

#define bn_change_child(old_node, new_node, parent, t) \
  do { \
    if (parent) { \
      if (parent->left == old_node) { \
        parent->left = new_node; \
      } else { \
        parent->right = new_node; \
      } \
    } else { \
      t->root = new_node; \
    } \
  } while (0)

#endif  // BN_H_
