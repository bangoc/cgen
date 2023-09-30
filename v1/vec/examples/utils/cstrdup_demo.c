#include "utils/str.h"

#include <stdio.h>

int main() {
  char *s = "Hello worlds!";
  char *hw = cstrdup(s);
  printf("hw = %s\n", hw);
  free(hw);
  return 0;
}