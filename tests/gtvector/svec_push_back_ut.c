#include "vec/arr.h"

#include "tests/base/utils.h"

#include <string.h>

int t1() {
  arr_make(v, 0, char*);
  char *s1 = "Nguyen Van A";
  char *s2 = "Tran Van B";
  char *s3 = "Nguyen Thi C";
  arr_append(v, s1);
  arr_append(v, s2);
  arr_append(v, s3);
  CHECK_MSG(arr_size(v) == 3, "Failed size");
  CHECK_MSG(strcmp(v[0], s1) == 0, "Failed value 1");
  CHECK_MSG(strcmp(v[1], s2) == 0, "Failed value 2");
  CHECK_MSG(strcmp(v[2], s3) == 0, "Failed value 3");
  arr_free(v);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  printf("Test Ok\n");
  return 0;
}