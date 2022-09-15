#include "tests/base/utils.h"
#include "tree/spec/s2i.h"

#include <string.h>

int t1() {
  struct rbmtree *si = s2i_create();
  CHECK_MSG(s2i_put(si, "Một", 1) == NULL, "Khóa mới");
  s2i_put(si, "Hai", 2);
  s2i_put(si, "Ba", 3);
  long *v = s2i_put(si, "Một", 10);
  CHECK_MSG(*v == 1, "Khóa đã tồn tại");
  CHECK_MSG(*s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn trùng lặp");
  CHECK_MSG(s2i_remove(si, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_remove(si, "Một") == 0, "Xóa Một (không tồn tại)");

  s2i_put(si, "Một", 1);
  CHECK_MSG(*s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn lại");
  CHECK_MSG(s2i_put(si, "Hai", 20), "Khóa Hai đã tồn tại");
  CHECK_MSG(*s2i_value(si, "Hai") == 2, "Giá trị khóa Hai sau chèn trùng lặp");
  CHECK_MSG(s2i_remove(si, "Hai") == 1, "Xóa Hai (có tồn tại)");
  CHECK_MSG(s2i_value(si, "Hai") == NULL, "Giá trị khóa Hai sau khi xóa");
  CHECK_MSG(s2i_remove(si, "Hai") == 0, "Xóa Hai (không tồn tại)");
  s2i_free(si);
  return 0;
}

int t2() {
  struct rbmtree *si = s2i_create();
  CHECK_MSG(s2i_put(si, "Một", 1) == NULL, "Khóa mới");
  s2i_put(si, "Hai", 2);
  s2i_put(si, "Ba", 3);
  long *v = s2i_put(si, "Một", 10);
  CHECK_MSG(*v == 1, "Khóa đã tồn tại");
  CHECK_MSG(*s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn trùng lặp");
  CHECK_MSG(s2i_remove(si, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_remove(si, "Một") == 0, "Xóa Một (không tồn tại)");

  s2i_put(si, "Một", 1);
  CHECK_MSG(*s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn lại");
  CHECK_MSG(s2i_put(si, "Hai", 20), "Khóa Hai đã tồn tại");
  CHECK_MSG(*s2i_value(si, "Hai") == 2, "Giá trị khóa Hai sau chèn trùng lặp");
  CHECK_MSG(s2i_remove(si, "Hai") == 1, "Xóa Hai (có tồn tại)");
  CHECK_MSG(s2i_value(si, "Hai") == NULL, "Giá trị khóa Hai sau khi xóa");
  CHECK_MSG(s2i_remove(si, "Hai") == 0, "Xóa Hai (không tồn tại)");
  s2i_free(si);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1 dup key");
  CHECK_MSG(t2() == 0, "t2 no dup key");
  TEST_OK();
  return 0;
}
