#include "tests/mylib/lib.h"
#include "tests/utils.h"

#include <string.h>

int main() {
  VCONSTRUCT(vectstr, v, 0);
  VFV(v) = frees;
  VAPPEND(v, strdup("aaaaaaaaaaaa"));
  VAPPEND(v, strdup("ddddd"));
  VAPPEND(v, strdup("bbbbbbb"));
  VAPPEND(v, strdup("cccccccccccccccc"));
  VAPPEND(v, strdup("aaaaeeeeeecc"));
  VSORT(v, cmps);
  VFOR(i, v) {
    printf("%s\n", VELEM(v, i));
  }
  VFREE(v);
  TEST_OK();
}