#include "tests/base/utils.h"
#include "s2i.h"

#include <string.h>

int main() {
  s2i_t si = s2i_create();
  s2i_node_t x = s2i_insert(si, "Một", 1);
  CHECK_MSG(s2i_node_value(x) == 1, "Giá trị được trả về khi chèn 1");
  CHECK_MSG(strcmp(s2i_node_key(x), "Một") == 0, "Khóa được trả về khi chèn 1");
  s2i_insert(si, "Hai", 2);
  s2i_insert(si, "Ba", 3);
  s2i_node_t y = s2i_insert(si, "Một", 10);
  CHECK_MSG(y == x, "Trùng lặp khóa 1");
  CHECK_MSG(s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn trùng lặp");
  CHECK_MSG(s2i_delete(si, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_delete(si, "Một") == 0, "Xóa Một (không tồn tại)");

  s2i_insert(si, "Một", 1);
  CHECK_MSG(s2i_value(si, "Một") == 1, "Giá trị khóa Một sau khi chèn lại");
  s2i_insert(si, "Hai", 20);
  CHECK_MSG(s2i_value(si, "Hai") == 2, "Giá trị khóa Hai sau chèn trùng lặp");
  CHECK_MSG(s2i_delete(si, "Hai") == 1, "Xóa Hai (có tồn tại)");
  CHECK_MSG(s2i_vref(si, "Hai") == NULL_PTR, "Giá trị khóa Hai sau khi xóa");
  CHECK_MSG(s2i_delete(si, "Hai") == 0, "Xóa Hai (không tồn tại)");
  s2i_free(si);
  return 0;
}
