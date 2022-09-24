/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Kiểm tra bố cục bộ nhớ:
 * 3 * 8 + n * 13
*/

#include "vec/arr.h"
#include "tests/base/utils.h"

#include <stdint.h>
#include <string.h>

struct s13 {
  char s[13];
};

int main() {
  arr_make(ss, 0, struct s13);
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
    printf("%s\n", ss[i].s);
  }
  struct s13 *tmp = malloc(7 * sizeof(struct s13));
  if ((intptr_t)tmp % 13 == 0) {
    printf("Divided (malloc)\n");
  } else {
    printf("Not divided (malloc)\n");
  }
  CHECK_MSG(strcmp(ss[1].s, "Danang") == 0, "Arr[1] - Danang");
  free(tmp);
  arr_free(ss);
  TEST_OK();
  return 0;
}