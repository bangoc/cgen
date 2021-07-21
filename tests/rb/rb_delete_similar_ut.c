#include "tests/rb/rbi.h"
#include "tests/base/bn_utils.h"
#include "tests/base/utils.h"

bn_tree_t make_tree1() {
  rbi_node_t n2 = rbi_create_color_node(2, RB_RED);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  rbi_node_t n6 = rbi_create_color_node(6, RB_BLACK);
  rbi_node_t n8 = rbi_create_color_node(8, RB_RED);
  /*
           5B
      3B          6B
    2R               8R
  */
  bn_connect2(n3, left, n2, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  bn_tree_t t = bn_create_tree(to_bn(n5));
  return t;
}

int delete_node_one_left_child() {
  bn_tree_t t = make_tree1();

  rbi_node_t n2 = rbi_create_color_node(2, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  rbi_node_t n6 = rbi_create_color_node(6, RB_BLACK);
  rbi_node_t n8 = rbi_create_color_node(8, RB_RED);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));

  rbi_delete(t, 3);
  /* Sau khi xóa 3
           5B
       2B        6B
                     8R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 3 trong cây 1");
  return 0;
}

int delete_node_one_right_child() {
  bn_tree_t t = make_tree1();

  rbi_node_t n2 = rbi_create_color_node(2, RB_RED);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  rbi_node_t n8 = rbi_create_color_node(8, RB_BLACK);
  bn_connect2(n3, left, n2, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n8, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));

  rbi_delete(t, 6);
  /* Sau khi xóa 6
           5B
       3B        8B
     2R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 6 trong cây 1");
  return 0;
}

int delete_red_node_no_child() {
  /*
  Trường hợp đơn giản, các nút còn lại không thay đổi
  */
  bn_tree_t t = make_tree1();
  rbi_delete(t, 2);

  /*
    Cây sau khi xóa 2
           5B
      3B          6B
                     8R
  */
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  rbi_node_t n6 = rbi_create_color_node(6, RB_BLACK);
  rbi_node_t n8 = rbi_create_color_node(8, RB_RED);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 2 trong cây 1");

  rbi_delete(t, 8);

  /*
    Cây sau khi xóa 8
           5B
      3B          6B
  */
  bn_connect(n6, right, NULL_PTR);
  bn_connect(n8, top, NULL_PTR);

  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa thêm nút 8 trong cây 1");
  return 0;
}

int main() {
  CHECK_MSG(delete_node_one_left_child() == 0, "Sai ở delete_node_one_left_child()");
  CHECK_MSG(delete_node_one_right_child() == 0, "Sai ở delete_node_one_right_child()");
  CHECK_MSG(delete_red_node_no_child() == 0, "Sai ở delete_red_node_no_child()");
  return 0;
}