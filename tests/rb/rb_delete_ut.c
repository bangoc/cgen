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

int test_delete_root_2nodes() {
  rbi_node_t r = rbi_create_node(5);
  rbi_node_t rc = rbi_create_node(8);
  rb_set_red(rc);
  bn_connect(r, right, rc);
  bn_connect(rc, top, r);
  bn_tree_t t = bn_create_tree(to_bn(r));
  /*
     Xóa    5B     Thu được   8B
              8R
  */
  free(rbi_delete(t, 5));
  CHECK_MSG(lnr_match(t, (int[]){8}, 1), "Giá trị tăng dần 8");
  CHECK_MSG(rbi_value(t->root) == 8, "Gốc bằng 8");
  CHECK_MSG(rb_is_black(t->root), "Nút gốc là nút đen");

  CHECK_MSG(rbi_delete(t, 6) == NULL_PTR, "Hàm xóa nút không có trả về NULL");

  free(rbi_delete(t, 8));
  CHECK_MSG(t->root == NULL_PTR, "Xóa nút 1 gốc cây thành rỗng.");
  return 0;
}

int main() {
  CHECK_MSG(test_delete_root() == 0, "lỗi ở test_delete_root");
  CHECK_MSG(test_delete_root_2nodes() == 0, "lỗi ở test_delete_root_2nodes");
  return 0;
}