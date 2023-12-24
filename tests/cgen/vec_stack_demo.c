#include "cgen.h"
#include "tests/utils.h"

VDECL_IMPL(ivector, int, vi);
VDECL_IMPL(svector, char *, vs);
void demo_vector_str() {
  struct svector *v = svector(0);
  vspush(v, "aaaaaa");
  vspush(v, "bbbbbbbbbb");
  vspush(v, "cccccccc");
  while (!vsempty(v)) {
    printf("%s\n", *vstop(v));
    vspop(v);
  }
  vsfree(v);
}
int main() {
  struct ivector *stk = ivector(0);
  vipush(stk, 3);
  vipush(stk, 5);
  vipush(stk, 7);
  while (!viempty(stk)) {
    printf("%d\n", *vitop(stk));
    vipop(stk);
  }
  vifree(stk);
  demo_vector_str();
  TEST_OK();
}