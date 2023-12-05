/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"

#include "tests/ut/utils.h"

int main() {
  struct slist *list = screate();
  spush(list, 1);
  spush(list, 3);
  spush(list, 5);
  spush(list, 7);
  spush(list, 9);
  CHECK_MSG(ssize(list) == 5, "length == 5");
  CHECK_MSG(stop(list)->l == 9, "top == 9");
  CHECK_MSG(stop(spop(list))->l == 7, "top == 7");
  CHECK_MSG(stop(spop(list))->l == 5, "top == 5");
  CHECK_MSG(stop(spop(list))->l == 3, "top == 3");
  CHECK_MSG(stop(spop(list))->l == 1, "top == 1");
  CHECK_MSG(ssize(list) == 1, "len == 1");
  sfree(list);
  TEST_OK();
}