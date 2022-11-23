#include "tests/base/utils.h"
#include "tree/spec/s2i.h"

#include <string.h>

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  struct rbmtree *si = s2i_create();
  s2i_put(si, "Một", 1);
  s2i_put(si, "Hai", 2);
  s2i_put(si, "Ba", 3);
  long *v = s2i_put(si, "Một", 1);
  *v = 10;
  CHECK_MSG(*s2i_value(si, "Một") == 10, "Giá trị khóa Một sau khi lưu cùng khóa");
  CHECK_MSG(s2i_remove(si, "Một") == 1, "Xóa Một (có tồn tại)");
  CHECK_MSG(s2i_remove(si, "Một") == 0, "Xóa Một (không tồn tại)");
  s2i_free(si);
  TEST_OK();
  return 0;
}