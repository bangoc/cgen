#include "sll.h"

#include "tests/base/utils.h"

int main() {
  sll_node_t n1 = sll_create_node(),
             n2 = sll_create_node(),
             n3 = sll_create_node();
  sll_t list = sll_create_list();
  CHECK_MSG(list->size == 0, "Init size");
  CHECK_MSG(list->front == NULL, "Init first");
  CHECK_MSG(list->back == NULL, "Init last");

  sll_push_back(list, n2);
  CHECK_MSG(list->size == 1, "Append 2 size");
  CHECK_MSG(list->front == n2, "Append 2 first");
  CHECK_MSG(list->back = n2, "Append 2 last");

  sll_push_back(list, n3);
  CHECK_MSG(list->size == 2, "Append 3 size");
  CHECK_MSG(list->front == n2, "Append 3 first");
  CHECK_MSG(list->back = n3, "Append 3 last");

  sll_push_front(list, n1);
  CHECK_MSG(list->size == 3, "Prepend 1 size");
  CHECK_MSG(list->front == n1, "Prepend 1 first");

  CHECK_MSG(sll_front(list) == n1, "Remove return n1");
  sll_pop_front(list);

  CHECK_MSG(list->size == 2, "Remove n1 size");
  CHECK_MSG(sll_front(list) == n2, "Remove n1 first");
  sll_pop_front(list);

  CHECK_MSG(list->size == 1, "Remove n2 size");
  CHECK_MSG(list->front == n3, "Remove n2 first");
  sll_pop_front(list);

  CHECK_MSG(list->size == 0, "Remove n3 size");
  CHECK_MSG(list->front == NULL, "Remove n3 first");
  CHECK_MSG(list->back == NULL, "Remove n3 last");
  sll_free_list(list);
  return 0;
}