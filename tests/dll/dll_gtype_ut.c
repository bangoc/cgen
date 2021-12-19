/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "gdl.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

int test_create_node_g() {
  dll_node_g_t nn = (dll_node_g_t)dll_create_node_g((gtype){.i = 102});
  CHECK_MSG(nn->base.next == NULL, "base.next NULL");
  CHECK_MSG(nn->base.prev == NULL, "base.prev NULL");
  CHECK_MSG(dll_node_g_value(nn).i == 102, "value 102");
  dll_free_node(to_dll(nn));
  return 0;
}

int test_push_back_front_g() {
  dll_t list = dll_create_list();
  CHECK_MSG(list->front == NULL, "front NULL");
  CHECK_MSG(list->back == NULL, "back NULL");

  gtype v3 = {.i = 3},
        v5 = {.i = 5},
        v9 = {.i = 9},
        v2 = {.i = 2},
        v6 = {.i = 6};
  dll_push_back_g(list, v3);
  dll_push_back_g(list, v5);
  dll_push_back_g(list, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v3, v5, v9}, 3, gtype_cmp_i), "sequence 3 values");

  dll_push_front_g(list, v2);
  dll_push_front_g(list, v6);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v6, v2, v3, v5, v9}, 5, gtype_cmp_i),
                "sequence 5 values");

  CHECK_MSG(dll_pop_front_g(list).i == 6, "pop front 6");
  CHECK_MSG(dll_pop_back_g(list).i == 9, "pop back 9");
  CHECK_MSG(dll_front_g(list).i == 2, "front 2");
  CHECK_MSG(dll_back_g(list).i == 5, "back 5");

  CHECK_MSG(dll_pop_front_g(list).i == 2, "pop front 2");
  CHECK_MSG(dll_pop_back_g(list).i == 5, "pop back 5");
  CHECK_MSG(dll_pop_front_g(list).i == 3, "pop front 3");
  CHECK_MSG(dll_is_empty(list), "list should be empty");

  dll_push_front_g(list, v2);
  dll_push_front_g(list, v3);
  dll_push_back_g(list, v6);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v3, v2, v6}, 3, gtype_cmp_i),
          "push 3 values");

  CHECK_MSG(dll_pop_back_g(list).i == 6, "pop back 6");
  CHECK_MSG(dll_pop_front_g(list).i == 3, "pop front 3");
  CHECK_MSG(dll_pop_back_g(list).i == 2, "pop back 2");
  CHECK_MSG(dll_is_empty(list), "list should be empty");
  dll_free_list(list);
  return 0;
}

int test_insert_ab() {
  dll_t list = dll_create_list();
  CHECK_MSG(list->front == NULL, "front NULL");
  CHECK_MSG(list->back == NULL, "back NULL");

  gtype v1 = {.i = 1},
        v2 = {.i = 2},
        v3 = {.i = 3},
        v6 = {.i = 6},
        v9 = {.i = 9};
  dll_node_t tmp = dll_inserta_g(list, NULL, v1);
  CHECK_MSG(tmp == list->front, "insert 1 front");
  CHECK_MSG(tmp == list->back, "insert 1 back");

  dll_insertb_g(list, NULL, v2);
  CHECK_MSG(dll_front_g(list).i == 2, "front 2");
  CHECK_MSG(dll_back_g(list).i == 1, "back 1");

  dll_inserta_g(list, dll_front(list), v3);
  dll_insertb_g(list, dll_back(list), v6);
  dll_insertb_g(list, NULL, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v9, v2, v3, v6, v1}, 5, gtype_cmp_i),
          "insertab 5 values");

  dll_clear(list);
  CHECK_MSG(dll_is_empty(list), "List should be empty");

  dll_inserta_g(list, NULL, v1);
  tmp = dll_inserta_g(list, NULL, v2);
  tmp = dll_insertb_g(list, tmp, v3);
  tmp = dll_inserta_g(list, tmp, v6);
  tmp = dll_insertb_g(list, tmp, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v1, v3, v9, v6, v2}, 5, gtype_cmp_i),
         "inssertba 5 values (another sequence)");

  dll_free_list(list);
  return 0;
}

int main() {
  CHECK_MSG(test_create_node_g() == 0, "create_node_g");
  CHECK_MSG(test_push_back_front_g() == 0, "push_back_front_g");
  CHECK_MSG(test_insert_ab() == 0, "insert a&b");
  printf("Test Ok\n");
  return 0;
}