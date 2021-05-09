#include "gtlist1.h"

#include "tests/base/utils.h"

int main() {
  list1_t list = list1_create();
  gtl_node_t n1 = gtl_make_node((gtype){.i = 1});
  gtl_node_t n2 = gtl_make_node((gtype){.i = 2});
  gtl_node_t n3 = gtl_make_node((gtype){.i = 3});
  gtl_append(list, n1);
  CHECK_MSG(list->size == 1, "Append n1 size");

  gtl_prepend(list, n2);
  CHECK_MSG(list->size == 2, "Prepend n2 size");

  gtl_append(list, n3);
  CHECK_MSG(list->size == 3, "Append n3 size");

  CHECK_MSG(gtl_node_value(list->first).i == 2, "Value 2");
  CHECK_MSG(gtl_node_value(list->first->next).i == 1, "Value 1");
  CHECK_MSG(gtl_node_value(list->first->next->next).i == 3, "Value 3");
  CHECK_MSG(gtl_remove_first(list)->val.i == 2, "Remove 2");
  CHECK_MSG(gtl_remove_first(list)->val.i == 1, "Remove 1");
  CHECK_MSG(gtl_remove_first(list)->val.i == 3, "Remove 3");
  return 0;
}