#include "cgen.h"

#include "tests/base/utils.h"

int main() {
  sll_t list = sll_create_list();
  gsl_push_back(list, (gtype){.i = 1});
  CHECK_MSG(sll_length(list) == 1, "Append n1 size");

  gsl_push_front(list, (gtype){.i = 2});
  CHECK_MSG(sll_length(list) == 2, "Prepend n2 size");

  gsl_push_back(list, (gtype){.i = 3});
  CHECK_MSG(sll_length(list) == 3, "Append n3 size");

  CHECK_MSG(gsn_value(list->front).i == 2, "Value 2");
  CHECK_MSG(gsn_value(list->front->next).i == 1, "Value 1");
  CHECK_MSG(gsn_value(list->front->next->next).i == 3, "Value 3");
  CHECK_MSG(gsl_pop_front(list).i == 2, "Remove 2");
  CHECK_MSG(gsl_pop_front(list).i == 1, "Remove 1");
  CHECK_MSG(gsl_pop_front(list).i == 3, "Remove 3");
  sll_free_list(list);
  return 0;
}