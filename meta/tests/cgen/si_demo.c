/* Đếm tần suất từ */

#include "cgen.h"
#include "tests/utils.h"

TDECL_IMPL(simap, char *, int, si);

int main() {
  char key[100];
  struct simap *si = simap(cmps);
  si->fk = frees;
  while (scanf("%s", key) == 1) {
    int *value = siget(si, key);
    if (value) {
      ++(*value);
    } else {
      siput(si, strdup(key), 1);
    }
  }
  struct TNN(simap) *nd = sifirst_lnr(si);
  while (nd) {
    printf("%s: %d\n", nd->key, nd->value);
    nd = sinext_lnr(nd);
  }
  sifree(si);
  TEST_OK();
}