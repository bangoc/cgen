#include "all.h"

#include "tests/base/utils.h"

#include <stdlib.h>

int sll_t1() {
  struct slnode *n1 = sll_create_node(),
             *n2 = sll_create_node(),
             *n3 = sll_create_node();
  struct sllist *list = sll_create_list();
  CHECK_MSG(sll_length(list) == 0, "Init size");
  CHECK_MSG(list->front == NULL, "Init first");
  CHECK_MSG(list->back == NULL, "Init last");

  sll_push_back(list, n2);
  CHECK_MSG(sll_length(list) == 1, "Append 2 size");
  CHECK_MSG(list->front == n2, "Append 2 first");
  CHECK_MSG(list->back = n2, "Append 2 last");

  sll_push_back(list, n3);
  CHECK_MSG(sll_length(list) == 2, "Append 3 size");
  CHECK_MSG(list->front == n2, "Append 3 first");
  CHECK_MSG(list->back = n3, "Append 3 last");

  sll_push_front(list, n1);
  CHECK_MSG(sll_length(list) == 3, "Prepend 1 size");
  CHECK_MSG(list->front == n1, "Prepend 1 first");

  CHECK_MSG(sll_front(list) == n1, "Remove return n1");
  sll_pop_front(list);

  CHECK_MSG(sll_length(list) == 2, "Remove n1 size");
  CHECK_MSG(sll_front(list) == n2, "Remove n1 first");
  sll_pop_front(list);

  CHECK_MSG(sll_length(list) == 1, "Remove n2 size");
  CHECK_MSG(list->front == n3, "Remove n2 first");
  sll_pop_front(list);

  CHECK_MSG(sll_length(list) == 0, "Remove n3 size");
  CHECK_MSG(list->front == NULL, "Remove n3 first");
  CHECK_MSG(list->back == NULL, "Remove n3 last");
  sll_free(list);
  return 0;
}

int test_create_list() {
  #define N 1000
  int *a = malloc(N * sizeof(int));
  for (int i = 0; i < N; ++i) {
    a[i] = i;
  }
  free(a);
  struct sllist *lists[N];
  for (int i = 0; i < N; ++i) {
    lists[i] = sll_create_list();
    CHECK_MSG(sll_is_empty(lists[i]), "Empty on create");
  }
  for (int i = 0; i < N; ++i) {
    sll_free(lists[i]);
  }
  #undef N
  return 0;
}

int main() {
  CHECK_MSG(sll_t1() == 0, "t1 (old tests)");
  CHECK_MSG(test_create_list() == 0, "create_list");
  return 0;
}