#include "rbi.h"
#include "rbi_helper.h"
#include "tests/base/utils.h"

int test_delete_root() {
  struct grbtree *t = rbi_create_tree(NULL);
  struct grbnode *root = rbi_create_node(5);
  bn_tree(t)->root = bn_node(root);
  rb_set_black(root);
  struct grbnode *lc = rbi_create_node(3);
  rb_set_red(lc);
  struct grbnode *rc = rbi_create_node(8);
  rb_set_red(lc);
  bn_connect2(root, left, lc, top);
  bn_connect2(root, right, rc, top);
  /*
     Xóa    5B     Thu được   8B
          3R  8R             3R
  */
  rbi_delete(t, 5);
  CHECK_MSG(lnr_match_value(t, (int []){3, 8}, 2), "Giá trị tăng dần 3 8");
  struct bnnode *n8 = bn_tree(t)->root;
  CHECK_MSG(rbi_value(n8) == 8, "n8 == 8");
  CHECK_MSG(rb_is_black(n8), "n8 là nút đen");

  struct bnnode *n3 = bn_tree(t)->root->left;
  CHECK_MSG(rbi_value(n3) == 3, "n3 == 3");
  CHECK_MSG(rb_is_red(n3), "n3 là nút đỏ");
  CHECK_MSG(n3->top == n8, "top của n3 == n8");
  rbi_free_tree(t);
  return 0;
}

int test_delete_root_2nodes() {
  struct grbnode *r = rbi_create_node(5);
  rb_set_black(r);
  struct grbnode *rc = rbi_create_node(8);
  rb_set_red(rc);
  bn_connect2(r, right, rc, top);
  struct grbtree *t = rbi_create_tree(bn_node(r));
  rbi_delete(t, 5);
  /*
     Xóa -> 5B     Thu được   8B
              8R
  */
  CHECK_MSG(lnr_match_value(t, (int[]){8}, 1), "Giá trị tăng dần 8");
  CHECK_MSG(rbi_value(bn_tree(t)->root) == 8, "Gốc bằng 8");
  CHECK_MSG(rb_is_black(bn_tree(t)->root), "Nút gốc là nút đen");

  CHECK_MSG(rbi_delete(t, 6) == 0, "Hàm xóa nút không có trả về NULL");

  rbi_delete(t, 8);
  CHECK_MSG(bn_tree(t)->root == NULL, "Xóa nút 1 gốc cây thành rỗng.");
  rbi_free_tree(t);
  return 0;
}

int test_delete_single_deep_child() {
  struct grbnode *r = rbi_create_node(20);
  struct grbtree *t = rbi_create_tree(bn_node(r));
  rb_set_black(r);

  // Cây con trái
  struct grbnode *n10 = rbi_create_node(10);
  rb_set_black(n10);
  struct grbnode *n5 = rbi_create_node(5);
  rb_set_red(n5);
  struct grbnode *n15 = rbi_create_node(15);
  rb_set_red(n15);
  bn_connect2(n5, top, n10, left);
  bn_connect2(n15, top, n10, right);

  // Cây con phải
  struct grbnode *n38 = rbi_create_node(38);
  rb_set_red(n38);
  struct grbnode *n28 = rbi_create_node(28);
  rb_set_black(n28);
  struct grbnode *n48 = rbi_create_node(48);
  rb_set_black(n48);
  bn_connect2(n28, top, n38, left);
  bn_connect2(n48, top, n38, right);

  // Cây con của n28
  struct grbnode *n23 = rbi_create_node(23);
  rb_set_red(n23);
  struct grbnode *n29 = rbi_create_node(29);
  rb_set_red(n29);
  bn_connect2(n23, top, n28, left);
  bn_connect2(n29, top, n28, right);

  // Cây con của n48
  struct grbnode *n41 = rbi_create_node(41);
  rb_set_red(n41);
  struct grbnode *n49 = rbi_create_node(49);
  rb_set_red(n49);
  bn_connect2(n41, top, n48, left);
  bn_connect2(n49, top, n48, right);

  bn_connect2(n10, top, r, left);
  bn_connect2(n38, top, r, right);
  /*
                   20B
       10B                  38R
    5R     15R       28B         48B
                  23R  29R     41R   49R <-- Xóa
  */
  rbi_delete(t, 49);

  // Xóa nút đỏ không con: - dễ, không cần tái cân bằng cây
  CHECK_MSG(lnr_match_attrib(t,
      (struct attrib[]){{5, 0}, {10, 1}, {15, 0}, {20, 1}, {23, 0}, {28, 1}, {29, 0},
                             {38, 0}, {41, 0}, {48, 1}}, 10),
      "Thuộc tính của các nút sau khi xóa 49.");

  /*
                   20B
       10B                  38R
    5R     15R       28B         48B  <-- Xóa
                  23R  29R     41R
  */
  rbi_delete(t, 48);

  // Nút có 1 con thì nó phải là nút đen và con của nó phải là nút đỏ
  // - Trường hợp dễ: thay thế nút con vào vị trí nút cha + tô lại mầu
  //   nút con thành đen
  CHECK_MSG(lnr_match_attrib(t,
      (struct attrib[]){{5, 0}, {10, 1}, {15, 0}, {20, 1}, {23, 0}, {28, 1}, {29, 0},
                             {38, 0}, {41, 1}}, 9),
      "Thuộc tính của các nút sau khi xóa 48.");

  /*
                   20B
       10B                  38R
    5R     15R       28B         41B  <-- Xóa
                  23R  29R

                     20B
       10B                     38R (parent)  <-- Xoay phải
    5R     15R       28B (sibling)  (node)
                  23R  29R
    --- sibling là nút đen và có con trái --> trường hợp 4: xoay phải
    ở parent và lật mầu các nút: 28 lấy mầu cũ của 38, 23 và 38 thành
    đen --
                     20B
       10B                     28R
    5R     15R            23B       38B
                                 29R


  */
  rbi_delete(t, 41);

  // Xóa nút đen không con -> tái cân bằng cây
  CHECK_MSG(lnr_match_attrib(t,
      (struct attrib[]){{5, 0}, {10, 1}, {15, 0}, {20, 1}, {23, 1},
              {28, 0}, {29, 0}, {38, 1}}, 9),
      "Thuộc tính của các nút sau khi xóa 41.");
  CHECK_MSG(bn_node(n28) == bn_tree(t)->root->right, "n28 là con phải của gốc");
  CHECK_MSG(bn_node(n28)->right == bn_node(n38),
        "n38 là con phải của n2");
  CHECK_MSG(bn_node(n29) == bn_node(n38)->left,
        "n29 là con trái của n38");
  rbi_free_tree(t);
  return 0;
}

int test_delete_red_node_red_successor() {
  struct grbnode *r = rbi_create_node(10);
  rb_set_black(r);
  struct grbtree *t = rbi_create_tree(bn_node(r));

  //  Nhánh trái
  struct grbnode *n5 = rbi_create_node(5);
  rb_set_red(n5);
  struct grbnode *m5 = rbi_create_node(-5);
  rb_set_black(m5);
  bn_connect2(m5, top, n5, left);
  struct grbnode *n7 = rbi_create_node(7);
  rb_set_black(n7);
  bn_connect2(n7, top, n5, right);

  // Nhánh phải
  struct grbnode *n35 = rbi_create_node(35);
  rb_set_red(n35);
  struct grbnode *n20 = rbi_create_node(20);
  rb_set_black(n20);
  bn_connect2(n20, top, n35, left);
  struct grbnode *n38 = rbi_create_node(38);
  rb_set_black(n38);
  bn_connect2(n38, top, n35, right);

  struct grbnode *n36 = rbi_create_node(36);
  rb_set_red(n36);
  bn_connect2(n36, top, n38, left);

  bn_connect2(n5, top, r, left);
  bn_connect2(n35, top, r, right);

  /*
            10B
         5R       35R         <-- Xóa
      -5B  7B  20B   38B
                    36R
    ---- Thu được -------
            10B
         5R       36R
      -5B  7B  20B   38B
  */
  rbi_delete(t, 35);
  CHECK_MSG(lnr_match_attrib(t, (struct attrib[]){{-5, 1}, {5, 0}, {7, 1},
            {10, 1}, {20, 1}, {36, 0}, {38, 1}}, 7), "Thuộc tính sau khi xóa 35");

  rbi_free_tree(t);
  return 0;
}

int test_delete_black_node_black_successor_no_child() {
  struct grbnode *root = rbi_create_node(10);
  rb_set_black(root);
  struct grbtree *t = rbi_create_tree(bn_node(root));
  struct grbnode *m10 = rbi_create_node(-10);
  rb_set_black(m10);

  // Cây con trái
  bn_connect2(m10, top, root, left);

  // Cây con phải
  struct grbnode *n30 = rbi_create_node(30);
  rb_set_red(n30);
  bn_connect2(n30, top, root, right);
  struct grbnode *n20 = rbi_create_node(20);
  rb_set_black(n20);
  bn_connect2(n20, top, n30, left);
  struct grbnode *n38 = rbi_create_node(38);
  rb_set_black(n38);
  bn_connect2(n38, top, n30, right);

  /*
                        10B  <-- Xóa
                 -10B     30R
     Nút liền sau -->   20B  38B
     -------Kết quả---->
                        20B
                 -10B     30B
                              38R

  */
  rbi_delete(t, 10);
  CHECK_MSG(lnr_match_attrib(t, (struct attrib[]){{-10, 1}, {20, 1},
      {30, 1}, {38, 0}}, 4), "Thuộc tính sau khi xóa 10");
  rbi_free_tree(t);
  return 0;
}

int main() {
  CHECK_MSG(test_delete_root() == 0, "lỗi ở test_delete_root");
  CHECK_MSG(test_delete_root_2nodes() == 0, "lỗi ở test_delete_root_2nodes");
  CHECK_MSG(test_delete_single_deep_child() == 0, "lỗi ở test_delete_single_deep_child");
  CHECK_MSG(test_delete_red_node_red_successor() == 0, "lỗi ở test_delete_red_node_red_successor");
  CHECK_MSG(test_delete_black_node_black_successor_no_child() == 0,
        "lỗi ở test_delete_black_node_black_successor_no_child");
  TEST_OK();
  return 0;
}