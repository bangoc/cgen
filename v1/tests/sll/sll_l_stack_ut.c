#include "all.h"
#include "tests/base/utils.h"

int main() {
  struct sllist *stk = sll_create_list();
  isl_stack_push(stk, 1);
  isl_stack_push(stk, 2);
  isl_stack_push(stk, 3);
  CHECK_MSG(sll_length(stk) == 3, "Stack size");
  CHECK_MSG(!sll_is_empty(stk), "Stack not empty");
  CHECK_MSG(isl_stack_pop(stk) == 3, "Stack 3");
  CHECK_MSG(isl_stack_pop(stk) == 2, "Stack 2");
  CHECK_MSG(isl_stack_pop(stk) == 1, "Stack 1");
  CHECK_MSG(sll_is_empty(stk), "Stack empty");
  sll_free(stk);
  return 0;
}