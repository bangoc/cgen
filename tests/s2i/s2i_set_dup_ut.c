#include "tests/base/utils.h"
#include "s2i.h"

#include <string.h>

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  bn_node_t x = s2i_set(t, "Một", 1);
  CHECK_MSG(s2i_node_value(x) == 1, "Giá trị được trả về khi chèn 1");
  CHECK_MSG(strcmp(s2i_node_key(x), "Một") == 0, "Khóa được trả về khi chèn 1");
  s2i_set(t, "Hai", 2);
  s2i_set(t, "Ba", 3);
  bn_node_t y = s2i_set(t, "Một", 10);
  CHECK_MSG(y == x, "Trùng lặp khóa 1");
  CHECK_MSG(s2i_value(t, "Một") == 10, "Giá trị khóa Một sau khi lưu cùng khóa");
  CHECK_MSG(s2i_delete(t, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_delete(t, "Một") == 0, "Xóa Một (không tồn tại)");
  s2i_free(t);
  return 0;
}