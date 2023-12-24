/* (C) Nguyen Ba Ngoc, 2021 */

#include "list/spec/idl.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

int test_idn_create() {
  struct idlnode *n = idl_node(idl_create_node(90));
  CHECK_MSG(n->base.prev == NULL, "base->prev");
  CHECK_MSG(n->base.next == NULL, "base->next");
  CHECK_MSG(n->value == 90, "value 90");
  free(dll_node(n));
  return 0;
}

int test_idl_push_back() {
  struct dllist *list = dll_create_list();
  idl_push_back(list, 1);
  idl_push_back(list, 2);
  idl_push_back(list, 3);
  CHECK_MSG(dll_sequence_i(list, (int[]){1, 2, 3}, 3), "push_back 3");
  dll_free(list);
  return 0;
}

int test_idl_push_front() {
  struct dllist *list = dll_create_list();
  idl_push_front(list, 1);
  idl_push_front(list, 2);
  idl_push_front(list, 3);
  CHECK_MSG(dll_sequence_i(list, (int[]){3, 2, 1}, 3), "push_front 3");
  dll_free(list);
  return 0;
}

int test_dll_pop_front_back_i() {
  struct dllist *list = dll_create_list();
  idl_push_front(list, 1);
  idl_push_front(list, 2);
  idl_push_back(list, 3);
  CHECK_MSG(dll_sequence_i(list, (int[]){2, 1, 3}, 3), "push front back");
  CHECK_MSG(idl_front_value(list) == 2, "front 2");
  CHECK_MSG(idl_back_value(list) == 3, "back 3");
  CHECK_MSG(idl_pop_front(list) == 2, "pop_front 2");
  CHECK_MSG(idl_pop_back(list) == 3, "pop_back 3");
  CHECK_MSG(dll_sequence_i(list, (int[]){1}, 1), "one last");
  dll_free(list);
  return 0;
}

int test_dll_insert_abi() {
  struct dllist *list = dll_create_list();
  idl_insert_a(list, NULL, 1);
  idl_insertb(list, idl_front(list), 2);
  idl_insertb(list, idl_front(list), 3);
  idl_insert_a(list, idl_front(list), 5);
  idl_insert_a(list, idl_back(list), 6);
  CHECK_MSG(dll_sequence_i(list, (int[]){3, 5, 2, 1, 6}, 5), "intsert ab 5");
  dll_free(list);
  return 0;
}

int main() {
  CHECK_MSG(test_idn_create() == 0, "create_node_i");
  CHECK_MSG(test_idl_push_back() == 0, "push_back_i");
  CHECK_MSG(test_idl_push_front() == 0, "push_front_i");
  CHECK_MSG(test_dll_pop_front_back_i() == 0, "pop_front_back_i");
  CHECK_MSG(test_dll_insert_abi() == 0, "insert_abi");
  printf("Test Ok\n");
  return 0;
}