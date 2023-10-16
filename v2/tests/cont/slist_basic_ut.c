/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

int main() {
  struct slist *list = screate();
  sappend(list, GLONG(100));
  sappend(list, GLONG(200));
  sappend(list, GLONG(300));
  sprepend(list, GLONG(2));
  sprepend(list, GLONG(4));
  sprepend(list, GLONG(6));
  CHECK_MSG(sfront(list)->l == 6, "front 6");
  CHECK_MSG(sback(list)->l == 300, "back 300");
  CHECK_MSG(sfront(sdfront(list))->l == 4, "front 6");
  CHECK_MSG(sfront(sdfront(list))->l == 2, "front 2");
  CHECK_MSG(sfront(sdfront(list))->l == 100, "front 100");
  CHECK_MSG(sfront(sdfront(list))->l == 200, "front 200");
  CHECK_MSG(sfront(sdfront(list))->l == 300, "front 300");
  CHECK_MSG(ssize(list) == 1, "length == 1");

  sdfront(list);
  CHECK_MSG(sempty(list), "Empty list");
  sfree(list);
  TEST_OK();
}