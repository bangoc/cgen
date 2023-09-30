/* (C) Nguyen Ba Ngoc 2022 */

#include "mix/s2w.h"
#include "tests/base/utils.h"

int main() {
  struct si2ways *col = s2w_create();
  CHECK_MSG(s2w_put(col, "aaaa") == NULL, "put new aaaa");
  CHECK_MSG(s2w_put(col, "bbbb") == NULL, "put new bbbb");
  CHECK_MSG(s2w_put(col, "cccc") == NULL, "put new cccc");
  CHECK_MSG(*s2w_put(col, "bbbb") == 1, "repeat put aaaa");
  CHECK_MSG(s2w_id(col, "aaaa") == 0, "id 0");
  CHECK_MSG(s2w_id(col, "bbbb") == 1, "id 1");
  CHECK_MSG(s2w_id(col, "cccc") == 2, "id 2");
  CHECK_MSG(s2w_id(col, "aaaa") == 0, "id 0");
  CHECK_MSG(s2w_insert(col, "dddd").inserted, "insert dddd");
  CHECK_MSG(s2w_id(col, "dddd") == 3, "id 3");
  s2w_free(col);
  TEST_OK();
  return 0;
}