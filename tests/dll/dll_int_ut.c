/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "dll.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

int test_dll_create_node_i() {
  dll_node_i_t n = to_node_i(dll_create_node_i(90));
  ASSERT(n->base.prev == NULL, "base->prev");
  ASSERT(n->base.next == NULL, "base->next");
  ASSERT(n->value == 90, "value 90");
  dll_free_node(to_dll(n));
  return 0;
}

int test_dll_push_back_i() {
  dll_t list = dll_create_list();
  dll_push_back_i(list, 1);
  dll_push_back_i(list, 2);
  dll_push_back_i(list, 3);
  ASSERT(dll_sequence_i(list, (int[]){1, 2, 3}, 3), "push_back 3");
  dll_free_list(list);
  return 0;
}

int test_dll_push_front_i() {
  dll_t list = dll_create_list();
  dll_push_front_i(list, 1);
  dll_push_front_i(list, 2);
  dll_push_front_i(list, 3);
  ASSERT(dll_sequence_i(list, (int[]){3, 2, 1}, 3), "push_front 3");
  dll_free_list(list);
  return 0;
}

int test_dll_pop_front_back_i() {
  dll_t list = dll_create_list();
  dll_push_front_i(list, 1);
  dll_push_front_i(list, 2);
  dll_push_back_i(list, 3);
  ASSERT(dll_sequence_i(list, (int[]){2, 1, 3}, 3), "push front back");
  ASSERT(dll_front_i(list) == 2, "front 2");
  ASSERT(dll_back_i(list) == 3, "back 3");
  ASSERT(dll_pop_front_i(list) == 2, "pop_front 2");
  ASSERT(dll_pop_back_i(list) == 3, "pop_back 3");
  ASSERT(dll_sequence_i(list, (int[]){1}, 1), "one last");
  dll_free_list(list);
  return 0;
}

int test_dll_insert_abi() {
  dll_t list = dll_create_list();
  dll_inserta_i(list, NULL, 1);
  dll_insertb_i(list, list->front, 2);
  dll_insertb_i(list, list->front, 3);
  dll_inserta_i(list, list->front, 5);
  dll_inserta_i(list, list->back, 6);
  ASSERT(dll_sequence_i(list, (int[]){3, 5, 2, 1, 6}, 5), "intsert ab 5");
  dll_free_list(list);
  return 0;
}

int main() {
  ASSERT(test_dll_create_node_i() == 0, "create_node_i");
  ASSERT(test_dll_push_back_i() == 0, "push_back_i");
  ASSERT(test_dll_push_front_i() == 0, "push_front_i");
  ASSERT(test_dll_pop_front_back_i() == 0, "pop_front_back_i");
  ASSERT(test_dll_insert_abi() == 0, "insert_abi");
  printf("Test Ok\n");
  return 0;
}