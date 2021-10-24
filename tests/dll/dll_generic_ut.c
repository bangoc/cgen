/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "dll.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

int test_dll_create_node() {
  dll_node_t nn = dll_create_node();
  if (!nn) {
    DEBUG_MSG("Null node");
    return 1;
  }
  if (nn->prev || nn->next) {
    return 1;
  }
  dll_free_node(nn);
  return 0;
}

int test_dll_create_list() {
  dll_t list = dll_create_list();
  if (!list) {
    DEBUG_MSG("Null list");
    return 1;
  }
  if (list -> front || list->back) {
    return 1;
  }
  dll_free_list(list);
  return 0;
}
int test_dll_push_t1() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node();
  dll_push_back(list, n1);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1}, 1), "push_back empty list");

  dll_node_t n2 = dll_create_node();
  dll_push_front(list, n2);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n1}, 2), "push_front 2 node");

  dll_free_list(list);
  list = dll_create_list();
  n1 = dll_create_node();
  dll_push_front(list, n1);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1}, 1), "push_front empty list");

  n2 = dll_create_node();
  dll_push_back(list, n2);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2}, 2), "push back 2 nodes");

  dll_free_list(list);

  return 0;
}

int test_dll_pop_t1() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node();
  dll_node_t n2 = dll_create_node();
  dll_node_t n3 = dll_create_node();
  dll_push_back(list, n1);
  dll_push_back(list, n2);
  dll_push_back(list, n3);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2, n3}, 3), "push_back 3 nodes");

  dll_pop_back(list);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2}, 2), "pop_back 3 nodes");

  dll_pop_front(list);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2}, 1), "pop_front 2 nodes");

  dll_pop_front(list);
  ASSERT(dll_is_empty(list), "pop_front => empty");

  n1 = dll_create_node();
  dll_push_back(list, n1);
  dll_pop_back(list);
  ASSERT(dll_is_empty(list), "pop_back => empty");

  dll_pop_back(list);
  dll_pop_front(list);
  ASSERT(dll_is_empty(list), "pop no ops on empty");

  dll_free_list(list);
  return 0;
}

int test_dll_front_back() {
  dll_t list = dll_create_list();
  ASSERT(dll_front(list) == NULL, "front empty");
  ASSERT(dll_back(list) == NULL, "back empty");

  dll_node_t n1 = dll_create_node();
  dll_push_back(list, n1);
  ASSERT(dll_front(list) == n1, "front one node");
  ASSERT(dll_back(list) == n1, "back one node");

  dll_node_t n2 = dll_create_node();
  dll_push_front(list, n2);
  ASSERT(dll_front(list) == n2, "front two node");
  ASSERT(dll_back(list) == n1, "back two node");

  dll_free_list(list);

  return 0;
}

int test_dll_insert_ab() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node();
  dll_node_t n2 = dll_create_node();
  dll_inserta(list, NULL, n1);
  dll_inserta(list, n1, n2);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2}, 2), "2 nodes");


  dll_node_t n3 = dll_create_node();
  dll_inserta(list, n1, n3);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n3, n2}, 3), "after n1");

  dll_node_t n5 = dll_create_node();
  dll_insertb(list, n1, n5);
  ASSERT(dll_sequence(list, (dll_node_t[]){n5, n1, n3, n2}, 4), "before n1");

  dll_free_list(list);
  list = dll_create_list();
  n1 = dll_create_node();
  dll_insertb(list, NULL, n1);
  n2 = dll_create_node();
  dll_insertb(list, n1, n2);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n1}, 2), "insertb 2 nodes");

  n3 = dll_create_node();
  dll_insertb(list, n1, n3);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n3, n1}, 3), "insertb 3 nodes");

  n5 = dll_create_node();
  dll_inserta(list, n1, n5);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n3, n1, n5}, 4), "inserta 4 nodes");

  dll_free_list(list);
  return 0;
}

int test_dll_is_empty() {
  dll_t list = dll_create_list();
  ASSERT(dll_is_empty(list), "Empty after create");

  dll_node_t n1 = dll_create_node();
  dll_push_back(list, n1);
  ASSERT(!dll_is_empty(list), "Not empty after push_back");

  dll_pop_front(list);
  ASSERT(dll_is_empty(list), "Empty after pop_front");

  list->front = n1;
  ASSERT(!dll_is_empty(list), "Wrong state");

  list->front = NULL;

  dll_free_list(list);
  return 0;
}

int test_dll_size() {
  dll_t list = dll_create_list();
  ASSERT(list->size == 0, "Length == 0 after create");

  dll_node_t n1 = dll_create_node();
  dll_node_t n2 = dll_create_node();
  dll_node_t n3 = dll_create_node();
  dll_push_back(list, n1);
  ASSERT(list->size == 1, "Length == 1 push_back");

  dll_push_back(list, n2);
  ASSERT(list->size == 2, "Length == 2 push_back");

  dll_push_back(list, n3);
  ASSERT(list->size == 3, "Length == 3 push_back");

  dll_pop_front(list);
  ASSERT(list->size == 2, "Length == 2 pop_front");

  dll_pop_back(list);
  ASSERT(list->size == 1, "Length == 1 pop_back");

  dll_pop_front(list);
  ASSERT(list->size == 0, "Length == 0 pop_front");

  dll_free_list(list);
  return 0;
}

int test_dll_erase() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node(),
      n2 = dll_create_node(),
      n3 = dll_create_node(),
      n4 = dll_create_node(),
      n5 = dll_create_node();
  dll_push_back(list, n1);
  dll_push_back(list, n2);
  dll_push_back(list, n3);
  dll_push_back(list, n4);
  dll_push_back(list, n5);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2, n3, n4, n5}, 5), "Init 5 nodes");

  dll_erase(list, n1);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n3, n4, n5}, 4), "Delete n1");


  dll_erase(list, n4);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n3, n5}, 3), "Delete n4");

  dll_erase(list, n5);
  ASSERT(dll_sequence(list, (dll_node_t[]){n2, n3}, 2), "Delete n5");

  dll_erase(list, n2);
  ASSERT(dll_sequence(list, (dll_node_t[]){n3}, 1), "Delete n2");

  dll_erase(list, n3);
  ASSERT(dll_is_empty(list), "Delete n3");

  dll_free_list(list);
}

int test_dll_clear() {
  dll_t list = dll_create_list();
  dll_node_t n1 = dll_create_node(),
      n2 = dll_create_node(),
      n3 = dll_create_node();
  dll_push_back(list, n1);
  dll_push_back(list, n2);
  dll_push_back(list, n3);
  ASSERT(dll_sequence(list, (dll_node_t[]){n1, n2, n3}, 3), "Init 3 nodes");

  dll_clear(list);
  ASSERT(dll_is_empty(list), "should be empty after clear");

  dll_free_list(list);
}

int main() {
  ASSERT(test_dll_create_node() == 0, "dll_create_node");
  ASSERT(test_dll_create_list() == 0, "dll_create_list");
  ASSERT(test_dll_push_t1() == 0, "dll_push_t1");
  ASSERT(test_dll_pop_t1() == 0, "dll_pop_t1");
  ASSERT(test_dll_front_back() == 0, "dll front & back");
  ASSERT(test_dll_insert_ab() == 0, "dll_insert_ab");
  ASSERT(test_dll_is_empty() == 0, "dll_is_empty");
  ASSERT(test_dll_size() == 0, "dll->size");
  ASSERT(test_dll_erase() == 0, "dll_erase");
  ASSERT(test_dll_clear() == 0, "dll_clear");
  printf("Test Ok!\n");
  return 0;
}