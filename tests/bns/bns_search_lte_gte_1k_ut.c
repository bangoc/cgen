#include "base/bns.h"

#include "tests/base/utils.h"
#include "tests/rb/rbi.h"

#define N 1000

int main() {
  bn_tree_t t = bn_create_tree(NULL);
  // 0, 2, ..., 2 * N - 2
  for (int i = 0; i < N; ++i) {
    rbi_insert(t, 2  * i);
  }
  for (int i = 0; i < N - 1; ++i) {
    int value = 2 * i + 1;
    bns_search_gte_inline(out, t, value, rbi_compare_data,
      CHECK_MSG(out && rbi_value(out) == value + 1, "search gte with odd number"));
    bns_search_lte_inline(out, t, value, rbi_compare_data,
      CHECK_MSG(out && rbi_value(out) == value - 1, "search lte with odd number"));
  }
  return 0;
}