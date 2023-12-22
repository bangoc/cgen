/* (C) Nguyễn Bá Ngọc 2023 */
#include "tests/mylib/lib.h"
#include "tests/utils.h"

#include <string.h>

int main() {
  TCONSTRUCT(tsimap, si, cmps);
  TPUT(si, "aaa", 100);
  TPUT(si, "ccc", 200);
  TPUT(si, "bbb", 300);
  TPUT(si, "eee", 500);
  TPUT(si, "ddd", 600);
  printf("aaa: %d\n", *TGET(si, "aaa"));
  printf("bbb: %d\n", *TGET(si, "bbb"));
  printf("ccc: %d\n", *TGET(si, "aaa"));
  printf("--- Duyệt thứ tự thuận ---\n");
  struct TNN(tsimap) *n = TFIRST_LNR(si->root);
  while (n) {
    printf("%s: %d\n", n->key, n->value);
    n = TNEXT_LNR(n);
  }
  printf("--- Duyệt thứ tự ngược ---\n");
  n = TLAST_LNR(si->root);
  while (n) {
    printf("%s: %d\n", n->key, n->value);
    n = TPREV_LNR(n);
  }
  TFREE(si);
  TEST_OK();
}