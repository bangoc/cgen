/* (C) Nguyễn Bá Ngọc 2023 */
#include "all.h"
#include "tests/ut/utils.h"

#include <stdio.h>

void vprint(struct vector *v) {
  VTRAVERSE(cur, v) {
    printf(" %ld", cur->l);
  }
  printf("\n");
}

int main() {
  struct vector *v = create_perm(5);
  long cc = 0;
  do {
    vprint(v);
    ++cc;
  } while (next_perm(v));
  do {
    vprint(v);
    ++cc;
  } while (prev_perm(v));
  vfree(v);
  long tmp = 2 * 3 * 4 * 5;
  CHECK_MSG(2 * tmp == cc, "Số lượng hoán vị x 2.");
  struct vector *v1 = create_perm(1);
  CHECK_MSG(next_perm(v1) == NULL, "Không có hoán vị tiếp theo của 1");
  CHECK_MSG(prev_perm(v1) == NULL, "Không có hoán vị liền trước của 1");
  vfree(v1);
  TEST_OK();
}