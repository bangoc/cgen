#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_fnt)(const void *p1, const void *p2);
static inline int cmpi(const void *p1, const void *p2) {
  return *(const int *)p1 - *(const int *)p2;
}
static inline int rcmpi(const void *p1, const void *p2) {
  return *(const int *)p2 - *(const int *)p1;
}
static inline int cmpd(const void *p1, const void *p2) {
  double v1 = *(const double *)p1, v2 = *(const double *)p2;
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int rcmpd(const void *p1, const void *p2) {
  double v2 = *(const double *)p1, v1 = *(const double *)p2;
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int cmps(const void *p1, const void *p2) {
  char *const *s1 = p1, *const *s2 = p2;
  return strcmp(*s1, *s2);
}
static inline int rcmps(const void *p1, const void *p2) {
  char *const *s2 = p1, *const *s1 = p2;
  return strcmp(*s1, *s2);
}
static inline void frees(char *s) { free(s); }
static inline void vswap(void *o1, void *o2, int sz) {
  char tmp, *p = o1, *q = o2;
  for (int i = 0; i < sz; ++i) {
    tmp = *p;
    *p = *q;
    *q = tmp;
    ++p;
    ++q;
  }
}
static void q2sort(void *a, int n, int sz, compare_fnt cmp) {
  if (n <= 1) {
    return;
  }
  void *left = a, *right = a + (n - 2) * sz;
  void *v = a + (n - 1) * sz;
  for (;;) {
    while (cmp(v, left) > 0) {
      left += sz;
    }
    while (cmp(right, v) > 0) {
      if (right == a) {
        break;
      }
      right -= sz;
    }
    if (left >= right) {
      break;
    }
    vswap(left, right, sz);
    left += sz;
    right -= sz;
  }
  vswap(left, v, sz);
  right = left + sz;
  left = left - sz;
  q2sort(a, (left - a) / sz + 1, sz, cmp);
  q2sort(right, (a - right) / sz + n, sz, cmp);
}
static int binsearch(const void *a, int n, int sz, const void *v,
                     compare_fnt cmp) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    int x = cmp(a + m * sz, v);
    if (x == 0) {
      return m;
    }
    if (x < 0) {
      l = m + 1;
    } else if (x > 0) {
      r = m - 1;
    }
  }
  return -1;
}
static void heap_shift_down(void *a, int n, int sz, int i, compare_fnt cmp) {
  for (;;) {
    int lc = (((i) << 1) + 1), rc = (((i) << 1) + 2), top = i;
    if (lc < n && cmp(a + top * sz, a + lc * sz) < 0) {
      top = lc;
    }
    if (rc < n && cmp(a + top * sz, a + rc * sz) < 0) {
      top = rc;
    }
    if (top == i) {
      break;
    }
    vswap(a + i * sz, a + top * sz, sz);
    i = top;
  }
}
static void heap_shift_up(void *a, int n, int sz, int i, compare_fnt cmp) {
  int j = (((i)-1) >> 1);
  while (i > 0 && cmp(a + j * sz, a + i * sz) < 0) {
    vswap(a + i * sz, a + j * sz, sz);
    i = j;
    j = (((i)-1) >> 1);
  }
}
static void heap_make(void *a, int n, int sz, compare_fnt cmp) {
  for (int i = n / 2; i >= 0; --i) {
    heap_shift_down(a, n, sz, i, cmp);
  }
}
static int *first_perm(int n) {
  int *a = malloc((n + 1) * sizeof(int));
  a[0] = n;
  ++a;
  for (int i = 0; i < n; ++i) {
    a[i] = i;
  }
  return a;
}
static int next_perm(int *a) {
  int n = a[-1], k = n - 1;
  while (k > 0) {
    if (a[k - 1] < a[k]) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return 0;
  }
  int i = k - 1, l = n - 1;
  while (a[l] < a[i]) {
    --l;
  }
  int tmp = a[l];
  a[l] = a[i];
  a[i] = tmp;
  l = n - 1;
  while (k < l) {
    tmp = a[k];
    a[k] = a[l];
    a[l] = tmp;
    ++k;
    --l;
  }
  return 1;
}
static int has_next_perm(int *a) {
  int n = a[-1], k = n - 1;
  while (k > 0) {
    if (a[k - 1] < a[k]) {
      return 1;
    }
    --k;
  }
  return 0;
}
static void free_perm(int *a) { free(a - 1); }
static int *first_comb(int k, int n) {
  if (k > n || k < 1) {
    return ((void *)0);
  }
  int *a = malloc((k + 2) * sizeof(int));
  a[0] = k;
  a[1] = n;
  a += 2;
  for (int i = 0; i < k; ++i) {
    a[i] = i;
  }
  return a;
}
static int next_comb(int *a) {
  int k = a[-2], n = a[-1], r = k - 1;
  while (r >= 0) {
    if (a[r] < n - k + r) {
      ++a[r];
      for (int i = r + 1; i < k; ++i) {
        a[i] = a[i - 1] + 1;
      }
      return 1;
    }
    --r;
  }
  return 0;
}
static int has_next_comb(int *a) {
  int k = a[-2], n = a[-1], r = k - 1;
  while (r >= 0) {
    if (a[r] < n - k + r) {
      return 1;
    }
    --r;
  }
  return 0;
}
static void free_comb(int *a) { free(a - 2); }
typedef long int ptrdiff_t;
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld
      __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
enum tcolors { RED = 0, BLACK = 1 };
struct simap_node {
  char *key;
  int value;
  enum tcolors color;
  struct simap_node *left;
  struct simap_node *right;
  struct simap_node *top;
};
struct simap {
  struct simap_node *root;
  compare_fnt cmp;
  void (*fk)(char *);
  void (*fv)(int);
  long size;
};
struct simap_node *sileft_most(struct simap_node *n);
struct simap_node *siright_most(struct simap_node *n);
struct simap_node *sileft_deepest(struct simap_node *n);
struct simap_node *sinext_lrn(struct simap_node *n);
struct simap_node *sinext_lnr(struct simap_node *n);
struct simap_node *siprev_lnr(struct simap_node *n);
struct simap_node *sifirst_lrn(struct simap *tm);
struct simap_node *sifirst_lnr(struct simap *tm);
struct simap_node *silast_lnr(struct simap *tm);
struct simap_node *sipval_node(void *pv);
struct simap *sicreate(compare_fnt cmp);
struct simap *simap(compare_fnt cmp);
void siclear(struct simap *tm);
void sifree(struct simap *tm);
int *siput(struct simap *tm, char *key, int value);
int *siget(struct simap *tm, char *key);
struct simap *siremove(struct simap *tm, char *key);
static inline void sichange(struct simap *tm, struct simap_node *old_node,
                            struct simap_node *new_node) {
  struct simap_node *top = old_node->top;
  if (top) {
    if (top->left == old_node) {
      top->left = new_node;
    } else {
      top->right = new_node;
    }
  } else {
    tm->root = new_node;
  }
  if (new_node) {
    (new_node)->top = top;
  }
}
static inline void sirotate_left(struct simap *tm, struct simap_node *x) {
  struct simap_node *y = x->right;
  x->right = y->left;
  if (y->left != ((void *)0)) {
    y->left->top = x;
  }
  sichange(tm, x, y);
  y->left = x;
  x->top = y;
}
static inline void sirotate_right(struct simap *tm, struct simap_node *x) {
  struct simap_node *y = x->left;
  x->left = y->right;
  if (y->right != ((void *)0)) {
    y->right->top = x;
  }
  sichange(tm, x, y);
  y->right = x;
  x->top = y;
}
static inline void siput_fixup(struct simap *tm, struct simap_node *n) {
  struct simap_node *t = n->top, *tt = t->top;
  while (1) {
    if (t == tt->left) {
      if (((tt->right) && (tt->right)->color == RED)) {
        (t)->color = BLACK;
        (tt->right)->color = BLACK;
        (tt)->color = RED;
        n = tt;
        t = n->top;
        if (t == ((void *)0)) {
          (n)->color = BLACK;
          break;
        }
        tt = t->top;
        if ((!(t) || (t)->color == BLACK)) {
          break;
        }
      } else {
        if (n == t->right) {
          sirotate_left(tm, t);
          n = t;
          t = n->top;
        }
        (t)->color = BLACK;
        (tt)->color = RED;
        sirotate_right(tm, tt);
        break;
      }
    } else {
      if (((tt->left) && (tt->left)->color == RED)) {
        (t)->color = BLACK;
        (tt->left)->color = BLACK;
        (tt)->color = RED;
        n = tt;
        t = n->top;
        if (t == ((void *)0)) {
          (n)->color = BLACK;
          break;
        }
        tt = t->top;
        if ((!(t) || (t)->color == BLACK)) {
          break;
        }
      } else {
        if (n == t->left) {
          sirotate_right(tm, t);
          n = t;
          t = n->top;
          tt = t->top;
        }
        (t)->color = BLACK;
        (tt)->color = RED;
        sirotate_left(tm, tt);
        break;
      }
    }
  }
}
static inline void sidelete_fixup(struct simap *tm, struct simap_node *t) {
  struct simap_node *n = ((void *)0), *s, *cn, *dn;
  while (1) {
    s = t->right;
    if (n != s) {
      if (((s) && (s)->color == RED)) {
        sirotate_left(tm, t);
        (t)->color = RED;
        (s)->color = BLACK;
        s = t->right;
      }
      dn = s->right;
      if ((!(dn) || (dn)->color == BLACK)) {
        cn = s->left;
        if ((!(cn) || (cn)->color == BLACK)) {
          (s)->color = RED;
          if (((t) && (t)->color == RED)) {
            (t)->color = BLACK;
            break;
          }
          n = t;
          t = n->top;
          if (t) {
            continue;
          } else {
            break;
          }
        }
        sirotate_right(tm, s);
        sirotate_left(tm, t);
        (cn)->color = (t->color);
        (t)->color = BLACK;
        break;
      }
      dn = s->right;
      sirotate_left(tm, t);
      (s)->color = (t->color);
      (t)->color = BLACK;
      (dn)->color = BLACK;
      break;
    } else {
      s = t->left;
      if (((s) && (s)->color == RED)) {
        sirotate_right(tm, t);
        (t)->color = RED;
        (s)->color = BLACK;
        s = t->left;
      }
      dn = s->left;
      if ((!(dn) || (dn)->color == BLACK)) {
        cn = s->right;
        if ((!(cn) || (cn)->color == BLACK)) {
          (s)->color = RED;
          if (((t) && (t)->color == RED)) {
            (t)->color = BLACK;
          } else {
            n = t;
            t = n->top;
            if (t) {
              continue;
            }
          }
          break;
        }
        sirotate_left(tm, s);
        s = t->left;
      }
      dn = s->left;
      sirotate_right(tm, t);
      (s)->color = (t->color);
      (t)->color = BLACK;
      (dn)->color = BLACK;
      break;
    }
  }
}
struct simap_node *simap_node(char *key, int value) {
  struct simap_node *nn = malloc(sizeof(struct simap_node));
  nn->key = key;
  nn->value = value;
  (nn)->color = RED;
  nn->left = nn->right = nn->top = ((void *)0);
  return nn;
}
struct simap_node *sileft_most(struct simap_node *n) {
  while (n->left) {
    n = n->left;
  }
  return n;
}
struct simap_node *siright_most(struct simap_node *n) {
  while (n->right) {
    n = n->right;
  }
  return n;
}
struct simap_node *sileft_deepest(struct simap_node *n) {
  for (;;) {
    if (n->left) {
      n = n->left;
    } else if (n->right) {
      n = n->right;
    } else {
      break;
    }
  }
  return n;
}
struct simap_node *sinext_lrn(struct simap_node *n) {
  struct simap_node *top = n->top;
  if (top && n == top->left && top->right) {
    return sileft_deepest(top->right);
  }
  return top;
}
struct simap_node *sinext_lnr(struct simap_node *n) {
  if (n->right) {
    return sileft_most(n->right);
  }
  struct simap_node *top = n->top;
  while (top != ((void *)0) && n == top->right) {
    n = top;
    top = n->top;
  }
  return top;
}
struct simap_node *siprev_lnr(struct simap_node *n) {
  if (n->left) {
    return siright_most(n->left);
  }
  struct simap_node *top = n->top;
  while (top != ((void *)0) && n == top->left) {
    n = top;
    top = n->top;
  }
  return top;
}
struct simap_node *sifirst_lrn(struct simap *tm) {
  return tm->root ? sileft_deepest(tm->root) : ((void *)0);
}
struct simap_node *sifirst_lnr(struct simap *tm) {
  return tm->root ? sileft_most(tm->root) : ((void *)0);
}
struct simap_node *silast_lnr(struct simap *tm) {
  return tm->root ? siright_most(tm->root) : ((void *)0);
}
struct simap_node *sipval_node(void *pv) {
  return pv ? pv - __builtin_offsetof(struct simap_node, value) : ((void *)0);
}
struct simap *sicreate(compare_fnt cmp) {
  if (!cmp) {
    ;
    return ((void *)0);
  }
  struct simap *tm = malloc(sizeof(struct simap));
  if (!tm) {
    ;
    return ((void *)0);
  }
  tm->root = ((void *)0);
  tm->cmp = cmp;
  tm->fk = ((void *)0);
  tm->fv = ((void *)0);
  tm->size = 0;
  return tm;
}
struct simap *simap(compare_fnt cmp) {
  return sicreate(cmp);
}
void siclear(struct simap *tm) {
  struct simap_node *n = sifirst_lrn(tm);
  struct simap_node *tmp = ((void *)0);
  while (n) {
    if (tm->fk) {
      tm->fk(n->key);
    }
    if (tm->fv) {
      tm->fv(n->value);
    }
    tmp = n;
    n = sinext_lrn(n);
    free(tmp);
  }
  tm->size = 0;
}
void sifree(struct simap *tm) {
  siclear(tm);
  free(tm);
}
static struct simap *sidelete(struct simap *tm, struct simap_node *dn) {
  struct simap_node *node = dn;
  struct simap_node *child = node->right, *tmp = node->left, *top, *rebalance;
  if (!tmp) {
    sichange(tm, node, child);
    if (child) {
      (child)->color = BLACK;
      rebalance = ((void *)0);
    } else {
      rebalance = (!(node) || (node)->color == BLACK) ? node->top : ((void *)0);
    }
  } else if (!child) {
    sichange(tm, node, tmp);
    (tmp)->color = BLACK;
    rebalance = ((void *)0);
  } else {
    struct simap_node *sss = child, *child2;
    tmp = child->left;
    if (!tmp) {
      top = sss;
      child2 = sss->right;
    } else {
      do {
        sss = tmp;
        tmp = tmp->left;
      } while (tmp);
      top = sss->top;
      child2 = sss->right;
      top->left = child2;
      if (child2) {
        child2->top = top;
      }
      sss->right = child;
      child->top = sss;
    }
    tmp = node->left;
    sss->left = tmp;
    tmp->top = sss;
    if (child2) {
      (child2)->color = BLACK;
      rebalance = ((void *)0);
    } else {
      rebalance = (!(sss) || (sss)->color == BLACK) ? top : ((void *)0);
    }
    sichange(tm, node, sss);
    (sss)->color = (node->color);
  }
  if (rebalance) {
    sidelete_fixup(tm, rebalance);
  }
  free(dn);
  --(tm->size);
  return tm;
}
int *siput(struct simap *tm, char *key, int value) {
  struct simap_node *nn = simap_node(key, value), *top = ((void *)0),
                    *x = tm->root, **loc = &tm->root;
  int rl = 0;
  while (x) {
    rl = tm->cmp(&key, &x->key);
    if (rl == 0) {
      free(nn);
      return &x->value;
    }
    top = x;
    if (rl < 0) {
      x = top->left;
      loc = &top->left;
    } else {
      x = top->right;
      loc = &top->right;
    }
  }
  *loc = nn;
  nn->top = top;
  if (top == ((void *)0)) {
    nn->color = BLACK;
  } else if (((top) && (top)->color == RED)) {
    siput_fixup(tm, nn);
  }
  ++tm->size;
  return ((void *)0);
}
int *siget(struct simap *tm, char *key) {
  struct simap_node *x = tm->root;
  while (x) {
    int rl = tm->cmp(&key, &x->key);
    if (rl == 0) {
      break;
    }
    x = rl < 0 ? x->left : x->right;
  }
  if (!x) {
    return ((void *)0);
  }
  return &x->value;
}
struct simap *siremove(struct simap *tm, char *key) {
  struct simap_node *n = sipval_node(siget(tm, key));
  if (!n) {
    return ((void *)0);
  }
  if (tm->fk) {
    tm->fk(n->key);
  }
  if (tm->fv) {
    tm->fv(n->value);
  }
  sidelete(tm, n);
  return tm;
};
int main() {
  char key[100];
  struct simap *si = simap(cmps);
  si->fk = frees;
  while (scanf("%s", key) == 1) {
    int *value = siget(si, key);
    if (value) {
      ++(*value);
    } else {
      siput(si, strdup(key), 1);
    }
  }
  struct simap_node *nd = sifirst_lnr(si);
  while (nd) {
    printf("%s: %d\n", nd->key, nd->value);
    nd = sinext_lnr(nd);
  }
  sifree(si);
  printf("Test Ok!\n");
  ;
}
