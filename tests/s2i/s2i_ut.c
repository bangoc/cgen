#include "s2i.h"
#include "tests/base/utils.h"

#include <stdio.h>

int t1() {
  s2i_t si = s2i_create();
  CHECK_MSG(s2i_vref(si, "Mot") == NULL, "Failed search empty");
  s2i_insert(si, "Mot", 1);
  s2i_insert(si, "Hai", 2);
  s2i_insert(si, "Ba", 3);
  s2i_insert(si, "Bon", 4);
  s2i_insert(si, "Nam", 5);
  s2i_insert(si, "Sau", 6);
  s2i_insert(si, "Bay", 7);
  s2i_insert(si, "Tam", 8);
  s2i_insert(si, "Chin", 9);
  CHECK_MSG(s2i_value(si, "Mot") == 1, "Failed 1");
  CHECK_MSG(s2i_value(si, "Hai") == 2, "Failed 2");
  CHECK_MSG(s2i_value(si, "Ba") == 3, "Failed 3");
  CHECK_MSG(s2i_value(si, "Bon") == 4, "Failed 4");
  CHECK_MSG(s2i_value(si, "Nam") == 5, "Failed 5");
  CHECK_MSG(s2i_value(si, "Sau") == 6, "Failed 6");
  CHECK_MSG(s2i_value(si, "Bay") == 7, "Failed 7");
  CHECK_MSG(s2i_value(si, "Tam") == 8, "Failed 8");
  CHECK_MSG(s2i_value(si, "Chin") == 9, "Failed 9");
  CHECK_MSG(s2i_vref(si, "Muoi") == NULL, "Failed 10");
  CHECK_MSG(s2i_vref(si, "Khong") == NULL, "Failed 0");

  CHECK(s2i_delete(si, "Bon") == 1);
  CHECK(s2i_delete(si, "Muoi") == 0);
  CHECK(s2i_vref(si, "Bon") == NULL);
  CHECK(s2i_delete(si, "Tam") == 1);
  CHECK(s2i_vref(si, "Tam") == NULL);
  s2i_free(si);
  return 0;
}

int main() {
  return t1();
}