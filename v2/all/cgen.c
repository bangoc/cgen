/** (C) Nguyễn Bá Ngọc 2023
 *  cgen version:2.0.0
 */
#include "cgen.h"

/***** ./cont/vector.c *****/
#ifdef CGEN_DEBUG
#endif
struct vector {
  gtype *elems;
  long sz;
  long cap;
  double k;
  gtype_free_t fv;
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
gtype_free_t vfv(const struct vector *v) {
  return v->fv;
}
struct vector *vsetfv(struct vector *v, gtype_free_t fv) {
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
void vreserve(struct vector *v, long newcap) {
  if (newcap < v->sz) {
#ifdef CGEN_DEBUG
    flog("Dự trữ với dung lượng (%ld) < kích thước (%ld)", newcap, v->sz);
#endif
    return;
  }
  v->elems = realloc(v->elems, newcap * sizeof(gtype));
  v->cap = newcap;
}
void vresize(struct vector *v, long newsz) {
  if (newsz > v->cap) {
    vreserve(v, newsz);
  } else if (newsz < v->sz && v->fv) {
    for (long j = newsz; j < vsize(v); ++j) {
      v->fv(v->elems + j);
    }
  }
  v->sz = newsz;
}
void vappend(struct vector *v, gtype val) {
  if (v->sz == 0) {
    vreserve(v, 10);
  } else if (v->sz == v->cap) {
    vreserve(v, v->k * v->sz);
  }
  v->elems[v->sz] = val;
  ++v->sz;
}
void vremove(struct vector *v, long idx) {
  gtype *_arr = varr(v);
  long _sz = vsize(v);
  if ((idx) >= _sz || (idx) < 0) {
#if defined CGEN_DEBUG
  flog("Xóa phần tử với chỉ số không hợp lệ sz = %ld, idx = %ld",
      _sz, (long)idx);
#endif
    return;
  }
  gtype _tmp = _arr[(idx)];
  for (long _i = (idx); _i < _sz - 1; ++_i) {
    _arr[_i] = _arr[_i + 1];
  }
  _arr[_sz - 1] = _tmp;
  vresize(v, _sz - 1);
}
void vclear(struct vector *v) {
  vresize(v, 0);
}
void vfree(struct vector *v) {
  vclear(v);
  free((v)->elems);
  free(v);
}
void vfill(struct vector *v, gtype value) {
  vtraverse(_cur, v) {
    *_cur = (value);
  }
}
void gfree_vec(gtype *value) {
  vfree(value->vec);
}
struct vector *vcreate(long sz) {
  if (sz < 0) {
#ifdef CGEN_DEBUG
    flog("Tạo vec-tơ với kích thước không hợp lệ, sz = %ld", sz);
#endif
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
  if (v1->sz != v2->sz || v1->cap != v2->cap) {
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
struct vector *vpush(struct vector *v, gtype val) {
  vappend(v, val);
  return v;
}
struct vector *vpop(struct vector *v) {
  if (!v || v->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Xóa ngăn xếp không hợp lệ.");
#endif
    return NULL;
  }
  vresize(v, v->sz - 1);
  return v;
}
gtype *vtop(struct vector *v) {
  if (!v || v->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Đọc đỉnh của ngăn xếp không hợp lệ.");
#endif
    return NULL;
  }
  return v->elems + (v->sz - 1);
}

/***** ./cont/queue.c *****/
#include <stdlib.h>
struct queue {
  long sz;
  long cap;
  long fi;
  long la;
  gtype_free_t fv;
  gtype *elems;
};
struct queue *qcreate(long cap) {
  if (cap < 0) {
#ifdef CGEN_DEBUG
    flog("Tạo hàng đợi với tham số không hợp lệ.");
#endif
    return NULL;
  }
  struct queue *q = malloc(sizeof(struct queue));
  if (!q) {
#ifdef CGEN_DEBUG
    flog("Lỗi cấp phát bộ nhớ cho hàng đợi.");
#endif
    return NULL;
  }
  q->sz = 0;
  q->cap = cap > 0? cap: 8;
  q->fi = -1;
  q->la = -1;
  q->fv = NULL;
  q->elems = calloc(cap, sizeof(gtype));
  if (!q->elems) {
#ifdef CGEN_DEBUG
    flog("Lỗi cấp phát bộ nhớ cho các phần tử");
#endif
    free(q);
    return NULL;
  }
  return q;
}
struct queue *qenque(struct queue* q, gtype val) {
  if (!q) {
#ifdef CGEN_DEBUG
    flog("Lỗi tham số NULL");
#endif
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
#ifdef CGEN_DEBUG
    flog("Lỗi mở rộng bộ nhớ.");
#endif
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
#ifdef CGEN_DEBUG
    flog("Hàng đợi không hợp lệ");
#endif
    return NULL;
  }
  if (q->fv) {
    q->fv(q->elems + q->fi);
  }
  q->fi = qnext(q, q->fi);
  --q->sz;
  return q;
}
gtype *qpeek(struct queue *q) {
  if (!q || q->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Hàng đợi không hợp lệ");
#endif
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
gtype_free_t qfv(struct queue *q) {
  return q->fv;
}
struct queue *qsetfv(struct queue *q, gtype_free_t fv) {
  q->fv = fv;
  return q;
}
void qfree(struct queue *q) {
  while (!qempty(q)) {
    qdeque(q);
  }
  free(q->elems);
  free(q);
}

/***** ./cont/slist.c *****/
#ifdef CGEN_DEBUG
#endif
struct snode {
  gtype data;
  struct snode *next;
};
struct slist {
  struct snode *front;
  struct snode *back;
  gtype_free_t fv;
  long length;
};
struct snode *snode(gtype data) {
  struct snode *tmp = malloc(sizeof(struct snode));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Lỗi cấp phát bộ nhớ tạo nút.");
#endif
    return NULL;
  }
  tmp->data = data;
  tmp->next = NULL;
  return tmp;
}
struct slist *screate() {
  struct slist *tmp = malloc(sizeof(struct slist));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Lỗi cấp phát bộ nhớ tạo danh sách.");
#endif
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
struct slist *sappend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
#ifdef CGEN_DEBUG
    flog("Lỗi tạo nút");
#endif
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
struct slist *sprepend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
#ifdef CGEN_DEBUG
    flog("Lỗi tạo nút");
#endif
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
#ifdef CGEN_DEBUG
    flog("Xóa đầu danh sách không hợp lệ.");
#endif
    return NULL;
  }
  if (list->front == list->back) {
    list->back = NULL;
  }
  struct snode *tmp = list->front;
  list->front = tmp->next;
  if (list->fv) {
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}
gtype_free_t sfv(struct slist *list) {
  return list->fv;
}
struct slist *ssetfv(struct slist *list, gtype_free_t fv) {
  list->fv = fv;
  return list;
}
void sfree(struct slist *list) {
  while (!sempty(list)) {
    sdfront(list);
  }
  free(list);
}
struct slist *spush(struct slist *list, gtype elem) {
  return sprepend(list, elem);
}
struct slist *spop(struct slist *list) {
  return sdfront(list);
}
gtype *stop(struct slist *list) {
  if (list == NULL || sempty(list)) {
#ifdef CGEN_DEBUG
    flog("Ngăn xếp ở trạng thái không hợp lệ.");
#endif
    return NULL;
  }
  return sfront(list);
}
struct slist *senque(struct slist *list, gtype elem) {
  return sappend(list, elem);
}
struct slist *sdeque(struct slist *list) {
  return sdfront(list);
}
gtype *speek(struct slist *list) {
  if (list == NULL || sempty(list)) {
#ifdef CGEN_DEBUG
    flog("hàng đợi ở trạng thái không hợp lệ.");
#endif
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
  gtype_free_t fv;
};
struct dnode *dnode(gtype data) {
  struct dnode *tmp = malloc(sizeof(struct dnode));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Không thể cấp phát bộ nhớ cho nút.");
#endif
    return NULL;
  }
  tmp->data = data;
  tmp->next = tmp->prev = NULL;
  return tmp;
}
struct dlist *dcreate() {
  struct dlist *tmp = malloc(sizeof(struct dlist));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Không thể cấp phát bộ nhớ cho danh sách.");
#endif
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
void dfree(struct dlist *list) {
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
struct dlist *dappend(struct dlist *list, gtype elem) {
  struct dnode *nn = dnode(elem);
  if (!nn) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif
    return NULL;
  }
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif
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
struct dlist *dprepend(struct dlist *list, gtype elem) {
  struct dnode *nn = dnode(elem);
  if (!nn) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif
    return NULL;
  }
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif
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
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif
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
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}
struct dlist *ddback(struct dlist *list) {
  if (!list || dempty(list)) {
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif
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
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}
gtype_free_t dfv(struct dlist *list) {
  return list->fv;
}
struct dlist *dsetfv(struct dlist *list, gtype_free_t fv) {
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif
    return NULL;
  }
  list->fv = fv;
  return list;
}
