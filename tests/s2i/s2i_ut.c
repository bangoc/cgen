#include "tree/spec/s2i.h"
#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  struct rbmtree *si = s2i_create();
  CHECK_MSG(s2i_value(si, "Mot") == NULL, "Failed search empty");
  s2i_put(si, "Mot", 1);
  s2i_put(si, "Hai", 2);
  s2i_put(si, "Ba", 3);
  s2i_put(si, "Bon", 4);
  s2i_put(si, "Nam", 5);
  s2i_put(si, "Sau", 6);
  s2i_put(si, "Bay", 7);
  s2i_put(si, "Tam", 8);
  s2i_put(si, "Chin", 9);
  CHECK_MSG(*s2i_value(si, "Mot") == 1, "Failed 1");
  CHECK_MSG(*s2i_value(si, "Hai") == 2, "Failed 2");
  CHECK_MSG(*s2i_value(si, "Ba") == 3, "Failed 3");
  CHECK_MSG(*s2i_value(si, "Bon") == 4, "Failed 4");
  CHECK_MSG(*s2i_value(si, "Nam") == 5, "Failed 5");
  CHECK_MSG(*s2i_value(si, "Sau") == 6, "Failed 6");
  CHECK_MSG(*s2i_value(si, "Bay") == 7, "Failed 7");
  CHECK_MSG(*s2i_value(si, "Tam") == 8, "Failed 8");
  CHECK_MSG(*s2i_value(si, "Chin") == 9, "Failed 9");
  CHECK_MSG(s2i_value(si, "Muoi") == NULL, "Failed 10");
  CHECK_MSG(s2i_value(si, "Khong") == NULL, "Failed 0");

  CHECK_MSG(s2i_remove(si, "Bon") == 1, "Xoa Bon");
  CHECK_MSG(s2i_remove(si, "Muoi") == 0, "Xoa Muoi");
  CHECK_MSG(s2i_value(si, "Bon") == NULL, "Tim Bon");
  CHECK_MSG(s2i_remove(si, "Tam") == 1, "Xoa Tam");
  CHECK_MSG(s2i_value(si, "Tam") == NULL, "Tim Tam");
  s2i_free(si);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}