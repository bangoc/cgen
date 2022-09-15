#include "all.h"

#include "tests/base/utils.h"

gtype pop_value_front(struct gsllist *list) {
  gtype value = gsl_front(list)->value;
  gsl_pop_front(list);
  return value;
}

int main() {
  struct gsllist *list = gsl_create_list(NULL);
  gsl_push_back(list, (gtype){.l = 1});
  CHECK_MSG(gsl_length(list) == 1, "Append n1 size");

  gsl_push_front(list, (gtype){.l = 2});
  CHECK_MSG(gsl_length(list) == 2, "Prepend n2 size");

  gsl_push_back(list, (gtype){.l = 3});
  CHECK_MSG(gsl_length(list) == 3, "Append n3 size");

  CHECK_MSG(gsl_node_value(gsl_front(list)).l == 2, "Value 2");
  CHECK_MSG(gsl_node_value(gsl_node_next(gsl_front(list))).l == 1, "Value 1");
  CHECK_MSG(gsl_node_value(gsl_node_next(gsl_node_next(gsl_front(list)))).l == 3, "Value 3");
  CHECK_MSG(pop_value_front(list).l == 2, "Remove 2");
  CHECK_MSG(pop_value_front(list).l == 1, "Remove 1");
  CHECK_MSG(pop_value_front(list).l == 3, "Remove 3");
  gsl_free(list);
  TEST_OK();
  return 0;
}