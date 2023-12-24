#include "all.h"

#include "tests/base/utils.h"

int t1() {
  struct gsllist *stk = gsl_create_list(NULL);
  stk_push(stk, gtype_l(1));
  stk_push(stk, gtype_l(2));
  stk_push(stk, gtype_l(3));
  stk_push(stk, gtype_l(4));
  stk_push(stk, gtype_l(5));
  CHECK_MSG(stk_size(stk) == 5, "Size 5");
  CHECK_MSG(stk_top(stk).l == 5, "Top 5");
  stk_pop(stk_pop(stk));
  CHECK_MSG(stk_top(stk).l == 3, "Top 3");
  stk_pop(stk);
  CHECK_MSG(stk_top(stk).l == 2, "Top 2");
  gsl_free(stk);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "Test 1");
  TEST_OK();
  return 0;
}