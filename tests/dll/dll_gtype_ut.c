/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "gdl.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

int test_create_node_g() {
  gdn_t nn = (gdn_t)gdn_create((gtype){.i = 102});
  CHECK_MSG(nn->base.next == NULL, "base.next NULL");
  CHECK_MSG(nn->base.prev == NULL, "base.prev NULL");
  CHECK_MSG(gdn_value(nn).i == 102, "value 102");
  dll_free_node(to_dll_node(nn));
  return 0;
}

gtype pop_value_front(gdl_t list) {
  gtype tmp = gdl_front(list);
  gdl_pop_front(list);
  return tmp;
}

gtype pop_value_back(gdl_t list) {
  gtype tmp = gdl_back(list);
  gdl_pop_back(list);
  return tmp;
}

int test_push_back_front_g() {
  gdl_t list = gdl_create(NULL);
  CHECK_MSG(gdl_front_node(list) == NULL, "front NULL");
  CHECK_MSG(gdl_back_node(list) == NULL, "back NULL");

  gtype v3 = {.i = 3},
        v5 = {.i = 5},
        v9 = {.i = 9},
        v2 = {.i = 2},
        v6 = {.i = 6};
  gdl_push_back(list, v3);
  gdl_push_back(list, v5);
  gdl_push_back(list, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v3, v5, v9}, 3, gtype_cmp_i), "sequence 3 values");

  gdl_push_front(list, v2);
  gdl_push_front(list, v6);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v6, v2, v3, v5, v9}, 5, gtype_cmp_i),
                "sequence 5 values");

  CHECK_MSG(pop_value_front(list).i == 6, "pop front 6");
  CHECK_MSG(pop_value_back(list).i == 9, "pop back 9");
  CHECK_MSG(gdl_front(list).i == 2, "front 2");
  CHECK_MSG(gdl_back(list).i == 5, "back 5");

  CHECK_MSG(pop_value_front(list).i == 2, "pop front 2");
  CHECK_MSG(pop_value_back(list).i == 5, "pop back 5");
  CHECK_MSG(pop_value_front(list).i == 3, "pop front 3");
  CHECK_MSG(dll_is_empty(list), "list should be empty");

  gdl_push_front(list, v2);
  gdl_push_front(list, v3);
  gdl_push_back(list, v6);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v3, v2, v6}, 3, gtype_cmp_i),
          "push 3 values");

  CHECK_MSG(pop_value_back(list).i == 6, "pop back 6");
  CHECK_MSG(pop_value_front(list).i == 3, "pop front 3");
  CHECK_MSG(pop_value_back(list).i == 2, "pop back 2");
  CHECK_MSG(dll_is_empty(list), "list should be empty");
  dll_free_list(list);
  return 0;
}

int test_insert_ab() {
  gdl_t list = gdl_create(NULL);
  CHECK_MSG(gdl_front_node(list) == NULL, "front NULL");
  CHECK_MSG(gdl_back_node(list) == NULL, "back NULL");

  gtype v1 = {.i = 1},
        v2 = {.i = 2},
        v3 = {.i = 3},
        v6 = {.i = 6},
        v9 = {.i = 9};
  dll_node_t tmp = gdl_inserta(list, NULL, v1);
  CHECK_MSG(tmp == gdl_front_node(list), "insert 1 front");
  CHECK_MSG(tmp == gdl_back_node(list), "insert 1 back");

  gdl_insertb(list, NULL, v2);
  CHECK_MSG(gdl_front(list).i == 2, "front 2");
  CHECK_MSG(gdl_back(list).i == 1, "back 1");

  gdl_inserta(list, dll_front(list), v3);
  gdl_insertb(list, dll_back(list), v6);
  gdl_insertb(list, NULL, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v9, v2, v3, v6, v1}, 5, gtype_cmp_i),
          "insertab 5 values");

  dll_clear(list);
  CHECK_MSG(dll_is_empty(list), "List should be empty");

  gdl_inserta(list, NULL, v1);
  tmp = gdl_inserta(list, NULL, v2);
  tmp = gdl_insertb(list, tmp, v3);
  tmp = gdl_inserta(list, tmp, v6);
  tmp = gdl_insertb(list, tmp, v9);
  CHECK_MSG(dll_sequence_g(list, (gtype[]){v1, v3, v9, v6, v2}, 5, gtype_cmp_i),
         "insertba 5 values (another sequence)");

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
