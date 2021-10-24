#include "sll.h"

#include "tests/base/utils.h"

int main() {
  sll_t list = sll_create();
  gsl_node_t n1 = gsl_make_node((gtype){.i = 1});
  gsl_node_t n2 = gsl_make_node((gtype){.i = 2});
  gsl_node_t n3 = gsl_make_node((gtype){.i = 3});
  gsl_push_back(list, n1);
  CHECK_MSG(list->size == 1, "Append n1 size");

  gsl_push_front(list, n2);
  CHECK_MSG(list->size == 2, "Prepend n2 size");

  gsl_push_back(list, n3);
  CHECK_MSG(list->size == 3, "Append n3 size");

  CHECK_MSG(gsl_node_value(list->front).i == 2, "Value 2");
  CHECK_MSG(gsl_node_value(list->front->next).i == 1, "Value 1");
  CHECK_MSG(gsl_node_value(list->front->next->next).i == 3, "Value 3");
  CHECK_MSG(gsl_pop_front(list)->val.i == 2, "Remove 2");
  CHECK_MSG(gsl_pop_front(list)->val.i == 1, "Remove 1");
  CHECK_MSG(gsl_pop_front(list)->val.i == 3, "Remove 3");
  return 0;
}