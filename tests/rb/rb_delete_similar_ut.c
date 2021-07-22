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

bn_tree_t make_tree2() {
  /*
               5B
         2B           7B
      1B     3B   6B      9R
                        8B   10B
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_RED);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
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

int delete_black_node_no_child_red_top_black_sibling1() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 8);
  /* Cây sau khi xóa 8:
               5B
         2B           7B
      1B     3B   6B      9B    <-- top (đỉnh)
                             10R  <-- sibling (đối xứng)
                      Đảo mầu nút đỉnh và nút đối xứng
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  rbi_node_t n10 = rbi_create_color_node(10, RB_RED);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, right, n10, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 8 trong cây 2");
  return 0;
}

int delete_black_node_no_child_red_top_black_sibling2() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 10);
  /*
               5B
         2B           7B
      1B     3B   6B      9B  <-- nút đỉnh
                        8R  <-- nút đối xứng
                        Đảo mầu nút đỉnh và nút đối xứng
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_RED);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 8 trong cây 2");
  return 0;
}

int delete_black_node_no_child_red_sibling_black_top() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 6);
  /*
    Sau khi xóa 6:
               5B
         2B           9B
      1B     3B   7B      10B
                     8R

  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_RED);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n9, top);
  bn_connect2(n9, left, n7, top);
  bn_connect2(n9, right, n10, top);
  bn_connect2(n7, right, n8, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 6 trong cây 2");
  return 0;
}

int delete_black_node_no_child_black_sibling_black_top1() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 1);
  /*
               5B
         2B           7B
             3B   6B      9R
                        8B   10B
             >>>>>
           p->  5B
     n-> 2B           7B    <- s
             3R   6B      9R
                        8B   10B
              >>>>>
                 7B
            5B       9B
        2B     6B  8B  10B
          3R
  */
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_RED);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n7, left, n5, top);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  bn_tree_t s = bn_create_tree(to_bn(n7));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Cây sau khi xóa 1");
  return 0;
}

int delete_black_node_no_child_black_sibling_black_top2() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 3);
  /*
               5B
         2B           7B
      1B          6B      9R
                        8B   10B
             >>>>>
        p->    5B
     n->  2B      s -> 7B
      1R          6B       9R
                         8B   10B
              >>>>>
                 7B
            5B       9B
        2B     6B  8B  10B
      1R
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_RED);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n2, left, n1, top);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n7, left, n5, top);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  bn_tree_t s = bn_create_tree(to_bn(n7));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Cây sau khi xóa 3");
  return 0;
}

int main() {
  CHECK_MSG(delete_node_one_left_child() == 0, "Sai ở delete_node_one_left_child()");
  CHECK_MSG(delete_node_one_right_child() == 0, "Sai ở delete_node_one_right_child()");
  CHECK_MSG(delete_red_node_no_child() == 0, "Sai ở delete_red_node_no_child()");
  CHECK_MSG(delete_black_node_no_child_red_top_black_sibling1() == 0,
        "Sai ở delete_black_node_no_child_red_top_black_sibling1()");
  CHECK_MSG(delete_black_node_no_child_red_top_black_sibling2() == 0,
        "Sai ở delete_black_node_no_child_red_top_black_sibling2()");
  CHECK_MSG(delete_black_node_no_child_red_sibling_black_top() == 0,
        "Sai ở delete_black_node_no_child_red_sibling_black_top()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_black_top1() == 0,
        "Sai ở delete_black_node_no_child_black_sibling_black_top1()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_black_top2() == 0,
        "Sai ở delete_black_node_no_child_black_sibling_black_top2()");
  return 0;
}