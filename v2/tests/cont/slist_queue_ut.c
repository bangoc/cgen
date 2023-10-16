/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"

#include "tests/ut/utils.h"

int main() {
  struct slist *list = screate();
  senque(list, GLONG(20));
  senque(list, GLONG(30));
  senque(list, GLONG(50));
  senque(list, GLONG(60));
  senque(list, GLONG(90));
  CHECK_MSG(ssize(list) == 5, "length == 5");
  CHECK_MSG(speek(list)->l == 20, "first == 20");
  CHECK_MSG(speek(sdeque(list))->l == 30, "first == 30");
  CHECK_MSG(speek(sdeque(list))->l == 50, "first == 50");
  CHECK_MSG(speek(sdeque(list))->l == 60, "first == 60");
  CHECK_MSG(speek(sdeque(list))->l == 90, "first == 90");
  CHECK_MSG(ssize(list) == 1, "length == 1");
  sdeque(list);
  CHECK_MSG(sempty(list), "Empty queue");
  sfree(list);
  TEST_OK();
}