#include "istack.h"
#include "tests/base/utils.h"

int main() {
  list1_t stk = list1_create();
  istk_push(stk, 1);
  istk_push(stk, 2);
  istk_push(stk, 3);
  CHECK_MSG(stk->size == 3, "Stack size");
  CHECK_MSG(list1_empty(stk) == false, "Stack not empty");
  CHECK_MSG(istk_pop(stk) == 3, "Stack 3");
  CHECK_MSG(istk_pop(stk) == 2, "Stack 2");
  CHECK_MSG(istk_pop(stk) == 1, "Stack 1");
  CHECK_MSG(list1_empty(stk) == true, "Stack empty");
  return 0;
}