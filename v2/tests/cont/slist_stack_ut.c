/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"

#include "tests/ut/utils.h"

int main() {
  struct slist *list = screate();
  spush(list, gtype_l(1));
  spush(list, gtype_l(3));
  spush(list, gtype_l(5));
  spush(list, gtype_l(7));
  spush(list, gtype_l(9));
  CHECK_MSG(slen(list) == 5, "length == 5");
  gtype val;
  stop(list, &val);
  CHECK_MSG(val.l == 9, "top == 9");
  stop(spop(list), &val);
  CHECK_MSG(val.l == 7, "top == 7");
  stop(spop(list), &val);
  CHECK_MSG(val.l == 5, "top == 5");
  stop(spop(list), &val);
  CHECK_MSG(val.l == 3, "top == 3");
  stop(spop(list), &val);
  CHECK_MSG(val.l == 1, "top == 1");
  sfree(list);
  TEST_OK();
}