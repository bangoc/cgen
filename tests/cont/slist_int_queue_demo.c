/* (C) Nguễn Bá Ngọc 2023 */
#include "tests/mylib/lib.h"
#include "tests/utils.h"

int main() {
  SCONSTRUCT(silist, list);
  SENQUE(list, 1);
  SENQUE(list, 3);
  SENQUE(list, 5);
  SENQUE(list, 7);
  SENQUE(SENQUE(list, 9), 10);
  while (!SEMPTY(list)) {
    printf(" %d", SPEEK(list));
    SDEQUE(list);
  }
  printf("\n");
  SFREE(list);
  TEST_OK();
}