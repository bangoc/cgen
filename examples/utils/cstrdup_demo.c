#include "utils/str.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  char *s = "Hello worlds!";
  char *hw = cstrdup(s);
  printf("hw = %s\n", hw);
  ext_free(hw);
  return 0;
}