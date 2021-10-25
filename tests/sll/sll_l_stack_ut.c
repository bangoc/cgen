#include "sll.h"
#include "tests/base/utils.h"

int main() {
  sll_t stk = sll_create_list();
  sll_stack_push_l(stk, 1);
  sll_stack_push_l(stk, 2);
  sll_stack_push_l(stk, 3);
  CHECK_MSG(sll_length(stk) == 3, "Stack size");
  CHECK_MSG(!sll_is_empty(stk), "Stack not empty");
  CHECK_MSG(sll_stack_pop_l(stk) == 3, "Stack 3");
  CHECK_MSG(sll_stack_pop_l(stk) == 2, "Stack 2");
  CHECK_MSG(sll_stack_pop_l(stk) == 1, "Stack 1");
  CHECK_MSG(sll_is_empty(stk), "Stack empty");
  sll_free_list(stk);
  return 0;
}