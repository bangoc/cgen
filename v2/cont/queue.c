/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/flog.h"
#include "cont/queue.h"

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
#endif  // CGEN_DEBUG
    return NULL;
  }
  struct queue *q = malloc(sizeof(struct queue));
  if (!q) {
#ifdef CGEN_DEBUG
    flog("Lỗi cấp phát bộ nhớ cho hàng đợi.");
#endif  // CGEN_DEBUG
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
#endif  // CGEN_DEBUG
    free(q);
    return NULL;
  }
  return q;
}

struct queue *qcreate2(long cap, gtype_free_t fv) {
  struct queue *q = qcreate1(cap);
  if (!q) {
#ifdef CGEN_DEBUG
    flog("Lỗi tạo hàng đợi");
#endif  // CGEN_DEBUG    
    return NULL;
  }
  q->fv = fv;
  return q;
}

struct queue *qenque(struct queue* q, gtype val) {
  if (!q) {
#ifdef CGEN_DEBUG
    flog("Lỗi tham số NULL");
#endif  // CGEN_DEBUG
  }

  // Phần tử đầu tiên
  if (q->sz == 0) {
    q->fi = q->la = 0;
    q->elems[0] = val;
    ++q->sz;
    return q;
  }

  // Còn dung lượng trống
  if (q->sz < q->cap) {
    q->la = qnext(q, q->la);
    q->elems[q->la] = val;
    ++q->sz;
    return q;
  }

  // q->sz == q->cap, hàng đợi đã đầy
  q->cap *= 2;
  void *tmp = realloc(q->elems, q->cap * sizeof(gtype));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Lỗi mở rộng bộ nhớ.");
#endif  // CGEN_DEBUG
    return NULL;
  }
  q->elems = tmp;
  if (q->fi > q->la) {
    // Xoay vòng
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
#endif  // CGEN_DEBUG
    return NULL;
  }
  if (q->fv) {
    q->fv(q->elems + q->fi);
  }
  q->fi = qnext(q, q->fi);
  --q->sz;
  return q;
}

struct queue *qpeek(struct queue *q, gtype *out) {
  if (!q || q->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Hàng đợi không hợp lệ");
#endif  // CGEN_DEBUG
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
  while (!qempty(q)) {
    qdeque(q);
  }
  free(q->elems);
  free(q);
}