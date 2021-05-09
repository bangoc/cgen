#include "s2i.h"
#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  bn_tree_t t = s2i_create();
  s2i_insert(t, "Mot", 1);
  s2i_insert(t, "Hai", 2);
  s2i_insert(t, "Ba", 3);
  s2i_insert(t, "Bon", 4);
  s2i_insert(t, "Nam", 5);
  s2i_insert(t, "Sau", 6);
  s2i_insert(t, "Bay", 7);
  s2i_insert(t, "Tam", 8);
  s2i_insert(t, "Chin", 9);
  CHECK_MSG(s2i_value(t, "Mot") == 1, "Failed 1");
  CHECK_MSG(s2i_value(t, "Hai") == 2, "Failed 2");
  CHECK_MSG(s2i_value(t, "Ba") == 3, "Failed 3");
  CHECK_MSG(s2i_value(t, "Bon") == 4, "Failed 4");
  CHECK_MSG(s2i_value(t, "Nam") == 5, "Failed 5");
  CHECK_MSG(s2i_value(t, "Sau") == 6, "Failed 6");
  CHECK_MSG(s2i_value(t, "Bay") == 7, "Failed 7");
  CHECK_MSG(s2i_value(t, "Tam") == 8, "Failed 8");
  CHECK_MSG(s2i_value(t, "Chin") == 9, "Failed 9");
  CHECK_MSG(s2i_value(t, "Muoi") == k_s2i_invalid, "Failed 10");
  CHECK_MSG(s2i_value(t, "Khong") == k_s2i_invalid, "Failed 0");

  CHECK(s2i_delete(t, "Bon") == 1);
  CHECK(s2i_delete(t, "Muoi") == 0);
  CHECK(s2i_value(t, "Bon") == k_s2i_invalid);
  CHECK(s2i_delete(t, "Tam") == 1);
  CHECK(s2i_value(t, "Tam") == k_s2i_invalid);
  s2i_free(&t);
  return 0;
}

int main() {
  return t1();
}