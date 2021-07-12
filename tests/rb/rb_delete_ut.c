#include "rbi.h"
#include "rbi_helper.h"
#include "tests/base/utils.h"

int test_delete_root() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_node_t root = rbi_create_node(5);
  t->root = to_bn(root);
  rbi_node_t lc = rbi_create_node(3);
  rb_node_init((&lc->rb_node), NULL_PTR, NULL_PTR, root, RB_RED);
  rbi_node_t rc = rbi_create_node(8);
  rb_node_init((&rc->rb_node), NULL_PTR, NULL_PTR, root, RB_RED);
  bn_connect(root, left, lc);
  bn_connect(root, right, rc);
  /*
     Xóa    5B     Thu được   8B
          3R  8R             3R
  */
  free(rbi_delete(t, 5));
  CHECK_MSG(lnr_match(t, (int []){3, 8}, 2), "Giá trị tăng dần 3 8");
  bn_node_t n8 = t->root;
  CHECK_MSG(rbi_value(n8) == 8, "n8 == 8");
  CHECK_MSG(rb_is_black(n8), "n8 là nút đen");

  bn_node_t n3 = t->root->left;
  CHECK_MSG(rbi_value(n3) == 3, "n3 == 3");
  CHECK_MSG(rb_is_red(n3), "n3 là nút đỏ");
  CHECK_MSG(n3->top == n8, "top của n3 == n8");
  return 0;
}

int main() {
  CHECK_MSG(test_delete_root() == 0, "lỗi ở test_delete_root");
  return 0;
}