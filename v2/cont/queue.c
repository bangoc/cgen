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
    // Tham số cap không hợp lệ
    return NULL;
  }
  struct queue *q = malloc(sizeof(struct queue));
  if (!q) {
    // Lỗi cấp phát
    return NULL;
  }
  q->sz = 0;
  q->cap = cap;
  q->fi = 0;
  q->la = 0;
  if (cap > 0) {
    q->elems = calloc(cap, sizeof(gtype));
    if (!q->elems) {
      // Lỗi cấp phát bộ nhớ;
      free(q);
      return NULL;
    }
  }
  return q;
}