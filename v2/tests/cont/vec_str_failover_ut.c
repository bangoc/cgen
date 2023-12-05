/* (C) Nguyễn Bá Ngọc */
/* Thử tạo vec-tơ của các chuỗi ký tự với 
   bộ nhớ được cấp phát động. */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdlib.h>
#include <string.h>

int main() {
  struct vector *v = vcreate(0);
  vsetfv(v, free);
  vappend(v, strdup("aaaaaaaa"));
  vappend(v, strdup("bbbbb"));
  vappend(v, strdup("ccccccccccc"));
  vappend(v, strdup("ddddddd"));
  vappend(v, strdup("eeeeeeeeeeeeeeee"));
  VTRAVERSE(cur, v) {
    printf("%s\n", cur->s);
  }
  vfree(v);
  return 0;
}