/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Trong ví dụ này chương trình sẽ hỏi người dùng nhập vào các số thực
 * cho tới khi người dùng nhập vào 1 số âm.
 * Các số không âm được thêm vào một cây nhị phân tìm kiếm, sau đó
 * được xuất ra theo thứ tự tăng dần và thứ tự giảm dần.
 */

#include "all.c"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    freopen(argv[1], "r", stdin);
  }
  struct gbstree *t = gbs_create_tree(NULL, gtype_cmp_d, NULL);
  double val;
  printf("Nhập vào một dãy số thực không âm (nhập 1 số âm bất kỳ để kết thúc nhập): \n");
  for (;;) {
    scanf("%lf", &val);
    if (val < 0) {
      break;
    }
    gbs_insert(t, gtype_d(val));
  }
  long sz = bn_size(t);
  printf("Số lượng số không âm đã nhập: %ld\n", sz);
  if (sz > 0) {
    gbs_pprint(t, gtype_print_d);
    printf("Các số theo thứ tự tăng dần: ");
    bn_traverse_lnr(cur, bn_tree(t)) {
      printf(" %f", gbs_node(cur)->key.d);
    }
    printf("\nCác số theo thứ tự giảm dần: ");
    bn_traverse_rnl(cur, bn_tree(t)) {
      printf(" %f", gbs_node(cur)->key.d);
    }
    printf("\n");
  }
  bn_free_tree(t);
  return 0;
}