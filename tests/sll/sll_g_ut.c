#include "sll.h"

#include "tests/base/utils.h"

int main() {
  sll_t list = sll_create_list();
  sll_push_back_g(list, (gtype){.i = 1});
  CHECK_MSG(list->size == 1, "Append n1 size");

  sll_push_front_g(list, (gtype){.i = 2});
  CHECK_MSG(list->size == 2, "Prepend n2 size");

  sll_push_back_g(list, (gtype){.i = 3});
  CHECK_MSG(list->size == 3, "Append n3 size");

  CHECK_MSG(sll_node_g_value(list->front).i == 2, "Value 2");
  CHECK_MSG(sll_node_g_value(list->front->next).i == 1, "Value 1");
  CHECK_MSG(sll_node_g_value(list->front->next->next).i == 3, "Value 3");
  CHECK_MSG(sll_pop_front_g(list).i == 2, "Remove 2");
  CHECK_MSG(sll_pop_front_g(list).i == 1, "Remove 1");
  CHECK_MSG(sll_pop_front_g(list).i == 3, "Remove 3");
  sll_free_list(list);
  return 0;
}