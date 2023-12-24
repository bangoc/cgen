/* Đếm tần suất từ */

#include "cgen.h"
#include "tests/utils.h"

TDECL_IMPL(simap, char *, int, si);

int main() {
  char *key = malloc(100);
  struct simap *si = simap(cmps);
  si->fk = frees;
  while (scanf("%s", key) == 1) {
    int *value = siput(si, key, 1);
    if (value) {
      ++(*value);
      printf("%s %d\n", key, *value);
    } else {
      printf("%s (null) %d\n", key, 1);
      key = malloc(100);
    }
  }
  free(key);
  struct TNN(simap) *nd = sifirst_lnr(si);
  while (nd) {
    printf("%s: %d\n", nd->key, nd->value);
    nd = sinext_lnr(nd);
  }
  sifree(si);
  TEST_OK();
}