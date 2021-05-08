#include "val_list1.h"

#include "tests/base/utils.h"

int main() {
  list1_t list = list1_create();
  val1_node_t n1 = val1_make_node((union gtype){.l = 1});
  val1_node_t n2 = val1_make_node((union gtype){.l = 2});
  val1_node_t n3 = val1_make_node((union gtype){.l = 3});
  val1_append(list, n1);
  CHECK_MSG(list->size == 1, "Append n1 size");

  val1_prepend(list, n2);
  CHECK_MSG(list->size == 2, "Prepend n2 size");

  val1_append(list, n3);
  CHECK_MSG(list->size == 3, "Append n3 size");

  CHECK_MSG(val1_value(list->first).l == 2, "Value 2");
  CHECK_MSG(val1_value(list->first->next).l == 1, "Value 1");
  CHECK_MSG(val1_value(list->first->next->next).l == 3, "Value 3");
  CHECK_MSG(val1_remove_first(list)->val.l == 2, "Remove 2");
  CHECK_MSG(val1_remove_first(list)->val.l == 1, "Remove 1");
  CHECK_MSG(val1_remove_first(list)->val.l == 3, "Remove 3");
  return 0;
}