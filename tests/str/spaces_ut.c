#include "tests/base/utils.h"
#include "utils/str.h"

#include <ctype.h>

int t1() {
  for (int i = 0; i < strlen(ascii_spaces); ++i) {
    CHECK_MSG(isspace(ascii_spaces[i]), "Space characters");
  }
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}