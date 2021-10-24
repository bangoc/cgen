#include "sll.h"
#include "tests/base/utils.h"

int main() {
  sll_t stk = sll_create();
  ist_push(stk, 1);
  ist_push(stk, 2);
  ist_push(stk, 3);
  CHECK_MSG(stk->size == 3, "Stack size");
  CHECK_MSG(sll_empty(stk) == false, "Stack not empty");
  CHECK_MSG(ist_pop(stk) == 3, "Stack 3");
  CHECK_MSG(ist_pop(stk) == 2, "Stack 2");
  CHECK_MSG(ist_pop(stk) == 1, "Stack 1");
  CHECK_MSG(sll_empty(stk) == true, "Stack empty");
  return 0;
}