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
 * bnn = binary tree node
 */
struct bnn {
  struct bnn *left;
  struct bnn *right;
  struct bnn *top;
};

#define bn_node(n) ((struct bnn *)(n))
#define bn_connect1(n1, link, n2) bn_node(n1)->link = bn_node(n2)
#define bn_connect2(n1, link1, n2, link2) bn_connect1(n1, link1, n2); \
    bn_connect1(n2, link2, n1)

struct bnt {
  struct bnn *root;
};

#define bn_tree(t) ((struct bnt *)(t))

typedef int (*bn_callback_t)();
typedef int (*bn_compare_t)(struct bnn *, struct bnn *, struct bnt *);
typedef void (*bn_node_print_t)();

struct bnn *bn_create_node();
#define bn_free_node(n) free(n)

struct bnt *bn_create_tree(struct bnn *root);
void bn_free_tree(struct bnt *t);
void bn_foreach_lrn(struct bnt *t, bn_callback_t op, void *u);
void bn_foreach_lnr(struct bnt *t, bn_callback_t op, void *u);
void bn_foreach_rnl(struct bnt *t, bn_callback_t op, void *u);
void bn_pprint(struct bnt *t, bn_node_print_t p);
long bn_size(struct bnt *t);
long bn_distance(struct bnn *n);  // số lượng cạnh tới gốc
long bn_edge_height(struct bnt *t);

struct bnn *bn_left_deepest_node(struct bnn *node);
struct bnn *bn_next_postorder(struct bnn *node);
struct bnn *bn_first_postorder(struct bnn *n);
struct bnn *bn_left_most(struct bnn *x);
struct bnn *bn_right_most(struct bnn *x);
struct bnn *bn_next_inorder(struct bnn *x);
struct bnn *bn_prev_inorder(struct bnn *x);

#define bn_traverse_lrn(cur, tree) \
  for (struct bnn *cur = bn_first_postorder(tree->root); \
       cur != NULL; cur = bn_next_postorder(cur))

#define bn_traverse_lnr(cur, tree) \
  for (struct bnn *cur = bn_left_most(tree->root); \
       cur != NULL; cur = bn_next_inorder(cur))

#define bn_traverse_rnl(cur, tree) \
  for (struct bnn *cur = bn_right_most(tree->root); \
       cur != NULL; cur = bn_prev_inorder(cur))

#define bn_pprint_inline(t, pad, step, npp) \
    bn_traverse_rnl(cur, t) { \
      printf("%*s", (int)(pad + step * bn_distance(cur)), ""); \
      npp(cur); \
    }

#define bn_clear_tree(t) \
  do { \
    struct bnn *_tmp = NULL; \
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
    struct bnn *_y = (x)->right; \
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
