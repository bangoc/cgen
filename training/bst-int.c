/* (C) Nguyễn Bá Ngọc 2023 */

#include "bst-int.h"

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

struct bst_node *bst_search(struct bst_tree *t, int key) {
  struct bst_node *u = t->root;
  while (u) {
    if (key == u->key) {
      return u;
    }
    u = key < u->key ? u->left: u->right;
  }
  return NULL;
}

int bst_equal(struct bst_tree *t1, struct bst_tree *t2) {
  if (t1->size != t2->size) {
    return 0;
  }
  struct bst_node *n1 = bst_first_lnr(t1), *n2 = bst_first_lnr(t2);
  while (n1 && n2) {
    if (n1->key != n2->key) {
      return 0;
    }
    n1 = bst_next_lnr(n1);
    n2 = bst_next_lnr(n2);
  }
  return 1;
}

void bst_change(struct bst_node *old_node, struct bst_node *new_node,
                struct bst_tree *t) {
  struct bst_node *top = old_node->top;
  if (top) {
    if (top->left == old_node) {
      top->left = new_node;
    } else if (top->right == old_node) {
      top->right = new_node;
    }
  } else {
    t->root = new_node;
  }
  if (new_node) {
    new_node->top = top;
  }
}

/* Xóa nút tương ứng với khóa khỏi cây
 * Trả về 1 nếu đã xóa, hoặc 0 nếu khóa không tồn tại
 */
int bst_remove(struct bst_tree *t, int key) {
  struct bst_node *d = bst_search(t, key);
  if (!d) {
    return 0;
  }
  struct bst_node *n = d, *nr = n->right, *tmp = n->left;
  if (!tmp) {
    bst_change(n, nr, t);
  } else if (!nr) {
    bst_change(n, tmp, t);
  } else {
    struct bst_node *s = nr;
    /* Trường hợp 2: Nút liền sau n là con phải của n.
       *
       *    (n)          (s)
       *    / \          / \
       *  (x) (s)  ->  (x) (sr)
       *        \
       *        (sr)
       */
    tmp = nr->left;
    if (tmp) {
       /* Trường hợp 3: Nút liền sau n là nút trái nhất trong
       * cây con phải của n
       *
       *    (n)          (s)
       *    / \          / \
       *  (x)(nr)  ->  (x)(nr)
       *      /            /
       *   (top)         (top)
       *    /            /
       *  (s)          (sr)
       *    \
       *    (sr)
       */
      struct bst_node *top;
      do {
        top = s;
        s = tmp;
        tmp = tmp->left;
      } while (tmp);
      struct bst_node *sr = s->right;
      top->left = sr;
      if (sr) {
        sr->top = top;
      }
      s->right = nr;
      nr->top = s;
    }
    tmp = n->left;
    s->left = tmp;
    tmp->top = s;
    bst_change(n, s, t);
  }
  free(d);
  --t->size;
  return 1;
}

void bst_node_print_rnl(struct bst_node *n, int depth) {
  if (n->right) {
    bst_node_print_rnl(n->right, depth + 1);
  }
  if (depth > 0) {
    printf("%1$*2$c", ' ', 2 * depth);
  }
  printf("%d\n", n->key);
  if (n->left) {
    bst_node_print_rnl(n->left, depth + 1);
  }
}

void bst_pprint(struct bst_tree *t) {
  if (t->root) {
    bst_node_print_rnl(t->root, 0);
  }
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