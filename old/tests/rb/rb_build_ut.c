#include "rbi.h"
#include "rbi_helper.h"
#include "tests/base/utils.h"

int main() {
  struct grbtree *t = rbi_create_tree(NULL);
  rbi_insert(t, 2);
  /*
    2B
  */
  struct bnnode *nd2 = bn_tree(t)->root;
  CHECK_MSG(rbi_value(bn_tree(t)->root) == 2, "Nút gốc == 2");
  CHECK_MSG(rb_is_black(bn_tree(t)->root), "Nút gốc là nút đen.");
  CHECK_MSG(lnr_match_value(t, (int []){2}, 1), "Giá trị tăng dần 2");
  rbi_insert(t, 1);
  /*
        2B
      1R
  */
  struct bnnode *nd1 = bn_tree(t)->root->left;
  CHECK_MSG(rbi_value(nd1) == 1, "Nút trái == 1");
  CHECK_MSG(rb_is_red(nd1), "Nút trái là nút đỏ");
  CHECK_MSG(lnr_match_value(t, (int []){1, 2}, 2), "Giá trị tăng dần 1 2");

  rbi_insert(t, 4);
  /*
        2B
      1R  4R
  */
  struct bnnode *nd4 = bn_tree(t)->root->right;
  CHECK_MSG(rbi_value(nd4) == 4, "Nút phải == 4");
  CHECK_MSG(rb_is_red(nd4), "Nút phải là nút đỏ");
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 4}, 3),
            "Giá trị tăng dần 1 2 4");

  rbi_insert(t, 5);
  /*
        2B                           2B
      1R  4R      --Tô lại mầu-->  1B  4B
           5R                           5R
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 4, 5}, 4),
            "Giá trị tăng dần 1 2 4 5");
  struct bnnode *nd5 = nd4->right;
  CHECK_MSG(rbi_value(nd5) == 5, "nd5 == 5");
  CHECK_MSG(rb_is_black(nd1), "Nút 1 đen");
  CHECK_MSG(rb_is_black(nd4), "Nút 4 đen");
  CHECK_MSG(rb_is_red(nd5), "Nút 5 đỏ");

  rbi_insert(t, 9);
  /*
        2B                           2B
      1R  4B      --Xoay trái-->  1B   5B
           5R                        4R   9R
            9R
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 4, 5, 9}, 5),
            "Giá trị tăng dần 1 2 4 5 9");
  struct bnnode *nd9 = nd5->right;
  CHECK_MSG(rbi_value(nd9) == 9, "nd9 == 9");
  CHECK_MSG(rb_is_red(nd9), "Nút 9 đỏ");
  CHECK_MSG(rb_is_red(nd4), "Nút 4 đỏ");
  CHECK_MSG(nd4->top == nd5, "top của nd4 bằng nd5");
  CHECK_MSG(rb_is_black(nd5), "Nút 5 đen");
  CHECK_MSG(nd5->left == nd4, "left của nd5 bằng nd4");

  rbi_insert(t, 3);
  /*
        2B                            2B
     1B   5B     --> Tô lại mầu     1B  5R
        4R   9R                       4B 9B
       3R                            3R
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 3, 4, 5, 9}, 6),
            "Giá trị tăng dần 1 2 3 4 5 9");
  struct bnnode *nd3 = nd4->left;
  CHECK_MSG(rbi_value(nd3) == 3, "nd3 == 3");
  CHECK_MSG(rb_is_red(nd3), "Nút 3 đỏ");
  CHECK_MSG(nd3->top == nd4, "top của nd3 bằng nd4");
  CHECK_MSG(rb_is_black(nd4), "Nút 4 đen");
  CHECK_MSG(nd4->top == nd5, "top của nd4 bằng nd5");
  CHECK_MSG(rb_is_red(nd5), "Nút 5 đỏ");
  CHECK_MSG(nd5->right == nd9, "right của nd5 bằng nd9");

  rbi_insert(t, 6);
  /*
        2B                            2B
     1B   5R     -------->          1B  5R
        4B   9B                       4B  9B
       3R                            3R  6R
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 3, 4, 5, 6, 9}, 7),
            "Giá trị tăng dần 1 2 3 4 5 6 9");
  struct bnnode *nd6 = nd9->left;
  CHECK_MSG(rbi_value(nd6) == 6, "nd6 == 6");
  CHECK_MSG(rb_is_red(nd6), "Nút 6 đỏ");
  CHECK_MSG(nd6->top == nd9, "top của nd6 bằng nd9");

  rbi_insert(t, 7);
  /*
     2B                     2B                            2B
  1B   5R     -Xoay trái  1B   5R    Xoay phải (tô) --> 1B  5R
     4B   9B                4B    9B                       4B 7B
    3R   6R               3R    7R                        3R 6R 9R
           7R                  6B
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 3, 4, 5, 6, 7, 9}, 8),
            "Giá trị tăng dần 1 2 3 4 5 6 7 9");
  struct bnnode *nd7 = nd5->right;
  CHECK_MSG(rbi_value(nd7) == 7, "nd7 == 7");
  CHECK_MSG(rb_is_black(nd7), "Nút 7 đen");
  CHECK_MSG(nd7->left == nd6, "left của nd7 bằng nd6");
  CHECK_MSG(nd7->right == nd9, "right của nd7 bằng nd9");
  CHECK_MSG(nd7->top == nd5, "top của nd7 bằng nd5");
  CHECK_MSG(rb_is_red(nd5), "Nút 5 đỏ");
  CHECK_MSG(nd5->right == nd7, "right của nd5 bằng nd7");
  CHECK_MSG(rb_is_red(nd6), "Nút 6 đỏ");
  CHECK_MSG(nd6->top == nd7, "top của nd6 bằng nd7");
  CHECK_MSG(rb_is_red(nd9), "Nút 9 đỏ");
  CHECK_MSG(nd9->top == nd7, "top của nd9 bằng nd7");

  rbi_insert(t, 15);
  /*
      2B                                      2B
    1B   5R                                 1B    5R
       4B  7B  -- Tô lại mầu thành             4B    7R
      3R  6R 9R                               3R    6R 9B
              15R                                       15R
    Hai nút đỏ liền nhau 5R-7R. Anh/em họ của 7R là nút đen, vì vậy chúng ta cần xoay. 7 là con phải của 5, 5 là con phải của 2 vì vậy chúng ta xoay trái và tô lại mầu, kết quả thu được là:
            5B
      2R          7R
    1B  4B      6B  9B
       3R            15R
  */
  CHECK_MSG(lnr_match_value(t, (int []){1, 2, 3, 4, 5, 6, 7, 9, 15}, 9),
            "Giá trị tăng dần 1 2 3 4 5 6 7 9 15");
  struct bnnode *nd15 = nd9->right;
  CHECK_MSG(rbi_value(nd15) == 15, "nd15 == 15");
  CHECK_MSG(rb_is_red(nd15), "Nút 15 là nút đỏ");
  CHECK_MSG(nd15->top == nd9, "top của nd15 bằng nd9");
  CHECK_MSG(rb_is_black(nd9), "Nút 9 đen");
  CHECK_MSG(nd9->right == nd15, "right của nd9 bằng nd15");
  CHECK_MSG(nd9->top == nd7, "top của nd9 bằng nd7");
  CHECK_MSG(rb_is_black(nd6), "Nút 6 đen");
  CHECK_MSG(rb_is_red(nd7), "Nút 7 là nút đỏ");
  CHECK_MSG(nd7->left == nd6, "left của nd7 bằng nd6");
  CHECK_MSG(nd7->right == nd9, "right của nd7 bằng nd9");
  CHECK_MSG(rbi_value(bn_tree(t)->root) == 5, "t->root == 5");
  CHECK_MSG(nd5->top == NULL, "top của nd5 bằng NULL");
  CHECK_MSG(nd5->left == nd2, "left của nd5 bằng nd2");
  CHECK_MSG(nd5->right == nd7, "right của nd5 bằng nd7");
  CHECK_MSG(rb_is_red(nd2), "Nút 2 là nút đỏ");
  CHECK_MSG(nd2->top == nd5, "top của nd2 bằng nd5");
  CHECK_MSG(nd2->left == nd1, "left của nd2 bằng nd1");
  CHECK_MSG(nd2->right == nd4, "right của nd2 bằng nd4");
  CHECK_MSG(rb_is_black(nd4), "Nút 4 là nút đen");
  CHECK_MSG(nd4->top == nd2, "top của nd4 bằng nd2");
  CHECK_MSG(nd4->left == nd3, "left của nd4 bằng nd3");
  CHECK_MSG(nd4->right == NULL, "right của nd4 bằng NULL");

  printf("RB Build test OK\n");

  rbi_free_tree(t);
  return 0;
}
