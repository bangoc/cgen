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
  free_fn_t fv;

  /** Con trỏ tới mảng phần tử */
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

struct queue *qenque(struct queue* q, gtype val) {
  if (!q) {
    FLOG("Lỗi hàng đợi chưa khởi tạo.");
    return NULL;
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
    FLOG("Lỗi mở rộng bộ nhớ.");
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

free_fn_t qfv(struct queue *q) {
  return q->fv;
}

struct queue *qsetfv(struct queue *q, free_fn_t fv) {
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