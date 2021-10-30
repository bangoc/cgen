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
bn_tree_t bn_create_tree(bn_node_t node);
void bn_free_tree(bn_tree_t *t, bn_free_node_t fn);
void bn_free(bn_tree_t t);
bn_tree_t bn_transplant(bn_tree_t t, bn_node_t u, bn_node_t v);
bn_node_t bn_left_most(bn_node_t x);
bn_node_t bn_right_most(bn_node_t x);
bn_node_t bn_first_postorder(bn_tree_t t);
bn_node_t bn_next_postorder(bn_node_t node);
void bn_postorder_foreach(bn_tree_t t,
  bn_callback_t op, void *u);
void bn_inorder_lnr_foreach(bn_tree_t t, bn_callback_t op, void *u);
void bn_inorder_rnl_foreach(bn_tree_t t, bn_callback_t op, void *u);

bn_node_t bn_prev_inorder(bn_node_t x);
bn_node_t bn_next_inorder(bn_node_t x);
void bn_pprint(bn_tree_t t, bn_node_print_t nprt);

#define bn_postorder_foreach_inline(cur, tree) \
  for (cur = bn_first_postorder(tree); cur != NULL_PTR; cur = bn_next_postorder(cur))

#endif  // BN_H_
