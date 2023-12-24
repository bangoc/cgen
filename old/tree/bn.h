#ifndef TREE_BN_H_
#define TREE_BN_H_

/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/** @file
 * @brief Triển khai cây nhị phân khái quát chỉ bao gồm cấu trúc liên kết
 * Có thể được kế thừa để lưu giữ liệu trong các nút.
 */

#include "base/core.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * Cấu trúc nút của cây nhị phân
 * bnnode = binary (tree) node
 */
struct bnnode {
  struct bnnode *left;
  struct bnnode *right;
  struct bnnode *top;
};

#define bn_node(n) ((struct bnnode *)(n))
#define bn_connect1(n1, link, n2) bn_node(n1)->link = bn_node(n2)
#define bn_connect2(n1, link1, n2, link2) bn_connect1(n1, link1, n2); \
    bn_connect1(n2, link2, n1)

/**
 * Cấu trúc điều khiển của cây nhị phân
 * bntree = binary tree
 */
struct bntree {
  struct bnnode *root;
};

#define bn_tree(t) ((struct bntree *)(t))
#define bn_root(t) (bn_tree(t)->root)

typedef int (*bn_callback_t)();
typedef int (*bn_compare_t)(struct bnnode *, struct bnnode *, struct bntree *);
typedef void (*bn_node_print_t)();

struct bnnode *bn_create_node();
#define bn_free_node(n) free(n)

struct bntree *bn_create_tree(struct bnnode *root);

void __bn_free_tree(struct bntree *t);
#define bn_free_tree(t) __bn_free_tree(bn_tree(t))

void bn_foreach_lrn(struct bntree *t, bn_callback_t op, void *u);
void bn_foreach_lnr(struct bntree *t, bn_callback_t op, void *u);
void bn_foreach_rnl(struct bntree *t, bn_callback_t op, void *u);
void bn_pprint(struct bntree *t, bn_node_print_t p);

long __bn_size(struct bntree *t);
#define bn_size(t) __bn_size(bn_tree(t))

long bn_distance(struct bnnode *n);  // số lượng cạnh tới gốc
long bn_edge_height(struct bntree *t);

struct bnnode *bn_left_deepest_node(struct bnnode *node);
struct bnnode *bn_next_postorder(struct bnnode *node);
struct bnnode *bn_first_postorder(struct bnnode *n);
struct bnnode *bn_left_most(struct bnnode *x);
struct bnnode *bn_right_most(struct bnnode *x);
struct bnnode *bn_next_inorder(struct bnnode *x);
struct bnnode *bn_prev_inorder(struct bnnode *x);

#define bn_traverse_lrn(cur, tree) \
  for (struct bnnode *cur = bn_first_postorder(tree->root); \
       cur != NULL; cur = bn_next_postorder(cur))

#define bn_traverse_lnr(cur, tree) \
  for (struct bnnode *cur = bn_left_most(tree->root); \
       cur != NULL; cur = bn_next_inorder(cur))

#define bn_traverse_rnl(cur, tree) \
  for (struct bnnode *cur = bn_right_most(tree->root); \
       cur != NULL; cur = bn_prev_inorder(cur))

#define bn_pprint_inline(t, pad, step, npp) \
    bn_traverse_rnl(cur, t) { \
      printf("%*s", (int)(pad + step * bn_distance(cur)), ""); \
      npp(cur); \
    }

#define bn_clear_tree(t) \
  do { \
    struct bnnode *_tmp = NULL; \
    bn_traverse_lrn(_cur, (t)) { \
      free(_tmp); \
      _tmp = _cur; \
    } \
    free(_tmp); \
    (t)->root = NULL; \
  } while (0)

#define bn_is_empty(t) ((t)->root == NULL)

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

#define bn_insert(nn, loc, par) \
    *loc = nn; \
    nn->top = par \

/* Xoay từ trái sang phải hoặc xoay từ phải sang trái */
/* x là trục xoay */
#define bn_rotate(t, x, right, left) \
  do { \
    struct bnnode *_y = (x)->right; \
    (x)->right = _y->left; \
    if (_y->left != NULL) { \
      _y->left->top = (x); \
    } \
    _y->top = (x)->top; \
    bn_change_child(x, _y, (x)->top, t); \
    _y->left = (x); \
    (x)->top = _y; \
  } while (0)

#define bn_ntref(n, t) \
 (bn_node(n)->top? \
    (bn_node(n)->top->left == n? \
      &(bn_node(n)->top->left): \
      &(bn_node(n)->top->right)): \
    &bn_tree(t)->root)

#define bn_recover(o, n, t) \
   do { \
     if (bn_node(n)->top) { \
       if (bn_node(n)->top->left == bn_node(o)) { \
         bn_node(n)->top->left = bn_node(n); \
       } else { \
         bn_node(n)->top->right = bn_node(n); \
       } \
     } else { \
       bn_tree(t)->root = bn_node(n); \
     } \
     if (bn_node(n)->left) { \
       bn_node(n)->left->top = bn_node(n); \
     } \
     if (bn_node(n)->right) { \
       bn_node(n)->right->top = bn_node(n); \
     } \
   }  while (0)

#endif  // TREE_BN_H_
