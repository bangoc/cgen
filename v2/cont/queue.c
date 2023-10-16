/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/flog.h"
#include "cont/queue.h"

#include <stdlib.h>

/** 
 * Hàng đợi FIFO dựa trên mảng động 
 */
struct queue {
  /** Kích thước (số lượng phần tử) của hàng đợi */
  long sz;

  /** Dung lượng (số chỗ) được cấp phát cho hàng đợi */
  long cap;

  /** Chỉ số phần tử đầu tiên */
  long fi;

  /** Chỉ số phần tử cuối cùng */
  long la;

  /** Con trỏ hàm giải phóng bộ nhớ phần tử */
  gtype_free_t fv;

  /** Con trỏ tới mảng phần tử */
  gtype *elems;
};

struct queue *qcreate(long cap) {
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

gtype *qpeek(struct queue *q) {
  if (!q || q->sz == 0) {
#ifdef CGEN_DEBUG
    flog("Hàng đợi không hợp lệ");
#endif  // CGEN_DEBUG
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