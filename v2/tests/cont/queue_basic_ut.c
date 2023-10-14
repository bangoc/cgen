/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct queue *q = qcreate(3);
  CHECK_MSG(qenque(q, gtype_l(1)) == q, "enque 1");
  CHECK_MSG(qenque(qenque(q, gtype_l(3)), gtype_l(5)) == q, "enque 3, 5");
  CHECK_MSG(qpeek(q)->l == 1, "peek 1");
  CHECK_MSG(qpeek(qdeque(q))->l == 3, "peek 3");
  qenque(qenque(qenque(q, gtype_l(7)), gtype_l(9)), gtype_l(11));
  CHECK_MSG(qpeek(q)->l == 3, "peek 3");
  CHECK_MSG(qpeek(qdeque(q))->l == 5, "peek 5");
  CHECK_MSG(qpeek(qdeque(q))->l == 7, "peek 7");
  CHECK_MSG(qpeek(qdeque(q))->l == 9, "peek 9");
  CHECK_MSG(qpeek(qdeque(q))->l == 11, "peek 11");
  CHECK_MSG(qsize(q) == 1, "size == 1");
  qdeque(q);
  CHECK_MSG(qempty(q), "empty queue");
  qfree(q);
  TEST_OK();
}