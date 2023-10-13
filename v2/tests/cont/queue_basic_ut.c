/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

int main() {
  struct queue *q = qcreate(3);
  CHECK_MSG(qenque(q, gtype_l(1)) == q, "enque 1");
  CHECK_MSG(qenque(qenque(q, gtype_l(3)), gtype_l(5)) == q, "enque 3, 5");
  gtype val;
  qpeek(q, &val);
  CHECK_MSG(val.l == 1, "peek 1");
  qpeek(qdeque(q), &val);
  CHECK_MSG(val.l == 3, "peek 3");
  qenque(qenque(qenque(q, gtype_l(7)), gtype_l(9)), gtype_l(11)); 
  qdeque(qpeek(q, &val));
  CHECK_MSG(val.l == 3, "peek 3");
  qdeque(qpeek(q, &val));
  CHECK_MSG(val.l == 5, "peek 5");
  qdeque(qpeek(q, &val));
  CHECK_MSG(val.l == 7, "peek 7");
  qdeque(qpeek(q, &val));
  CHECK_MSG(val.l == 9, "peek 9");
  qdeque(qpeek(q, &val));
  CHECK_MSG(val.l == 11, "peek 11");
  qfree(q);
  TEST_OK();
}