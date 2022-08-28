#include "base/bns.h"

#include "tests/base/utils.h"
#include "base/rb.h"

#define N 1000

int main() {
  bs_tree_t t = bs_create_tree(NULL, gtype_cmp_l, NULL);
  // 0, 2, ..., 2 * N - 2
  for (int i = 0; i < N; ++i) {
    rb_insert(t, gtype_l(2  * i));
  }
  for (int i = 0; i < N - 1; ++i) {
    int value = 2 * i + 1;
    CHECK_MSG(bs_search_gte(t, gtype_l(value))->key.l == value + 1, "search gte with odd number");
    CHECK_MSG(bs_search_lte(t, gtype_l(value))->key.l == value - 1, "search lte with odd number");
  }
  bs_free_tree(t);
  return 0;
}