#ifndef BST_H_
#define BST_H_

/* (C) Nguyễn Bá Ngọc 2024 */

const static char k_bst_version[] = "3.0.0";

#include <stdlib.h>
#include <string.h>

#define BST_DECL(bst, value_t) \
  struct bst##_node; \
  struct bst; \
  struct bst##_node *bst##_node(const char *key, value_t value); \
  struct bst *bst(); \
  struct bst##_node *bst##_put(struct bst *t, const char *key, value_t value); \
  struct bst##_node *bst##_first(struct bst *t); \
  struct bst##_node *bst##_next(struct bst##_node *n); \
  struct bst##_node *bst##_search(struct bst *t, const char *key); \
  int bst##_rem(struct bst *t, const char *key); \
  void bst##_free(struct bst *t);

#define BST_IMPL(bst, key_size, value_t) \
struct bst##_node { \
  char key[key_size]; \
  value_t value; \
  struct bst##_node *left, *right, *top; \
}; \
\
struct bst { \
  struct bst##_node *root; \
  int (*cmp)(const char *, const char *); \
  long size; \
}; \
\
struct bst##_node *bst##_node(const char *key, value_t value) { \
  struct bst##_node *nn = malloc(sizeof(struct bst##_node)); \
  strcpy(nn->key, key); \
  nn->value = value; \
  nn->left = nn->right = nn->top = NULL; \
  return nn; \
} \
\
struct bst *bst() { \
  struct bst *t = malloc(sizeof (struct bst)); \
  t->root = NULL; \
  t->cmp = strcmp; \
  t->size = 0; \
  return t; \
} \
\
struct bst##_node *bst##_put(struct bst *t, const char *key, value_t value) { \
  struct bst##_node *top = NULL, *n = t->root; \
  int order; \
  while (n) { \
    order = t->cmp(key, n->key); \
    if (order == 0) { \
      return n; \
    } \
    top = n; \
    n = order < 0? n->left: n->right; \
  } \
  n = bst##_node(key, value); \
  n->top = top; \
  ++t->size; \
  if (top == NULL) { \
    t->root = n; \
    return NULL; \
  } \
  if (order < 0) { \
    top->left = n; \
  } else { \
    top->right = n; \
  } \
  return NULL; \
} \
\
static inline struct bst##_node *bst##_left_most(struct bst##_node *n) { \
  struct bst##_node *top = NULL; \
  while (n) { \
    top = n; \
    n = n->left; \
  } \
  return top; \
}\
struct bst##_node *bst##_first(struct bst *t) { \
  return bst##_left_most(t->root); \
} \
\
struct bst##_node *bst##_next(struct bst##_node *n) { \
  if (n->right) { \
    return bst##_left_most(n->right); \
  } \
  while (n->top) { \
    if (n->top->left == n) { \
      return n->top; \
    } \
    n = n->top; \
  } \
  return NULL; \
} \
\
struct bst##_node *bst##_search(struct bst *t, const char *key) { \
  struct bst##_node *n = t->root; \
  while (n) { \
    int o = t->cmp(key, n->key); \
    if (o == 0) { \
      return n; \
    } \
    n = o < 0? n->left: n->right; \
  } \
  return NULL; \
} \
\
static inline void bst##_change(struct bst *t, struct bst##_node *old, struct bst##_node *nn) { \
  struct bst##_node *top = old->top; \
  if (top == NULL) { \
    t->root = nn; \
  } else { \
    if (top->left == old) { \
      top->left = nn; \
    } else { \
      top->right = nn; \
    } \
  } \
  if (nn) { \
    nn->top = top; \
  } \
} \
\
int bst##_rem(struct bst *t, const char *key) { \
  struct bst##_node *n = bst##_search(t, key); \
  if (!n) { \
    return 0; \
  } \
  if (n->left == NULL && n->right == NULL) { \
    /* TH1:
        (n)
        / \
      NULL NULL
    */ \
    bst##_change(t, n, NULL); \
    free(n); \
    return 1; \
  } \
  struct bst##_node *r = n->right, *l = n->left; \
  if (l == NULL) { \
    /* TH2:
        (n)
        /  \
       NULL r
    */ \
    bst##_change(t, n, r); \
    free(n); \
    return 1; \
  } \
  if (r == NULL) { \
    /* TH2:
        (n)
        / \
       l  NULL
    */ \
    bst##_change(t, n, l); \
    free(n); \
    return 1; \
  } \
  if (r->left == NULL) { \
    /* TH3:
         (n)
        /   \
      (x)    r
            /  \
          NULL (y)
    */ \
    r->left = n->left; \
    n->left->top = r; \
    bst##_change(t, n, r); \
    free(n); \
    return 1; \
  } \
  /* TH4:
      (n)
     /  \
    (x)   r
        /   \
       nn  (y)
      /   \
     NULL (z)
  */ \
  struct bst##_node *nn = r->left, *nnt = r; \
  while (nn->left) { \
    nnt = nn; \
    nn = nn->left; \
  } \
  nnt->left = nn->right; \
  if (nn->right) { \
    nn->right->top = nnt; \
  } \
  nn->left = l; \
  nn->right = r; \
  l->top = nn; \
  r->top = nn; \
  bst##_change(t, n, nn); \
  free(n); \
  return 1; \
} \
\
static void bst##_free_lrn(struct bst##_node *n) { \
  if (n->left) { \
    bst##_free_lrn(n->left); \
  } \
  if (n->right) { \
    bst##_free_lrn(n->right); \
  } \
  free(n); \
} \
\
void bst##_free(struct bst *t) { \
  if (t->root) { \
    bst##_free_lrn(t->root); \
  } \
  free(t); \
}

#define BST_DECL_IMPL(struct_name, key_size, value_t) \
  BST_DECL(struct_name, value_t) \
  BST_IMPL(struct_name, key_size, value_t)

#endif  // BST_H_