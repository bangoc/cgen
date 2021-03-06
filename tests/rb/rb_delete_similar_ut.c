#include "tests/rb/rbi.h"
#include "tests/base/helpers.h"
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

bn_tree_t make_tree3() {
  /*
                  5B
         2B               7B
      1B     3B       6B      9R
                4R          8B   10B
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n4  = rbi_create_color_node(4,  RB_RED);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_RED);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n3, right, n4, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  bn_tree_t t = bn_create_tree(to_bn(n5));
  return t;
}

bn_tree_t make_tree4() {
  /*
                  5B
         2B               7B
      1B     3B       6B      9B
                            8R
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
  /* Sau khi x??a 3
           5B
       2B        6B
                     8R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 3 trong c??y 1");
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
  /* Sau khi x??a 6
           5B
       3B        8B
     2R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 6 trong c??y 1");
  return 0;
}

int delete_red_node_no_child() {
  /*
  Tr?????ng h???p ????n gi???n, c??c n??t c??n l???i kh??ng thay ?????i
  */
  bn_tree_t t = make_tree1();
  rbi_delete(t, 2);

  /*
    C??y sau khi x??a 2
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 2 trong c??y 1");

  rbi_delete(t, 8);

  /*
    C??y sau khi x??a 8
           5B
      3B          6B
  */
  bn_connect1(n6, right, NULL_PTR);
  bn_connect1(n8, top, NULL_PTR);

  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a th??m n??t 8 trong c??y 1");
  return 0;
}

int delete_black_node_no_child_red_top_black_sibling1() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 8);
  /* C??y sau khi x??a 8:
               5B
         2B           7B
      1B     3B   6B      9B    <-- top (?????nh)
                             10R  <-- sibling (?????i x???ng)
                      ?????o m???u n??t ?????nh v?? n??t ?????i x???ng
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 8 trong c??y 2");
  return 0;
}

int delete_black_node_no_child_red_top_black_sibling2() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 10);
  /*
               5B
         2B           7B
      1B     3B   6B      9B  <-- n??t ?????nh
                        8R  <-- n??t ?????i x???ng
                        ?????o m???u n??t ?????nh v?? n??t ?????i x???ng
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 8 trong c??y 2");
  return 0;
}

int delete_black_node_no_child_red_sibling_black_top() {
  bn_tree_t t = make_tree2();
  rbi_delete(t, 6);
  /*
    Sau khi x??a 6:
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "X??a n??t 6 trong c??y 2");
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "C??y sau khi x??a 1");
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
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "C??y sau khi x??a 3");
  return 0;
}

int delete_black_node_no_child_black_sibling_red_child_black_top() {
  bn_tree_t t = make_tree3();
  rbi_delete(t, 1);
  /* C??y sau khi x??a 1
                5B
     p-> 2B               7B
      s->   3B       6B      9R
          Sc->  4R        8B   10B
          >>>>>>>>>>
                5B
        3B               7B
     2B     4B       6B      9R
                          8B   10B
  */
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n4  = rbi_create_color_node(4,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n6  = rbi_create_color_node(6,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_RED);
  rbi_node_t n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n3, left, n2, top);
  bn_connect2(n3, right, n4, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "C??y sau khi x??a 1");
  return 0;
}

int delete_black_node_no_child_black_sibling_with_black_top_red_left_child() {
  bn_tree_t t = make_tree4();
  rbi_delete(t, 6);

  /* Sau khi x??a 6:
                  5B
         2B               7B
      1B     3B   n-> 6B      9B
                            8R
          >>>>>>>>>>
                  5B
         2B               8B
      1B     3B       7B      9B
  */
  rbi_node_t n1  = rbi_create_color_node(1,  RB_BLACK);
  rbi_node_t n2  = rbi_create_color_node(2,  RB_BLACK);
  rbi_node_t n3  = rbi_create_color_node(3,  RB_BLACK);
  rbi_node_t n5  = rbi_create_color_node(5,  RB_BLACK);
  rbi_node_t n7  = rbi_create_color_node(7,  RB_BLACK);
  rbi_node_t n8  = rbi_create_color_node(8,  RB_BLACK);
  rbi_node_t n9  = rbi_create_color_node(9,  RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n8, top);
  bn_connect2(n8, left, n7, top);
  bn_connect2(n8, right, n9, top);
  bn_tree_t s = bn_create_tree(to_bn(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Sau khi x??a 6");
  return 0;
}

int builder() {
  bn_tree_t t1 = make_tree1();
  bn_tree_t t2 = make_tree2();
  bn_tree_t t3 = make_tree3();
  bn_tree_t t4 = make_tree4();
  CHECK_MSG(rb_is_valid(t1), "C??y 1");
  CHECK_MSG(rb_is_valid(t2), "C??y 2");
  CHECK_MSG(rb_is_valid(t3), "C??y 3");
  CHECK_MSG(rb_is_valid(t4), "C??y 4");
  return 0;
}

int main() {
  CHECK_MSG(builder() == 0, "builder()");
  CHECK_MSG(delete_node_one_left_child() == 0, "Sai ??? delete_node_one_left_child()");
  CHECK_MSG(delete_node_one_right_child() == 0, "Sai ??? delete_node_one_right_child()");
  CHECK_MSG(delete_red_node_no_child() == 0, "Sai ??? delete_red_node_no_child()");
  CHECK_MSG(delete_black_node_no_child_red_top_black_sibling1() == 0,
        "Sai ??? delete_black_node_no_child_red_top_black_sibling1()");
  CHECK_MSG(delete_black_node_no_child_red_top_black_sibling2() == 0,
        "Sai ??? delete_black_node_no_child_red_top_black_sibling2()");
  CHECK_MSG(delete_black_node_no_child_red_sibling_black_top() == 0,
        "Sai ??? delete_black_node_no_child_red_sibling_black_top()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_black_top1() == 0,
        "Sai ??? delete_black_node_no_child_black_sibling_black_top1()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_black_top2() == 0,
        "Sai ??? delete_black_node_no_child_black_sibling_black_top2()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_red_child_black_top() == 0,
        "delete_black_node_no_child_black_sibling_red_child_black_top()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_with_black_top_red_left_child() == 0,
        "delete_black_node_no_child_black_sibling_with_black_top_red_left_child()");
  return 0;
}
