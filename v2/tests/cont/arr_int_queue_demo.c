/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
int main() {
  amake(int, a, 0);
  for (int i = 0; i < 64; ++i) {
    aenque(a, i);
  }
  int head = 0;
  while (head < asize(a)) {
    printf(" %d", apeek(a, head));
    adeque(a, head);
    printf(" %d %ld %ld\n", head, asize(a), acap(a));
  }
  afree(a);
}