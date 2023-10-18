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
  vappend(v, GSTR(strdup("aaaaaaaa")));
  vappend(v, GSTR(strdup("bbbbb")));
  vappend(v, GSTR(strdup("ccccccccccc")));
  vappend(v, GSTR(strdup("ddddddd")));
  vappend(v, GSTR(strdup("eeeeeeeeeeeeeeee")));
  VTRAVERSE(cur, v) {
    printf("%s\n", cur->s);
  }
  vfree(v);
  return 0;
}