#include "tests/base/utils.h"
#include "spec/s2i.h"

#include <string.h>

int main() {
  s2i_t si = s2i_create(NULL);
  s2i_node_t x = s2i_set(si, "Một", 1);
  CHECK_MSG(x->value == 1, "Giá trị được trả về khi chèn 1");
  CHECK_MSG(strcmp(x->key, "Một") == 0, "Khóa được trả về khi chèn 1");
  s2i_set(si, "Hai", 2);
  s2i_set(si, "Ba", 3);
  s2i_node_t y = s2i_set(si, "Một", 10);
  CHECK_MSG(y == x, "Trùng lặp khóa 1");
  CHECK_MSG(s2i_value(si, "Một") == 10, "Giá trị khóa Một sau khi lưu cùng khóa");
  CHECK_MSG(s2i_delete(si, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_delete(si, "Một") == 0, "Xóa Một (không tồn tại)");
  s2i_free(si);
  return 0;
}