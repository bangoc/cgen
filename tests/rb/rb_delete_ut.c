#include "rbi.h"
#include "rbi_helper.h"
#include "tests/base/utils.h"

#define bn_connect1(n1, link, n2) to_bn(n1)->link = to_bn(n2)
#define bn_connect2(n1, link1, n2, link2) bn_connect1(n1, link1, n2); \
    bn_connect1(n2, link2, n1)


int test_delete_root() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_node_t root = rbi_create_node(5);
  t->root = to_bn(root);
  rb_set_black(root);
  rbi_node_t lc = rbi_create_node(3);
  rb_set_red(lc);
  rbi_node_t rc = rbi_create_node(8);
  rb_set_red(lc);
  bn_connect2(root, left, lc, top);
  bn_connect2(root, right, rc, top);
  /*
     Xóa    5B     Thu được   8B
          3R  8R             3R
  */
  free(rbi_delete(t, 5));
  CHECK_MSG(lnr_match_value(t, (int []){3, 8}, 2), "Giá trị tăng dần 3 8");
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
  rb_set_black(r);
  rbi_node_t rc = rbi_create_node(8);
  rb_set_red(rc);
  bn_connect2(r, right, rc, top);
  bn_tree_t t = bn_create_tree(to_bn(r));
  free(rbi_delete(t, 5));
  /*
     Xóa -> 5B     Thu được   8B
              8R
  */
  CHECK_MSG(lnr_match_value(t, (int[]){8}, 1), "Giá trị tăng dần 8");
  CHECK_MSG(rbi_value(t->root) == 8, "Gốc bằng 8");
  CHECK_MSG(rb_is_black(t->root), "Nút gốc là nút đen");

  CHECK_MSG(rbi_delete(t, 6) == NULL_PTR, "Hàm xóa nút không có trả về NULL");

  free(rbi_delete(t, 8));
  CHECK_MSG(t->root == NULL_PTR, "Xóa nút 1 gốc cây thành rỗng.");
  return 0;
}

int test_delete_single_deep_child() {
  rbi_node_t r = rbi_create_node(20);
  bn_tree_t t = bn_create_tree(to_bn(r));
  rb_set_black(r);

  // Cây con trái
  rbi_node_t n10 = rbi_create_node(10);
  rb_set_black(n10);
  rbi_node_t n5 = rbi_create_node(5);
  rb_set_red(n5);
  rbi_node_t n15 = rbi_create_node(15);
  rb_set_red(n15);
  bn_connect2(n5, top, n10, left);
  bn_connect2(n15, top, n10, right);

  // Cây con phải
  rbi_node_t n38 = rbi_create_node(38);
  rb_set_red(n38);
  rbi_node_t n28 = rbi_create_node(28);
  rb_set_black(n28);
  rbi_node_t n48 = rbi_create_node(48);
  rb_set_black(n48);
  bn_connect2(n28, top, n38, left);
  bn_connect2(n48, top, n38, right);

  // Cây con của n28
  rbi_node_t n23 = rbi_create_node(23);
  rb_set_red(n23);
  rbi_node_t n29 = rbi_create_node(29);
  rb_set_red(n29);
  bn_connect2(n23, top, n28, left);
  bn_connect2(n29, top, n28, right);

  // Cây con của n48
  rbi_node_t n41 = rbi_create_node(41);
  rb_set_red(n41);
  rbi_node_t n49 = rbi_create_node(49);
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
  free(rbi_delete(t, 49));

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
  free(rbi_delete(t, 48));

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
  free(rbi_delete(t, 41));

  // Xóa nút đen không con -> tái cân bằng cây
  CHECK_MSG(lnr_match_attrib(t,
      (struct attrib[]){{5, 0}, {10, 1}, {15, 0}, {20, 1}, {23, 1},
              {28, 0}, {29, 0}, {38, 1}}, 9),
      "Thuộc tính của các nút sau khi xóa 41.");
  CHECK_MSG(to_bn(n28) == t->root->right, "n28 là con phải của gốc");
  CHECK_MSG(to_bn(n28)->right == to_bn(n38),
        "n38 là con phải của n2");
  CHECK_MSG(to_bn(n29) == to_bn(n38)->left,
        "n29 là con trái của n38");
  return 0;
}

int test_delete_red_node_red_successor() {
  rbi_node_t r = rbi_create_node(10);
  rb_set_black(r);
  bn_tree_t t = bn_create_tree(to_bn(r));

  //  Nhánh trái
  rbi_node_t n5 = rbi_create_node(5);
  rb_set_red(n5);
  rbi_node_t m5 = rbi_create_node(-5);
  rb_set_black(m5);
  bn_connect2(m5, top, n5, left);
  rbi_node_t n7 = rbi_create_node(7);
  rb_set_black(n7);
  bn_connect2(n7, top, n5, right);

  // Nhánh phải
  rbi_node_t n35 = rbi_create_node(35);
  rb_set_red(n35);
  rbi_node_t n20 = rbi_create_node(20);
  rb_set_black(n20);
  bn_connect2(n20, top, n35, left);
  rbi_node_t n38 = rbi_create_node(38);
  rb_set_black(n38);
  bn_connect2(n38, top, n35, right);

  rbi_node_t n36 = rbi_create_node(36);
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
  free(rbi_delete(t, 35));
  CHECK_MSG(lnr_match_attrib(t, (struct attrib[]){{-5, 1}, {5, 0}, {7, 1},
            {10, 1}, {20, 1}, {36, 0}, {38, 1}}, 7), "Thuộc tính sau khi xóa 35");

  return 0;
}

int test_delete_black_node_black_successor_no_child() {
  rbi_node_t root = rbi_create_node(10);
  rb_set_black(root);
  bn_tree_t t = bn_create_tree(to_bn(root));
  rbi_node_t m10 = rbi_create_node(-10);
  rb_set_black(m10);

  // Cây con trái
  bn_connect2(m10, top, root, left);

  // Cây con phải
  rbi_node_t n30 = rbi_create_node(30);
  rb_set_red(n30);
  bn_connect2(n30, top, root, right);
  rbi_node_t n20 = rbi_create_node(20);
  rb_set_black(n20);
  bn_connect2(n20, top, n30, left);
  rbi_node_t n38 = rbi_create_node(38);
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
  free(rbi_delete(t, 10));
  CHECK_MSG(lnr_match_attrib(t, (struct attrib[]){{-10, 1}, {20, 1},
      {30, 1}, {38, 0}}, 4), "Thuộc tính sau khi xóa 10");
  return 0;
}

int main() {
  CHECK_MSG(test_delete_root() == 0, "lỗi ở test_delete_root");
  CHECK_MSG(test_delete_root_2nodes() == 0, "lỗi ở test_delete_root_2nodes");
  CHECK_MSG(test_delete_single_deep_child() == 0, "lỗi ở test_delete_single_deep_child");
  CHECK_MSG(test_delete_red_node_red_successor() == 0, "lỗi ở test_delete_red_node_red_successor");
  CHECK_MSG(test_delete_black_node_black_successor_no_child() == 0,
        "lỗi ở test_delete_black_node_black_successor_no_child");
  return 0;
}