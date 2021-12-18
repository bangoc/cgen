/*
  (C) Nguyen Ba Ngoc 2021
  Kiểm tra bố cục bộ nhớ:
    3 * 8 + n * 13
*/

#include "arr.h"
#include "tests/base/utils.h"

#include <stdint.h>
#include <string.h>

struct s13 {
  char s[13];
};

int main() {
  arr_t(struct s13) ss = arr_create(8, struct s13);
  intptr_t pi = (intptr_t)ss;
  printf("%zu %p\n", sizeof(struct s13), ss);
  if (pi % sizeof(struct s13) == 0) {
    printf("Divided\n");
  } else {
    printf("Not divided\n");
  }
  arr_append(ss, (struct s13){"Hanoi"});
  arr_append(ss, (struct s13){"Danang"});
  arr_append(ss, (struct s13){"Hue"});
  arr_append(ss, (struct s13){"Saigon"});
  arr_append(ss, (struct s13){"Hanoi"});
  for (int i = 0; i < arr_size(ss); ++i) {
    printf("%s\n", ARR(ss)[i].s);
  }
  arr_free(ss);
  TEST_OK();
}