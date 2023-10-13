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
gtype_free_t vfreeval(const struct vector *v) {
  return v->fv;
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
struct vector *vcreate1(long sz) {
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
struct vector *vcreate2(long sz, gtype_free_t fv) {
  struct vector *base = vcreate1(sz);
  if (base) {
    base->fv = fv;
  }
  return base;
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
    flog("Xóa ngăn xếp không hợp lệ.");
    return NULL;
  }
  vresize(v, v->sz - 1);
  return v;
}
struct vector *vtop(struct vector *v, gtype *out) {
  if (!v || v->sz == 0) {
    flog("Đọc đỉnh của ngăn xếp không hợp lệ.");
    return NULL;
  }
  *out = v->elems[v->sz - 1];
  return v;
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
struct queue *qcreate1(long cap) {
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
  q->fi = qnext(q, q->fi);
  --q->sz;
  return q;
}
struct queue *qpeek(struct queue *q, gtype *out) {
  if (!q || q->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Hàng đợi không hợp lệ");
#endif
    return NULL;
  }
  *out = q->elems[q->fi];
  return q;
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
void qfree(struct queue *q) {
  free(q->elems);
  free(q);
}
