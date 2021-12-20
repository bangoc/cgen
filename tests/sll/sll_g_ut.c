#include "cgen.h"

#include "tests/base/utils.h"

gtype pop_value_front(gsl_t list) {
  gtype tmp = gsl_front(list);
  gsl_pop_front(list);
  return tmp;
}

int main() {
  gsl_t list = gsl_create(NULL);
  gsl_push_back(list, (gtype){.i = 1});
  CHECK_MSG(sll_length(list) == 1, "Append n1 size");

  gsl_push_front(list, (gtype){.i = 2});
  CHECK_MSG(sll_length(list) == 2, "Prepend n2 size");

  gsl_push_back(list, (gtype){.i = 3});
  CHECK_MSG(sll_length(list) == 3, "Append n3 size");

  CHECK_MSG(gsn_value(gsl_front_node(list)).i == 2, "Value 2");
  CHECK_MSG(gsn_value(gsn_next(gsl_front_node(list))).i == 1, "Value 1");
  CHECK_MSG(gsn_value(gsn_next(gsn_next(gsl_front_node(list)))).i == 3, "Value 3");
  CHECK_MSG(pop_value_front(list).i == 2, "Remove 2");
  CHECK_MSG(pop_value_front(list).i == 1, "Remove 1");
  CHECK_MSG(pop_value_front(list).i == 3, "Remove 3");
  sll_free(list);
  return 0;
}