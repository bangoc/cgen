/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
int main() {
  amake(int, a, 0);
  aenque(a, 3);
  aenque(a, 5);
  aenque(a, 7);
  int head = 0;
  while (head < asize(a)) {
    printf("%d\n", apeek(a, head));
    adeque(a, head);
  }
  afree(a);
}