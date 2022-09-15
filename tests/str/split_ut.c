#include "all.h"

#include "tests/base/utils.h"

int t1() {
  char line[] = "Hello\tworld\nC\vProgramming\fBasic\r2022 C Is Fast";
  struct gvector *tokens = str_split(line);
  CHECK_MSG(gvec_size(tokens) == 9, "9 tokens");
  gtype *arr = gvec_arr(tokens);
  CHECK_MSG(strcmp(arr[0].s, "Hello") == 0, "Hello");
  CHECK_MSG(strcmp(arr[1].s, "world") == 0, "world");
  CHECK_MSG(strcmp(arr[2].s, "C") == 0, "C");
  CHECK_MSG(strcmp(arr[3].s, "Programming") == 0, "Programming");
  CHECK_MSG(strcmp(arr[4].s, "Basic") == 0, "Basic");
  CHECK_MSG(strcmp(arr[5].s, "2022") == 0, "2022");
  CHECK_MSG(strcmp(arr[6].s, "C") == 0, "C");
  CHECK_MSG(strcmp(arr[7].s, "Is") == 0, "Is");
  CHECK_MSG(strcmp(arr[8].s, "Fast") == 0, "Fast");
  gvec_free(tokens);
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  TEST_OK();
  return 0;
}