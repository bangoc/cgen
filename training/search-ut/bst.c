/* (C) Nguyễn Bá Ngọc 2023 */

#include "bst.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Minh họa ánh xạ char * => int dựa trên cây
   nhị phân tìm kiếm. */

struct bst_node {
  int key;
  struct bst_node *left;
  struct bst_node *right;
  struct bst_node *top;
};

struct bst_tree {
  struct bst_node *root;
  int size;
};

struct bst_node *bst_node(int key) {
  struct bst_node *nn = malloc(sizeof(struct bst_node));
  nn->key = key;
  nn->left = NULL;
  nn->right = NULL;
  nn->top = NULL;
  return nn;
}

struct bst_tree *bst_tree() {
  struct bst_tree *t = malloc(sizeof(struct bst_tree));
  t->root = NULL;
  t->size = 0;
}

/**
 * Thêm khóa key vào cây t, trong trường hợp key đã tồn tại thì trả về con trỏ
 * tới giá trị của nút tương ứng với key. Nếu khóa chưa tồn tại thì trả về NULL.
 */
struct bst_node *bst_put(struct bst_tree *t, int key) {
  if (t->root == NULL) {
    t->root = bst_node(key);
    ++t->size;
    return NULL;
  }
  struct bst_node *p = t->root, *c;
  for(;;) {
    if (key == p->key) {
      return p;
    }
    c = key < p->key? p->left: p->right;
    if (!c) {
      break;
    }
    p = c;
  }
  struct bst_node *nn = bst_node(key);
  if (key < p->key) {
    p->left = nn;
  } else {
    p->right = nn;
  }
  nn->top = p;
  ++t->size;
  return NULL;
}

void bst_node_free_lrn(struct bst_node *n) {
  if (n->left) {
    bst_node_free_lrn(n->left);
  }
  if (n->right) {
    bst_node_free_lrn(n->right);
  }
  free(n);
}

void bst_free(struct bst_tree *t) {
  if (t->root) {
    bst_node_free_lrn(t->root);
  }
  free(t);
}

struct bst_node *bst_left_most(struct bst_node *n) {
  while (n->left) {
    n = n->left;
  }
  return n;
}

struct bst_node *bst_first_lnr(struct bst_tree *t) {
  return bst_left_most(t->root);
}
struct bst_node *bst_next_lnr(struct bst_node *n) {
  if (n->right) {
    return bst_left_most(n->right);
  }
  struct bst_node *top = n->top;
  while (top != NULL && n == top->right) {
    n = top;
    top = n->top;
  }
  return top;
}

#include "solve.c"