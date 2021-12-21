/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "gdl.h"

#include "tests/base/utils.h"
#include "tests/dll/helper.h"

gtype pop_value_front(gdl_t list) {
  gtype tmp = gdn_value(gdl_front(list));
  gdl_pop_front(list);
  return tmp;
}

gtype pop_value_back(gdl_t list) {
  gtype tmp = gdn_value(gdl_back(list));
  gdl_pop_back(list);
  return tmp;
}

int test_push_back_front_g() {
  gdl_t list = gdl_create(NULL);
  CHECK_MSG(gdl_front(list) == NULL, "front NULL");
  CHECK_MSG(gdl_back(list) == NULL, "back NULL");

  gtype v3 = {.i = 3},
        v5 = {.i = 5},
        v9 = {.i = 9},
        v2 = {.i = 2},
        v6 = {.i = 6};
  gdl_push_back(list, v3);
  gdl_push_back(list, v5);
  gdl_push_back(list, v9);
  CHECK_MSG(gdl_sequence_g(list, (gtype[]){v3, v5, v9}, 3, gtype_cmp_i), "sequence 3 values");

  gdl_push_front(list, v2);
  gdl_push_front(list, v6);
  CHECK_MSG(gdl_sequence_g(list, (gtype[]){v6, v2, v3, v5, v9}, 5, gtype_cmp_i),
                "sequence 5 values");

  CHECK_MSG(pop_value_front(list).i == 6, "pop front 6");
  CHECK_MSG(pop_value_back(list).i == 9, "pop back 9");
  CHECK_MSG(gdl_front(list)->i == 2, "front 2");
  CHECK_MSG(gdl_back(list)->i == 5, "back 5");

  CHECK_MSG(pop_value_front(list).i == 2, "pop front 2");
  CHECK_MSG(pop_value_back(list).i == 5, "pop back 5");
  CHECK_MSG(pop_value_front(list).i == 3, "pop front 3");
  CHECK_MSG(gdl_is_empty(list), "list should be empty");

  gdl_push_front(list, v2);
  gdl_push_front(list, v3);
  gdl_push_back(list, v6);
  CHECK_MSG(gdl_sequence_g(list, (gtype[]){v3, v2, v6}, 3, gtype_cmp_i),
          "push 3 values");

  CHECK_MSG(pop_value_back(list).i == 6, "pop back 6");
  CHECK_MSG(pop_value_front(list).i == 3, "pop front 3");
  CHECK_MSG(pop_value_back(list).i == 2, "pop back 2");
  CHECK_MSG(gdl_is_empty(list), "list should be empty");
  gdl_free(list);
  return 0;
}

int test_insert_ab() {
  gdl_t list = gdl_create(NULL);
  CHECK_MSG(gdl_front(list) == NULL, "front NULL");
  CHECK_MSG(gdl_back(list) == NULL, "back NULL");

  gtype v1 = {.i = 1},
        v2 = {.i = 2},
        v3 = {.i = 3},
        v6 = {.i = 6},
        v9 = {.i = 9};
  gdl_inserta(list, NULL, v1);
  CHECK_MSG(gdl_front(list)->i == 1, "insert 1 front");
  CHECK_MSG(gdl_back(list)->i == 1, "insert 1 back");

  gdl_insertb(list, NULL, v2);
  CHECK_MSG(gdl_front(list)->i == 2, "front 2");
  CHECK_MSG(gdl_back(list)->i == 1, "back 1");

  gdl_inserta(list, gdl_front(list), v3);
  gdl_insertb(list, gdl_back(list), v6);
  gdl_insertb(list, NULL, v9);
  CHECK_MSG(gdl_sequence_g(list, (gtype[]){v9, v2, v3, v6, v1}, 5, gtype_cmp_i),
          "insertab 5 values");

  gdl_clear(list);
  CHECK_MSG(gdl_is_empty(list), "List should be empty");

  gdl_inserta(list, NULL, v1);
  gdl_inserta(list, NULL, v2);
  gdl_insertb(list, gdl_back(list), v3);
  gdl_inserta(list, gdn_prev(gdl_back(list)), v6);
  gdl_insertb(list, gdn_prev(gdl_back(list)), v9);
  CHECK_MSG(gdl_sequence_g(list, (gtype[]){v1, v3, v9, v6, v2}, 5, gtype_cmp_i),
         "insertba 5 values (another sequence)");

  gdl_free(list);
  return 0;
}

int main() {
  CHECK_MSG(test_push_back_front_g() == 0, "push_back_front_g");
  CHECK_MSG(test_insert_ab() == 0, "insert a&b");
  TEST_OK();
}
