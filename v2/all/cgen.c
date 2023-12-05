/** (C) Nguyễn Bá Ngọc 2023
 *  cgen version:2.0.0
 */
#include "cgen.h"

/***** ./cont/vector.c *****/
struct vector {
  gtype *elems;
  long sz;
  long cap;
  double k;
  destructor_fnt fv;
};
long vsize(const struct vector *v) {
  return v->sz;
}
int vempty(const struct vector *v) {
  return v->sz == 0;
}
long vcap(const struct vector *v) {
  return v->cap;
}
double vratio(const struct vector *v) {
  return v->k;
}
destructor_fnt vfv(const struct vector *v) {
  return v->fv;
}
struct vector *vsetfv(struct vector *v, destructor_fnt fv) {
  v->fv = fv;
  return v;
}
gtype *varr(struct vector *v) {
  return v->elems;
}
gtype *vref(struct vector *v, long i) {
  return v->elems + i;
}
long vidx(struct vector *v, gtype *elem_ptr) {
  return elem_ptr - v->elems;
}
struct vector *vreserve(struct vector *v, long newcap) {
  if (newcap < v->sz) {
    FLOG("Dự trữ với dung lượng (%ld) < kích thước (%ld)", newcap, v->sz);
    return NULL;
  }
  v->elems = realloc(v->elems, newcap * sizeof(gtype));
  v->cap = newcap;
  return v;
}
struct vector *vresize(struct vector *v, long newsz) {
  if (newsz > v->cap) {
    vreserve(v, newsz);
  } else if (newsz < v->sz && v->fv) {
    for (long j = newsz; j < vsize(v); ++j) {
      v->fv(v->elems[j].v);
    }
  }
  v->sz = newsz;
  return v;
}
struct vector *_vappend(struct vector *v, gtype val) {
  if (v->sz == v->cap) {
    vreserve(v, v->k * v->sz);
  }
  v->elems[v->sz] = val;
  ++v->sz;
  return v;
}
struct vector *vremove(struct vector *v, long idx) {
  gtype *_arr = varr(v);
  long _sz = vsize(v);
  if ((idx) >= _sz || (idx) < 0) {
    FLOG("Xóa phần tử với chỉ số không hợp lệ sz = %ld, idx = %ld",
         _sz, (long)idx);
    return NULL;
  }
  gtype _tmp = _arr[(idx)];
  for (long _i = (idx); _i < _sz - 1; ++_i) {
    _arr[_i] = _arr[_i + 1];
  }
  _arr[_sz - 1] = _tmp;
  vresize(v, _sz - 1);
  return v;
}
struct vector *vclear(struct vector *v) {
  return vresize(v, 0);
}
void vfree(void *op) {
  struct vector *v = op;
  vclear(v);
  free((v)->elems);
  free(v);
}
void _vfill(struct vector *v, gtype value) {
  VTRAVERSE(_cur, v) {
    *_cur = (value);
  }
}
struct vector *vcreate(long sz) {
  if (sz < 0) {
    FLOG("Tạo vec-tơ với kích thước không hợp lệ, sz = %ld", sz);
    return NULL;
  }
  struct vector *v = malloc(sizeof(struct vector));
  v->fv = NULL;
  v->sz = sz;
  v->cap = sz > 0? sz: 8;
  v->k = 2.0;
  v->elems = calloc(v->cap, sizeof(gtype));
  return v;
}
struct vector *vclone(struct vector *v) {
  struct vector *v2 = malloc(sizeof(struct vector));
  memcpy(v2, v, sizeof(struct vector));
  if (v->cap == 0) {
    v2->elems = NULL;
    return v2;
  }
  size_t elems_size = v2->cap * sizeof(gtype);
  v2->elems = malloc(elems_size);
  memcpy(v2->elems, v->elems, elems_size);
  return v2;
}
int vsameas(struct vector *v1, struct vector *v2) {
  if (v1->sz != v2->sz ||
      v1->cap != v2->cap ||
      v1->fv != v2->fv) {
    return 0;
  }
  size_t elems_size = v1->cap * sizeof(gtype);
  char *p = (char *)(v1->elems),
       *q = (char *)(v2->elems);
  for (size_t i = 0; i < elems_size; ++i) {
    if (p[i] != q[i]) {
      return 0;
    }
  }
  return 1;
}
struct vector *vpop(struct vector *v) {
  if (!v || v->sz == 0) {
    FLOG("Xóa ngăn xếp không hợp lệ.");
    return NULL;
  }
  vresize(v, v->sz - 1);
  return v;
}
gtype *vtop(struct vector *v) {
  if (!v || v->sz == 0) {
    FLOG("Đọc đỉnh của ngăn xếp không hợp lệ.");
    return NULL;
  }
  return v->elems + (v->sz - 1);
}
struct vector *_vinsertb(struct vector *v, gtype e, long i) {
  if (!v || i < 0 || i >= v->sz) {
    FLOG("Đầu vào không hợp lệ.");
    return NULL;
  }
  vresize(v, v->sz + 1);
  for (long j = v->sz - 1; j > i; --j) {
    v->elems[j] = v->elems[j - 1];
  }
  v->elems[i] = e;
  return NULL;
}

/***** ./cont/queue.c *****/
#include <stdlib.h>
struct queue {
  long sz;
  long cap;
  long fi;
  long la;
  destructor_fnt fv;
  gtype *elems;
};
struct queue *qcreate(long cap) {
  if (cap < 0) {
    FLOG("Tạo hàng đợi với tham số không hợp lệ.");
    return NULL;
  }
  struct queue *q = malloc(sizeof(struct queue));
  if (!q) {
    FLOG("Lỗi cấp phát bộ nhớ cho hàng đợi.");
    return NULL;
  }
  q->sz = 0;
  q->cap = cap > 0? cap: 8;
  q->fi = -1;
  q->la = -1;
  q->fv = NULL;
  q->elems = calloc(cap, sizeof(gtype));
  if (!q->elems) {
    FLOG("Lỗi cấp phát bộ nhớ cho các phần tử");
    free(q);
    return NULL;
  }
  return q;
}
struct queue *_qenque(struct queue* q, gtype val) {
  if (!q) {
    FLOG("Lỗi hàng đợi chưa khởi tạo.");
    return NULL;
  }
  if (q->sz == 0) {
    q->fi = q->la = 0;
    q->elems[0] = val;
    ++q->sz;
    return q;
  }
  if (q->sz < q->cap) {
    q->la = qnext(q, q->la);
    q->elems[q->la] = val;
    ++q->sz;
    return q;
  }
  q->cap *= 2;
  void *tmp = realloc(q->elems, q->cap * sizeof(gtype));
  if (!tmp) {
    FLOG("Lỗi mở rộng bộ nhớ.");
    return NULL;
  }
  q->elems = tmp;
  if (q->fi > q->la) {
    for (long i = 0; i <= q->la; ++i) {
      q->elems[q->sz + i] = q->elems[i];
    }
    q->la += q->sz;
  }
  q->la = qnext(q, q->la);
  q->elems[q->la] = val;
  ++q->sz;
  return q;
}
struct queue *qdeque(struct queue *q) {
  if (!q || q->sz == 0) {
    FLOG("Hàng đợi không hợp lệ");
    return NULL;
  }
  if (q->fv) {
    q->fv(q->elems[q->fi].v);
  }
  q->fi = qnext(q, q->fi);
  --q->sz;
  return q;
}
gtype *qpeek(struct queue *q) {
  if (!q || q->sz == 0) {
    FLOG("Hàng đợi không hợp lệ");
    return NULL;
  }
  return q->elems + q->fi;
}
long qnext(const struct queue *q, long id) {
  return (id + 1) % q->cap;
}
int qempty(const struct queue *q) {
  return q->sz == 0;
}
long qsize(const struct queue *q) {
  return q->sz;
}
destructor_fnt qfv(struct queue *q) {
  return q->fv;
}
struct queue *qsetfv(struct queue *q, destructor_fnt fv) {
  q->fv = fv;
  return q;
}
void qfree(void *op) {
  struct queue *q = op;
  while (!qempty(q)) {
    qdeque(q);
  }
  free(q->elems);
  free(q);
}

/***** ./cont/slist.c *****/
struct snode {
  gtype data;
  struct snode *next;
};
struct slist {
  struct snode *front;
  struct snode *back;
  destructor_fnt fv;
  long length;
};
struct snode *snode(gtype data) {
  struct snode *tmp = malloc(sizeof(struct snode));
  if (!tmp) {
    FLOG("Lỗi cấp phát bộ nhớ tạo nút.");
    return NULL;
  }
  tmp->data = data;
  tmp->next = NULL;
  return tmp;
}
struct slist *screate() {
  struct slist *tmp = malloc(sizeof(struct slist));
  if (!tmp) {
    FLOG("Lỗi cấp phát bộ nhớ tạo danh sách.");
    return NULL;
  }
  tmp->front = tmp->back = NULL;
  tmp->fv = NULL;
  tmp->length = 0;
  return tmp;
}
gtype *sfront(struct slist *list) {
  return (gtype*)list->front;
}
gtype *sback(struct slist *list) {
  return (gtype*)list->back;
}
long ssize(struct slist *list) {
  return list->length;
}
int sempty(struct slist *list) {
  return list->front == NULL && list->back == NULL;
}
struct slist *_sappend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
    FLOG("Lỗi tạo nút");
    return NULL;
  }
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  ++list->length;
  return list;
}
struct slist *_sprepend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
    FLOG("Lỗi tạo nút");
    return NULL;
  }
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->length;
  return list;
}
struct slist *sdfront(struct slist *list) {
  if (!list || sempty(list)) {
    FLOG("Xóa đầu danh sách không hợp lệ.");
    return NULL;
  }
  if (list->front == list->back) {
    list->back = NULL;
  }
  struct snode *tmp = list->front;
  list->front = tmp->next;
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}
destructor_fnt sfv(struct slist *list) {
  return list->fv;
}
struct slist *ssetfv(struct slist *list, destructor_fnt fv) {
  list->fv = fv;
  return list;
}
void sfree(void *op) {
  struct slist *list = op;
  while (!sempty(list)) {
    sdfront(list);
  }
  free(list);
}
gtype *stop(struct slist *list) {
  if (list == NULL || sempty(list)) {
    FLOG("Ngăn xếp ở trạng thái không hợp lệ.");
    return NULL;
  }
  return sfront(list);
}
gtype *speek(struct slist *list) {
  if (list == NULL || sempty(list)) {
    FLOG("hàng đợi ở trạng thái không hợp lệ.");
    return NULL;
  }
  return sfront(list);
}

/***** ./cont/dlist.c *****/
#include <stdlib.h>
struct dnode {
  gtype data;
  struct dnode *next;
  struct dnode *prev;
};
struct dlist {
  struct dnode *front;
  struct dnode *back;
  long length;
  destructor_fnt fv;
};
struct dnode *dnode(gtype data) {
  struct dnode *tmp = malloc(sizeof(struct dnode));
  if (!tmp) {
    FLOG("Không thể cấp phát bộ nhớ cho nút.");
    return NULL;
  }
  tmp->data = data;
  tmp->next = tmp->prev = NULL;
  return tmp;
}
struct dlist *dcreate() {
  struct dlist *tmp = malloc(sizeof(struct dlist));
  if (!tmp) {
    FLOG("Không thể cấp phát bộ nhớ cho danh sách.");
    return NULL;
  }
  tmp->front = tmp->back = NULL;
  tmp->length = 0;
  tmp->fv = NULL;
  return tmp;
}
gtype *dfront(struct dlist *list) {
  return (gtype*)list->front;
}
gtype *dback(struct dlist *list) {
  return (gtype*)list->back;
}
long dsize(struct dlist *list) {
  return list->length;
}
int dempty(struct dlist *list) {
  return dfront(list) == NULL && dback(list) == NULL;
}
void dfree(void *op) {
  struct dlist *list = op;
  while (!dempty(list)) {
    ddfront(list);
  }
  free(list);
}
void dclear(struct dlist *list) {
  while (!dempty(list)) {
    ddfront(list);
  }
}
struct dlist *_dappend(struct dlist *list, gtype elem) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;
  }
  struct dnode *nn = dnode(elem);
  if (!nn) {
    FLOG("Lỗi không thể tạo nút.");
    return NULL;
  }
  if (dempty(list)) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
  ++list->length;
  return list;
}
struct dlist *_dprepend(struct dlist *list, gtype elem) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;
  }
  struct dnode *nn = dnode(elem);
  if (!nn) {
    FLOG("Lỗi không thể tạo nút.");
    return NULL;
  }
  if (dempty(list)) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
  ++list->length;
  return list;
}
struct dlist *ddfront(struct dlist *list) {
  if (!list || dempty(list)) {
    FLOG("Lỗi truy cập danh sách không hợp lệ.");
    return NULL;
  }
  struct dnode *tmp = list->front;
  if (list->front == list->back) {
    list->front = NULL;
    list->back = NULL;
  } else {
    list->front = tmp->next;
    list->front->prev = NULL;
  }
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}
struct dlist *ddback(struct dlist *list) {
  if (!list || dempty(list)) {
    FLOG("Lỗi truy cập danh sách không hợp lệ.");
    return NULL;
  }
  struct dnode *tmp = list->back;
  if (list->back == list->front) {
    list->front = NULL;
    list->back = NULL;
  } else {
    list->back = tmp->prev;
    list->back->next = NULL;
  }
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}
destructor_fnt dfv(struct dlist *list) {
  return list->fv;
}
struct dlist *dsetfv(struct dlist *list, destructor_fnt fv) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;
  }
  list->fv = fv;
  return list;
}

/***** ./cont/tmap.c *****/
#include <stdlib.h>
enum tcolors {
  RED = 0,
  BLACK = 1
};
struct tnode {
  gtype key;
  gtype value;
  enum tcolors color;
  struct tnode *left;
  struct tnode *right;
  struct tnode *top;
};
#define TCOLOR_OF(n) ((n)? (n)->color: BLACK)
#define TIS_RED(n) (TCOLOR_OF(n) == RED)
#define TIS_BLACK(n) (TCOLOR_OF(n) == BLACK)
#define TPAINT_BLACK(n) ((n)->color = BLACK)
#define TPAINT_RED(n) ((n)->color = RED)
#define TPAINT(n,c) ((n)->color = (c))
#define TSET_PC(n,p,c) (n)->top = (p); TPAINT(n, c)
struct tnode *tnode(const gtype key, const gtype value) {
  struct tnode *nn = malloc(sizeof(struct tnode));
  if (!nn) {
    FLOG("Không thể cấp phát bộ nhớ cho nút.");
    return NULL;
  }
  nn->key = key;
  nn->value = value;
  TPAINT_RED(nn);
  nn->left = nn->right = nn->top = NULL;
  return nn;
}
struct tmap {
  struct tnode *root;
  compare_fnt cmp;
  destructor_fnt fk, fv;
  long size;
};
struct tmap *tcreate(compare_fnt cmp) {
  if (!cmp) {
    FLOG("Không thể tạo bảng cây nếu không biết hàm so sánh.");
    return NULL;
  }
  struct tmap *t = malloc(sizeof(struct tmap));
  if (!t) {
    FLOG("Không thể cấp phát bộ nhớ.");
    return NULL;
  }
  t->root = NULL;
  t->cmp = cmp;
  t->fv = t->fk = NULL;
  t->size = 0;
  return t;
}
struct tmap *tconstruct(compare_fnt cmp, destructor_fnt fk, destructor_fnt fv) {
  struct tmap *t = tcreate(cmp);
  if (t) {
    tsetfk(t, fk);
    tsetfv(t, fv);
  }
  return t;
}
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
#define TROTATE(t,x,right,left) \
  do { \
    struct tnode *_y = (x)->right; \
    (x)->right = _y->left; \
    if (_y->left != NULL) { \
      _y->left->top = (x); \
    } \
    _y->top = (x)->top; \
    TCHANGE(x, _y, (x)->top, t); \
    _y->left = (x); \
    (x)->top = _y; \
  } while (0)
static void tput_fixup(struct tmap *t, struct tnode *n, struct tnode *p) {
  while (1) {
    if (p == p->top->left) {
#define IMPL_INSERT_FIXUP(left,right) \
      struct tnode *_u = p->top->right; \
      if (TIS_RED(_u)) { \
            \
        TPAINT_BLACK(p); \
        TPAINT_BLACK(_u); \
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
          TROTATE(t, p, right, left); \
          n = p; \
          p = n->top; \
        } \
                                                      \
        TPAINT_BLACK(p); \
        TPAINT_RED(p->top); \
        p = p->top; \
        TROTATE(t, p, left, right); \
        break; \
      }
      IMPL_INSERT_FIXUP(left, right)
    } else {
      IMPL_INSERT_FIXUP(right, left)
    }
#undef IMPL_INSERT_FIXUP
  }
}
gtype *_tput(struct tmap *t, const gtype key, const gtype value) {
  struct tnode *nn = tnode(key, value);
  if (!nn) {
    FLOG("Không thể tạo nút mới.");
    return NULL;
  }
  struct tnode *top = NULL;
  struct tnode *x = t->root;
  struct tnode **loc = &t->root;
  int rl = 0;
  while (x) {
    rl = t->cmp(&key, &x->key);
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
  if (top == NULL) {
    nn->color = BLACK;
  } else if (TIS_RED(top)) {
    tput_fixup(t, nn, top);
  }
  ++t->size;
  return NULL;
}
static struct tnode *tsearch(struct tmap *t, gtype key) {
  if (!t || !t->cmp) {
    FLOG("Bảng ở trạng thái không hợp lệ.");
    return NULL;
  }
  int rl;
  struct tnode *x = t->root;
  while (x) {
    rl = t->cmp(&key, &x->key);
    if (rl == 0) {
      return x;
    }
    x = rl < 0? x->left: x->right;
  }
  return NULL;
}
gtype *_tget(struct tmap *t, const gtype key) {
  struct tnode *n = tsearch(t, key);
  if (!n) {
    return NULL;
  }
  return &n->value;
}
static void tdelete_fixup(struct tmap *t, struct tnode *parent) {
  struct tnode *node = NULL, *sibling,
          *cn,
          *dn;
  while (1) {
    sibling = parent->right;
    if (node != sibling) {
#define ERASE_COLOR_SYMMETRY(left,right) \
         \
      if (TIS_RED(sibling)) { \
                                                  \
        TROTATE(t, parent, right, left); \
        TPAINT_RED(parent); \
        TPAINT_BLACK(sibling); \
        sibling = parent->right; \
      } \
      dn = sibling->right; \
      if (TIS_BLACK(dn)) { \
        cn = sibling->left; \
        if (TIS_BLACK(cn)) { \
                                                                     \
          TPAINT_RED(sibling); \
          if (TIS_RED(parent)) { \
            TPAINT_BLACK(parent); \
          } else { \
            node = parent; \
            parent = node->top; \
            if (parent) { \
              continue; \
            } \
          } \
          break; \
        } \
                                                                     \
        TROTATE(t, sibling, left, right); \
        sibling = parent->right; \
      } \
          \
      dn = sibling->right; \
      TROTATE(t, parent, right, left); \
      TPAINT(sibling, TCOLOR_OF(parent)); \
      TPAINT_BLACK(parent); \
      TPAINT_BLACK(dn); \
      break
      ERASE_COLOR_SYMMETRY(left, right);
    } else {
      sibling = parent->left;
      ERASE_COLOR_SYMMETRY(right, left);
#undef ERASE_COLOR_SYMMETRY
    }
  }
}
static struct tmap *tdelete(struct tmap *t, struct tnode *dn) {
  struct tnode *node = dn;
  struct tnode *child = node->right,
            *tmp = node->left,
            *parent, *rebalance;
  struct tnode *p;
  enum tcolors c;
  if (!tmp) {
    p = node->top;
    c = TCOLOR_OF(node);
    parent = p;
    TCHANGE(node, child, parent, t);
    if (child) {
      TSET_PC(child, p, c);
      rebalance = NULL;
    } else {
      rebalance = c == BLACK? parent: NULL;
    }
    tmp = parent;
  } else if (!child) {
    p = node->top;
    c = TCOLOR_OF(node);
    TSET_PC(tmp, p, c);
    parent = p;
    TCHANGE(node, tmp, parent, t);
    rebalance = NULL;
    tmp = parent;
  } else {
    struct tnode *successor = child, *child2;
    tmp = child->left;
    if (!tmp) {
      parent = successor;
      child2 = successor->right;
    } else {
      do {
        parent = successor;
        successor = tmp;
        tmp = tmp->left;
      } while (tmp);
      child2 = successor->right;
      parent->left = child2;
      successor->right = child;
      child->top = successor;
    }
    tmp = node->left;
    successor->left = tmp;
    tmp->top = successor;
    p = node->top;
    c = TCOLOR_OF(node);
    tmp = p;
    TCHANGE(node, successor, tmp, t);
    if (child2) {
      TSET_PC(child2, parent, BLACK);
      rebalance = NULL;
    } else {
      enum tcolors c2 = TCOLOR_OF(successor);
      rebalance = c2 == BLACK? parent: NULL;
    }
    TSET_PC(successor, p, c);
    tmp = successor;
  }
  if (rebalance) {
    tdelete_fixup(t, rebalance);
  }
  free(dn);
  return t;
}
struct tmap *_tremove(struct tmap *t, gtype key) {
  struct tnode *n = tsearch(t, key);
  if (!n) {
    return NULL;
  }
  if (t->fk) {
    t->fk(n->key.v);
  }
  if (t->fv) {
    t->fv(n->value.v);
  }
  tdelete(t, n);
  --(t->size);
  return t;
}
long tsize(const struct tmap *t) {
  return t->size;
}
gtype *tkey_of(struct tnode *n) {
  return &n->key;
}
gtype *tvalue_of(struct tnode *n) {
  return &n->value;
}
struct tnode *tleft_most(struct tnode *n) {
  if (!n) {
    FLOG("Tham số nút không hợp lệ.");
    return NULL;
  }
  while (n->left) {
    n = n->left;
  }
  return n;
}
struct tnode *tright_most(struct tnode *n) {
  if (!n) {
    FLOG("Tham số nút không hợp lệ.");
    return NULL;
  }
  while (n->right) {
    n = n->right;
  }
  return n;
}
struct tnode *tleft_deepest(struct tnode *n) {
  if (!n) {
    FLOG("Tham số nút không hợp lệ.");
    return NULL;
  }
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
struct tnode *tnext_lrn(struct tnode *x) {
  struct tnode *top = x->top;
  if (top && x == top->left && top->right) {
    return tleft_deepest(top->right);
  }
  return top;
}
void tnextkv_lrn(gtype **pk, gtype **pv) {
  struct tnode *node = (struct tnode *)(*pk);
  if (!node) {
    FLOG("Tham số không hợp lệ");
    return;
  }
  struct tnode *tmp = tnext_lrn(node);
  if (tmp) {
    *pk = &tmp->key;
    *pv = &tmp->value;
    return;
  }
  *pk = *pv = NULL;
}
struct tnode *troot(struct tmap *t) {
  return t->root;
}
struct tnode *tnext_lnr(struct tnode *x) {
  if (!x) {
    FLOG("Truy cập nút NULL");
    return NULL;
  }
  if (x->right) {
    return tleft_most(x->right);
  }
  struct tnode *top = x->top;
  while (top != NULL && x == top->right) {
    x = top;
    top = x->top;
  }
  return top;
}
void tnextkv_lnr(gtype **k, gtype **v) {
  struct tnode *n = (struct tnode *)(*k);
  struct tnode *tmp = tnext_lnr(n);
  if (!tmp) {
    *k = NULL;
    *v = NULL;
    return;
  }
  *k = &tmp->key;
  *v = &tmp->value;
}
struct tnode *tprev_lnr(struct tnode *x) {
  if (!x) {
    FLOG("Truy cập nút NULL");
    return NULL;
  }
  if (x->left) {
    return tright_most(x->left);
  }
  struct tnode *top = x->top;
  while (top != NULL && x == top->left) {
    x = top;
    top = x->top;
  }
  return top;
}
void tprevkv_lnr(gtype **k, gtype **v) {
  struct tnode *n = (struct tnode *)(*k);
  struct tnode *tmp = tprev_lnr(n);
  if (!tmp) {
    *k = NULL;
    *v = NULL;
    return;
  }
  *k = &tmp->key;
  *v = &tmp->value;
}
int tis_red(struct tnode *n) {
  return TIS_RED(n);
}
int tis_black(struct tnode *n) {
  return TIS_BLACK(n);
}
struct tnode *tleft_of(struct tnode *n) {
  if (!n) {
    FLOG("Nút không hợp lệ.");
    return NULL;
  }
  return n->left;
}
struct tnode *tright_of(struct tnode *n) {
  if (!n) {
    FLOG("Nút không hợp lệ.");
    return NULL;
  }
  return n->right;
}
struct tnode *ttop_of(struct tnode *n) {
  if (!n) {
    FLOG("Nút không hợp lệ.");
    return NULL;
  }
  return n->top;
}
void tfree(void *op) {
  struct tmap *t = op;
  struct tnode *tmp = NULL;
  TTRAVERSE_LRN(key, value, t) {
    free(tmp);
    tmp = (struct tnode *)key;
    if (t->fk) {
      t->fk(key->v);
    }
    if (t->fv) {
      t->fv(value->v);
    }
  }
  free(tmp);
  free(t);
}
destructor_fnt tfk(struct tmap *t) {
  return t->fk;
}
destructor_fnt tfv(struct tmap *t) {
  return t->fv;
}
struct tmap *tsetfk(struct tmap *t, destructor_fnt fk) {
  if (!t) {
    FLOG("Tham số t không hợp lệ.");
    return NULL;
  }
  t->fk = fk;
  return t;
}
struct tmap *tsetfv(struct tmap *t, destructor_fnt fv) {
  if (!t) {
    FLOG("Tham số t không hợp lệ.");
    return NULL;
  }
  t->fv = fv;
  return t;
}

/***** ./algo/perm.c *****/
struct vector *create_perm(long n) {
  if (n < 1) {
    FLOG("Tạo hoán vị với tham số không hợp lệ.");
    return NULL;
  }
  struct vector *v = vcreate(n);
  if (!v) {
    FLOG("Lỗi tạo vec-tơ");
    return NULL;
  }
  long i = 0;
  VTRAVERSE(cur, v) {
    cur->l = i++;
  }
  return v;
}
struct vector *next_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l < a[k].l) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return NULL;
  }
  long i = k - 1, l = vsize(v) - 1;
  while (a[l].l < a[i].l) {
    --l;
  }
  GSWAP(a[l], a[i]);
  l = vsize(v) - 1;
  while (k < l) {
    GSWAP(a[k], a[l]);
    ++k;
    --l;
  }
  return v;
}
struct vector *prev_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l > a[k].l) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return NULL;
  }
  long i = k - 1, l = vsize(v) - 1;
  while (a[l].l > a[i].l) {
    --l;
  }
  GSWAP(a[i], a[l]);
  l = vsize(v) - 1;
  while (k < l) {
    GSWAP(a[k], a[l]);
    ++k;
    --l;
  }
  return v;
}
int has_next_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l < a[k].l) {
      return 1;
    }
  }
  return 0;
}
int has_prev_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l > a[k].l) {
      return 1;
    }
  }
  return 0;
}
