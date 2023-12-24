/** (C) Nguyễn Bá Ngọc 2023
 *  cgen version:3.6.9
 */
#ifndef CGEN_H_
#define CGEN_H_

/***** ./base/flog.h *****/
#ifndef BASE_FLOG_H_
#define BASE_FLOG_H_ 
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define FLOG_VERSION "1.0.0";
#ifdef CGEN_DEBUG
  #define FLOG(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
#else
  #define FLOG(...)
#endif
static inline void _flog(const char *file, int line, const char *fmt, ...) {
  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  fprintf(stderr, "%s:%d: ", filename, line);
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}
#endif

/***** ./base/fnt.h *****/
#ifndef BASE_FNT_H_
#define BASE_FNT_H_ 
#include <stdlib.h>
#include <string.h>
typedef int (*compare_fnt)(const void *p1, const void *p2);
static inline int cmpi(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int*)p2;
}
static inline int rcmpi(const void *p1, const void *p2) {
  return *(const int*)p2 - *(const int*)p1;
}
static inline int cmpd(const void *p1, const void *p2) {
  double v1 = *(const double *)p1, v2 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int rcmpd(const void *p1, const void *p2) {
  double v2 = *(const double *)p1, v1 = *(const double *)p2;
  if (v1 < v2) {
    return - 1;
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
static inline void frees(char *s) {
  free(s);
}
#endif

/***** ./algo/algo.h *****/
#ifndef ALGO_ALGO_H_
#define ALGO_ALGO_H_ 
#include <stdlib.h>
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
  q2sort(a, (left - a)/sz + 1, sz, cmp);
  q2sort(right, (a - right)/sz + n, sz, cmp);
}
static int binsearch(const void *a, int n, int sz, const void *v, compare_fnt cmp) {
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
#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)
static void heap_shift_down(void *a, int n, int sz, int i, compare_fnt cmp) {
  for (;;) {
    int lc = HLEFT(i), rc = HRIGHT(i), top = i;
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
  int j = HTOP(i);
  while (i > 0 && cmp(a + j * sz, a + i * sz) < 0) {
    vswap(a + i * sz, a + j * sz, sz);
    i = j;
    j = HTOP(i);
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
  int n = a[-1], k = n -1;
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
  int n = a[-1], k = n -1;
  while (k > 0) {
    if (a[k - 1] < a[k]) {
      return 1;
    }
    --k;
  }
  return 0;
}
static void free_perm(int *a) {
  free(a - 1);
}
static int *first_comb(int k, int n) {
  if (k > n || k < 1) {
    return NULL;
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
static void free_comb(int *a) {
  free(a - 2);
}
#endif

/***** ./cont/slist.h *****/
#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_ 
#define SDEFN(sname,dtype) \
struct sname##_node { \
  dtype data; \
  struct sname##_node *next; \
}; \
struct sname { \
  struct sname##_node *front; \
  struct sname##_node *back; \
  void (*fv)(dtype); \
  long size; \
}
#define SDECL(sname,dtype,prefix) \
SDEFN(sname, dtype); \
struct sname *prefix##create(); \
struct sname *sname(); \
void prefix##clear(struct sname *list); \
void prefix##free(struct sname *list); \
struct sname *prefix##append(struct sname *list, dtype data); \
struct sname *prefix##prepend(struct sname *list, dtype data); \
struct sname *prefix##dfront(struct sname *list); \
struct sname *prefix##push(struct sname *list, dtype elem); \
dtype *prefix##top(struct sname *list); \
struct sname *prefix##pop(struct sname *list); \
struct sname *prefix##enque(struct sname *list, dtype elem); \
dtype *prefix##peek(struct sname *list); \
struct sname *prefix##deque(struct sname *list); \
int prefix##empty(struct sname *list)
#define SIMPL(sname,dtype,prefix) \
struct sname##_node *sname##_node(dtype data) { \
  struct sname##_node *tmp = malloc(sizeof(struct sname##_node)); \
  if (!tmp) { \
    FLOG("Lỗi cấp phát bộ nhớ tạo nút."); \
    return NULL; \
  } \
  tmp->data = data; \
  tmp->next = NULL; \
  return tmp; \
} \
struct sname *prefix##create() { \
  struct sname *tmp = malloc(sizeof(struct sname)); \
  if (!tmp) { \
    FLOG("Lỗi cấp phát bộ nhớ tạo danh sách."); \
    return NULL; \
  } \
  tmp->front = tmp->back = NULL; \
  tmp->fv = NULL; \
  tmp->size = 0; \
  return tmp; \
} \
struct sname *sname() { \
  return prefix##create(); \
} \
void prefix##clear(struct sname *list) { \
  while (!prefix##empty(list)) { \
    prefix##dfront(list); \
  } \
} \
void prefix##free(struct sname *list) { \
  prefix##clear(list); \
  free(list); \
} \
struct sname *prefix##append(struct sname *list, dtype data) {\
  struct sname##_node *node = sname##_node(data); \
  if (!node) { \
    FLOG("Lỗi tạo nút"); \
    return NULL; \
  } \
  if (list->front == NULL) { \
    list->front = list->back = node; \
  } else { \
    list->back->next = node; \
    list->back = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *prefix##prepend(struct sname *list, dtype data) {\
  struct sname##_node *node = sname##_node(data); \
  if (!node) { \
    FLOG("Lỗi tạo nút"); \
    return NULL; \
  } \
  if (list->front == NULL) { \
    list->front = list->back = node; \
  } else { \
    node->next = list->front; \
    list->front = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *prefix##dfront(struct sname *list) {\
  if (!list || prefix##empty(list)) { \
    FLOG("Xóa đầu danh sách không hợp lệ."); \
    return NULL; \
  } \
  if (list->front == list->back) { \
    list->back = NULL; \
  } \
  struct sname##_node *tmp = list->front; \
  list->front = tmp->next; \
  if (list->fv) { \
    list->fv(tmp->data); \
  } \
  free(tmp); \
  --list->size; \
  return list; \
} \
struct sname *prefix##push(struct sname *list, dtype elem) { \
  return prefix##prepend(list, elem); \
} \
dtype *prefix##top(struct sname *list) { \
  return &list->front->data; \
} \
struct sname *prefix##pop(struct sname *list) {\
  return prefix##dfront(list); \
} \
struct sname *prefix##enque(struct sname *list, dtype elem) { \
  return prefix##append(list, elem); \
} \
dtype *prefix##peek(struct sname *list) {\
  return &list->front->data; \
} \
struct sname *prefix##deque(struct sname *list) { \
  return prefix##dfront(list); \
} \
int prefix##empty(struct sname *list) { \
  return list->front == NULL || list->back == NULL; \
}
#define SDECL_IMPL(sname,dtype,prefix) \
SDECL(sname, dtype, prefix); \
SIMPL(sname, dtype, prefix)
#endif

/***** ./cont/tmap.h *****/
#ifndef CONT_TMAP_H_
#define CONT_TMAP_H_ 
#include <stddef.h>
enum tcolors {
  RED = 0,
  BLACK = 1
};
#define TNN(tname) tname ##_node
#define TDEFN(tname,ktype,vtype) \
struct TNN(tname) { \
  ktype key; \
  vtype value; \
  enum tcolors color; \
  struct TNN(tname) *left; \
  struct TNN(tname) *right; \
  struct TNN(tname) *top; \
}; \
struct tname { \
  struct TNN(tname) *root; \
  compare_fnt cmp; \
  void (*fk)(ktype);\
  void (*fv)(vtype); \
  long size; \
}
#define TCOLOR(n) ((n)? (n)->color: BLACK)
#define TIS_RED(n) ((n) && (n)->color == RED)
#define TIS_BLACK(n) (!(n) || (n)->color == BLACK)
#define TPAINT_BLACK(n) (n)->color = BLACK
#define TPAINT_RED(n) (n)->color = RED
#define TPAINT(n,c) (n)->color = (c)
#define TSET_PC(n,p,c) (n)->top = (p); TPAINT(n, c)
#define TDECL(tname,ktype,vtype,prefix) \
TDEFN(tname, ktype, vtype); \
struct TNN(tname) *prefix##left_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##right_most(struct TNN(tname) *n); \
struct TNN(tname) *prefix##left_deepest(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lrn(struct TNN(tname) *n); \
struct TNN(tname) *prefix##next_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##prev_lnr(struct TNN(tname) *n); \
struct TNN(tname) *prefix##first_lrn(struct tname *t); \
struct TNN(tname) *prefix##first_lnr(struct tname *t); \
struct TNN(tname) *prefix##last_lnr(struct tname *t); \
struct TNN(tname) *prefix##pval_node(void *pv); \
struct tname *prefix##create(compare_fnt cmp); \
struct tname *tname(compare_fnt cmp); \
void prefix##clear(struct tname *t); \
void prefix##free(struct tname *t); \
vtype *prefix##put(struct tname *t, ktype key, vtype value); \
vtype *prefix##get(struct tname *t, ktype key); \
struct tname *prefix##remove(struct tname *t, ktype key)
#define TSEARCH(t,key,x) \
do { \
  int rl; \
  x = t->root; \
  while (x) { \
    rl = t->cmp(&key, &x->key); \
    if (rl == 0) { \
      break; \
    } \
    x = rl < 0? x->left: x->right; \
  } \
} while (0)
#define TCHANGE(old_node,new_node,parent,t) \
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
#define TROTATE(t,x,right,left,y_) \
  do { \
    y_ = (x)->right; \
    (x)->right = y_->left; \
    if (y_->left != NULL) { \
      y_->left->top = (x); \
    } \
    y_->top = (x)->top; \
    TCHANGE(x, y_, (x)->top, t); \
    y_->left = (x); \
    (x)->top = y_; \
  } while (0)
#define IMPL_INSERT_FIXUP(t,n,p,left,right,y_) \
      if (TIS_RED(p->top->right)) { \
            \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(p->top->right); \
        TPAINT_RED(p->top); \
        n = p->top; \
        p = n->top; \
        if (p == NULL) { \
                                       \
          TPAINT_BLACK(n); \
          break; \
        } \
        if (TIS_BLACK(p)) { \
                                                            \
          break; \
        } \
      } else { \
        if (n == n->top->right) { \
              \
          TROTATE(t, p, right, left, y_); \
          n = p; \
          p = n->top; \
        } \
            \
        TPAINT_BLACK(p); \
        TPAINT_RED(p->top); \
        p = p->top; \
        TROTATE(t, p, left, right, y_); \
        break; \
      }
#define TPUT_FIXUP(t,n,p,y_) \
do { \
      \
  while (1) { \
        \
    if (p == p->top->left) { \
      IMPL_INSERT_FIXUP(t, n, p, left, right, y_) \
    } else { \
       IMPL_INSERT_FIXUP(t, n, p, right, left, y_) \
    } \
  } \
} while (0)
#define ERASE_COLOR_SYMMETRY(left,right,p,n,s,cn,dn,u_) \
         \
      if (TIS_RED(s)) { \
            \
        TROTATE(t, p, right, left, u_); \
        TPAINT_RED(p); \
        TPAINT_BLACK(s); \
        s = p->right; \
      } \
      dn = s->right; \
      if (TIS_BLACK(dn)) { \
        cn = s->left; \
        if (TIS_BLACK(cn)) { \
              \
          TPAINT_RED(s); \
          if (TIS_RED(p)) { \
            TPAINT_BLACK(p); \
          } else { \
            n = p; \
            p = n->top; \
            if (p) { \
              continue; \
            } \
          } \
          break; \
        } \
            \
        TROTATE(t, s, left, right, u_); \
        s = p->right; \
      } \
          \
      dn = s->right; \
      TROTATE(t, p, right, left, u_); \
      TPAINT(s, p->color); \
      TPAINT_BLACK(p); \
      TPAINT_BLACK(dn); \
      break
#define TDELETE_FIXUP(t,p,n,s,cn,dn,u_) \
do { \
                                                                    \
  n = NULL; \
  while (1) { \
       \
    s = p->right; \
    if (n != s) { \
      ERASE_COLOR_SYMMETRY(left, right, p, n, s, cn, dn, u_); \
    } else { \
      s = p->left; \
      ERASE_COLOR_SYMMETRY(right, left, p, n, s, cn, dn, u_); \
    } \
  } \
} while (0)
#define TIMPL(tname,ktype,vtype,prefix) \
struct TNN(tname) *TNN(tname)(ktype key, vtype value) { \
  struct TNN(tname) *nn = malloc(sizeof(struct TNN(tname))); \
  nn->key = key; \
  nn->value = value; \
  TPAINT_RED(nn); \
  nn->left = nn->right = nn->top = NULL; \
  return nn; \
} \
struct TNN(tname) *prefix##left_most(struct TNN(tname) *n) { \
  while (n->left) { \
    n = n->left; \
  } \
  return n; \
} \
struct TNN(tname) *prefix##right_most(struct TNN(tname) *n) { \
  while (n->right) { \
    n = n->right; \
  } \
  return n; \
} \
struct TNN(tname) *prefix##left_deepest(struct TNN(tname) *n) { \
  for (;;) { \
    if (n->left) { \
      n = n->left; \
    } else if (n->right) { \
      n = n->right; \
    } else { \
      break; \
    } \
  } \
  return n; \
} \
struct TNN(tname) *prefix##next_lrn(struct TNN(tname) *n) { \
  struct TNN(tname) *top = n->top; \
  if (top && n == top->left && top->right) { \
    return prefix##left_deepest(top->right); \
  } \
  return top; \
} \
struct TNN(tname) *prefix##next_lnr(struct TNN(tname) *n) { \
  if (n->right) { \
    return prefix##left_most(n->right); \
  } \
  struct TNN(tname) *top = n->top; \
  while (top != NULL && n == top->right) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct TNN(tname) *prefix##prev_lnr(struct TNN(tname) *n) { \
  if (n->left) { \
    return prefix##right_most(n->left); \
  } \
  struct TNN(tname) *top = n->top; \
  while (top != NULL && n == top->left) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct TNN(tname) *prefix##first_lrn(struct tname *t) { \
  return prefix##left_deepest(t->root); \
} \
struct TNN(tname) *prefix##first_lnr(struct tname *t) { \
  return prefix##left_most(t->root); \
} \
struct TNN(tname) *prefix##last_lnr(struct tname *t) { \
  return prefix##right_most(t->root); \
} \
struct TNN(tname) *prefix##pval_node(void *pv) { \
  void *tmp = pv; \
  return tmp - offsetof(struct TNN(tname), value); \
} \
struct tname *prefix##create(compare_fnt cmp) { \
  if (!cmp) { \
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh."); \
    return NULL; \
  } \
  struct tname *t = malloc(sizeof(struct tname)); \
  if (!t) { \
    FLOG("Không thể cấp phát bộ nhớ."); \
    return NULL; \
  } \
  t->root = NULL; \
  t->cmp = cmp; \
  t->fk = NULL; \
  t->fv = NULL; \
  t->size = 0; \
  return t; \
} \
struct tname *tname(compare_fnt cmp) { \
  return prefix##create(cmp); \
} \
void prefix##clear(struct tname *t) { \
  struct TNN(tname) *n = prefix##first_lrn(t); \
  struct TNN(tname) *tmp = NULL; \
  while (n) { \
    if (t->fk) { \
      t->fk(n->key); \
    } \
    if (t->fv) { \
      t->fv(n->value); \
    } \
    tmp = n; \
    n = prefix##next_lrn(n); \
    free(tmp); \
  } \
  t->size = 0; \
} \
void prefix##free(struct tname *t) { \
  prefix##clear(t); \
  free(t); \
} \
static struct tname *prefix##delete(struct tname *t, struct TNN(tname) *dn) { \
  struct TNN(tname) *node = dn; \
  struct TNN(tname) *child = node->right, \
            *tmp = node->left, \
            *parent, *rebalance; \
  struct TNN(tname) *p; \
  enum tcolors c; \
  if (!tmp) { \
        \
    p = node->top; \
    c = node->color; \
    parent = p; \
    TCHANGE(node, child, parent, t); \
    if (child) { \
      TSET_PC(child, p, c); \
      rebalance = NULL; \
    } else { \
      rebalance = c == BLACK? parent: NULL; \
    } \
    tmp = parent; \
  } else if (!child) { \
                                                                 \
    p = node->top; \
    c = node->color; \
    TSET_PC(tmp, p, c); \
    parent = p; \
    TCHANGE(node, tmp, parent, t); \
    rebalance = NULL; \
    tmp = parent; \
  } else { \
    struct TNN(tname) *successor = child, *child2; \
    tmp = child->left; \
    if (!tmp) { \
          \
      parent = successor; \
      child2 = successor->right; \
    } else { \
          \
      do { \
        parent = successor; \
        successor = tmp; \
        tmp = tmp->left; \
      } while (tmp); \
      child2 = successor->right; \
      parent->left = child2; \
      successor->right = child; \
      child->top = successor; \
    } \
    tmp = node->left; \
    successor->left = tmp; \
    tmp->top = successor; \
    p = node->top; \
    c = node->color; \
    tmp = p; \
    TCHANGE(node, successor, tmp, t); \
    if (child2) { \
      TSET_PC(child2, parent, BLACK); \
      rebalance = NULL; \
    } else { \
      enum tcolors c2 = successor->color; \
      rebalance = c2 == BLACK? parent: NULL; \
    } \
    TSET_PC(successor, p, c); \
    tmp = successor; \
  } \
  if (rebalance) { \
    struct TNN(tname) *n, *s, *cn, *dn, *u_; \
    TDELETE_FIXUP(t, rebalance, n, s, cn, dn, u_); \
  } \
  free(dn); \
  return t; \
} \
vtype *prefix##put(struct tname *t, ktype key, vtype value) { \
  struct TNN(tname) *nn = TNN(tname)(key, value), \
                    *top = NULL, \
                    *x = t->root, \
                   **loc = &t->root; \
  int rl = 0; \
  while (x) { \
    rl = t->cmp(&key, &x->key); \
    if (rl == 0) { \
      free(nn); \
      return &x->value; \
    } \
    top = x; \
    if (rl < 0) { \
      x = top->left; \
      loc = &top->left; \
    } else { \
      x = top->right; \
      loc = &top->right; \
    } \
  } \
  *loc = nn; \
  nn->top = top; \
  if (top == NULL) { \
    nn->color = BLACK; \
  } else if (TIS_RED(top)) { \
                                     \
    struct TNN(tname) *y_; \
    TPUT_FIXUP(t, nn, top, y_); \
  } \
  ++t->size; \
  return NULL; \
} \
vtype *prefix##get(struct tname *t, ktype key) { \
  struct TNN(tname) *x; \
  TSEARCH(t, key, x); \
  if (!x) { \
    return NULL; \
  } \
  return &x->value; \
} \
struct tname *prefix##remove(struct tname *t, ktype key) { \
  struct TNN(tname) *n; \
  TSEARCH(t, key, n); \
  if (!n) { \
    return NULL; \
  } \
  if (t->fk) { \
    t->fk(n->key); \
  } \
  if (t->fv) { \
    t->fv(n->value); \
  }\
  prefix##delete(t, n);\
  --(t->size); \
  return t; \
}
#define TDECL_IMPL(tname,keytype,valtype,prefix) \
TDECL(tname, keytype, valtype, prefix); \
TIMPL(tname, keytype, valtype, prefix)
#endif

/***** ./cont/vector.h *****/
#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_ 
#define VDEFN(vecname,elemtype) \
  struct vecname { \
    elemtype *elems; \
    long size; \
    long cap; \
    double rio; \
    void (*fv)(elemtype); \
  }
#define VDECL(vecname,elemtype,prefix) \
VDEFN(vecname, elemtype); \
struct vecname *prefix##create(long sz); \
struct vecname *vecname(long sz); \
struct vecname *prefix##clear(struct vecname *v); \
void prefix##free(struct vecname *po); \
int prefix##empty(struct vecname *v); \
struct vecname *prefix##reserve(struct vecname *v, long newcap); \
struct vecname *prefix##resize(struct vecname *v, long newsz); \
struct vecname *prefix##append(struct vecname *v, elemtype val); \
struct vecname *prefix##remove(struct vecname *v, long idx); \
struct vecname *prefix##insertb(struct vecname *v, elemtype elem, long pos); \
struct vecname *prefix##fill(struct vecname *v, elemtype value); \
struct vecname *prefix##push(struct vecname *v, elemtype elem); \
struct vecname *prefix##pop(struct vecname *v); \
elemtype *prefix##top(struct vecname *v)
#define VIMPL(vecname,elemtype,prefix) \
struct vecname *prefix##create(long sz) { \
  if (sz < 0) { \
    FLOG("Tạo vec-tơ với kích thước không hợp lệ, sz = %ld", sz); \
    return NULL; \
  } \
  struct vecname *v = malloc(sizeof(struct vecname)); \
  v->fv = NULL; \
  v->size = sz; \
  v->cap = sz > 0? sz: 8; \
  v->rio = 2.0; \
  v->elems = calloc(v->cap, sizeof(elemtype)); \
  return v; \
} \
struct vecname *vecname(long sz) { \
  return prefix##create(sz); \
} \
struct vecname *prefix##clear(struct vecname *v) { \
  return prefix##resize(v, 0); \
} \
void prefix##free(struct vecname *v) { \
  prefix##clear(v); \
  free(v->elems); \
  free(v); \
} \
int prefix##empty(struct vecname *v) { \
  return v->size == 0; \
} \
struct vecname *prefix##reserve(struct vecname *v, long newcap) {\
  if (newcap < v->size) { \
    FLOG("Dự trữ với dung lượng (%ld) < kích thước (%ld)", newcap, v->size); \
    return NULL; \
  } \
  v->elems = realloc(v->elems, newcap * sizeof(elemtype)); \
  v->cap = newcap; \
  return v; \
} \
struct vecname *prefix##resize(struct vecname *v, long newsize) {\
  if (newsize > v->cap) { \
    prefix##reserve(v, newsize); \
  } else if (newsize < v->size && v->fv) { \
    for (long j_ = newsize; j_ < v->size; ++j_) { \
      v->fv(v->elems[j_]); \
    } \
  } \
  v->size = newsize; \
  return v; \
} \
struct vecname *prefix##append(struct vecname *v, elemtype val) {\
  if (v->size == v->cap) { \
    prefix##reserve(v, v->rio * v->size); \
  } \
  v->elems[v->size] = val; \
  ++v->size; \
  return v; \
} \
struct vecname *prefix##remove(struct vecname *v, long idx) { \
  long sz = v->size; \
  if (idx >= sz || idx < 0) { \
    FLOG("Xóa phần tử với chỉ số không hợp lệ sz = %ld, idx = %ld", sz, idx); \
    return NULL; \
  } \
  elemtype *arr = v->elems; \
  elemtype tmp = arr[idx]; \
  for (long i = idx; i < sz - 1; ++i) { \
    arr[i] = arr[i + 1]; \
  } \
  arr[sz - 1] = tmp; \
  return prefix##resize(v, sz - 1); \
}\
struct vecname *prefix##insertb(struct vecname *v, elemtype elem, long pos) { \
 prefix##resize(v, v->size + 1); \
 elemtype *arr = v->elems; \
 for (long i = v->size - 1; i > pos; --i) { \
   arr[i] = arr[i - 1]; \
 } \
 arr[pos] = elem; \
 return v; \
} \
struct vecname *prefix##fill(struct vecname *v, elemtype value) { \
  for (long i = 0; i < v->size; ++i) {\
    v->elems[i] = value; \
  } \
  return v; \
} \
struct vecname *prefix##push(struct vecname *v, elemtype elem) { \
  return prefix##append(v, elem); \
}\
struct vecname *prefix##pop(struct vecname *v) { \
  return prefix##remove(v, v->size - 1); \
} \
elemtype *prefix##top(struct vecname *v) { \
  return v->elems + (v->size - 1); \
}
#define VDECL_IMPL(vecname,elemtype,prefix) \
VDECL(vecname, elemtype, prefix); \
VIMPL(vecname, elemtype, prefix)
#endif
#endif  // CGEN_H_
