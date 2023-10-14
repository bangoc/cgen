/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"

#include "tests/ut/utils.h"

int main() {
  struct slist *list = screate();
  senque(list, gtype_l(20));
  senque(list, gtype_l(30));
  senque(list, gtype_l(50));
  senque(list, gtype_l(60));
  senque(list, gtype_l(90));
  CHECK_MSG(slen(list) == 5, "length == 5");
  gtype val;
  speek(list, &val);
  CHECK_MSG(val.l == 20, "first == 20");
  speek(sdeque(list), &val);
  CHECK_MSG(val.l == 30, "first == 30");
  speek(sdeque(list), &val);
  CHECK_MSG(val.l == 50, "first == 50");
  speek(sdeque(list), &val);
  CHECK_MSG(val.l == 60, "first == 60");
  speek(sdeque(list), &val);
  CHECK_MSG(val.l == 90, "first == 90");
  CHECK_MSG(slen(list) == 1, "length == 1");
  sdeque(list);
  CHECK_MSG(sempty(list), "Empty queue");
  sfree(list);
  TEST_OK();
}