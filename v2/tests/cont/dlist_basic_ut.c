/* (C) Nguyễn Bá Ngọc 2023 */

#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct dlist *list = dcreate();
  dappend(list, 10);
  dappend(list, 30);
  dappend(list, 50);
  dprepend(list, 20);
  dprepend(list, 40);
  dprepend(list, 60);
  CHECK_MSG(dsize(list) == 6, "size == 6");
  CHECK_MSG(dfront(list)->l == 60, "front 60");
  CHECK_MSG(dfront(ddfront(list))->l == 40, "front 40");
  CHECK_MSG(dfront(ddfront(list))->l == 20, "front 20");
  CHECK_MSG(dback(list)->l == 50, "back 50");
  CHECK_MSG(dback(ddback(list))->l == 30, "back 30");
  CHECK_MSG(dback(ddback(list))->l == 10, "back 10");
  CHECK_MSG(dsize(list) == 2, "size 2");
  ddfront(list);
  ddback(list);
  CHECK_MSG(dempty(list), "empty list");
  dfree(list);
  TEST_OK();
}