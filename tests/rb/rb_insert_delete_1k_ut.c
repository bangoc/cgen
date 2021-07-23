#include "rbi.h"
#include "rbi_helper.h"
#include "tests/base/bn_utils.h"
#include "tests/base/utils.h"

#define N 1000

int main() {
  int a[N];
  for (int i = 0; i < N; ++i) {
    a[i] = i;
  }
  bn_tree_t t = bn_create_tree(NULL_PTR);

  // insert
  for (int i = 0; i < N; ++i) {
    rbi_insert(t, a[i]);
    CHECK_MSG(lnr_match_value(t, a, i + 1), "Lỗi giá trị");
    CHECK_MSG(rb_is_valid(t), "Lỗi cây đỏ-đen");
  }

  // delete
  for (int i = N - 1; i >= 0; --i) {
    rbi_node_t nd = rbi_delete(t, a[i]);
    CHECK_MSG(nd && nd->value == a[i], "Lỗi giá trị trả về bởi hàm xóa.");
    CHECK_MSG(lnr_match_value(t, a, i), "Lỗi xóa giá trị");
    CHECK_MSG(rb_is_valid(t), "Lỗi cây đỏ-đen");
  }
  printf("rb_insert_delete_1k Ok\n");
  return 0;
}