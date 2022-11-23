#include "utils/str.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  GC_INIT();
  char *s = "Hello worlds!";
  char *hw = cstrdup(s);
  printf("hw = %s\n", hw);
  ext_free(hw);
  return 0;
}