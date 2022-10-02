#include "tests/base/helpers.h"
#include "tests/base/utils.h"

#include "rbi.h"

int main() {
  int a[] = {1, 2, 2, 3, 3, 3, 5, 5, 5, 5, 5, 6, 6, 6, 6, 8, 9, 10};
  int n = sizeof(a)/sizeof(a[0]);
  struct grbtree *t = rbi_create_tree(NULL);
  for (int i = 0; i < n; ++i) {
    rbi_insert(t, a[i]);
    CHECK_MSG(lnr_match_value(t, a, i + 1), "Giá trị sau khi thêm vào.");
    CHECK_MSG(rb_is_valid(t), "Tính chất đỏ-đen sau khi thêm giá trị.");
  }
  bn_pprint(bn_tree(t), rbi_print_node);
  for (int i = n - 1; i >= 0; --i) {
    CHECK_MSG(rbi_delete(t, a[i]) == 1, "Giá trị hàm xóa trả về.");
    CHECK_MSG(lnr_match_value(t, a, i), "Các giá trị còn lại sau khi xóa.");
    CHECK_MSG(rb_is_valid(t), "Tính chất đỏ-đen sau khi xóa.");
  }
  printf("insert_delete_duplicates ok\n");
  rbi_free_tree(t);
  return 0;
}