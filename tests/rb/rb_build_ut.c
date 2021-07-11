#include "rbi.h"
#include "tests/base/utils.h"

struct match_args {
  int *arr;
  int n;
  int i;
  int ok;
};

int match_callback(bn_node_t nd, struct match_args *u) {
  int value = rbi_value(nd);
  if (u->i < u->n && u->arr[u->i] == value) {
    ++(u->i);
    return 0;
  }
  u->ok = 0;
  return 1;
}

int lnr_match(bn_tree_t t, int *arr, int n) {
  struct match_args args = {arr, n, 0, 1};
  bn_inorder_lnr_foreach(t, match_callback, &args);
  return args.ok;
}

int main() {
  bn_tree_t t = bn_create_tree(NULL_PTR);
  rbi_insert(t, 2);
  /*
    2B
  */
  CHECK_MSG(rbi_value(t->root) == 2, "Nút gốc == 2");
  CHECK_MSG(rb_is_black(t->root), "Nút gốc là nút đen.");
  CHECK_MSG(lnr_match(t, (int []){2}, 1), "Giá trị tăng dần 2");
  rbi_insert(t, 1);
  /*
        2B
      1R
  */
  bn_node_t nd1 = t->root->left;
  CHECK_MSG(rbi_value(nd1) == 1, "Nút trái == 1");
  CHECK_MSG(rb_is_red(nd1), "Nút trái là nút đỏ");
  CHECK_MSG(lnr_match(t, (int []){1, 2}, 2), "Giá trị tăng dần 1 2");

  rbi_insert(t, 4);
  /*
        2B
      1R  4R
  */
  bn_node_t nd4 = t->root->right;
  CHECK_MSG(rbi_value(nd4) == 4, "Nút trái == 1");
  CHECK_MSG(rb_is_red(nd4), "Nút phải là nút đỏ");
  CHECK_MSG(lnr_match(t, (int []){1, 2, 4}, 3), "Giá trị tăng dần 1 2 4");

  return 0;
}