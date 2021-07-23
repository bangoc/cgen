#include "rbi.h"

#include "tests/base/helpers.h"
#include "tests/base/utils.h"

int t1() {
  rbi_node_t n1 = rbi_create_color_node(1, RB_BLACK);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(rb_is_valid(t), "Cây 1");
  return 0;
}

int t2() {
  rbi_node_t n1 = rbi_create_color_node(1, RB_BLACK);
  rbi_node_t n3 = rbi_create_color_node(3, RB_RED);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(!rb_is_valid(t), "Cây 2");
  return 0;
}

int t3() {
  rbi_node_t n1 = rbi_create_color_node(1, 3);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(!rb_is_valid(t), "Cây 3");
  return 0;
}

int t4() {
  rbi_node_t n1 = rbi_create_color_node(1, RB_RED);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_RED);
  rbi_node_t n6 = rbi_create_color_node(6, RB_RED);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_connect2(n5, right, n6, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(!rb_is_valid(t), "Cây 4");
  return 0;
}

int t5() {
  rbi_node_t n1 = rbi_create_color_node(1, RB_RED);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_RED);
  rbi_node_t n6 = rbi_create_color_node(6, RB_BLACK);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_connect2(n5, right, n6, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(!rb_is_valid(t), "Cây 5");
  return 0;
}

int t6() {
  rbi_node_t n1 = rbi_create_color_node(1, RB_BLACK);
  rbi_node_t n3 = rbi_create_color_node(3, RB_BLACK);
  rbi_node_t n5 = rbi_create_color_node(5, RB_BLACK);
  rbi_node_t n6 = rbi_create_color_node(6, RB_RED);
  bn_connect2(n3, left, n1, top);
  bn_connect2(n3, right, n5, top);
  bn_connect2(n5, right, n6, top);
  bn_tree_t t = bn_create_tree(to_bn(n3));
  CHECK_MSG(rb_is_valid(t), "Cây 6");
  return 0;
}

int main() {
  CHECK_MSG(t1() == 0, "t1()");
  CHECK_MSG(t2() == 0, "t2()");
  CHECK_MSG(t3() == 0, "t3()");
  CHECK_MSG(t4() == 0, "t4()");
  CHECK_MSG(t5() == 0, "t5()");
  CHECK_MSG(t6() == 0, "t6()");
  printf("Test rb_is_valid Ok\n");
  return 0;
}
