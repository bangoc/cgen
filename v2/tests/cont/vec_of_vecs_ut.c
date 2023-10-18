/* (C) Nguyễn Bá Ngọc */
/* Thử tạo vec-tơ của các vec-tơ của các chuỗi ký tự */

#include "all.h"
#include "tests/ut/utils.h"

#include <stdlib.h>

int main() {
  struct vector *v = vcreate(0);
  struct vector *v1 = vcreate(0);
  struct vector *v2 = vcreate(0);
  struct vector *v3 = vcreate(0);
  vsetfv(v, vfree);
  vsetfv(v1, free);
  vsetfv(v3, free);
  vappend(v, GVOID(v1));
  vappend(v, GVOID(v2));
  vappend(v, GVOID(v3));
  vappend(v1, GSTR(strdup("aaa")));
  vappend(v1, GSTR(strdup("aaaaaa")));
  vappend(v1, GSTR(strdup("aaaaaaaaa")));
  vappend(v2, GSTR("bbb"));
  vappend(v2, GSTR("bbbbbb"));
  vappend(v2, GSTR("bbbbbbbb"));
  vappend(v3, GSTR(strdup("cc")));
  vappend(v3, GSTR(strdup("ccccc")));
  vappend(v3, GSTR(strdup("cccccccccccc")));
  VTRAVERSE(cur, v) {
    struct vector *tmp = (struct vector *)cur->v;
    VTRAVERSE(elem, tmp) {
      printf("%s\n", elem->s);
    }
  }
  vfree(v);
  return 0;
}