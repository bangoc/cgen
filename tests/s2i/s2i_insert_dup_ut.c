#include "tests/base/utils.h"
#include "s2i.h"

#include <string.h>

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  bn_node_t x = s2i_insert(t, "Một", 1);
  CHECK_MSG(s2i_node_value(x) == 1, "Giá trị được trả về khi chèn 1");
  CHECK_MSG(strcmp(s2i_node_key(x), "Một") == 0, "Khóa được trả về khi chèn 1");
  s2i_insert(t, "Hai", 2);
  s2i_insert(t, "Ba", 3);
  bn_node_t y = s2i_insert(t, "Một", 10);
  CHECK_MSG(y == x, "Trùng lặp khóa 1");
  CHECK_MSG(s2i_value(t, "Một") == 1, "Giá trị khóa Một sau khi chèn trùng lặp");
  CHECK_MSG(s2i_delete(t, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_delete(t, "Một") == 0, "Xóa Một (không tồn tại)");

  s2i_insert(t, "Một", 1);
  CHECK_MSG(s2i_value(t, "Một") == 1, "Giá trị khóa Một sau khi chèn lại");
  s2i_insert(t, "Hai", 20);
  CHECK_MSG(s2i_value(t, "Hai") == 2, "Giá trị khóa Hai sau chèn trùng lặp");
  CHECK_MSG(s2i_delete(t, "Hai") == 1, "Xóa Hai (có tồn tại)");
  CHECK_MSG(s2i_value(t, "Hai") == k_s2i_invalid, "Giá trị khóa Hai sau khi xóa");
  CHECK_MSG(s2i_delete(t, "Hai") == 0, "Xóa Hai (không tồn tại)");
  s2i_free(t);
  return 0;
}