/* (C) Nguyễn Bá Ngọc 2023 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Minh họa ánh xạ char * => int dựa trên cây
   nhị phân tìm kiếm. */

struct bst_node {
  char key[100];
  int value;
  struct bst_node *left;
  struct bst_node *right;
  struct bst_node *top;
};

typedef int (*cmp_fnt)(const void *, const void *);

struct bst_tree {
  struct bst_node *root;
  int size;
  cmp_fnt cmp;
};

struct bst_node *bst_node(char *key, int value) {
  struct bst_node *nn = malloc(sizeof(struct bst_node));
  strcpy(nn->key, key);
  nn->value = value;
  nn->left = NULL;
  nn->right = NULL;
  nn->top = NULL;
  return nn;
}

struct bst_tree *bst_tree(cmp_fnt cmp) {
  struct bst_tree *t = malloc(sizeof(struct bst_tree));
  t->cmp = cmp;
  t->root = NULL;
  t->size = 0;
}

/**
 * Thêm cặp (key, value) vào cây t,
 * trong trường hợp key đã tồn tại thì trả về con trỏ
 * tới giá trị của nút tương ứng với key.
 * Nếu khóa chưa tồn tại thì trả về NULL.
 */
int *bst_put(struct bst_tree *t, char *key, int value) {
  if (t->root == NULL) {
    t->root = bst_node(key, value);
    ++t->size;
    return NULL;
  }
  struct bst_node *p = t->root, *c;
  int r;
  for(;;) {
    r = t->cmp(key, p->key);
    if (r == 0) {
      return &p->value;
    }
    c = r < 0? p->left: p->right;
    if (!c) {
      break;
    }
    p = c;
  }
  struct bst_node *nn = bst_node(key, value);
  if (r < 0) {
    p->left = nn;
  } else {
    p->right = nn;
  }
  nn->top = p;
  ++t->size;
  return NULL;
}

int *bst_search(struct bst_tree *t, char *key) {
  struct bst_node *u = t->root;
  while (u) {
    int r = t->cmp(key, u->key);
    if (r == 0) {
      return &u->value;
    }
    u = r < 0 ? u->left: u->right;
  }
  return NULL;
}

struct bst_node *bst_pvalnode(int *pval) {
  return pval? ((void*)pval) - offsetof(struct bst_node, value): NULL;
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
int bst_remove(struct bst_tree *t, char *key) {
  struct bst_node *d = bst_pvalnode(bst_search(t, key));
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

void bst_node_print_lnr(struct bst_node *n, int depth) {
  if (n->left) {
    bst_node_print_lnr(n->left, depth + 1);
  }
  for (int i = 0; i < depth * 2; ++i) {
    printf(" ");
  }
  printf("(%s: %d)\n", n->key, n->value);
  if (n->right) {
    bst_node_print_lnr(n->right, depth + 1);
  }
}

void bst_pprint(struct bst_tree *t) {
  printf("size: %d\n", t->size);
  if (t->root) {
    bst_node_print_lnr(t->root, 0);
  }
}

int cmps(const void *p1, const void *p2) {
  return strcmp(p1, p2);
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

int main() {
  struct bst_tree *t = bst_tree(cmps);
  char key[100];
  int value;
  while (scanf("%s", key) == 1) {
    if (strcmp(key, "***") == 0) {
      break;
    }
    scanf("%d", &value);
    bst_put(t, key, value);
  }
  bst_pprint(t);
  while (scanf("%s", key) == 1) {
    if (strcmp(key, "***") == 0) {
      break;
    }
    int *pval = bst_search(t, key);
    if (pval) {
      printf("Found: (%s: %d)\n", bst_pvalnode(pval)->key, *pval);
    } else {
      printf("Key %s not exists\n", key);
    }
  }
  while (scanf("%s", key) == 1) {
    int ret = bst_remove(t, key);
    if (ret) {
      printf("Đã xóa %s\n", key);
      bst_pprint(t);
    } else {
      printf("Không tìm thấy %s\n", key);
    }
  }
  bst_free(t);
}