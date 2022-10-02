#include "tests/rb/rbi.h"
#include "tests/base/helpers.h"
#include "tests/base/utils.h"

struct bntree *make_tree1() {
  struct grbnode *n2 = rbi_create_color_node(2, RB_RED);
  struct grbnode *n3 = rbi_create_color_node(3, RB_BLACK);
  struct grbnode *n5 = rbi_create_color_node(5, RB_BLACK);
  struct grbnode *n6 = rbi_create_color_node(6, RB_BLACK);
  struct grbnode *n8 = rbi_create_color_node(8, RB_RED);
  /*
           5B
      3B          6B
    2R               8R
  */
  bn_connect2(n3, left, n2, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  return bn_tree(rbi_create_tree(bn_node(n5)));
}

struct bntree *make_tree2() {
  /*
               5B
         2B           7B
      1B     3B   6B      9R
                        8B   10B
  */
  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_RED);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  return bn_tree(rbi_create_tree(bn_node(n5)));
}

struct bntree *make_tree3() {
  /*
                  5B
         2B               7B
      1B     3B       6B      9R
                4R          8B   10B
  */
  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n4  = rbi_create_color_node(4,  RB_RED);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_RED);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n3, right, n4, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  return bn_tree(rbi_create_tree(bn_node(n5)));
}

struct bntree *make_tree4() {
  /*
                  5B
         2B               7B
      1B     3B       6B      9B
                            8R
  */
  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_RED);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  return bn_tree(rbi_create_tree(bn_node(n5)));
}

int delete_node_one_left_child() {
  struct bntree *t = make_tree1();

  struct grbnode *n2 = rbi_create_color_node(2, RB_BLACK);
  struct grbnode *n5 = rbi_create_color_node(5, RB_BLACK);
  struct grbnode *n6 = rbi_create_color_node(6, RB_BLACK);
  struct grbnode *n8 = rbi_create_color_node(8, RB_RED);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));

  rbi_delete(t, 3);
  /* Sau khi xóa 3
           5B
       2B        6B
                     8R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 3 trong cây 1");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_node_one_right_child() {
  struct bntree *t = make_tree1();

  struct grbnode *n2 = rbi_create_color_node(2, RB_RED);
  struct grbnode *n3 = rbi_create_color_node(3, RB_BLACK);
  struct grbnode *n5 = rbi_create_color_node(5, RB_BLACK);
  struct grbnode *n8 = rbi_create_color_node(8, RB_BLACK);
  bn_connect2(n3, left, n2, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n8, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));

  rbi_delete(t, 6);
  /* Sau khi xóa 6
           5B
       3B        8B
     2R
  */
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 6 trong cây 1");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_red_node_no_child() {
  /*
  Trường hợp đơn giản, các nút còn lại không thay đổi
  */
  struct bntree *t = make_tree1();
  rbi_delete(t, 2);

  /*
    Cây sau khi xóa 2
           5B
      3B          6B
                     8R
  */
  struct grbnode *n3 = rbi_create_color_node(3, RB_BLACK);
  struct grbnode *n5 = rbi_create_color_node(5, RB_BLACK);
  struct grbnode *n6 = rbi_create_color_node(6, RB_BLACK);
  struct grbnode *n8 = rbi_create_color_node(8, RB_RED);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n6, right, n8, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 2 trong cây 1");

  rbi_delete(t, 8);

  /*
    Cây sau khi xóa 8
           5B
      3B          6B
  */
  bn_connect1(n6, right, NULL);
  bn_connect1(n8, top, NULL);
  free(n8);

  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa thêm nút 8 trong cây 1");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_red_top_black_sibling1() {
  struct bntree *t = make_tree2();
  rbi_delete(t, 8);
  /* Cây sau khi xóa 8:
               5B
         2B           7B
      1B     3B   6B      9B    <-- top (đỉnh)
                             10R  <-- sibling (đối xứng)
                      Đảo mầu nút đỉnh và nút đối xứng
  */
  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  struct grbnode *n10 = rbi_create_color_node(10, RB_RED);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, right, n10, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 8 trong cây 2");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_red_top_black_sibling2() {
  struct bntree *t = make_tree2();
  rbi_delete(t, 10);

  /*
               5B
         2B           7B
      1B     3B   6B      9B  <-- nút đỉnh
                        8R  <-- nút đối xứng
                        Đảo mầu nút đỉnh và nút đối xứng
  */

  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_RED);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 8 trong cây 2");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_red_sibling_black_top() {
  struct bntree *t = make_tree2();
  rbi_delete(t, 6);

  /*
    Sau khi xóa 6:
               5B
         2B           9B
      1B     3B   7B      10B
                     8R

  */

  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_RED);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n9, top);
  bn_connect2(n9, left, n7, top);
  bn_connect2(n9, right, n10, top);
  bn_connect2(n7, right, n8, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node) == 1, "Xóa nút 6 trong cây 2");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_black_sibling_black_top1() {
  struct bntree *t = make_tree2();
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

  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_RED);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n7, left, n5, top);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  struct grbtree *s = rbi_create_tree(bn_node(n7));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Cây sau khi xóa 1");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_black_sibling_black_top2() {
  struct bntree *t = make_tree2();
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
  struct grbnode *n1  = rbi_create_color_node(1,  RB_RED);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n2, left, n1, top);
  bn_connect2(n5, left, n2, top);
  bn_connect2(n5, right, n6, top);
  bn_connect2(n7, left, n5, top);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  struct grbtree *s = rbi_create_tree(bn_node(n7));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Cây sau khi xóa 3");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_black_sibling_red_child_black_top() {
  struct bntree *t = make_tree3();
  rbi_delete(t, 1);
  /* Cây sau khi xóa 1
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
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n4  = rbi_create_color_node(4,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n6  = rbi_create_color_node(6,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_RED);
  struct grbnode *n10 = rbi_create_color_node(10, RB_BLACK);
  bn_connect2(n3, left, n2, top);
  bn_connect2(n3, right, n4, top);
  bn_connect2(n5, left, n3, top);
  bn_connect2(n5, right, n7, top);
  bn_connect2(n6, top, n7, left);
  bn_connect2(n7, right, n9, top);
  bn_connect2(n9, left, n8, top);
  bn_connect2(n9, right, n10, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Cây sau khi xóa 1");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int delete_black_node_no_child_black_sibling_with_black_top_red_left_child() {
  struct bntree *t = make_tree4();
  rbi_delete(t, 6);

  /* Sau khi xóa 6:
                  5B
         2B               7B
      1B     3B   n-> 6B      9B
                            8R
          >>>>>>>>>>
                  5B
         2B               8B
      1B     3B       7B      9B
  */
  struct grbnode *n1  = rbi_create_color_node(1,  RB_BLACK);
  struct grbnode *n2  = rbi_create_color_node(2,  RB_BLACK);
  struct grbnode *n3  = rbi_create_color_node(3,  RB_BLACK);
  struct grbnode *n5  = rbi_create_color_node(5,  RB_BLACK);
  struct grbnode *n7  = rbi_create_color_node(7,  RB_BLACK);
  struct grbnode *n8  = rbi_create_color_node(8,  RB_BLACK);
  struct grbnode *n9  = rbi_create_color_node(9,  RB_BLACK);
  bn_connect2(n1, top, n2, left);
  bn_connect2(n2, right, n3, top);
  bn_connect2(n2, top, n5, left);
  bn_connect2(n5, right, n8, top);
  bn_connect2(n8, left, n7, top);
  bn_connect2(n8, right, n9, top);
  struct grbtree *s = rbi_create_tree(bn_node(n5));
  CHECK_MSG(bn_similar_tree(t, s, rbi_similar_node), "Sau khi xóa 6");
  rbi_free_tree(t);
  rbi_free_tree(s);
  return 0;
}

int builder() {
  struct bntree *t1 = make_tree1();
  struct bntree *t2 = make_tree2();
  struct bntree *t3 = make_tree3();
  struct bntree *t4 = make_tree4();
  CHECK_MSG(rb_is_valid(t1), "Cây 1");
  CHECK_MSG(rb_is_valid(t2), "Cây 2");
  CHECK_MSG(rb_is_valid(t3), "Cây 3");
  CHECK_MSG(rb_is_valid(t4), "Cây 4");
  rbi_free_tree(t1);
  rbi_free_tree(t2);
  rbi_free_tree(t3);
  rbi_free_tree(t4);
  return 0;
}

int main() {
  CHECK_MSG(builder() == 0, "builder()");
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
  CHECK_MSG(delete_black_node_no_child_black_sibling_red_child_black_top() == 0,
        "delete_black_node_no_child_black_sibling_red_child_black_top()");
  CHECK_MSG(delete_black_node_no_child_black_sibling_with_black_top_red_left_child() == 0,
        "delete_black_node_no_child_black_sibling_with_black_top_red_left_child()");
  TEST_OK();
  return 0;
}
