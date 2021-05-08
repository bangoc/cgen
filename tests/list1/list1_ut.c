#include "list1.h"

#include "tests/base/utils.h"

int main() {
  struct list1_node n1, n2, n3;
  list1_t list = list1_create();
  CHECK_MSG(list->size == 0, "Init size");
  CHECK_MSG(list->first == NULL, "Init first");
  CHECK_MSG(list->last == NULL, "Init last");

  list1_append(list, &n2);
  CHECK_MSG(list->size == 1, "Append 2 size");
  CHECK_MSG(list->first == &n2, "Append 2 first");
  CHECK_MSG(list->last = &n2, "Append 2 last");

  list1_append(list, &n3);
  CHECK_MSG(list->size == 2, "Append 3 size");
  CHECK_MSG(list->first == &n2, "Append 3 first");
  CHECK_MSG(list->last = &n3, "Append 3 last");

  list1_prepend(list, &n1);
  CHECK_MSG(list->size == 3, "Prepend 1 size");
  CHECK_MSG(list->first == &n1, "Prepend 1 first");

  CHECK_MSG(list1_remove_first(list) == &n1, "Remove return n1");
  CHECK_MSG(list->size == 2, "Remove n1 size");
  CHECK_MSG(list->first == &n2, "Remove n1 first");

  CHECK_MSG(list1_remove_first(list) == &n2, "Remove return n2");
  CHECK_MSG(list->size == 1, "Remove n2 size");
  CHECK_MSG(list->first == &n3, "Remove n2 first");

  CHECK_MSG(list1_remove_first(list) == &n3, "Remove return n3");
  CHECK_MSG(list->size == 0, "Remove n3 size");
  CHECK_MSG(list->first == NULL, "Remove n3 first");
  CHECK_MSG(list->last == NULL, "Remove n3 last");
  return 0;
}