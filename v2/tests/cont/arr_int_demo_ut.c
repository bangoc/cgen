/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdlib.h>
#include <time.h>

int icmp(const void *p1, const void *p2) {
  return *(const int*)p1 - *(const int *)p2;
}

int simple_traverse() {
  int **a = acreate(int, 10);
  srand(time(NULL));
  atraverse(int *, cur, a) {
    *cur = rand();
  }
  printf("%ld %ld %ld\n", asize(a), acap(a), aesz(a));
  atraverse(int *, cur, a) {
    printf(" %d", *cur);
  }
  printf("\n");
  afree(a);
  return 1;
}

int main() {
  CHECK_MSG(simple_traverse(), "Simple traverse");
  int **a = acreate(int, 0);
  int elem;
  while (scanf("%d", &elem) == 1) {
    aappend(a, elem);
  }
  printf("%ld %ld\n", asize(a), acap(a));
  aqsort(a, icmp);
  atraverse(int *, cur, a) {
    printf(" %d", *cur);
  }
  afree(a);
  TEST_OK();
}